package ru.nsu.ccfit.g13202.troshnev.tetris.events;

/**
 * Created by zerlok on 6/6/15.
 */
public class NewFigureCreationEvent extends AbstractTetrisEvent {
    public NewFigureCreationEvent(Object source) {
        super(source);
        listenerClass = NewFigureCreationListener.class;
    }
}
