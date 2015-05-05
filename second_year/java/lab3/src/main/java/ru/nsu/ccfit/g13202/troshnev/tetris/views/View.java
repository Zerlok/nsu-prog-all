package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.SquareFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.figures.TFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/4/15.
 */
public class View implements Runnable {
    @Override
    public void run() {
        JFrame frame = new JFrame();
        frame.setSize(500, 500);
        frame.setTitle("Tetris Test");

        Block.setSize(40, 3, 2);
        Figure f1 = new TFigure(new Color(61, 161, 116));
        f1.setPos(0, 1);
        Figure f2 = new SquareFigure(new Color(116, 161, 61));
        f2.setPos(3, 4);
        Field gameField = new Field(10, 20);
        gameField.addFigure(f2);
//        gameField.addFigure(f1);
//        gameField.moveFigureRight();
        frame.add(gameField);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        frame.pack();
        frame.setVisible(true);
    }
}