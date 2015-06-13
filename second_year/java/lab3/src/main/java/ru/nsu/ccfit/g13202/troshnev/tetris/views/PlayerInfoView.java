package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/31/15.
 */
public class PlayerInfoView extends JComponent {
    private Player currentPlayer;
    private JLabel currentScoreValue;
    private JLabel currentLevelValue;

    public PlayerInfoView(Player player, long highscore) {
        currentPlayer = player;
        currentLevelValue = new JLabel("Level: " + String.valueOf(player.getLevelNum()));
        currentScoreValue = new JLabel("Score: " + String.valueOf(player.getScorePoints()));

        setLayout(new GridLayout(4, 1, 20, 20));
        add(new JLabel(String.format("Highscore: %1$d", highscore)));
        add(currentLevelValue);
        add(currentScoreValue);
    }

    public void updateStatistics() {
        currentLevelValue.setText("Level: " + String.valueOf(currentPlayer.getLevelNum()));
        currentScoreValue.setText("Score: " + String.valueOf(currentPlayer.getScorePoints()));
    }
}
