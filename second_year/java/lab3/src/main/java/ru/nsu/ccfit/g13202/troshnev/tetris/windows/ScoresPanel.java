package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class ScoresPanel extends JPanel {
    public ScoresPanel() {
        setLayout(new FlowLayout(FlowLayout.LEFT));

        add(new JLabel("Blah Label"));
        add(new JTextArea("TEXT AREA"));
        add(new JButton("Ok"));
        
        setSize(new Dimension(500, 500));
    }
}
