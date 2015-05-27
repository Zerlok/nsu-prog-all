package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;

import javax.swing.*;

/**
 * Created by zerlok on 4/29/15.
 */

public class GameWindow extends JFrame {
    private GameFieldView gameView;

    public GameWindow(Field field) {
        gameView = new GameFieldView(field);

        add(gameView);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
