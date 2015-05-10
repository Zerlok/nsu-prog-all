package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;

import java.awt.*;

/**
 * Created by zerlok on 5/6/15.
 */
public class IFigure extends Figure {
    public IFigure() {
        rotation = 0;
        maxRotationsNum = 2;
        figureColor = new Color(42, 163, 139);

        blocks = new Block[4];
        for (int i = 0; i < blocks.length; i++)
            blocks[i] = new Block(figureColor);

        blocksLocalPositions = new int[blocks.length][2];

        applyBlocksPositions();
        System.out.println("IFigure created");
    }

    @Override
    protected void applyBlocksPositions() {
        switch (rotation) {
            case 0: {

                blocks[0].moveToBlock(posX, posY);
                blocks[1].moveToBlock(posX - 1, posY);
                blocks[2].moveToBlock(posX + 1, posY);
                blocks[3].moveToBlock(posX + 2, posY);
                break;
            }
            case 1: {
                blocks[0].moveToBlock(posX, posY);
                blocks[1].moveToBlock(posX, posY - 1);
                blocks[2].moveToBlock(posX, posY + 1);
                blocks[3].moveToBlock(posX, posY + 2);
                break;
            }
        }
    }
}
