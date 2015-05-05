package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Figure;

import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class TFigure extends Figure {
    public TFigure(Color clr) {
        rotation = 0;
        maxRotationsNum = 4;
        figureColor = clr;

        blocks = new Block[4];
        for (int i = 0; i < blocks.length; i++)
            blocks[i] = new Block(figureColor);

        applyRotation();
        System.out.println("TFigure created");
    }

    @Override
    protected void applyRotation() {
        switch (rotation) {
            case 0: {
                posX = blocks[0].getBlockPosX();
                posY = blocks[0].getBlockPosY();
                blocks[1].moveToBlock(posX - 1, posY);
                blocks[2].moveToBlock(posX + 1, posY);
                blocks[3].moveToBlock(posX, posY + 1);
                break;
            }
            case 1: {
                posX = blocks[0].getBlockPosX();
                posY = blocks[0].getBlockPosY();
                blocks[1].moveToBlock(posX, posY - 1);
                blocks[2].moveToBlock(posX, posY + 1);
                blocks[3].moveToBlock(posX - 1, posY);
                break;
            }
            case 2: {
                posX = blocks[0].getBlockPosX();
                posY = blocks[0].getBlockPosY();
                blocks[1].moveToBlock(posX + 1, posY);
                blocks[2].moveToBlock(posX - 1, posY);
                blocks[3].moveToBlock(posX, posY - 1);
                break;
            }
            case 3: {
                posX = blocks[0].getBlockPosX();
                posY = blocks[0].getBlockPosY();
                blocks[1].moveToBlock(posX, posY + 1);
                blocks[2].moveToBlock(posX, posY - 1);
                blocks[3].moveToBlock(posX + 1, posY);
                break;
            }
        }
    }
}
