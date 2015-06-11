package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/31/15.
 */
public class BaseWindow extends JFrame {
    private JPanel innerWindow;

    public BaseWindow(ActionMap actionsMap) {
        JMenuItem menuMain = new JMenuItem();
        menuMain.setAction(actionsMap.get("MAIN-HOME"));

        JMenuItem menuStart = new JMenuItem();
        menuStart.setAction(actionsMap.get("GAME-NEW"));

        JMenuItem menuPause = new JMenuItem();
        menuPause.setAction(actionsMap.get("GAME-PAUSE"));

        JMenuBar windowHeader = new JMenuBar();

        setTitle("Tetris");
        windowHeader.add(menuMain);
        windowHeader.add(menuStart);
        windowHeader.add(menuPause);

        setJMenuBar(windowHeader);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        setLayout(new BorderLayout());
    }

    public void centrateWindow() {
        //Get the screen size
        Toolkit toolkit = Toolkit.getDefaultToolkit();
        Dimension screenSize = toolkit.getScreenSize();

        //Calculate the frame location
        setLocation(
                (screenSize.width - getWidth()) / 2,
                (screenSize.height - getHeight()) / 2
        );
    }

    public void setInnerWindow(JPanel window) {
        if ((window == null)
                || (window == innerWindow))
            return;

        if (innerWindow != null)
            remove(innerWindow);

        innerWindow = window;
        Container content = getContentPane();
        content.add(window, BorderLayout.CENTER);
        content.setSize(window.getWidth(), window.getHeight());
        pack();
    }
}
