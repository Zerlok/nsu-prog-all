package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;
import ru.nsu.ccfit.g13202.troshnev.tetris.figures.SquareFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.figures.TFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.View;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;

/**
 * Created by zerlok on 4/29/15.
 */
public class Controller {
    private Field gameField;
    private View tetrisView;
    private Figure activeFigure;

    public Controller() {
        gameField = new Field(10, 18);
        tetrisView = new View(gameField);
        activeFigure = null;

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
        Figure f = new SquareFigure(new Color(61, 161, 161));
        f.setPos(5, 6);
        gameField.addFigure(f);
        createNewFigure();
        tetrisView.run();

        System.out.println("Game running...");
    }

    public void createNewFigure() {
//        TODO: get new figure from figure factory.
        activeFigure = new TFigure(new Color(116, 161, 61));
        activeFigure.setPos(2, 0);
        gameField.addFigure(activeFigure);

        if (gameField.hasIntersection())
            System.out.println("GAME OVER!");
    }

    public void moveFigureDown() {
        if (activeFigure == null)
            return;

        activeFigure.moveDown();

        if (gameField.hasIntersection()) {
            activeFigure.moveUp();
            activeFigure = null;
            System.out.println("Figure position fixed.");

            gameField.removeFullLines();
            createNewFigure();
        }
    }

    public void moveFigureLeft() {
        if (activeFigure == null)
            return;

        activeFigure.moveLeft();

        if (gameField.hasIntersection())
            activeFigure.moveRight();
    }

    public void moveFigureRight() {
        if (activeFigure == null)
            return;

        activeFigure.moveRight();

        if (gameField.hasIntersection())
            activeFigure.moveLeft();
    }

    public void rotateFigureLeft() {
        if (activeFigure == null)
            return;

        activeFigure.rotateLeft();

        if (gameField.hasIntersection())
            activeFigure.rotateRight();
    }

    public void rotateFigureRight() {
        if (activeFigure == null)
            return;

        activeFigure.rotateRight();

        if (gameField.hasIntersection())
            activeFigure.rotateLeft();
    }
}
