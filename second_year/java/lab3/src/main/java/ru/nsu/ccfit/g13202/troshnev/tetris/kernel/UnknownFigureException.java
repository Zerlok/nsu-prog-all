package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

/**
 * Created by zerlok on 4/29/15.
 */

public class UnknownFigureException extends FigureException {
    private String figurename;

    public UnknownFigureException(String name) {
        figurename = name;
    }

    @Override
    public String getMessage() {
        return String.format("FIgure '$1%s' unknown!");
    }
}
