package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;

import java.awt.*;

/**
 * Created by zerlok on 5/6/15.
 */
public class MSFigure extends AbstractFigure {
    public MSFigure() {
        rotation = 0;
        maxRotationsNum = 2;
        figureColor = new Color(67, 122, 254);

        figureBlocks = new Block[4];
        for (int i = 0; i < figureBlocks.length; i++)
            figureBlocks[i] = new Block(figureColor);

        applyFigureRotation();
        System.out.println("Mirrored SFigure created");
    }

    @Override
    protected void applyFigureRotation() {
        switch (rotation) {
            case 0: {
                figureBlocks[1].moveTo(-1, 0);
                figureBlocks[2].moveTo(0, 1);
                figureBlocks[3].moveTo(1, 1);
                break;
            }
            case 1: {
                figureBlocks[1].moveTo(0, 1);
                figureBlocks[2].moveTo(1, 0);
                figureBlocks[3].moveTo(1, -1);
                break;
            }
        }
    }
}
