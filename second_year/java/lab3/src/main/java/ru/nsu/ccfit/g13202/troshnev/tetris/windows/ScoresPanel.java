package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.HighscoreTable;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class ScoresPanel extends JPanel {
    public ScoresPanel(HighscoreTable table) {
        setLayout(new GridLayout(0, 1, 100, 8));

        String[] players = table.getPlayers();
        long[] scores = table.getScores();

        for (int i = 0; i < players.length; i++) {
            add(new JLabel(String.format("%1$02d : %2$20s %3$10d",
                    (i+1),
                    (players[i] != null) ? players[i] : "-",
                    scores[i]
            )));
        }
        
        setSize(new Dimension(500, 500));
    }
}
