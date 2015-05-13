package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import com.sun.jmx.remote.internal.ArrayQueue;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.GameStartEvent;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEvent;

import java.util.Observable;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * Created by zerlok on 5/14/15.
 */
public class EventManager extends Observable implements Runnable {
    private LinkedBlockingQueue<TetrisEvent> eventsQueue;

    public EventManager() {
        eventsQueue = new LinkedBlockingQueue<TetrisEvent>();
    }

    public void push(TetrisEvent event) {
        eventsQueue.add(event);
    }

    public TetrisEvent pop() {
        if (eventsQueue.size() > 0)
            try {
                return eventsQueue.take();

            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        return null;
    }

    @Override
    public void run() {
        push(new GameStartEvent());
    }
}
