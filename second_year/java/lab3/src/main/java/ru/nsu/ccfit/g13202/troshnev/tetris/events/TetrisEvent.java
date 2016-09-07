package ru.nsu.ccfit.g13202.troshnev.tetris.events;

import java.util.EventObject;

/**
 * Created by zerlok on 6/12/15.
 */
public class TetrisEvent extends EventObject {
    private String command;
    private Object argument;

    public TetrisEvent(Object source) {
        this(source, null, null);
    }

    public TetrisEvent(Object source, String cmd) {
        this(source, cmd, null);
    }

    public TetrisEvent(Object source, String cmd, Object arg) {
        super(source);

        command = cmd;
        argument = arg;
    }

    public String getEventCommand() {
        return command;
    }

    public Object getEventArgument() {
        return argument;
    }
}
