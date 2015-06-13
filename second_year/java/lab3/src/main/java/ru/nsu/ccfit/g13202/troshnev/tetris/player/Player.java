package ru.nsu.ccfit.g13202.troshnev.tetris.player;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEvent;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventListener;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.HighscoreTable;

/**
 * Created by zerlok on 5/26/15.
 */
public class Player implements TetrisEventListener {
    private String name;
    private Level level;
    private Score score;
    private HighscoreTable scoresTable;
    private int totalRowsNum;
    private int totalFiguresNum;

    public Player(Level lvl, Score scr, HighscoreTable table) {
        name = null;
        level = lvl;
        score = scr;
        scoresTable = table;
        totalRowsNum = 0;
        totalFiguresNum = 0;
    }

    public void setName(String text) {
        name = text;
    }

    public void addFiguresNum() {
        score.incrementFiguresNum();
        level.updateLevel();
        ++totalFiguresNum;
    }

    public void addRowsNum(int rowsNum) {
        score.incrementRows(rowsNum);
        level.updateLevel();
        ++totalRowsNum;
    }

    public void saveScore() {
        if (name != null)
            scoresTable.addHighscore(name, getScorePoints());
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

    public String getName() {
        return name;
    }

    public int getLevelNum() {
        return level.getLevelNum();
    }

    public long getScorePoints() {
        return score.getTotalScore();
    }

    public int getTotalRowsNum() {
        return totalRowsNum;
    }

    public int getTotalFiguresNum() {
        return totalFiguresNum;
    }
}
