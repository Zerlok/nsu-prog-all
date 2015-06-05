package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Coordinate;

import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class TFigure extends AbstractFigure {
    public TFigure() {
        rotation = 0;
        maxRotationsNum = 4;
        figureColor = new Color(116, 161, 61);

        figureBlocks = new Block[4];
        for (int i = 0; i < figureBlocks.length; i++)
            figureBlocks[i] = new Block(figureColor);

        applyFigureRotation();
        System.out.println("TFigure created");
    }

    @Override
    protected void applyFigureRotation() {
        switch (rotation) {
            case 3: {
                figureBlocks[1].moveTo(-1, 0);
                figureBlocks[2].moveTo(1, 0);
                figureBlocks[3].moveTo(0, 1);
                break;
            }
            case 2: {
                figureBlocks[1].moveTo(0, -1);
                figureBlocks[2].moveTo(0, 1);
                figureBlocks[3].moveTo(-1, 0);
                break;
            }
            case 1: {
                figureBlocks[1].moveTo(1, 0);
                figureBlocks[2].moveTo(-1, 0);
                figureBlocks[3].moveTo(0, -1);
                break;
            }
            case 0: {
                figureBlocks[1].moveTo(0, 1);
                figureBlocks[2].moveTo(0, -1);
                figureBlocks[3].moveTo(1, 0);
                break;
            }
        }
    }
}
