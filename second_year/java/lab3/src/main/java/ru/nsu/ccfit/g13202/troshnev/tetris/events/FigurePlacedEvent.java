package ru.nsu.ccfit.g13202.troshnev.tetris.events;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;

/**
 * Created by zerlok on 5/14/15.
 */
public class FigurePlacedEvent extends TetrisEvent {
    private Figure figure;

    public FigurePlacedEvent(Figure f) {
        name = String.format("Figure placed on game field.");
        figure = f;
    }
}
