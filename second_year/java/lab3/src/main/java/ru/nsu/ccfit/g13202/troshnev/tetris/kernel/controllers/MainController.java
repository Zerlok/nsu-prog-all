package ru.nsu.ccfit.g13202.troshnev.tetris.kernel.controllers;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.HighscoreTable;
import ru.nsu.ccfit.g13202.troshnev.tetris.windows.AboutPanel;
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
    private HighscoreTable scoresTable;

    public MainController() {
        actionsMap = new ActionMap();
        setupActions();

        baseWindow = new BaseWindow(actionsMap);
        scoresTable = new HighscoreTable();
        gameLogic = null;

        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                baseWindow.setVisible(true);
            }
        });
    }

    private void setupActions() {
        actionsMap.put("MAIN-HOME", new AbstractAction("Menu") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                initMainMenu();
            }
        });
        actionsMap.put("GAME-NEW", new AbstractAction("New") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                startNewGame();
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
    }

    private void initMainMenu() {
        stopTheGame();
        baseWindow.setInnerWindow(new MainPanel(actionsMap));
        baseWindow.centrateWindow();
    }

    private void startNewGame() {
        stopTheGame();
        gameLogic = new GameController(actionsMap, scoresTable);

        baseWindow.setInnerWindow(gameLogic.getGamePanel());
        baseWindow.centrateWindow();

        gameLogic.run();
    }

    private void showScoresTable() {
        stopTheGame();
        baseWindow.setInnerWindow(new ScoresPanel(scoresTable));
        baseWindow.centrateWindow();
    }

    private void showAbout() {
        stopTheGame();
        baseWindow.setInnerWindow(new AboutPanel());
        baseWindow.centrateWindow();
    }

    private void stopTheGame() {
        if (gameLogic != null) {
            gameLogic.stop();
            gameLogic = null;
        }
    }

    private void exitTheGame() {
        stopTheGame();
        System.exit(0);
    }
}
