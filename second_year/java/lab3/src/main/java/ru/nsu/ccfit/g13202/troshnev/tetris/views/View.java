package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.TFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Figure;

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

        Block.setSize(40, 4, 2);
        Figure f = new TFigure(new Color(61, 161, 116));
        Field gameField = new Field(10, 20);
        gameField.addFigure(f);

//        gameField.addBlock(0, 0, new Block(new Color(61, 161, 116), new Color(71, 181, 117)));
//        gameField.addBlock(1, 1, new Block(new Color(61, 111, 161), new Color(71, 117, 181)));
//        gameField.addBlock(1, 0, new Block(new Color(116, 161, 61), new Color(117, 181, 71)));
        frame.add(gameField);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//        frame.pack();
        frame.setVisible(true);
    }
}