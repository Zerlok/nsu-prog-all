package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.FieldBlocksView;

import javax.swing.*;

/**
 * Created by zerlok on 4/29/15.
 */

public class GamePanel extends JPanel {
    private FieldBlocksView gameView;

    public GamePanel(Field field) {
        gameView = new FieldBlocksView(field);

        add(new JTextArea("Here will be shown the game..."));
    }
}
