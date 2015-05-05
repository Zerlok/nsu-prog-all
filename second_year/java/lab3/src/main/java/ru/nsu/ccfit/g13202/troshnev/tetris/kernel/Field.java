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
    private Block[] blocks;
    private Figure activeFigure;

    public Field(int w, int h) {
        fieldWidth = w;
        fieldHeight = h;
        activeFigure = null;
        blocks = new Block[w * (h + 2)];
    }

    public void addBlock(Block b) {
        int i;
        for (i = 0; blocks[i] != null; i++);
        blocks[i] = b;
    }

    public void removeBlock(int x, int y) {
        for (int i = 0; i < blocks.length; i++)
            if ((blocks[i] != null)
                    && (blocks[i].getBlockPosX() == x)
                    && (blocks[i].getBlockPosY() == y))
                blocks[i] = null;
    }

    public void addFigure(Figure figure) {
//        Save previous figure blocks on field.
        if (activeFigure != null)
            for (Block b : activeFigure.getBlocks())
                addBlock(b);

        activeFigure = figure;
    }

    private boolean hasIntersection() {
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
            for (Block fieldBlock : blocks)
                if ((fieldBlock != null)
                        && (blockPosX == fieldBlock.getBlockPosX())
                        && (blockPosY == fieldBlock.getBlockPosY()))
                    return true;
        }

        return false;
    }

    public void moveFigureDown() {
        if (activeFigure == null)
            return;

        activeFigure.moveDown();

        if (hasIntersection())
            activeFigure.moveUp();
    }

    public void moveFigureLeft() {
        if (activeFigure == null)
            return;

        activeFigure.moveLeft();

        if (hasIntersection())
            activeFigure.moveRight();
    }

    public void moveFigureRight() {
        if (activeFigure == null)
            return;

        activeFigure.moveRight();

        if (hasIntersection())
            activeFigure.moveLeft();
    }

    public void rotateFigureLeft() {
        if (activeFigure == null)
            return;

        activeFigure.rotateLeft();

        if (hasIntersection())
            activeFigure.rotateRight();
    }

    public void rotateFigureRight() {
        if (activeFigure == null)
            return;

        activeFigure.rotateRight();

        if (hasIntersection())
            activeFigure.rotateLeft();
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
        for (Block fieldBlock : blocks)
            if (fieldBlock != null)
                fieldBlock.draw(g2d);
    }
}
