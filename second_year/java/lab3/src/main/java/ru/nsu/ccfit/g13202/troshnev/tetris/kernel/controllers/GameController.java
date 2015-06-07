package ru.nsu.ccfit.g13202.troshnev.tetris.kernel.controllers;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventController;
import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.FigureFactory;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;
import ru.nsu.ccfit.g13202.troshnev.tetris.windows.GamePanel;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

/**
 * Created by zerlok on 4/29/15.
 */
public class GameController implements Runnable {
    private Player currentPlayer;

    private FigureFactory figureFactory;
    private AbstractFigure currentFigure;
    private AbstractFigure nextFigure;
    private Field gameField;
    private Field previewField;

    private Timer ticker;
    private boolean gamePaused;

    private GamePanel gamePanel;

    private TetrisEventController eventController;

    public GameController(ActionMap actionsMap) {
        currentPlayer = new Player();
        eventController = new TetrisEventController();
        eventController.addActionListener(currentPlayer);

        figureFactory = new FigureFactory();
        try {
            figureFactory.configure();

        } catch (IOException e) {
            e.printStackTrace();
        }
        currentFigure = null;
        nextFigure = null;
        gameField = new Field(18, 10);
        previewField = new Field(6, 6);

        ticker = new Timer(600, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                eventController.handleEvent();
                gamePanel.repaint();
            }
        });
        ticker.setRepeats(true);
        ticker.setCoalesce(false);

        gamePaused = true;

        gamePanel = new GamePanel(gameField, previewField);
        setupActions(actionsMap);
        gamePanel.registerListeners(eventController);
    }

    private void setupActions(ActionMap actionsMap) {
        ActionMap actionMap = gamePanel.getActionMap();

        actionMap.put("GAME-PAUSE", new AbstractAction("Pause") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                togglePauseGame();
                gamePanel.repaint();
            }
        });

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
        actionMap.put("rotateFigureClockwiseAction", new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                rotateFigureClockwise();
                gamePanel.repaint();
            }
        });

        InputMap inputMap = gamePanel.getInputMap(JPanel.WHEN_IN_FOCUSED_WINDOW);
        inputMap.put(KeyStroke.getKeyStroke("RIGHT"), "moveFigureRightAction");
        inputMap.put(KeyStroke.getKeyStroke("LEFT"), "moveFigureLeftAction");
        inputMap.put(KeyStroke.getKeyStroke("DOWN"), "moveFigureDownAction");
        inputMap.put(KeyStroke.getKeyStroke("UP"), "rotateFigureClockwiseAction");
        inputMap.put(KeyStroke.getKeyStroke("P"), "GAME-PAUSE");
    }

    @Override
    public void run() {
        createNewFigure();
        togglePauseGame();
    }

    public void stop() {
        ticker.stop();
    }

    private void createNewFigure() {
        currentFigure = (nextFigure != null) ? nextFigure : figureFactory.createRandomFigure();
        nextFigure = figureFactory.createRandomFigure();

        currentFigure.setPosition(0, gameField.getFieldColumnsNum() / 2);
        nextFigure.setPosition(previewField.getFieldRowsNum() / 2, previewField.getFieldColumnsNum() / 2);

        gamePanel.setNextFigure(nextFigure);
        gamePanel.setCurrentFigure(currentFigure);

        if (gameField.hasIntersection(currentFigure.getGlobalBlocks())) {
            currentFigure = null;

        } else {
            eventController.pushEvent(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, "TETRIS-FIGURE-NEW"));
        }
    }

    public void moveFigureDown() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.moveDown();

        if (gameField.hasIntersection(currentFigure.getGlobalBlocks())) {
            currentFigure.moveUp();

            gameField.saveBlocks(currentFigure.getGlobalBlocks());
            System.out.println("Figure position locked.");

            int removedRowsNum = gameField.removeFullRows();
            if (removedRowsNum > 0) {
                recalculateTickerDelay(removedRowsNum);
                eventController.pushEvent(new ActionEvent(this, ActionEvent.ACTION_PERFORMED,
                        String.format("TETRIS-ROWS-REMOVED=%1$d", removedRowsNum)));
            }

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

    private void recalculateTickerDelay(int rowsNum) {
        ticker.setDelay(
                ticker.getDelay() - 10
        );
    }

    public JPanel getGamePanel() {
        return gamePanel;
    }
}
