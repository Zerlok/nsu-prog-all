package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.HighscoreTable;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/31/15.
 */
public class ScoresView extends JComponent {
    public HighscoreTable scoreTable;

    public ScoresView(HighscoreTable table) {
        scoreTable = table;
        setLayout(new GridLayout(0, 3, 5, 3));
        createTableView();
    }

    private void createTableView() {
        // setup table header.
        JLabel h1 = new JLabel("#");
        JLabel h2 = new JLabel("Player");
        JLabel h3 = new JLabel("Score");

        Font headerFont = new Font(Font.SANS_SERIF, Font.BOLD, 16);
        h1.setFont(headerFont);
        h2.setFont(headerFont);
        h3.setFont(headerFont);

        // add table header.
        add(h1);
        add(h2);
        add(h3);

        // setup table body.
        String[] players = scoreTable.getPlayers();
        long[] scores = scoreTable.getScores();

        // add table body.
        for (int i = 0; i < players.length; i++) {
            add(new JLabel(String.format("%1$02d", (i+1))));
            add(new JLabel(String.format("%1$-16s", (players[i] != null) ? players[i] : "---")));
            add(new JLabel(String.format("%1$-10d", scores[i])));
        }
    }
}
