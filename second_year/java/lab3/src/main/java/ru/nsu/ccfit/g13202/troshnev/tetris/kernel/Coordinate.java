package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

/**
 * Created by zerlok on 5/12/15.
 */
public class Coordinate {
    private int rowNum;
    private int columnNum;

    public Coordinate(int row, int column) {
        rowNum = row;
        columnNum = column;
    }

    public Coordinate(Coordinate co) {
        rowNum = co.rowNum;
        columnNum = co.columnNum;
    }

    public void moveTo(int row, int column) {
        rowNum = row;
        columnNum = column;
    }

    public void addCoordinate(Coordinate co) {
        rowNum += co.rowNum;
        columnNum += co.columnNum;
    }

    public void incrementRowNum() {
        rowNum++;
    }

    public void decrementRowNum() {
        rowNum--;
    }

    public void incrementColumnNum() {
        columnNum++;
    }

    public void decrementColumnNum() {
        columnNum--;
    }

    public int getRowNum() {
        return rowNum;
    }

    public int getColumnNum() {
        return columnNum;
    }
}
