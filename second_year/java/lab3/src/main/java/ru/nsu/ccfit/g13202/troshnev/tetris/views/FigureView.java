package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/31/15.
 */
public class FigureView extends JComponent {
    private BlockView blockView;
    private AbstractFigure figure;

    public FigureView(BlockView bView) {
        blockView = bView;
    }

    public void setFigure(AbstractFigure f) {
        figure = f;
    }

    public void draw(Graphics2D g2d) {
        if (figure == null)
            return;

        Block[] figureBlocks = figure.getGlobalBlocks();
        for (int i = 0; i < figureBlocks.length; i++) {
            blockView.draw(figureBlocks[i], g2d);
        }
    }
}
