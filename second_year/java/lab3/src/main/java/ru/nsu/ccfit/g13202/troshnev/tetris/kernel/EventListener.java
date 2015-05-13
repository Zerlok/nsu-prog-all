package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEvent;

/**
 * Created by zerlok on 5/14/15.
 */
public class EventListener implements Runnable {
    private EventManager gameEvents;

    public EventListener(EventManager eventManager) {
        gameEvents = eventManager;
    }

    @Override
    public void run() {
        TetrisEvent event;

        while (true) {
            event = gameEvents.pop();

            if (event != null)
                System.out.println(String.format("Event: %1$s", event.getEventName()));
        }
    }
}
