package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class Block {
//    Block pixelWidth in pixels.
    static private int pixelWidth = 100;
    static private int pixelPadding = 5;
    static private int pixelMargin = 1;
//    Top left X, Y position of the block.
    private int blockPosX;
    private int blockPosY;
//    The block color.
    private Color innerColor;
    private Color borderColor;

    static public void setSize(int w, int p, int m) {
        pixelWidth = w > 0 ? w : pixelWidth;
        pixelPadding = p > 0 ? p : pixelPadding;
        pixelMargin = m > 0 ? m : pixelMargin;
    }

    public Block(Color clr) {
        blockPosX = 0;
        blockPosY = 0;
        innerColor = clr;
        borderColor = clr;
    }

    public Block(Color inColor, Color brColor) {
        blockPosX = 0;
        blockPosY = 0;
        innerColor = inColor;
        borderColor = brColor;
    }

    public void moveToBlock(int blockX, int blockY) {
        blockPosX = blockX;
        blockPosY = blockY;
    }

    public void draw(Graphics2D g) {
        int offset = pixelWidth + pixelMargin;
        int pixelX = blockPosX * offset;
        int pixelY = blockPosY * offset;

        g.setColor(borderColor);
        g.fillRect(
                pixelX,
                pixelY,
                pixelWidth,
                pixelWidth
        );
        g.setColor(innerColor);
        g.fillRect(
                pixelX + pixelPadding,
                pixelY + pixelPadding,
                pixelWidth - (2*pixelPadding),
                pixelWidth - (2*pixelPadding)
        );
    }

    public int getBlockPosX() {
        return blockPosX;
    }

    public int getBlockPosY() {
        return blockPosY;
    }
}
