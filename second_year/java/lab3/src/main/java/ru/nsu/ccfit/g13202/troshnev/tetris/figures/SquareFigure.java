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

        figureBlocks = new Block[] {
                new Block(figureColor, 0, 0),
                new Block(figureColor, 1, 0),
                new Block(figureColor, 0, 1),
                new Block(figureColor, 1, 1)
        };

        System.out.println("SquareFigure created");
    }

    @Override
    protected void applyFigureRotation() {}
}

