package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

/**
 * Created by zerlok on 5/12/15.
 */
public class Coordinate {
    private int coX;
    private int coY;

    public Coordinate(int x, int y) {
        coX = x;
        coY = y;
    }

    public Coordinate(Coordinate co) {
        coX = co.coX;
        coY = co.coY;
    }

    public void moveTo(int x, int y) {
        coX = x;
        coY = y;
    }

    public void addCoordinate(Coordinate co) {
        coX += co.coX;
        coY += co.coY;
    }

    public void incrementCoX() {
        coX++;
    }

    public void decrementCoX() {
        coX--;
    }

    public void incrementCoY() {
        coY++;
    }

    public void decrementCoY() {
        coY--;
    }

    public int getCoX() {
        return coX;
    }

    public int getCoY() {
        return coY;
    }
}
