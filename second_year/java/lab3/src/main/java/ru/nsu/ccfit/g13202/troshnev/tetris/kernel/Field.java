package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class Field extends JPanel {
    private boolean muteBlocks;
    private int fieldColumnsNum;
    private int fieldRowsNum;

    private Block[][] fieldBlocks;
    private Figure activeFigure;

    public Field(int w, int h) {
        muteBlocks = false;
        fieldColumnsNum = w;
        fieldRowsNum = h;
        activeFigure = null;
        fieldBlocks = new Block[fieldRowsNum][fieldColumnsNum];
    }

    public void addBlock(int rowNum, int columnNum, Block b) {
        if ((rowNum >= 0)
                && (columnNum >= 0)
                && (rowNum < fieldRowsNum)
                && (columnNum < fieldColumnsNum))
            fieldBlocks[rowNum][columnNum] = b;
    }

    public void setFigure(Figure figure) {
        activeFigure = figure;
    }

    public void saveFigureBlocks() {
        System.out.println(String.format("Saving figure %1$s", activeFigure.getClass().getName()));
        if (activeFigure == null)
            return;

        Block[] figureBlocks = activeFigure.getBlocks();
        Coordinate[] figureBlocksPositions = activeFigure.getBlocksGlobalPositions();

        for (int i = 0; i < figureBlocks.length; i++)
            addBlock(
                    figureBlocksPositions[i].getCoY(), // rowNum
                    figureBlocksPositions[i].getCoX(), // columnNum
                    figureBlocks[i]
            );
    }

    public boolean hasIntersectionWithFigure() {
        if (activeFigure == null)
            return false;

//        Cycle throw figure blocks.
        for (Coordinate figureBlockPosition : activeFigure.getBlocksGlobalPositions()) {
            int blockRowNum = figureBlockPosition.getCoY();
            int blockColumnNum = figureBlockPosition.getCoX();

//            Check intersections with field borders and field blocks.
            if ((blockColumnNum < 0)
                    || (blockColumnNum >= fieldColumnsNum)
                    || (blockRowNum >= fieldRowsNum)
                    || ((blockRowNum >= 0)
                        && (fieldBlocks[blockRowNum][blockColumnNum] != null)))
                return true;
        }

        return false;
    }

    public int removeFullRows() {
        int columnNum;
        int rowNum;
        int blocksInRow;
        int fullRowsNum = 0;

        for (rowNum = 0; rowNum < fieldRowsNum; rowNum++) {
            blocksInRow = 0;
            for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++)
                if (fieldBlocks[rowNum][columnNum] != null)
                    blocksInRow++;

            if (blocksInRow == fieldColumnsNum) {
                System.out.println(String.format("Removing row %1$d", rowNum));
                shiftLinesDownFromRow(rowNum);
                ++fullRowsNum;
            }
        }

        return fullRowsNum;
    }

    private void shiftLinesDownFromRow(int emptyRowNum) {
        int columnNum;
        int rowNum;

//        Cycle from empty row to top.
        for (rowNum = emptyRowNum; rowNum > 0; rowNum--)
            for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++)
                fieldBlocks[rowNum][columnNum] = fieldBlocks[rowNum - 1][columnNum];

//        Delete top fieldBlocks at 0 rowNum.
        for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++)
            fieldBlocks[0][columnNum] = null;
    }

    public int getFieldColumnsNum() {
        return fieldColumnsNum;
    }

    public int getFieldRowsNum() {
        return fieldRowsNum;
    }

    public void setMuteBlocks(boolean bool) {
        muteBlocks = bool;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        Block mutedBlock = new Block(new Color(117, 117, 117));

//        Draw figure fieldBlocks.
        if (activeFigure != null) {
            Block[] figureBlocks = null;
            Coordinate[] figureBlocksPositions= activeFigure.getBlocksGlobalPositions();

            if (!muteBlocks) {
                figureBlocks = activeFigure.getBlocks();
            }

            for (int i = 0; i < figureBlocksPositions.length; i++) {
                if (!muteBlocks) {
                    figureBlocks[i].draw(
                            figureBlocksPositions[i].getCoY(), // rowNum
                            figureBlocksPositions[i].getCoX(), // columnNum
                            g2d);
                } else {
                    mutedBlock.draw(
                            figureBlocksPositions[i].getCoY(), // rowNum
                            figureBlocksPositions[i].getCoX(), // columnNum
                            g2d);
                }
            }
        }

//        Draw the rest fieldBlocks.
        int columnNum;
        int rowNum;

        for(rowNum = 0; rowNum < fieldRowsNum; rowNum++) {
            for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++) {
                if (!muteBlocks) {
                    if (fieldBlocks[rowNum][columnNum] != null) {
                        fieldBlocks[rowNum][columnNum].draw(rowNum, columnNum, g2d);
                    }
                } else {
                    mutedBlock.draw(rowNum, columnNum, g2d);
                }
            }
        }
    }
}
