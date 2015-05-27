package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Block;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Coordinate;

import java.awt.*;

/**
 * Created by zerlok on 5/6/15.
 */
public class LFigure extends AbstractFigure {
    public LFigure() {
        rotation = 0;
        maxRotationsNum = 4;
        figureColor = new Color(85, 88, 164);

        blocksPositions = new Coordinate[] {
                new Coordinate(0, 0),
                new Coordinate(-1, 0),
                new Coordinate(1, 0),
                new Coordinate(1, -1)
        };

        blocks = new Block[blocksPositions.length];
        for (int i = 0; i < blocks.length; i++)
            blocks[i] = new Block(figureColor);

        System.out.println("LFigure created");
    }

    @Override
    protected void applyFigureRotation() {
        switch (rotation) {
            case 0: {
                blocksPositions[1].moveTo(-1, 0);
                blocksPositions[2].moveTo(1, 0);
                blocksPositions[3].moveTo(1, -1);
                break;
            }
            case 1: {
                blocksPositions[1].moveTo(0, -1);
                blocksPositions[2].moveTo(0, 1);
                blocksPositions[3].moveTo(0 + 1, 1);
                break;
            }
            case 2: {
                blocksPositions[1].moveTo(1, 0);
                blocksPositions[2].moveTo(-1, 0);
                blocksPositions[3].moveTo(-1, 1);
                break;
            }
            case 3: {
                blocksPositions[1].moveTo(0, 1);
                blocksPositions[2].moveTo(0, -1);
                blocksPositions[3].moveTo(-1, -1);
                break;
            }
        }
    }
}
