package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */

public class MainPanel extends JPanel {

    public MainPanel(ActionMap actionsMap) {
        // create buttons
        JButton startBtn = new JButton();
        JButton highscoreBtn = new JButton();
        JButton aboutBtn = new JButton();
        JButton exitBtn = new JButton();

        // bind actions to buttons.
        startBtn.setAction(actionsMap.get("GAME-NEW"));
        highscoreBtn.setAction(actionsMap.get("MAIN-SCORES"));
        aboutBtn.setAction(actionsMap.get("MAIN-ABOUT"));
        exitBtn.setAction(actionsMap.get("GAME-EXIT"));

        // set buttons sizes
        Dimension btnDefaultSize = new Dimension(130, 30);
        startBtn.setPreferredSize(btnDefaultSize);
        highscoreBtn.setPreferredSize(btnDefaultSize);
        aboutBtn.setPreferredSize(btnDefaultSize);
        exitBtn.setPreferredSize(btnDefaultSize);

        // add buttons to pane.
        JPanel contentPanel = new JPanel(new GridLayout(4, 1, 0, 10));
        contentPanel.add(startBtn);
        contentPanel.add(highscoreBtn);
        contentPanel.add(aboutBtn);
        contentPanel.add(exitBtn);
        add(contentPanel);

        // set window size
        Dimension windowSize = new Dimension(180, 230);
        setSize(windowSize);
    }
}
