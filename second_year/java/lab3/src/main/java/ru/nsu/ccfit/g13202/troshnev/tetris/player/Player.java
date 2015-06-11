package ru.nsu.ccfit.g13202.troshnev.tetris.player;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventController;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 5/26/15.
 */
public class Player implements ActionListener {
    private Level level;
    private Score score;

    public Player(TetrisEventController eventController) {
        score = new Score();
        level = new Level(score, eventController);
        eventController.addActionListener(this);
    }

    public long getScorePoints() {
        return score.countCurrentScore();
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
    public void actionPerformed(ActionEvent actionEvent) {
        String cmd = actionEvent.getActionCommand();

        if (cmd == "TETRIS-FIGURE-NEW") {
            addFiguresNum();
            return;
        }

        if (cmd.startsWith("TETRIS-ROWS-REMOVED=")) {
            addRowsNum(Integer.valueOf(cmd.split("=")[1]));
            return;
        }
    }
}
