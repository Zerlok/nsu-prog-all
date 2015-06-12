package ru.nsu.ccfit.g13202.troshnev.tetris.player;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEvent;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventController;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventListener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 5/26/15.
 */
public class Player implements TetrisEventListener {
    private Level level;
    private Score score;

    public Player(TetrisEventController eventController) {
        score = new Score();
        level = new Level(score, eventController);
        eventController.addListener(this);
    }

    public long getScorePoints() {
        return score.getTotalScore();
    }

    public int getLevelNum() {
        return level.getLevelNum();
    }

    public void addFiguresNum() {
        score.incrementFiguresNum();
        level.updateLevel();
    }

    public void addRowsNum(int rowsNum) {
        score.incrementRows(rowsNum);
        level.updateLevel();
    }

    @Override
    public void handleTetrisEvent(TetrisEvent event) {
        String cmd = event.getEventCommand();

        if (cmd == "TETRIS-FIGURE-NEW") {
            addFiguresNum();
            return;
        }

        if (cmd == "TETRIS-ROWS-REMOVED") {
            addRowsNum((Integer)event.getEventArgument());
            return;
        }
    }
}
