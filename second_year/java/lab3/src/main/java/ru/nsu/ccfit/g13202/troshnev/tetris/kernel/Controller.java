package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.GamePausedEvent;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.GameStoppedEvent;
import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.GameView;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Observable;

/**
 * Created by zerlok on 4/29/15.
 */
public class Controller extends Observable implements Runnable {
    private Field gameField;
    private GameView gameView;
    private FigureFactory figureFactory;
    private Figure activeFigure;
    private Timer ticker;
    private boolean gamePaused;
    private EventManager gameEvents;
    private Thread eventListenerThread;

    public Controller() {
        activeFigure = null;
        gameEvents = new EventManager();
        gameField = new Field(10, 15, gameEvents);
        gameView = new GameView(gameField, gameEvents);
        gamePaused = false;

        ticker = new Timer(600, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureDown();
                gameField.repaint();
            }
        });
        ticker.setRepeats(true);
        ticker.setCoalesce(false);

        figureFactory = new FigureFactory();
        try {
            figureFactory.configure();

        } catch (IOException e) {
            e.printStackTrace();
        }

        bindKeys();
    }

    private void bindKeys() {
        Action moveRightAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureRight();
                gameField.repaint();
            }
        };

        Action moveLeftAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureLeft();
                gameField.repaint();
            }
        };

        Action moveDownAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureDown();
                gameField.repaint();
            }
        };

        Action rotateRightAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                rotateFigureRight();
                gameField.repaint();
            }
        };

        Action rotateLeftAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                rotateFigureLeft();
                gameField.repaint();
            }
        };

        Action togglePauseAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                togglePauseGame();
            }
        };

        InputMap inputMap = gameField.getInputMap(JPanel.WHEN_IN_FOCUSED_WINDOW);
        ActionMap actionMap = gameField.getActionMap();

        inputMap.put(KeyStroke.getKeyStroke("RIGHT"), "moveRightAction");
        actionMap.put("moveRightAction", moveRightAction);

        inputMap.put(KeyStroke.getKeyStroke("LEFT"), "moveLeftAction");
        actionMap.put("moveLeftAction", moveLeftAction);

        inputMap.put(KeyStroke.getKeyStroke("DOWN"), "moveDownAction");
        actionMap.put("moveDownAction", moveDownAction);

        inputMap.put(KeyStroke.getKeyStroke("Q"), "rotateLeftAction");
        actionMap.put("rotateLeftAction", rotateLeftAction);

        inputMap.put(KeyStroke.getKeyStroke("E"), "rotateRightAction");
        actionMap.put("rotateRightAction", rotateRightAction);

        inputMap.put(KeyStroke.getKeyStroke("P"), "togglePauseAction");
        actionMap.put("togglePauseAction", togglePauseAction);
    }

    @Override
    public void run() {
        createNewFigure();
        gameView.run();

        gameEvents.run();
        eventListenerThread = new Thread(new EventListener(gameEvents));
        eventListenerThread.start();
        ticker.start();
    }

    private void createNewFigure() {
        activeFigure = figureFactory.createRandomFigure();
        activeFigure.setPos(gameField.getFieldColumnsNum() / 2, 0);
        gameField.setFigure(activeFigure);

        if (gameField.hasIntersectionWithFigure()) {
            activeFigure = null;
            gameEvents.push(new GameStoppedEvent("Game over"));
        }
    }

    private void moveFigureDown() {
        if (gamePaused || (activeFigure == null))
            return;

        activeFigure.moveDown();

        if (gameField.hasIntersectionWithFigure()) {
            activeFigure.moveUp();
            activeFigure = null;

            gameField.saveFigureBlocks();
            System.out.println("Figure figurePosition fixed.");

            int removedRowsNum = gameField.removeFullRows();
            if (removedRowsNum > 0)
                recalculateTickerDelay(removedRowsNum);

            createNewFigure();
        }
    }

    private void moveFigureLeft() {
        if (gamePaused || (activeFigure == null))
            return;

        activeFigure.moveLeft();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.moveRight();
    }

    private void moveFigureRight() {
        if (gamePaused || (activeFigure == null))
            return;

        activeFigure.moveRight();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.moveLeft();
    }

    private void rotateFigureLeft() {
        if (gamePaused || (activeFigure == null))
            return;

        activeFigure.rotateLeft();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.rotateRight();
    }

    private void rotateFigureRight() {
        if (gamePaused || (activeFigure == null))
            return;

        activeFigure.rotateRight();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.rotateLeft();
    }

    private void togglePauseGame() {
        if (gamePaused) {
            ticker.start();

        } else {
            ticker.stop();
        }

        gamePaused = !gamePaused;
        gameEvents.push(new GamePausedEvent(gamePaused));
    }

    private void recalculateTickerDelay(int rowsNum) {
        ticker.setDelay(
                ticker.getDelay() - 10
        );
    }
}
