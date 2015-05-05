package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Figure;

import java.awt.*;

/**
 * Created by zerlok on 5/5/15.
 */
public class SquareFigure extends Figure {
    public SquareFigure(Color clr) {
        rotation = 0;
        maxRotationsNum = 1;
        figureColor = clr;
        blocks = new Block[] {
                new Block(0, 0, figureColor),
                new Block(0, 1, figureColor),
                new Block(1, 0, figureColor),
                new Block(1, 1, figureColor)
        };
        System.out.println("SquareFigure created");
    }
}

