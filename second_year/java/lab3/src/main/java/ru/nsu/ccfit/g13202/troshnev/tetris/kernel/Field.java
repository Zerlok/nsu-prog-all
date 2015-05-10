package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class Field extends JPanel {
//    Height and width in blocks.
    private int fieldWidth;
    private int fieldHeight;
    private Block[][] blocks;
    private Figure activeFigure;

    public Field(int w, int h) {
        fieldWidth = w;
        fieldHeight = h;
        activeFigure = null;
        blocks = new Block[h + 2][w];
    }

    public void addBlock(int x, int y, Block b) {
        blocks[y][x] = b;
    }

    public void removeBlock(int x, int y) {
        blocks[y][x] = null;
    }

    public void setFigure(Figure figure) {
        activeFigure = figure;
    }

    public void saveFigureBlocks() {
        if (activeFigure == null)
            return;

        Block[] figureBlocks = activeFigure.getBlocks();
        int[][] figureBlocksPositions = activeFigure.getBlocksLocalPositions();
        for (Block b : )
            addBlock(b);
    }

    public boolean hasIntersection() {
        if (activeFigure == null)
            return false;

        int x;
        int y;

        for (Block figureBlock : activeFigure.getBlocks()) {
            int blockPosX = figureBlock.getBlockPosX();
            int blockPosY = figureBlock.getBlockPosY();

//            Check intersections between figure block and field borders.
            if ((blockPosX < 0)
                    || (blockPosY < 0)
                    || (blockPosX >= fieldWidth)
                    || (blockPosY >= fieldHeight))
                return true;

//            Check intersections between figure block and field blocks.
            for (x = 0; x < fieldWidth; x++)
                for (y = 0; y < fieldHeight; y++)
                    if ((blocks[x][y] != null)
                            && (blockPosX == blocks[x][y].getBlockPosX())
                            && (blockPosY == blocks[x][y].getBlockPosY()))
                        return true;
        }

        return false;
    }

    public void removeFullLines() {
        System.out.println("Removing full lines...");

        int x;
        int y;
        int blocksInRow;
        int emptyRowNum = -1;

        for (y = 0; y < fieldHeight; y++) {
            blocksInRow = 0;
            for (x = 0; x < fieldWidth; x++)
                if (blocks[x][y] != null)
                    blocksInRow++;

            if (blocksInRow == fieldWidth) {
                for (x = 0; x < fieldWidth; x++)
                    blocks[x][y] = null;

                emptyRowNum = y;
            }
        }

        if (emptyRowNum >= 0)
            shiftLinesDownFromRow(emptyRowNum);
    }

    private void shiftLinesDownFromRow(int rowNum) {
        int x;
        int y;
        for (y = rowNum; y > 0; y--) {
            for (x = 0; x < fieldWidth; x++) {
                if (blocks[x][y - 1] != null) {
                    blocks[x][y] = blocks[x][y - 1];
                    blocks[x][y].moveToBlock(x, y);
                }
            }
        }
    }

    public int getFieldWidth() {
        return fieldWidth;
    }

    public int getFieldHeight() {
//        TODO: repair this method (remove +1).
        return fieldHeight + 1;
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

//        Draw figure blocks.
        if (activeFigure != null)
            for (Block figureBlock : activeFigure.getBlocks())
                figureBlock.draw(g2d);

//        Draw the rest blocks.
        int x;
        int y;
        for (x = 0; x < fieldWidth; x++)
            for(y = 0; y < fieldHeight; y++)
                if (blocks[x][y] != null)
                    blocks[x][y].draw(g2d);
    }
}
