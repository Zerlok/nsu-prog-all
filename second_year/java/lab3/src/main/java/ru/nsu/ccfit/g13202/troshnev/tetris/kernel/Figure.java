package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

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

    public boolean movable() {
        return true;
    }

    public boolean rotatable() {
        return true;
    }

    public void moveDown() {
        System.out.println(String.format("Moving figure %1$s down...", getClass().getName()));
        if (movable()) {
            posY += 1;
            applyBlocksPositions();
        }
    }

    public void moveLeft() {
        System.out.println(String.format("Moving figure %1$s down...", getClass().getName()));
        if (movable()) {
            posX -= 1;
            applyBlocksPositions();
        }
    }

    public void moveRight() {
        System.out.println(String.format("Moving figure %1$s down...", getClass().getName()));
        if (movable()) {
            posX += 1;
            applyBlocksPositions();
        }
    }

    public void pushDown() {
        System.out.println(String.format("Pushing figure %1$s down...", getClass().getName()));
        while (movable())
            moveDown();
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
}
