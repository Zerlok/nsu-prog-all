package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */

public class SwingExample implements Runnable {
    @Override
    public void run() {
        // Create the window
        JFrame frame = new JFrame("Hello, !");
        // Sets the behavior for when the window is closed
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // Add a layout manager so that the button is not placed on top of the label
        frame.setLayout(new FlowLayout());
        // Add a label and a button
        frame.add(new JLabel("Hello, world!"));
        frame.add(new JButton("Press me!"));
        // Arrange the components inside the window
        frame.pack();
        // By default, the window is not visible. Make it visible.
        frame.setVisible(true);
    }
}
