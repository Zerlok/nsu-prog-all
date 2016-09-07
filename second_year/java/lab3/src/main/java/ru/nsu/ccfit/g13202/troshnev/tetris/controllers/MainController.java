package ru.nsu.ccfit.g13202.troshnev.tetris.controllers;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.HighscoreTable;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.ScoresView;
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
    private Player player;

    public MainController() {
        actionsMap = new ActionMap();
        setupActions();

        scoresTable = new HighscoreTable();
        gameLogic = null;
    }

    private void setupActions() {
        actionsMap.put("MAIN-HOME", new AbstractAction("Menu") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                showMainMenu();
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
        // run swing in another thread.
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                baseWindow = new BaseWindow(actionsMap);
                baseWindow.setVisible(true);
                showMainMenu();
            }
        });
    }

    private void showMainMenu() {
        checkAndStopGame();
        baseWindow.setInnerWindow(new MainPanel(actionsMap));
        baseWindow.centrateWindow();
    }

    private void startNewGame() {
        checkAndStopGame();

        gameLogic = new GameController(scoresTable, actionsMap);

        // change inner window.
        baseWindow.setInnerWindow(gameLogic.getGamePanel());
        baseWindow.centrateWindow();

        gameLogic.run();
    }

    private void showScoresTable() {
        checkAndStopGame();
        baseWindow.setInnerWindow(new ScoresPanel(new ScoresView(scoresTable)));
        baseWindow.centrateWindow();
    }

    private void showAbout() {
        checkAndStopGame();
        baseWindow.setInnerWindow(new AboutPanel());
        baseWindow.centrateWindow();
    }

    private void checkAndStopGame() {
        if (gameLogic != null) {
            gameLogic.stop();
            gameLogic = null;
        }
    }

    private void exitTheGame() {
        checkAndStopGame();
        System.exit(0);
    }
}
