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

        blocksPositions = new Coordinate[] {
                new Coordinate(0, 0),
                new Coordinate(-1, 0),
                new Coordinate(1, 0),
                new Coordinate(0, 1)
        };

        blocks = new Block[blocksPositions.length];
        for (int i = 0; i < blocks.length; i++)
            blocks[i] = new Block(figureColor);

        applyFigureRotation();
        System.out.println("TFigure created");
    }

    @Override
    protected void applyFigureRotation() {
        switch (rotation) {
            case 0: {
                blocksPositions[1].moveTo(-1, 0);
                blocksPositions[2].moveTo(1, 0);
                blocksPositions[3].moveTo(0, 1);
                break;
            }
            case 1: {
                blocksPositions[1].moveTo(0, -1);
                blocksPositions[2].moveTo(0, 1);
                blocksPositions[3].moveTo(-1, 0);
                break;
            }
            case 2: {
                blocksPositions[1].moveTo(1, 0);
                blocksPositions[2].moveTo(-1, 0);
                blocksPositions[3].moveTo(0, -1);
                break;
            }
            case 3: {
                blocksPositions[1].moveTo(0, 1);
                blocksPositions[2].moveTo(0, -1);
                blocksPositions[3].moveTo(1, 0);
                break;
            }
        }
    }
}
