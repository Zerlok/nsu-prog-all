package ru.nsu.ccfit.g13202.troshnev.tetris.events;

import java.util.EventObject;

/**
 * Created by zerlok on 6/6/15.
 */
public class AbstractTetrisEvent extends EventObject {
    protected Class<? extends AbstractEventListener> listenerClass;

    public AbstractTetrisEvent(Object source) {
        super(source);
        listenerClass = AbstractEventListener.class;
    }

    public Class<? extends AbstractEventListener> getListenerClass() {
        return listenerClass;
    }
}
