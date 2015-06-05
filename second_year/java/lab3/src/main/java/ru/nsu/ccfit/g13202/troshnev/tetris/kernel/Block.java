package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class Block {
    private Color innerColor;
    private Coordinate position;

    public Block(Color clr) {
        innerColor = clr;
        position = new Coordinate(0, 0);
    }

    public Block(Color clr, Coordinate pos) {
        innerColor = clr;
        position = new Coordinate(pos);
    }

    public Block(Color clr, int rowNum, int columnNum) {
        innerColor = clr;
        position = new Coordinate(rowNum, columnNum);
    }

    public Block(Block block) {
        innerColor = block.innerColor;
        position = new Coordinate(block.position);
    }

    public Color getColor() {
        return innerColor;
    }

    public Coordinate getCoordinates() {
        return new Coordinate(position);
    }

    public void moveTo(int rowNum, int columnNum) {
        position = new Coordinate(rowNum, columnNum);
    }
}
