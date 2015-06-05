package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Coordinate;

import java.awt.*;

/**
 * Created by zerlok on 5/6/15.
 */
public class IFigure extends AbstractFigure {
    public IFigure() {
        rotation = 0;
        maxRotationsNum = 2;
        figureColor = new Color(42, 163, 139);

        figureBlocks = new Block[] {
                new Block(figureColor, 0, 0),
                new Block(figureColor, -1, 0),
                new Block(figureColor, 1, 0),
                new Block(figureColor ,2, 0)
        };

        System.out.println("IFigure created");
    }

    @Override
    protected void applyFigureRotation() {
        switch (rotation) {
            case 0: {
                figureBlocks[1].moveTo(-1, 0);
                figureBlocks[2].moveTo(1, 0);
                figureBlocks[3].moveTo(2, 0);
                break;
            }
            case 1: {
                figureBlocks[1].moveTo(0, -1);
                figureBlocks[2].moveTo(0, 1);
                figureBlocks[3].moveTo(0, 2);
                break;
            }
        }
    }
}
