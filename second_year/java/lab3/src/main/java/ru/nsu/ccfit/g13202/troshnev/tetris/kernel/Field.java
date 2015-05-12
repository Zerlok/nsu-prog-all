package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class Field extends JPanel {
    private int fieldColumnsNum;
    private int fieldRowsNum;
    private Block[][] fieldBlocks;
    private Figure activeFigure;

    public Field(int w, int h) {
        fieldColumnsNum = w;
        fieldRowsNum = h;
        activeFigure = null;
        fieldBlocks = new Block[fieldRowsNum][fieldColumnsNum];
    }

    public void addBlock(int rowNum, int columnNum, Block b) {
        fieldBlocks[rowNum][columnNum] = b;
    }

    public void setFigure(Figure figure) {
        activeFigure = figure;
    }

    public void saveFigureBlocks() {
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
            int blockPosX = figureBlockPosition.getCoX();
            int blockPosY = figureBlockPosition.getCoY();

//            Check intersections with field borders and field blocks.
            if ((blockPosY < 0)
                    || (blockPosX < 0)
                    || (blockPosY >= fieldRowsNum)
                    || (blockPosX >= fieldColumnsNum)
                    || (fieldBlocks[blockPosY][blockPosX] != null))
                return true;
        }

        return false;
    }

    public void removeFullLines() {
        System.out.println("Removing full lines...");

        int columnNum;
        int rowNum;
        int blocksInRow;
        int emptyRowNum = -1;

        for (rowNum = 0; rowNum < fieldRowsNum; rowNum++) {
            blocksInRow = 0;
            for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++)
                if (fieldBlocks[rowNum][columnNum] != null)
                    blocksInRow++;

            if (blocksInRow == fieldColumnsNum)
                shiftLinesDownFromRow(rowNum);
        }
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
            fieldBlocks[columnNum][0] = null;
    }

    public int getFieldColumnsNum() {
        return fieldColumnsNum;
    }

    public int getFieldRowsNum() {
//        TODO: repair this method (remove +1).
        return fieldRowsNum + 1;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

//        Draw figure fieldBlocks.
        if (activeFigure != null) {
            Block[] figureBlocks = activeFigure.getBlocks();
            Coordinate[] figureBlocksPositions = activeFigure.getBlocksGlobalPositions();

            for (int i = 0; i < figureBlocks.length; i++)
                figureBlocks[i].draw(
                        figureBlocksPositions[i].getCoY(),
                        figureBlocksPositions[i].getCoX(),
                        g2d);
        }

//        Draw the rest fieldBlocks.
        int columnNum;
        int rowNum;

        for(rowNum = 0; rowNum < fieldRowsNum; rowNum++)
            for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++)
                if (fieldBlocks[rowNum][columnNum] != null)
                    fieldBlocks[rowNum][columnNum].draw(rowNum, columnNum, g2d);
    }
}
