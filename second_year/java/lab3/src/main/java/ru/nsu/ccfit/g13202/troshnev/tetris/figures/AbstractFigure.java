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

    public void setPosition(int rowNum, int columnNum) {
        figurePosition.moveTo(rowNum, columnNum);
    }

    public void moveUp() {
        figurePosition.decrementRowNum();
    }

    public void moveDown() {
        figurePosition.incrementRowNum();
    }

    public void moveLeft() {
        figurePosition.decrementColumnNum();
    }

    public void moveRight() {
        figurePosition.incrementColumnNum();
    }

    public void rotateOverClockwise() {
        rotation = (rotation + maxRotationsNum - 1) % maxRotationsNum;
        applyFigureRotation();
    }

    public void rotateClockwise() {
        rotation = (rotation + 1) % maxRotationsNum;
        applyFigureRotation();
    }

    public Block[] getGlobalBlocks() {
        Block[] globalBlocks = new Block[figureBlocks.length];

        for (int i = 0; i < figureBlocks.length; i++) {
            Coordinate globalPosition = figureBlocks[i].getCoordinates();
            globalPosition.addCoordinateOffset(figurePosition);
            globalBlocks[i] = new Block(figureBlocks[i].getColor(), globalPosition);
        }

        return globalBlocks;
    }
}
