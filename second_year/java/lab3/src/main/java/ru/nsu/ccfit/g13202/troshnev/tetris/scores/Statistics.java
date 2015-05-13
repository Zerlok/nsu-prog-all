package ru.nsu.ccfit.g13202.troshnev.tetris.scores;

/**
 * Created by zerlok on 5/13/15.
 */
public class Statistics {
    private int rowPoints = 1000;
    private int figurePoints = 200;
    private int rowsNum;
    private int figuresNum;

    public Statistics(int rowPoint, int figurePoint) {
        rowPoints = rowPoint;
        figurePoints = figurePoint;
        rowsNum = 0;
        figuresNum = 0;
    }

    public void incrementRows() {
        ++rowsNum;
    }

    public void incrementFiguresNum() {
        ++figuresNum;
    }

    public long getCurrentScore() {
        return ((rowsNum * rowPoints)
                + Math.round(Math.sqrt(figuresNum * figurePoints))
                - figuresNum
        );
    }
}
