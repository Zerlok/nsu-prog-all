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

        Dimension rowSize = new Dimension(100, 20);
        JLabel gameOverMessage = new JLabel("GAME OVER");
        JLabel scoreMessage = new JLabel(String.format("Score: %1$d", currentScore));
        nameInput = new JTextField("Name");
        nameInput.setFocusable(true);
        JButton btn = new JButton("Enter");
        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                if (actionEvent.getActionCommand() == "Enter") {
                    scoreTable.addHighscore(nameInput.getText(), currentScore);
                }
            }
        });

        gameOverMessage.setPreferredSize(rowSize);
        scoreMessage.setPreferredSize(rowSize);
        nameInput.setPreferredSize(rowSize);
        btn.setPreferredSize(rowSize);

        setLayout(new GridLayout(8, 1, 20, 20));

        add(gameOverMessage);
        add(scoreMessage);
        add(nameInput);
        add(btn);
    }
}
