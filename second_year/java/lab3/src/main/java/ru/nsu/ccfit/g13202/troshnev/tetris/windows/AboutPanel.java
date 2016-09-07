package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class AboutPanel extends JPanel {
    private String aboutText = "This simple tetris game was developed by zerlok.\n"
            + "\nHow to play:\n"
            + "\tUse arrow keys to move the figure (left, right, down).\n"
            + "\tUse up arrow key to rotate the figure clockwise.\n"
            + "\tUse space key to smash down the figure (move down until it face field block).\n"
            + "\tUse 'p' key to pause the game.\n"
            + "\nContacts:\n"
            + "\temail: denergytro@gmail.com\n";

    public AboutPanel() {
        JTextArea textArea = new JTextArea(aboutText);
        textArea.setTabSize(4);
        textArea.setFont(new Font(Font.MONOSPACED, Font.PLAIN, 14));
        textArea.setDisabledTextColor(new Color(10, 10, 10));
        textArea.setEnabled(false);

        add(textArea);
    }
}
