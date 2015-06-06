//package ru.nsu.ccfit.g13202.troshnev.tetris.events;
//
//import java.util.HashMap;
//import java.util.Vector;
//import java.util.concurrent.LinkedBlockingQueue;
//
///**
// * Created by zerlok on 6/6/15.
// */
//public class TetrisEventController {
////    private EventListenerList eventListeners;
//    private HashMap<Class<AbstractTetrisEvent>, Vector<NewFigureCreationListener> > eventListeners;
//    private LinkedBlockingQueue<AbstractTetrisEvent> eventQueue;
//
//    public TetrisEventController() {
////        eventListeners = new EventListenerList();
//        eventListeners = new HashMap<Class<AbstractTetrisEvent>, Vector<NewFigureCreationListener>>();
//        eventQueue = new LinkedBlockingQueue<AbstractTetrisEvent>();
//    }
//
//    public void register(Class<AbstractTetrisEvent> eventType, NewFigureCreationListener listener) {
//        Vector<NewFigureCreationListener> similarListeners = eventListeners.get(eventType);
//
//        if (similarListeners == null)
//            similarListeners = new Vector<NewFigureCreationListener>(1);
//
//        similarListeners.add(listener);
//    }
//
//    public void pushEvent(AbstractTetrisEvent event) {
//        try {
//            eventQueue.put(event);
//
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//    }
//
//    public AbstractTetrisEvent peekEvent() {
//        AbstractTetrisEvent event = eventQueue.poll();
//
//        for (NewFigureCreationListener listener : eventListeners.get(event.getClass())) {
//            listener.tetrisEventOccurred(event);
//        }
//
//        return event;
//    }
//}
