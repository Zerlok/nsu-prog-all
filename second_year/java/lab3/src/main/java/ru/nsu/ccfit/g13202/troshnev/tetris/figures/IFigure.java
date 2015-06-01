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

        Coordinate[] blocksPositions = new Coordinate[] {
                new Coordinate(0, 0),
                new Coordinate(-1, 0),
                new Coordinate(1, 0),
                new Coordinate(2, 0)
        };

        figureBlocks = new Block[blocksPositions.length];
        for (int i = 0; i < figureBlocks.length; i++)
            figureBlocks[i] = new Block(figureColor);

        System.out.println("IFigure created");
    }

    @Override
    protected void applyFigureRotation() {
        switch (rotation) {
            case 0: {
                blocksPositions[1].moveTo(-1, 0);
                blocksPositions[2].moveTo(1, 0);
                blocksPositions[3].moveTo(2, 0);
                break;
            }
            case 1: {
                blocksPositions[1].moveTo(0, -1);
                blocksPositions[2].moveTo(0, 1);
                blocksPositions[3].moveTo(0, 2);
                break;
            }
        }
    }
}
