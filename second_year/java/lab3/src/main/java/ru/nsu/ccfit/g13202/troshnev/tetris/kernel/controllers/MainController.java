package ru.nsu.ccfit.g13202.troshnev.tetris.kernel.controllers;

import ru.nsu.ccfit.g13202.troshnev.tetris.windows.BaseWindow;
import ru.nsu.ccfit.g13202.troshnev.tetris.windows.MainPanel;
import ru.nsu.ccfit.g13202.troshnev.tetris.windows.ScoresPanel;

import javax.swing.*;
import java.awt.event.ActionEvent;
/**
 * Created by zerlok on 5/27/15.
 */
public class MainController implements Runnable {
    private ActionMap actionsMap;
    private BaseWindow baseWindow;
    private GameController gameLogic;

    public MainController() {
        actionsMap = new ActionMap();
        setupActions();

        baseWindow = new BaseWindow(actionsMap);
        gameLogic = null;
    }

    private void setupActions() {
        actionsMap.put("GAME-NEW", new AbstractAction("New Game") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                startNewGame();
            }
        });
        actionsMap.put("MAIN-HOME", new AbstractAction("Main Menu") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                initMainMenu();
            }
        });
        actionsMap.put("MAIN-SCORES", new AbstractAction("Highscores") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                showScoresTable();
            }
        });
        actionsMap.put("MAIN-ABOUT", new AbstractAction("About") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                showAbout();
            }
        });
        actionsMap.put("GAME-EXIT", new AbstractAction("Exit") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                exitTheGame();
            }
        });
    }

    @Override
    public void run() {
        initMainMenu();
        baseWindow.setVisible(true);
    }

    private void initMainMenu() {
        baseWindow.setInnerWindow(new MainPanel(actionsMap));
        baseWindow.centreWindow();
    }

    private void startNewGame() {
        gameLogic = new GameController(actionsMap);

        baseWindow.setInnerWindow(gameLogic.getGamePanel());
        baseWindow.centreWindow();
    }

    private void showScoresTable() {
        baseWindow.setInnerWindow(new ScoresPanel());
        baseWindow.centreWindow();
    }

    private void showAbout() {
        System.out.println("About is still in development.");
    }

    private void exitTheGame() {
        System.exit(0);
    }
}
