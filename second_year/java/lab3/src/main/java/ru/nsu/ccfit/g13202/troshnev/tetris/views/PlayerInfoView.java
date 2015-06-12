package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEvent;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventListener;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.HighscoreTable;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 5/31/15.
 */
public class PlayerInfoView extends JComponent implements TetrisEventListener {
    private Player currentPlayer;
    private JLabel currentScoreValue;
    private JLabel currentLevelValue;

    public PlayerInfoView(Player player, HighscoreTable scoresTable) {
        currentPlayer = player;
        currentLevelValue = new JLabel("Level: " + String.valueOf(player.getLevelNum()));
        currentScoreValue = new JLabel("Score: " + String.valueOf(player.getScorePoints()));

        setLayout(new GridLayout(2, 1, 20, 20));
        add(currentLevelValue);
        add(currentScoreValue);
    }

    @Override
    public void handleTetrisEvent(TetrisEvent event) {
        // TODO: Make updates for player statistics. (don't know why it won't work)
        currentLevelValue.setText("Level: " + String.valueOf(currentPlayer.getLevelNum()));
        currentScoreValue.setText("Score: " + String.valueOf(currentPlayer.getScorePoints()));
    }
}
