package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/31/15.
 */
public class BaseWindow extends JFrame {
    private JMenuBar windowHeader;
    private JMenu windowMenu;
    private JPanel innerWindow;

    public BaseWindow(ActionMap actionsMap) {
        JMenuItem menuStart = new JMenuItem();
        menuStart.setAction(actionsMap.get("GAME-NEW"));

        JMenuItem menuPause = new JMenuItem();
        menuPause.setAction(actionsMap.get("GAME-PAUSE"));

        JMenuItem menuMain = new JMenuItem();
        menuMain.setAction(actionsMap.get("MAIN-HOME"));

        JMenuItem menuExit = new JMenuItem();
        menuExit.setAction(actionsMap.get("GAME-EXIT"));

        windowMenu = new JMenu("Menu");
        windowHeader = new JMenuBar();

        setTitle("Tetris");
        windowMenu.add(menuStart);
        windowMenu.add(menuPause);
        windowMenu.add(menuMain);
        windowMenu.add(menuExit);
        windowHeader.add(windowMenu);

        setJMenuBar(windowHeader);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void centreWindow() {
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
        add(window);
        setSize(
                window.getWidth(),
                window.getHeight()
        );
    }
}
