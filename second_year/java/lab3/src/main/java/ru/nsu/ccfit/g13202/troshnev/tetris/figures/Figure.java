package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;

import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public abstract class Figure {
    protected int posX;
    protected int posY;
    protected int rotation;
    protected int maxRotationsNum;
    protected Color figureColor;
    protected Block[] blocks;
    protected int [][] blocksLocalPositions;

    protected void applyBlocksPositions() {}

    public void setRotation(int num) {
        rotation = (num + maxRotationsNum) % maxRotationsNum;
        applyBlocksPositions();
    }

    public void setPos(int x, int y) {
//        for (int i = 0; i < blocksLocalPositions.length; i++)
//            blocksLocalPositions[i] = new int[] {
//                    x + blocksLocalPositions[i][0] - posX,
//                    y + blocksLocalPositions[i][1] - posY
//            };

        posX = x;
        posY = y;
        applyBlocksPositions();
    }

    public void moveUp() {
        posY--;
        applyBlocksPositions();
    }

    public void moveDown() {
        posY++;
        System.out.println(String.format("Moving figure %1$s down... to posY %2$d", getClass().getName(), posY));
        applyBlocksPositions();
    }

    public void moveLeft() {
        System.out.println(String.format("Moving figure %1$s left...", getClass().getName()));
        posX--;
        applyBlocksPositions();
    }

    public void moveRight() {
        System.out.println(String.format("Moving figure %1$s right...", getClass().getName()));
        posX++;
        applyBlocksPositions();
    }

    public void rotateLeft() {
        System.out.println(String.format("Rotating figure %1$s left...", getClass().getName()));
        rotation = (rotation + maxRotationsNum - 1) % maxRotationsNum;
        applyBlocksPositions();
    }

    public void rotateRight() {
        System.out.println(String.format("Rotating figure %1$s right...", getClass().getName()));
        rotation = (rotation + 1) % maxRotationsNum;
        applyBlocksPositions();
    }

    public Block[] getBlocks() {
        return blocks;
    }

    public int[][] getBlocksLocalPositions() {
        int[][] positions = new int[blocks.length][];

        for (int i = 0; i < blocks.length; i++)
            positions[i] = new int[] {
                    blocksLocalPositions[i][0],
                    blocksLocalPositions[i][1]
            };

        return positions;
    }
}
