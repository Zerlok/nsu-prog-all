package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Coordinate;

import java.awt.*;

/**
 * Created by zerlok on 5/5/15.
 */
public class SquareFigure extends AbstractFigure {
    public SquareFigure() {
        rotation = 0;
        maxRotationsNum = 1;
        figureColor = new Color(161, 40, 41);

        blocksPositions = new Coordinate[] {
                new Coordinate(0, 0),
                new Coordinate(1, 0),
                new Coordinate(0, 1),
                new Coordinate(1, 1)
        };

        figureBlocks = new Block[blocksPositions.length];
        for (int i = 0; i < figureBlocks.length; i++)
            figureBlocks[i] = new Block(figureColor);

        System.out.println("SquareFigure created");
    }

    @Override
    protected void applyFigureRotation() {}
}

