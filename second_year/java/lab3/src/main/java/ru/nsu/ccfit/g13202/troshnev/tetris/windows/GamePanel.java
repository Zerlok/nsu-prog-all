package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.FieldBlocksView;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.FigureView;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.PlayerInfoView;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */

public class GamePanel extends JPanel {
    private FieldBlocksView blocksView;
    private FigureView currentFigureView;
    private FigureView nextFigureView;
    private PlayerInfoView infoView;

    public GamePanel(Field gameField) {
        blocksView = new FieldBlocksView(gameField);
        blocksView.setSize(new Dimension(550, 700));
        add(blocksView);

        currentFigureView = new FigureView(
                gameField.getFieldRowsNum(),
                gameField.getFieldColumnsNum()
        );
        currentFigureView.setSize(new Dimension(200, 700));
        add(currentFigureView);

        nextFigureView = new FigureView(6, 6);
        nextFigureView.setSize(new Dimension(150, 150));
        add(nextFigureView);

        infoView = new PlayerInfoView(new Player());
        infoView.setSize(new Dimension(150, 550));
        add(infoView);

        setLayout(new BorderLayout(10, 10));
        setSize(new Dimension(500, 700));
    }

    public void setCurrentFigure(AbstractFigure f) {
        currentFigureView.setFigure(f);
    }

    public void setNextFigure(AbstractFigure f) {
        currentFigureView.setFigure(f);
    }
}
