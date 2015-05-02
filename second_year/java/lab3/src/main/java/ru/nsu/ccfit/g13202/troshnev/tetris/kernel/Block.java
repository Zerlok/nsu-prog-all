package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */

public class Block {
//    The block color.
    private Color color;

//    Top left X, Y position of the block.
    private int posX;
    private int posY;

//    Block width in pixels.
    private int width;

    public Block(int x, int y, int w) {
        posX = x;
        posY = y;
        width = w;
        color = new Color(125, 167, 116);
    }

    public void draw() {
//        TODO: Draw the block object form x, y position.

    }
}
