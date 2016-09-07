package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 6/11/15.
 */
public class GameOverView extends JComponent {
    private JTextField nameInput;
    private JLabel scoreMessage;
    private Player currentPlayer;
    private JButton btn;
    private Action endAction;

    public GameOverView(Player player) {
        currentPlayer = player;

        Dimension rowSize = new Dimension(100, 20);

        JLabel gameOverMessage = new JLabel("GAME OVER");
        scoreMessage = new JLabel();
        nameInput = new JTextField("Name");
        nameInput.setFocusable(true);
        btn = new JButton("Enter");

        btn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                currentPlayer.setName(nameInput.getText());
                currentPlayer.saveScore();
                endAction.actionPerformed(actionEvent);
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

    public void refreshMessage() {
        scoreMessage.setText(String.format("Level: %1$d, Score: %2$d, Rows: %3$d, Figures: %4$d",
                currentPlayer.getLevelNum(),
                currentPlayer.getScorePoints(),
                currentPlayer.getTotalRowsNum(),
                currentPlayer.getTotalFiguresNum()
        ));
    }

    public void setGameOverAction(Action action) {
        endAction = action;
    }
}
