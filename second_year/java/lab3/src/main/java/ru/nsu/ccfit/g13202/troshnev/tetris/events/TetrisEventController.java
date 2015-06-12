package ru.nsu.ccfit.g13202.troshnev.tetris.events;

import javax.swing.event.EventListenerList;
import java.util.concurrent.LinkedBlockingQueue;

/**
* Created by zerlok on 6/6/15.
*/
public class TetrisEventController {
    private EventListenerList eventListeners;
    private LinkedBlockingQueue<TetrisEvent> eventQueue;

    public TetrisEventController() {
        eventListeners = new EventListenerList();
        eventQueue = new LinkedBlockingQueue<TetrisEvent>();
    }

    public void addListener(TetrisEventListener listener) {
        eventListeners.add(TetrisEventListener.class, listener);
    }

    public void removeListener(TetrisEventListener listener) {
        eventListeners.remove(TetrisEventListener.class, listener);
    }

    public void pushEvent(TetrisEvent event) {
        try {
            eventQueue.put(event);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void handleEvents() {
        TetrisEvent event;
        Object[] listenersList = eventListeners.getListenerList();
        int i;

        while ((event = eventQueue.poll()) != null) {
            System.out.println("Handling the event: " + event.getEventCommand());

            for (i = 0; i < listenersList.length; i += 2)
                if (listenersList[i] == TetrisEventListener.class)
                    ((TetrisEventListener)listenersList[i+1]).handleTetrisEvent(event);
        }
    }
}
