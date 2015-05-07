package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;

import java.awt.*;

/**
 * Created by zerlok on 5/6/15.
 */
public class LFigure extends Figure {
    public LFigure() {
        rotation = 0;
        maxRotationsNum = 4;
        figureColor = new Color(85, 88, 164);

        blocks = new Block[4];
        for (int i = 0; i < blocks.length; i++)
            blocks[i] = new Block(figureColor);

        applyBlocksPositions();
        System.out.println("LFigure created");
    }

    @Override
    protected void applyBlocksPositions() {
        System.out.println(String.format("Applying block positions for %1$d rotation.", rotation));
        switch (rotation) {
            case 0: {
                blocks[0].moveToBlock(posX, posY);
                blocks[1].moveToBlock(posX - 1, posY);
                blocks[2].moveToBlock(posX + 1, posY);
                blocks[3].moveToBlock(posX + 1, posY - 1);
                break;
            }
            case 1: {
                blocks[0].moveToBlock(posX, posY);
                blocks[1].moveToBlock(posX, posY - 1);
                blocks[2].moveToBlock(posX, posY + 1);
                blocks[3].moveToBlock(posX + 1, posY + 1);
                break;
            }
            case 2: {
                blocks[0].moveToBlock(posX, posY);
                blocks[1].moveToBlock(posX + 1, posY);
                blocks[2].moveToBlock(posX - 1, posY);
                blocks[3].moveToBlock(posX - 1, posY + 1);
                break;
            }
            case 3: {
                blocks[0].moveToBlock(posX, posY);
                blocks[1].moveToBlock(posX, posY + 1);
                blocks[2].moveToBlock(posX, posY - 1);
                blocks[3].moveToBlock(posX - 1, posY - 1);
                break;
            }
        }
    }
}
