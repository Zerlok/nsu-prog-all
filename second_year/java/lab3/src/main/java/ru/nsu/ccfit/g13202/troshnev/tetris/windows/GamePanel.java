package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.BlockView;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.FieldView;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.FigureView;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.PlayerInfoView;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class GamePanel extends JPanel {
    private BlockView blockView;

    private FigureView currentFigureView;
    private FieldView gameFieldView;

    private FigureView nextFigureView;
    private FieldView nextFigureFieldView;

    private PlayerInfoView infoView;

    public GamePanel(Field gameField) {
        blockView = new BlockView(40, 5, 1);

        currentFigureView = new FigureView(blockView);
        gameFieldView = new FieldView(gameField, blockView, currentFigureView);
        gameFieldView.setSize(new Dimension(400, 720));
        add(gameFieldView);

        nextFigureView = new FigureView(blockView);
        nextFigureFieldView = new FieldView(new Field(6, 6), new BlockView(blockView), nextFigureView);
        nextFigureFieldView.setSize(new Dimension(240, 240));
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
