package ru.nsu.ccfit.g13202.troshnev.tetris.events;

/**
 * Created by zerlok on 5/14/15.
 */
public class KeyboardPressedEvent extends TetrisEvent {
    public KeyboardPressedEvent() {
        name = String.format("Keyboard key pressed");
    }
}
