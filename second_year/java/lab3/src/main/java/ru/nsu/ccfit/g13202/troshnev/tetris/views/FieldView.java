package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/4/15.
 */
public class FieldView extends JComponent {
    private BlockView blockView;
    private FigureView figureView;
    private Field gameField;

    public FieldView(Field field, BlockView bView, FigureView fView) {
        blockView = bView;
        figureView = fView;
        gameField = field;
    }

    @Override
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);

        int fieldRowsNum = gameField.getFieldRowsNum();
        int fieldColumnsNum = gameField.getFieldColumnsNum();
        Block[][] fieldBlocks = gameField.getFieldBlocks();

        int rowNum;
        int columnNum;
        for(rowNum = 0; rowNum < fieldRowsNum; rowNum++)
            for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++)
                blockView.draw(fieldBlocks[rowNum][columnNum], (Graphics2D)graphics);

        figureView.draw((Graphics2D)graphics);
    }
}