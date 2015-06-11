package ru.nsu.ccfit.g13202.troshnev.tetris.player;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventController;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

/**
 * Created by zerlok on 5/26/15.
 */
public class Level {
    private static long[] levelUpScores = {
            10000, // 2
            30000, // 3
            70000, // 4
            125000, // 5
            200000, // 6
            315000, // 7
            500000, // 8
            1000000 // 9
    };

    private int levelNum;
    private boolean makeFigureFallEvents;
    private boolean makeExtraRowEvents;
    private boolean makeFigureMovementEvents;
    private boolean makeFigureRotationEvents;

    //    Current ticker delay.
    private Timer ExtraRowsTicker;
    private Timer FigureMovementTicker;
    private Timer FigureRotationTicker;

    //    Maximum ticker delay.
    private int maxTickerDelayExtraRows = 10;
    private int maxTickerDelayFigureMovement = 10;
    private int maxTickerDelayFigureRotation = 10;

    private Score playerScore;
    private TetrisEventController eventController;
    private Random rand;

    public Level(Score score, TetrisEventController controller) {
        rand = new Random();

        levelNum = 1;
        makeFigureFallEvents = true;
        makeExtraRowEvents = false;
        makeFigureRotationEvents = false;
        makeFigureMovementEvents = false;

        ExtraRowsTicker = new Timer(0, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                eventController.pushEvent(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, "TETRIS-FIELD-PUSH-ROW"));
                recalculateTicker(ExtraRowsTicker, maxTickerDelayExtraRows);
            }
        });
        FigureRotationTicker = new Timer(0, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                eventController.pushEvent(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, "TETRIS-FIGURE-ROTATE"));
                recalculateTicker(FigureRotationTicker, maxTickerDelayFigureRotation);
            }
        });
        FigureMovementTicker = new Timer(0, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                eventController.pushEvent(new ActionEvent(this, ActionEvent.ACTION_PERFORMED, String.format("TETRIS-FIGURE-MOVE=%1$d", rand.nextInt(3))));
                recalculateTicker(FigureMovementTicker, maxTickerDelayFigureMovement);
            }
        });

        playerScore = score;
    }

    private void recalculateTicker(Timer ticker, int delay) {
        ticker.setDelay(delay + rand.nextInt(delay));
    }

    public void updateLevel() {
        levelNum = 1;

        long currentScore = playerScore.countCurrentScore();
        for (int i = 0; i < levelUpScores.length; i++)
            if (currentScore > levelUpScores[i])
                ++levelNum;

        updateHardness();
    }

    private void updateHardness() {
        makeFigureFallEvents = (levelNum > 0);
        makeExtraRowEvents = (levelNum > 2);
        makeFigureMovementEvents = (levelNum > 6);
        makeFigureRotationEvents = (levelNum > 8);

        setupEvents();
    }

    private void setupEvents() {
        // TODO: Make level events

        if (makeExtraRowEvents && (!ExtraRowsTicker.isRunning()))
            ExtraRowsTicker.start();

        if (makeFigureRotationEvents && (!FigureRotationTicker.isRunning()))
            FigureRotationTicker.start();

        if (makeFigureMovementEvents && (!FigureMovementTicker.isRunning()))
            FigureMovementTicker.start();
    }

    public int getLevelNum() {
        return levelNum;
    }
}
