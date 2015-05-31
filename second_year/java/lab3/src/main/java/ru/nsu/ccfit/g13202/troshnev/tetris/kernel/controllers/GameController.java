package ru.nsu.ccfit.g13202.troshnev.tetris.kernel.controllers;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.FigureFactory;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.FieldBlocksView;
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
    private Field gameField;
    private FieldBlocksView fieldView;

    private FigureFactory figureFactory;

    private AbstractFigure currentFigure;
    private AbstractFigure nextFigure;
    private FigureView currentFigureView;
    private FigureView nextFigureView;

    private GamePanel gamePanel;

    private Timer ticker;
    private boolean gamePaused;

    public GameController() {
        gameField = new Field(10, 15);
        gamePanel = new GamePanel(gameField);

        figureFactory = new FigureFactory();
        try {
            figureFactory.configure();

        } catch (IOException e) {
            e.printStackTrace();
        }

        currentFigure = null;
        nextFigure = null;

        ticker = new Timer(600, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                moveFigureDown();
                fieldView.repaint();
            }
        });
        ticker.setRepeats(true);
        ticker.setCoalesce(false);

        gamePaused = false;
    }

    @Override
    public void run() {
        createNewFigure();
        ticker.start();
    }

    private void createNewFigure() {
        currentFigure = figureFactory.createRandomFigure();
        currentFigure.setPos(gameField.getFieldColumnsNum() / 2, 0);
        gameField.setFigure(currentFigure);

        if (gameField.hasIntersectionWithFigure()) {
            currentFigure = null;
        }
    }

    private void moveFigureDown() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.moveDown();

        if (gameField.hasIntersectionWithFigure()) {
            currentFigure.moveUp();
            currentFigure = null;

            gameField.saveFigureBlocks();
            System.out.println("Figure figurePosition fixed.");

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

        if (gameField.hasIntersectionWithFigure())
            currentFigure.moveRight();
    }

    private void moveFigureRight() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.moveRight();

        if (gameField.hasIntersectionWithFigure())
            currentFigure.moveLeft();
    }

    private void rotateFigureLeft() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.rotateLeft();

        if (gameField.hasIntersectionWithFigure())
            currentFigure.rotateRight();
    }

    private void rotateFigureRight() {
        if (gamePaused || (currentFigure == null))
            return;

        currentFigure.rotateRight();

        if (gameField.hasIntersectionWithFigure())
            currentFigure.rotateLeft();
    }

    private void togglePauseGame() {
        if (gamePaused)
            ticker.start();
        else
            ticker.stop();

        gamePaused = !gamePaused;
//        gameWindow.setMuteBlocks(gamePaused);
    }

    private void recalculateTickerDelay(int rowsNum) {
        ticker.setDelay(
                ticker.getDelay() - 10
        );
    }
}
