package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;

import javax.swing.*;

/**
 * Created by zerlok on 5/4/15.
 */
public class GameView implements Runnable {
    private Field gameField;
    private JFrame gameFrame;

    public GameView(Field field) {
        Block.setSize(30, 4, 1);
        gameField = field;
        gameFrame = new JFrame();

        int blockMargin = Block.getPixelMargin();
        int blockOffset = Block.getPixelOffset();
        gameFrame.setSize(
                blockOffset * gameField.getFieldColumnsNum() - blockMargin + 2,
                blockOffset * gameField.getFieldRowsNum() + 4
        );
        gameFrame.setTitle("Tetris");
        gameFrame.add(gameField);
        gameFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    @Override
    public void run() {
        gameFrame.setVisible(true);
    }
}