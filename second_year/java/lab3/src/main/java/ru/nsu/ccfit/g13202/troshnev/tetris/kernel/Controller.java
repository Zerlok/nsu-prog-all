package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.GameView;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

/**
 * Created by zerlok on 4/29/15.
 */
public class Controller {
    private Field gameField;
    private GameView gameView;
    private FigureFactory figureFactory;
    private Figure activeFigure;
    private Timer ticker;
    private boolean paused;

    public Controller() {
        activeFigure = null;
        gameField = new Field(10, 15);
        gameView = new GameView(gameField);
        paused = false;
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
                ticker.restart();
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

    public void run() {
        createNewFigure();
        gameView.run();

        System.out.println("Game running...");
        ticker.start();
    }

    private void createNewFigure() {
        activeFigure = figureFactory.createRandomFigure();
        activeFigure.setPos(gameField.getFieldColumnsNum() / 2, 0);
        gameField.setFigure(activeFigure);

        if (gameField.hasIntersectionWithFigure()) {
            activeFigure = null;
            System.out.println("GAME OVER!");
        }
    }

    private void moveFigureDown() {
        if (paused || (activeFigure == null))
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
        if (paused || (activeFigure == null))
            return;

        activeFigure.moveLeft();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.moveRight();
    }

    private void moveFigureRight() {
        if (paused || (activeFigure == null))
            return;

        activeFigure.moveRight();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.moveLeft();
    }

    private void rotateFigureLeft() {
        if (paused || (activeFigure == null))
            return;

        activeFigure.rotateLeft();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.rotateRight();
    }

    private void rotateFigureRight() {
        if (paused || (activeFigure == null))
            return;

        activeFigure.rotateRight();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.rotateLeft();
    }

    private void togglePauseGame() {
        if (paused) {
            System.out.println("Game runs!");
            ticker.start();

        } else {
            System.out.println("Game paused!");
            ticker.stop();
        }

        paused = !paused;
    }

    private void recalculateTickerDelay(int rowsNum) {
        ticker.setDelay(
                ticker.getDelay() - 40
        );
    }
}
