package ru.nsu.ccfit.g13202.troshnev.tetris.events;

/**
 * Created by zerlok on 5/14/15.
 */
public class GamePausedEvent extends TetrisEvent {
    private boolean gamePaused;

    public GamePausedEvent(boolean paused) {
        name = paused ? String.format("Game was paused") : String.format("Game goes on");
        gamePaused = paused;
    }

    public boolean isGamePaused() {
        return gamePaused;
    }
}
