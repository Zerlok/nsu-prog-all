package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class Field extends JComponent {
//    Height and width in blocks.
    private int fieldWidth;
    private int fieldHeight;
    private Block[][] blocks;

    public Field(int w, int h) {
        fieldWidth = w;
        fieldHeight = h;
        blocks = new Block[w][h];
    }

    public void addBlock(int x, int y, Block b) {
        b.moveToBlock(x % fieldWidth, y % fieldWidth);
        blocks[x % fieldWidth][y % fieldHeight] = b;
    }

    public void addBlock(Block b) {
        int posX = b.getBlockPosX();
        int posY = b.getBlockPosY();

        if ((posX >= 0)
                && (posX < fieldWidth)
                && (posY >= 0)
                && (posY < fieldHeight))
            blocks[posX][posY] = b;
    }

    public void addFigure(Figure figure) {
        figure.setPos(3, 1);
        for (Block b : figure.blocks)
            addBlock(b);
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;

        for (int x = 0; x < fieldWidth; x++) {
            for (int y = 0; y < fieldHeight; y++) {
                if (blocks[x][y] != null)
                    blocks[x][y].draw(g2d);
            }
        }
    }
}
