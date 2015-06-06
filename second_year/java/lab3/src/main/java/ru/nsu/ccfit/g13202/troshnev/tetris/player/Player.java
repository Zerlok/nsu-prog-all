package ru.nsu.ccfit.g13202.troshnev.tetris.player;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 5/26/15.
 */
public class Player implements ActionListener {
    private Level level;
    private Score score;

    public Player() {
        score = new Score();
        level = new Level(score);
    }

    public long getScorePoints() {
        return score.countCurrentScore();
    }

    public int getLevelNum() {
        return level.getLevelNum();
    }

    public void incrementFigures() {
        score.incrementFiguresNum();
        level.updateLevel();
    }

    public void incrementRows(int rowsNum) {
        score.incrementRows(rowsNum);
        level.updateLevel();
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if (actionEvent.getActionCommand() == "TETRIS-FIGURE-NEW") {
            incrementFigures();
        }
    }
}
