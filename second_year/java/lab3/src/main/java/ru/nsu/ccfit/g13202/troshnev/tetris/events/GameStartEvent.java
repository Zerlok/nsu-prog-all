package ru.nsu.ccfit.g13202.troshnev.tetris.events;

/**
 * Created by zerlok on 5/14/15.
 */
public class GameStartEvent extends TetrisEvent {
    public GameStartEvent() {
        name = String.format("Tetris game was started");
    }
}
