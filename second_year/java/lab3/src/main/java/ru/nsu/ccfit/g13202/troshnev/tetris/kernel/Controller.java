package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;
import ru.nsu.ccfit.g13202.troshnev.tetris.figures.LFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.GameView;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.io.IOException;

/**
 * Created by zerlok on 4/29/15.
 */
public class Controller {
    private Field gameField;
    private GameView gameView;
    private FigureFactory figureFactory;
    private Figure activeFigure;

    public Controller() {
        gameField = new Field(10, 15);
        gameView = new GameView(gameField);
        figureFactory = new FigureFactory();
        activeFigure = null;

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

        InputMap inputMap = gameField.getInputMap(JPanel.WHEN_IN_FOCUSED_WINDOW);
        ActionMap actionMap = gameField.getActionMap();

        inputMap.put(KeyStroke.getKeyStroke("RIGHT"), "moveRightAction");
        actionMap.put("moveRightAction", moveRightAction);

        inputMap.put(KeyStroke.getKeyStroke("LEFT"), "moveLeftAction");
        actionMap.put("moveLeftAction", moveLeftAction);

        inputMap.put(KeyStroke.getKeyStroke("SPACE"), "moveDownAction");
        actionMap.put("moveDownAction", moveDownAction);

        inputMap.put(KeyStroke.getKeyStroke("UP"), "rotateLeftAction");
        actionMap.put("rotateLeftAction", rotateLeftAction);

        inputMap.put(KeyStroke.getKeyStroke("DOWN"), "rotateRightAction");
        actionMap.put("rotateRightAction", rotateRightAction);
    }

    public void run() {
        createNewFigure();
        gameView.run();

        System.out.println("Game running...");
    }

    public void createNewFigure() {
//        activeFigure = figureFactory.createRandomFigure();
        activeFigure = new LFigure();
        activeFigure.setPos(gameField.getFieldColumnsNum() / 2, 0);
        gameField.setFigure(activeFigure);

        if (gameField.hasIntersectionWithFigure()) {
            activeFigure = null;
            System.out.println("GAME OVER!");
        }
    }

    public void moveFigureDown() {
        if (activeFigure == null)
            return;

        activeFigure.moveDown();

        if (gameField.hasIntersectionWithFigure()) {
            activeFigure.moveUp();
            activeFigure = null;

            gameField.saveFigureBlocks();
            gameField.removeFullRows();
            System.out.println("Figure figurePosition fixed.");
            createNewFigure();
        }
    }

    public void moveFigureLeft() {
        if (activeFigure == null)
            return;

        activeFigure.moveLeft();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.moveRight();
    }

    public void moveFigureRight() {
        if (activeFigure == null)
            return;

        activeFigure.moveRight();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.moveLeft();
    }

    public void rotateFigureLeft() {
        if (activeFigure == null)
            return;

        activeFigure.rotateLeft();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.rotateRight();
    }

    public void rotateFigureRight() {
        if (activeFigure == null)
            return;

        activeFigure.rotateRight();

        if (gameField.hasIntersectionWithFigure())
            activeFigure.rotateLeft();
    }
}
