package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 5/31/15.
 */
public class PlayerInfoView extends JComponent implements ActionListener {
    private Player currentPlayer;
    private JLabel highscoreValue;
    private JLabel currentScoreValue;
    private JLabel currentLevelValue;

    public PlayerInfoView(Player player) {
        currentPlayer = player;
        highscoreValue = new JLabel("0");
        currentScoreValue = new JLabel(String.valueOf(player.getScorePoints()));
        currentLevelValue = new JLabel(String.valueOf(player.getLevelNum()));

        setLayout(new GridLayout(3, 2, 20, 20));
        add(new JLabel("Highscore"));
        add(highscoreValue);
        add(new JLabel("Score:"));
        add(currentScoreValue);
        add(new JLabel("Level:"));
        add(currentLevelValue);
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        currentLevelValue.setText(String.valueOf(currentPlayer.getLevelNum()));
        currentScoreValue.setText(String.valueOf(currentPlayer.getScorePoints()));
        repaint();
    }
}
