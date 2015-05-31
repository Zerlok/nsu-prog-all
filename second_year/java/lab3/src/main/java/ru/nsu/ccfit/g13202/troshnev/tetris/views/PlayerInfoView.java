package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/31/15.
 */
public class PlayerInfoView extends JComponent {
    private Player currentPlayer;
    private JLabel highscoreValue;
    private JLabel currentScoreValue;
    private JLabel currentLevelValue;

    public PlayerInfoView(Player player) {
        currentPlayer = player;
        highscoreValue = new JLabel("Unknown");
        currentScoreValue = new JLabel(String.valueOf(player.getScore()));
        currentLevelValue = new JLabel(String.valueOf(player.getLevel()));

        setLayout(new GridLayout(3, 2, 20, 20));
        add(new JLabel("Highscore"));
        add(highscoreValue);
        add(new JLabel("Score:"));
        add(currentScoreValue);
        add(new JLabel("Level:"));
        add(currentLevelValue);

        setSize(new Dimension(200, 500));
    }
}
