package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import javax.swing.*;
import java.awt.*;

public class RectanglesExample extends JFrame {

    public RectanglesExample() {
        initUI();
    }

    public final void initUI() {
        DrawPanel dpnl = new DrawPanel();
        add(dpnl);

        setSize(400, 400);
        setTitle("Rectangles");
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public static void runExample() {
        SwingUtilities.invokeLater(
                new Runnable() {
                    public void run() {
                        RectanglesExample ex = new RectanglesExample();
                        ex.setVisible(true);
                    }
                }
        );
    }
}

class DrawPanel extends JPanel {
    private void doDrawing(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        int x = 10;
        int y = 10;
        int width = 100;
        int offset = 6;

        g2d.setColor(new Color(15, 38, 27));
        g2d.fill(new Rectangle(100, 100, 120, 120));
        g2d.setColor(new Color(63, 161, 116));
        g2d.fillRect(x, y, x + width, y + width);
        g2d.setColor(new Color(75, 191, 137));
        g2d.fillRect(x + offset, y + offset, x + width - 2*offset, y + width - 2*offset);
    }

    @Override
    public void paintComponent(Graphics grphcs) {
        super.paintComponent(grphcs);
        doDrawing(grphcs);
    }
}
