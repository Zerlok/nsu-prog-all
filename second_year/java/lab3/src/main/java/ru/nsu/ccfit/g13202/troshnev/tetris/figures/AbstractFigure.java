package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Coordinate;

import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public abstract class AbstractFigure implements Cloneable {
    protected Coordinate figurePosition = new Coordinate(0, 0);
    protected int rotation;
    protected int maxRotationsNum;
    protected Color figureColor;
    protected Block[] figureBlocks;

    protected abstract void applyFigureRotation();

    public AbstractFigure clone() {
        AbstractFigure figure = null;

        try {
            figure = getClass().newInstance();
            figure.figurePosition = new Coordinate(figurePosition);
            figure.rotation = rotation;
            figure.maxRotationsNum = maxRotationsNum;
            figure.figureColor = figureColor;
            figure.figureBlocks = new Block[figureBlocks.length];

            for (int i = 0; i < figureBlocks.length; i++) {
                figure.figureBlocks[i] = new Block(figureBlocks[i]);
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
        figurePosition.incrementCoY();
    }

    public void moveLeft() {
        figurePosition.decrementCoX();
    }

    public void moveRight() {
        figurePosition.incrementCoX();
    }

    public void rotateLeft() {
        rotation = (rotation + maxRotationsNum - 1) % maxRotationsNum;
        applyFigureRotation();
    }

    public void rotateRight() {
        rotation = (rotation + 1) % maxRotationsNum;
        applyFigureRotation();
    }

    public Block[] getBlocks() {
        Block[] blocks = new Block[figureBlocks.length];

        for (int i = 0; i < figureBlocks.length; i++)
            blocks[i] = new Block(figureBlocks[i]);

        return figureBlocks;
    }

    public Coordinate[] getBlocksGlobalPositions() {
        Coordinate[] positions = new Coordinate[figureBlocks.length];

        for (int i = 0; i < figureBlocks.length; i++) {
            positions[i] = new Coordinate(blocksPositions[i]);
            positions[i].addCoordinate(figurePosition);
        }

        return positions;
    }
}
