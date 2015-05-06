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
    protected int centerBlockNum = 0;
    protected Color figureColor;
    protected Block[] blocks;

    protected void applyBlocksPositions() {}

    public void setRotation(int num) {
        rotation = num % maxRotationsNum;
    }

    public void setPos(int x, int y) {
        for (Block b : blocks)
            b.moveToBlock(
                    x + b.getBlockPosX() - posX,
                    y + b.getBlockPosY() - posY
            );

        posX = x;
        posY = y;
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
}
