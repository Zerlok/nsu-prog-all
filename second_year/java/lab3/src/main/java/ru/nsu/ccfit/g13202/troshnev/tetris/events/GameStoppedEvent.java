package ru.nsu.ccfit.g13202.troshnev.tetris.events;

/**
 * Created by zerlok on 5/14/15.
 */
public class GameStoppedEvent extends TetrisEvent {
    public GameStoppedEvent(String reasonName) {
        name = reasonName;
    }
}
