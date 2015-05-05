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
    private Field gameField;

    public View (Field field) {
        gameField = field;
    }

    @Override
    public void run() {
        Block.setSize(30, 2, 1);

        JFrame frame = new JFrame();
        frame.setSize(500, 500);
        frame.setTitle("Tetris");

        frame.add(gameField);

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        frame.pack();
        frame.setVisible(true);
    }
}