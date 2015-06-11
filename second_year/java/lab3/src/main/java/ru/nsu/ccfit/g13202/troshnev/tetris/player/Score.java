package ru.nsu.ccfit.g13202.troshnev.tetris.player;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 5/13/15.
 */
public class Score {
    static private int rowPoints = 100;
    static private int figurePoints = 10;
    private long totalScore;

    public void incrementRows(int n) {
        totalScore += (rowPoints * n) + (rowPoints * (n - 1) / 2);
    }

    public void incrementFiguresNum() {
        totalScore += figurePoints;
    }

    public long getTotalScore() {
        return totalScore;
    }
}
