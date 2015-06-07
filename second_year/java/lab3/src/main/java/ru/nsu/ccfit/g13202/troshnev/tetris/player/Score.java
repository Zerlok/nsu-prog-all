package ru.nsu.ccfit.g13202.troshnev.tetris.player;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 5/13/15.
 */
public class Score {
    static private int rowPoints = 100;
    static private int figurePoints = 10;
    private int rowsNum;
    private int figuresNum;

    public Score() {
        rowsNum = 0;
        figuresNum = 0;
    }

    public void incrementRows(int n) {
        rowsNum += n;
    }

    public void incrementFiguresNum() {
        ++figuresNum;
    }

    public long countCurrentScore() {
        return ((rowsNum * rowPoints)
                + figuresNum * figurePoints
        );
    }
}
