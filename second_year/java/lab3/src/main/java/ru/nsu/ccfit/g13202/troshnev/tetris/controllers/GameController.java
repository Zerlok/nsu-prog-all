package ru.nsu.ccfit.g13202.troshnev.tetris.controllers;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEvent;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventController;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventListener;
import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.FigureFactory;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.HighscoreTable;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Level;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Score;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.GameOverView;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.PlayerInfoView;
import ru.nsu.ccfit.g13202.troshnev.tetris.windows.GamePanel;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

/**
 * Created by zerlok on 4/29/15.
 */
public class GameController implements Runnable {
    private TetrisEventController eventController;
    private Timer ticker;

    private FigureFactory figureFactory;
    private AbstractFigure currentFigure;
    private AbstractFigure nextFigure;
    private Field gameField;
    private Field previewField;

    private GamePanel gamePanel;
    private boolean gamePaused;

    public GameController(HighscoreTable scoresTable, ActionMap actionsMap) {
        // event controller setup.
        eventController = new TetrisEventController();

        // current player creation.
        Score score = new Score();
        Level level = new Level(score);
        Player player = new Player(level, score, scoresTable);

        // figure factory setup
        figureFactory = new FigureFactory();
        try {
            figureFactory.configure();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // game field and next figure preview setup.
        gameField = new Field(18, 10);
        previewField = new Field(6, 6);

        // tetris ticker setup.
        ticker = new Timer(600, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureDown();
                eventController.handleEvents();
                gamePanel.repaint();
            }
        });
        ticker.setRepeats(true);
        ticker.setCoalesce(false);

        // default values for game state and figures.
        gamePaused = true;
        currentFigure = null;
        nextFigure = null;

        // game panel setup.
        PlayerInfoView info = new PlayerInfoView(player, scoresTable.getHighscore());
        GameOverView gov = new GameOverView(player);
        gov.setGameOverAction(actionsMap.get("MAIN-SCORES"));
        gamePanel = new GamePanel(gameField, previewField, info, gov);

        // registering event listeners.
        eventController.addListener(player);
        eventController.addListener(gamePanel);
        eventController.addListener(new TetrisEventListener() {
            @Override
            public void handleTetrisEvent(TetrisEvent event) {
                if (event.getEventCommand() == "GAME-PAUSE")
                    togglePauseGame();
            }
        });

        setupActions();
    }

    private void setupActions() {
        ActionMap actionMap = gamePanel.getActionMap();

        actionMap.put("moveFigureLeftAction", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureLeft();
                gamePanel.repaint();
            }
        });
        actionMap.put("moveFigureRightAction", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureRight();
                gamePanel.repaint();
            }
        });
        actionMap.put("moveFigureDownAction", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureDown();
                gamePanel.repaint();
            }
        });
        actionMap.put("smashFigureDownAction", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                smashFigureDown();
                gamePanel.repaint();
            }
        });
        actionMap.put("rotateFigureClockwiseAction", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                rotateFigureClockwise();
                gamePanel.repaint();
            }
        });
        actionMap.put("GAME-PAUSE", new AbstractAction("Pause") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if (ticker.isRunning())
                    eventController.pushEvent(new TetrisEvent(this, "GAME-PAUSE"));
                else
                    togglePauseGame();
            }
        });

        InputMap inputMap = gamePanel.getInputMap(JPanel.WHEN_IN_FOCUSED_WINDOW);
        inputMap.put(KeyStroke.getKeyStroke("RIGHT"), "moveFigureRightAction");
        inputMap.put(KeyStroke.getKeyStroke("LEFT"), "moveFigureLeftAction");
        inputMap.put(KeyStroke.getKeyStroke("DOWN"), "moveFigureDownAction");
        inputMap.put(KeyStroke.getKeyStroke("SPACE"), "smashFigureDownAction");
        inputMap.put(KeyStroke.getKeyStroke("UP"), "rotateFigureClockwiseAction");
        inputMap.put(KeyStroke.getKeyStroke("P"), "GAME-PAUSE");
    }

    private void recalculateTickerDelay() {
        ticker.setDelay(
                ticker.getDelay() - 10
        );
    }

    private void createNewFigure() {
        currentFigure = (nextFigure != null) ? nextFigure : figureFactory.createRandomFigure();
        nextFigure = figureFactory.createRandomFigure();

        currentFigure.setPosition(0, gameField.getFieldColumnsNum() / 2);
        nextFigure.setPosition((previewField.getFieldRowsNum() / 2) - 1, previewField.getFieldColumnsNum() / 2);

        gamePanel.setNextFigure(nextFigure);
        gamePanel.setCurrentFigure(currentFigure);

        eventController.pushEvent(new TetrisEvent(this, "TETRIS-FIGURE-NEW"));

        if (gameField.hasIntersection(currentFigure.getGlobalBlocks())) {
            eventController.pushEvent(new TetrisEvent(this, "GAME-OVER"));
            stop();
        }
    }

    private void placeFigureToField() {
        gameField.saveBlocks(currentFigure.getGlobalBlocks());

        int removedRowsNum = gameField.removeFullRows();
        if (removedRowsNum > 0) {
            eventController.pushEvent(new TetrisEvent(this, "TETRIS-ROWS-REMOVED", removedRowsNum));
            recalculateTickerDelay();
        }
    }

    @Override
    public void run() {
        createNewFigure();
        togglePauseGame();
    }

    public void stop() {
        ticker.stop();
        eventController.handleEvents();
        currentFigure = null;
        gamePanel.repaint();
    }

    public void smashFigureDown() {
        if (gamePaused || (currentFigure == null))
            return;

        while (!gameField.hasIntersection(currentFigure.getGlobalBlocks()))
            currentFigure.moveDown();

        currentFigure.moveUp();
        placeFigureToField();
        createNewFigure();
//        eventController.pushEvent(new TetrisEvent(this, "TETRIS-FIGURE-NEW"));
    }

    public void moveFigureDown() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.moveDown();

        if (gameField.hasIntersection(currentFigure.getGlobalBlocks())) {
            currentFigure.moveUp();
            placeFigureToField();
            createNewFigure();
        }
    }

    public void moveFigureLeft() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.moveLeft();

        if (gameField.hasIntersection(currentFigure.getGlobalBlocks()))
            currentFigure.moveRight();
    }

    public void moveFigureRight() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.moveRight();

        if (gameField.hasIntersection(currentFigure.getGlobalBlocks()))
            currentFigure.moveLeft();
    }

    public void rotateFigureClockwise() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.rotateClockwise();

        if (gameField.hasIntersection(currentFigure.getGlobalBlocks()))
            currentFigure.rotateOverClockwise();
    }

    public void togglePauseGame() {
        gamePaused = !gamePaused;

        if (gamePaused)
            ticker.stop();
        else
            ticker.start();

        gamePanel.hideBlocks(gamePaused);
    }

    public JPanel getGamePanel() {
        return gamePanel;
    }
}
