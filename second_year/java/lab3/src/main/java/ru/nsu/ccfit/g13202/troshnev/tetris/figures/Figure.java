package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Coordinate;

import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public abstract class Figure implements Cloneable {
    protected Coordinate figurePosition = new Coordinate(0, 0);
    protected int rotation;
    protected int maxRotationsNum;
    protected Color figureColor;
    protected Block[] blocks;
    protected Coordinate[] blocksPositions;

    protected abstract void applyFigureRotation();

    public Figure clone() {
        Figure figure = null;

        try {
            figure = getClass().newInstance();
            figure.figurePosition = new Coordinate(figurePosition);
            figure.rotation = rotation;
            figure.maxRotationsNum = maxRotationsNum;
            figure.figureColor = figureColor;
            figure.blocks = new Block[blocks.length];
            figure.blocksPositions = new Coordinate[blocks.length];

            for (int i = 0; i < blocks.length; i++) {
                figure.blocks[i] = blocks[i];
                figure.blocksPositions[i] = new Coordinate(blocksPositions[i]);
            }

        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }

        return figure;
    }

    public void setRotation(int num) {
        rotation = (num + maxRotationsNum) % maxRotationsNum;
        applyFigureRotation();
    }

    public void setPos(int x, int y) {
        figurePosition.moveTo(x, y);
    }

    public void moveUp() {
        figurePosition.decrementCoY();
    }

    public void moveDown() {
        System.out.println(String.format("Moving figure %1$s down...", getClass().getName()));
        figurePosition.incrementCoY();
    }

    public void moveLeft() {
        System.out.println(String.format("Moving figure %1$s left...", getClass().getName()));
        figurePosition.decrementCoX();
    }

    public void moveRight() {
        System.out.println(String.format("Moving figure %1$s right...", getClass().getName()));
        figurePosition.incrementCoX();
    }

    public void rotateLeft() {
        System.out.println(String.format("Rotating figure %1$s left...", getClass().getName()));
        rotation = (rotation + maxRotationsNum - 1) % maxRotationsNum;
        applyFigureRotation();
    }

    public void rotateRight() {
        System.out.println(String.format("Rotating figure %1$s right...", getClass().getName()));
        rotation = (rotation + 1) % maxRotationsNum;
        applyFigureRotation();
    }

    public Block[] getBlocks() {
        return blocks;
    }

    public Coordinate[] getBlocksGlobalPositions() {
        Coordinate[] positions = new Coordinate[blocks.length];

        for (int i = 0; i < blocks.length; i++) {
            positions[i] = new Coordinate(blocksPositions[i]);
            positions[i].addCoordinate(figurePosition);
        }

        return positions;
    }
}
