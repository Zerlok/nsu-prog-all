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
                new Block(posX, posY, figureColor),
                new Block(posX, posY + 1, figureColor),
                new Block(posX + 1, posY, figureColor),
                new Block(posX + 1, posY + 1, figureColor)
        };
        System.out.println("SquareFigure created");
    }

    @Override
    protected void applyBlocksPositions() {
        blocks[0].moveToBlock(posX, posY);
        blocks[1].moveToBlock(posX, posY + 1);
        blocks[2].moveToBlock(posX + 1, posY);
        blocks[3].moveToBlock(posX + 1, posY + 1);
    }
}

