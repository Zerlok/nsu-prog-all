package ru.nsu.ccfit.g13202.troshnev.tetris.views;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 5/31/15.
 */
public class FigureView extends JComponent {
    private AbstractFigure figure;

    public FigureView(int rowsNum, int columnsNum) {
        setBackground(new Color(200, 200, 200));
        setLayout(new GridLayout(rowsNum, columnsNum));
    }

    public void setFigure(AbstractFigure f) {
        figure = f;
    }
}
