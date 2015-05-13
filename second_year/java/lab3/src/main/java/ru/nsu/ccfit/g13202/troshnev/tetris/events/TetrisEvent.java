package ru.nsu.ccfit.g13202.troshnev.tetris.events;

import org.w3c.dom.events.Event;

import javax.swing.*;
import java.util.EventObject;
import java.util.Observable;

/**
 * Created by zerlok on 5/13/15.
 */
public abstract class TetrisEvent {
    protected String name;

    public String getEventName() {
        return name;
    }
}
