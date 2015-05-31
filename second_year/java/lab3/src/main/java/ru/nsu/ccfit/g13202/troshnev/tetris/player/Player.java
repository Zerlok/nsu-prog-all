package ru.nsu.ccfit.g13202.troshnev.tetris.player;

/**
 * Created by zerlok on 5/26/15.
 */
public class Player {
    private Level level;
    private Score score;

    public Player() {
        score = new Score();
        level = new Level(score);
    }

    public long getScore() {
        return score.countCurrentScore();
    }

    public int getLevel() {
        return level.getLevelNum();
    }
}
