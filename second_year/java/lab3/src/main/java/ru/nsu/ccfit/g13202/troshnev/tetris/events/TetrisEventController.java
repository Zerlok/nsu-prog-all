package ru.nsu.ccfit.g13202.troshnev.tetris.events;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;
import java.util.concurrent.LinkedBlockingQueue;

/**
* Created by zerlok on 6/6/15.
*/
public class TetrisEventController {
    private Vector<ActionListener> eventListeners;
    private LinkedBlockingQueue<ActionEvent> eventQueue;

    public TetrisEventController() {
        eventListeners = new Vector<ActionListener>();
        eventQueue = new LinkedBlockingQueue<ActionEvent>();
    }

    public void addActionListener(ActionListener listener) {
        eventListeners.add(listener);
    }

    public void pushEvent(ActionEvent event) {
        try {
            eventQueue.put(event);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public ActionEvent handleEvent() {
        ActionEvent event = eventQueue.poll();

        if (event == null)
            return null;

        System.out.println("Handling the event... " + event);
        for (ActionListener listener : eventListeners) {
            listener.actionPerformed(event);
        }

        return event;
    }
}
