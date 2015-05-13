package ru.nsu.ccfit.g13202.troshnev.tetris.events;

/**
 * Created by zerlok on 5/14/15.
 */
public class FieldRowRemovedEvent extends TetrisEvent {
    private int rowNum;

    public FieldRowRemovedEvent(int n) {
        name = String.format("%1$d row removed", n);
        rowNum = n;
    }
}
