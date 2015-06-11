package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.HighscoreTable;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 6/11/15.
 */
public class GameOverView extends JComponent {
    private JTextField nameInput;
    private long currentScore;
    private HighscoreTable scoreTable;

    public GameOverView(HighscoreTable table, long score) {
        scoreTable = table;
        currentScore = score;

        setLayout(new FlowLayout(FlowLayout.CENTER));

        JLabel gameOverMessage = new JLabel("GAME OVER");
        JLabel scoreMessage = new JLabel(String.format("Your score: %1$d", currentScore));
        nameInput = new JTextField("Name");
        nameInput.setPreferredSize(new Dimension(200, 20));
        JButton btn = new JButton("Enter");
        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if (actionEvent.getActionCommand() == "Enter") {
                    scoreTable.addHighscore(nameInput.getText(), currentScore);
                }
            }
        });

        add(gameOverMessage);
        add(scoreMessage);
        add(nameInput);
        add(btn);
    }
}
