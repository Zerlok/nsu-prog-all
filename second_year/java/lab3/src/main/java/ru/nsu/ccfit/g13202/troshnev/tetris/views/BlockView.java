package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Coordinate;

import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */

public class BlockView {
    private static Color mutedBlockColor = new Color(117, 117, 117);

    private int pixelWidth;
    private int pixelPadding;
    private int pixelOffset;

    private boolean muteBlock;

    public BlockView(int width, int padding, int margin) {
        pixelWidth = width;
        pixelPadding = padding;
        pixelOffset = width + margin;

        muteBlock = false;
    }

    public BlockView(BlockView blockView) {
        pixelWidth = blockView.pixelWidth;
        pixelPadding = blockView.pixelPadding;
        pixelOffset = blockView.pixelOffset;
        muteBlock = blockView.muteBlock;
    }

    public void setBlockMuting(boolean bool) {
        muteBlock = bool;
    }

    public void draw(Block block, Graphics2D g2d) {
        if (block == null)
            return;

        Coordinate blockPosition = block.getCoordinates();
        int pixelY = blockPosition.getRowNum() * pixelOffset;
        int pixelX = blockPosition.getColumnNum() * pixelOffset;

        Color innerColor = (!muteBlock) ? block.getColor() : mutedBlockColor;
        Color borderColor = (!muteBlock) ? innerColor.brighter() : mutedBlockColor.brighter();

        g2d.setColor(borderColor);
        g2d.fillRect(
                pixelX,
                pixelY,
                pixelWidth,
                pixelWidth
        );
        g2d.setColor(innerColor);
        g2d.fillRect(
                pixelX + pixelPadding,
                pixelY + pixelPadding,
                pixelWidth - (2 * pixelPadding),
                pixelWidth - (2 * pixelPadding)
        );
    }
}
