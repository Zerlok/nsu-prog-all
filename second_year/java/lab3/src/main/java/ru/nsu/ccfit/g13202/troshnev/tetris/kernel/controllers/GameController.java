package ru.nsu.ccfit.g13202.troshnev.tetris.kernel.controllers;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.FigureFactory;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.FigureView;
import ru.nsu.ccfit.g13202.troshnev.tetris.windows.GamePanel;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

/**
 * Created by zerlok on 4/29/15.
 */
public class GameController implements Runnable {
    private Player currentPlayer;

    private FigureFactory figureFactory;
    private AbstractFigure currentFigure;
    private AbstractFigure nextFigure;
    private Field gameField;

    private Timer ticker;
    private boolean gamePaused;

    private GamePanel gamePanel;

    public GameController(ActionMap actionsMap) {
        setupActions(actionsMap);

        currentPlayer = new Player();

        figureFactory = new FigureFactory();
        try {
            figureFactory.configure();

        } catch (IOException e) {
            e.printStackTrace();
        }
        currentFigure = null;
        nextFigure = null;
        gameField = new Field(10, 18);

        ticker = new Timer(600, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureDown();
                gamePanel.repaint();
            }
        });
        ticker.setRepeats(true);
        ticker.setCoalesce(false);

        gamePaused = true;

        gamePanel = new GamePanel(gameField);
    }

    private void setupActions(ActionMap actionsMap) {
        actionsMap.put("GAME-PAUSE", new AbstractAction("Pause") {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                togglePauseGame();
            }
        });
    }

    @Override
    public void run() {
        createNewFigure();
        togglePauseGame();
    }

    private void createNewFigure() {
        if (nextFigure == null)
            nextFigure = figureFactory.createRandomFigure();

        currentFigure = nextFigure;
        currentFigure.setPos(gameField.getFieldColumnsNum() / 2, 0);

        gamePanel.setNextFigure(nextFigure);
        gamePanel.setCurrentFigure(currentFigure);

        if (gameField.hasIntersection(currentFigure.getBlocks())) {
            currentFigure = null;
        }
    }

    private void moveFigureDown() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.moveDown();

        if (gameField.hasIntersection(currentFigure.getBlocks())) {
            currentFigure.moveUp();

            gameField.saveBlocks(currentFigure.getBlocks());
            System.out.println("Figure position locked.");

            int removedRowsNum = gameField.removeFullRows();
            if (removedRowsNum > 0)
                recalculateTickerDelay(removedRowsNum);

            createNewFigure();
        }
    }

    private void moveFigureLeft() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.moveLeft();

        if (gameField.hasIntersection(currentFigure.getBlocks()))
            currentFigure.moveRight();
    }

    private void moveFigureRight() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.moveRight();

        if (gameField.hasIntersection(currentFigure.getBlocks()))
            currentFigure.moveLeft();
    }

    private void rotateFigureLeft() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.rotateLeft();

        if (gameField.hasIntersection(currentFigure.getBlocks()))
            currentFigure.rotateRight();
    }

    private void rotateFigureRight() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.rotateRight();

        if (gameField.hasIntersection(currentFigure.getBlocks()))
            currentFigure.rotateLeft();
    }

    private void togglePauseGame() {
        gamePaused = !gamePaused;

        if (gamePaused)
            ticker.stop();
        else
            ticker.start();

        gamePanel.hideBlocks(gamePaused);
    }

    private void recalculateTickerDelay(int rowsNum) {
        ticker.setDelay(
                ticker.getDelay() - 10
        );
    }

    public JPanel getGamePanel() {
        return gamePanel;
    }
}
