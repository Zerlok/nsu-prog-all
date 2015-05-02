package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

/**
 * Created by zerlok on 4/29/15.
 */

public class Field {
//    Height and width in blocks.
    private int width;
    private int height;
    private Block[] blocks;

    public Field(int w, int h) {
        width = w;
        height = h;
        blocks = new Block[w * h];
    }

    public void show() {
//        TODO: Draw the game window with blocks.
//        for (Block b : blocks) {
//            b.draw();
//        }
    }
}
