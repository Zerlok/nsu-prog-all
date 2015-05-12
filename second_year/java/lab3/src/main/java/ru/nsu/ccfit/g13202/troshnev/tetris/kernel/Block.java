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
//    The block color.
    private Color innerColor;
    private Color borderColor;

    static public void setSize(int w, int p, int m) {
        pixelWidth = w > 0 ? w : pixelWidth;
        pixelPadding = p >= 0 ? p : pixelPadding;
        pixelMargin = m >= 0 ? m : pixelMargin;
    }

    public static int getPixelOffset() {
        return pixelWidth + pixelMargin;
    }

    public static int getPixelMargin() {
        return pixelMargin;
    }

    public Block(Color clr) {
        innerColor = clr;
        borderColor = clr.brighter();
    }

    public Block(Color inColor, Color brColor) {
        innerColor = inColor;
        borderColor = brColor;
    }

    public void draw(int rowNum, int columnNum, Graphics2D g) {
        int offset = getPixelOffset();
        int pixelX = columnNum * offset;
        int pixelY = rowNum * offset;

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
}
