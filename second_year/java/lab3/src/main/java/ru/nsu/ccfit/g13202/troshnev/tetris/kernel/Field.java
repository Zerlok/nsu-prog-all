package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;

/**
 * Created by zerlok on 4/29/15.
 */
public class Field {
    private int fieldColumnsNum;
    private int fieldRowsNum;

    private Block[][] blocks;
    private AbstractFigure activeFigure;

    public Field(int w, int h) {
        fieldColumnsNum = w;
        fieldRowsNum = h;
        activeFigure = null;
        blocks = new Block[fieldRowsNum][fieldColumnsNum];
    }

    public void addBlock(int rowNum, int columnNum, Block b) {
        if ((rowNum >= 0)
                && (columnNum >= 0)
                && (rowNum < fieldRowsNum)
                && (columnNum < fieldColumnsNum))
            blocks[rowNum][columnNum] = b;
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
                        && (blocks[blockRowNum][blockColumnNum] != null)))
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
                if (blocks[rowNum][columnNum] != null)
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
                blocks[rowNum][columnNum] = blocks[rowNum - 1][columnNum];

//        Delete top blocks at 0 rowNum.
        for (columnNum = 0; columnNum < fieldColumnsNum; columnNum++)
            blocks[0][columnNum] = null;
    }

    public int getFieldColumnsNum() {
        return fieldColumnsNum;
    }

    public int getFieldRowsNum() {
        return fieldRowsNum;
    }

    public AbstractFigure getActiveFigure() {
        return activeFigure;
    }

    public void setFigure(AbstractFigure figure) {
        activeFigure = figure;
    }

    public Block[][] getFieldBlocks() {
        return blocks;
    }
}