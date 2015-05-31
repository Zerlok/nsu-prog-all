package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.util.HashMap;

/**
 * Created by zerlok on 4/29/15.
 */

public class MainPanel extends JPanel {
    private JPanel contentPanel;
    private JButton startBtn;
    private JButton highscoreBtn;
    private JButton aboutBtn;
    private JButton exitBtn;

    private Dimension windowSize;
    private Dimension btnDefaultSize;

    public MainPanel(ActionMap actionsMap) {
        windowSize = new Dimension(180, 230);
        btnDefaultSize = new Dimension(130, 30);

        startBtn = new JButton();
        highscoreBtn = new JButton();
        aboutBtn = new JButton();
        exitBtn = new JButton();
        bindButtons(actionsMap);

        contentPanel = new JPanel(new GridLayout(4, 1, 0, 10));
        contentPanel.add(startBtn);
        contentPanel.add(highscoreBtn);
        contentPanel.add(aboutBtn);
        contentPanel.add(exitBtn);

        add(contentPanel);
        setSize(windowSize);
    }

    private void bindButtons(ActionMap actionsMap) {
        startBtn.setAction(actionsMap.get("GAME-NEW"));
        highscoreBtn.setAction(actionsMap.get("MAIN-SCORES"));
        aboutBtn.setAction(actionsMap.get("MAIN-ABOUT"));
        exitBtn.setAction(actionsMap.get("GAME-EXIT"));

        startBtn.setPreferredSize(btnDefaultSize);
        highscoreBtn.setPreferredSize(btnDefaultSize);
        aboutBtn.setPreferredSize(btnDefaultSize);
        exitBtn.setPreferredSize(btnDefaultSize);
    }
}
