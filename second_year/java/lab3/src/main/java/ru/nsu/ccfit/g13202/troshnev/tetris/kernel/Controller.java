package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.views.View;

/**
 * Created by zerlok on 4/29/15.
 */

public class Controller {
    private View tetrisView;

    public Controller() {
        tetrisView = new View();
    }

    public void run() {
        tetrisView.run();
    }
}
