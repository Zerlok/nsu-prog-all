package ru.nsu.ccfit.g13202.troshnev.tetris.player;

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
    private boolean makeFigureRotationEvents;
    private boolean makeFigureMovementEvents;

    private Score playerScore;

    public Level(Score score) {
        levelNum = 1;
        makeFigureFallEvents = true;
        makeExtraRowEvents = false;
        makeFigureRotationEvents = false;
        makeFigureMovementEvents = false;

        playerScore = score;
    }

    public void updateLevel() {
        levelNum = 1;

        long currentScore = playerScore.countCurrentScore();
        for (int i = 0; i < levelUpScores.length; i++)
            if (currentScore > levelUpScores[i])
                ++levelNum;

        updateHardness();
    }

    public void updateHardness() {
        makeFigureFallEvents = (levelNum > 0);
        makeExtraRowEvents = (levelNum > 2);
        makeFigureMovementEvents = (levelNum > 6);
        makeFigureRotationEvents = (levelNum > 8);
    }

    public void makeGameEvents() {
        if (makeFigureFallEvents);
        if (makeExtraRowEvents);
        if (makeFigureMovementEvents);
        if (makeFigureRotationEvents);
    }

    public int getLevelNum() {
        return levelNum;
    }
}
