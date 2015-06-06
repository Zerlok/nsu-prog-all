package ru.nsu.ccfit.g13202.troshnev.tetris.events;

import javax.swing.event.EventListenerList;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Created by zerlok on 6/6/15.
 */
public class EventController {
    private EventListenerList eventListeners;
    private LinkedBlockingQueue<AbstractTetrisEvent> eventQueue;

    public EventController() {
        eventListeners = new EventListenerList();
        eventQueue = new LinkedBlockingQueue<AbstractTetrisEvent>();
    }

    public void register(Class<AbstractEventListener> eventListenerClass, AbstractEventListener listener) {
        eventListeners.add(eventListenerClass, listener);
    }

    public void pushEvent(AbstractTetrisEvent event) {
        try {
            eventQueue.put(event);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public AbstractTetrisEvent peekEvent() {
        AbstractTetrisEvent event = eventQueue.poll();

        eventListeners.getListeners(event.getListenerClass());

        return event;
    }
}
