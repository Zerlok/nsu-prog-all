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

    public Controller() {
        gameField = new Field(10, 20);
        tetrisView = new View(gameField);

        bindKeys();
    }

    private void bindKeys() {
        Action moveRightAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                gameField.moveFigureRight();
                gameField.repaint();
            }
        };

        Action moveLeftAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                gameField.moveFigureLeft();
                gameField.repaint();
            }
        };

        Action moveDownAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                gameField.moveFigureDown();
                gameField.repaint();
            }
        };

        Action rotateRightAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                gameField.rotateFigureRight();
                gameField.repaint();
            }
        };

        Action rotateLeftAction = new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                gameField.rotateFigureLeft();
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
        f.setPos(5, 3);
        gameField.addFigure(f);
        gameField.addFigure(new TFigure(new Color(116, 161, 61)));
        tetrisView.run();

        System.out.println("Game running...");
    }
}
