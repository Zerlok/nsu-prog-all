package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 6/11/15.
 */
public class GameOverView extends JComponent implements ActionListener {
    private JTextField nameInput;

    public GameOverView(long score) {
        setLayout(new FlowLayout(FlowLayout.CENTER));
        JLabel gameOverMessage = new JLabel("GAME OVER");
//        gameOverMessage.setPreferredSize(new Dimension(10, 100));
        JLabel scoreMessage = new JLabel(String.format("Your score: %1$d", score));
//        scoreMessage.setPreferredSize(new Dimension(10, 100));

        add(gameOverMessage);
        add(scoreMessage);

        nameInput = new JTextField("Name");
        nameInput.setPreferredSize(new Dimension(200, 20));
        add(nameInput, BorderLayout.CENTER);

        JButton btn = new JButton("Enter");
        btn.addActionListener(this);
        add(btn);
    }

    @Override
    public void actionPerformed(ActionEvent actionEvent) {
        if (actionEvent.getActionCommand() == "Enter")
            System.out.println("Dat action!");
    }
}
