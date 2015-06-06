package ru.nsu.ccfit.g13202.troshnev.tetris.events;

import java.util.EventListener;

/**
 * Created by zerlok on 6/6/15.
 */
public interface NewFigureCreationListener extends AbstractEventListener {
    public void newFigureCreationHandler(AbstractTetrisEvent event);
}
