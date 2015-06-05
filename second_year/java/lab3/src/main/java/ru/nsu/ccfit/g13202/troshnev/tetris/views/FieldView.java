package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Coordinate;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/4/15.
 */
public class FieldView extends JComponent {
    private static Block mutedBlock = new Block(new Color(117, 117, 117));
    private boolean muteBlocks;
    private BlockView blockView;
    private Field gameField;

    public FieldView(Field field) {
        muteBlocks = false;
        blockView = new BlockView(100, 5, 1);

        gameField = field;
        int rowsNum = field.getFieldRowsNum();
        int columnsNum = field.getFieldColumnsNum();

        setLayout(new GridLayout(rowsNum, columnsNum));
    }

    public void setMuteBlocks(boolean bool) {
        muteBlocks = bool;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        int fieldRowsNum = gameField.getFieldRowsNum();
        int fieldColumnsNum = gameField.getFieldColumnsNum();
        Block[][] fieldBlocks = gameField.getFieldBlocks();
//        AbstractFigure activeFigure = gameField.getActiveFigure();

//        Draw figure fieldBlocks.
//        if (activeFigure != null) {
//            Block[] figureBlocks = null;
//            Coordinate[] figureBlocksPositions= activeFigure.getBlocksGlobalPositions();
//
//            if (!muteBlocks) {
//                figureBlocks = activeFigure.getBlocks();
//            }
//
//            for (int i = 0; i < figureBlocksPositions.length; i++) {
//                if (!muteBlocks) {
//                    figureBlocks[i].draw(
//                            figureBlocksPositions[i].getColumnNum(), // rowNum
//                            figureBlocksPositions[i].getRowNum(), // columnNum
//                            g2d);
//                } else {
//                    mutedBlock.draw(
//                            figureBlocksPositions[i].getColumnNum(), // rowNum
//                            figureBlocksPositions[i].getRowNum(), // columnNum
//                            g2d);
//                }
//            }
//        }

//        Draw the rest fieldBlocks.
        int columnNum;
        int rowNum;

        for(rowNum = 0; rowNum < fieldRowsNum; rowNum++) {
            for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++) {
                if (!muteBlocks) {
                    blockView.draw(fieldBlocks[rowNum][columnNum], g2d);
                } else {
                    blockView.draw(mutedBlock, g2d);
                }
            }
        }
    }
}