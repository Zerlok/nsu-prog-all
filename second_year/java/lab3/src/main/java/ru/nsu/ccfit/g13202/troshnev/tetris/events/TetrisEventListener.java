package ru.nsu.ccfit.g13202.troshnev.tetris.events;

import java.util.EventListener;

/**
 * Created by zerlok on 6/12/15.
 */
public interface TetrisEventListener extends EventListener {
    public void handleTetrisEvent(TetrisEvent event);
}
