package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import com.sun.org.apache.bcel.internal.generic.FLOAD;
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
        gameFieldView.setPreferredSize(new Dimension(400, 720));
        gameFieldView.setBorder(BorderFactory.createTitledBorder("Game Field"));

        nextFigureView = new FigureView(blockView);
        nextFigureFieldView = new FieldView(new Field(6, 6), new BlockView(blockView), nextFigureView);
        nextFigureFieldView.setPreferredSize(new Dimension(240, 240));
        nextFigureFieldView.setBorder(BorderFactory.createTitledBorder("Next Figure"));

        infoView = new PlayerInfoView(new Player());
        infoView.setPreferredSize(new Dimension(240, 400));
        infoView.setBorder(BorderFactory.createTitledBorder("Info"));

        setLayout(new FlowLayout(FlowLayout.LEFT));

        add(gameFieldView);
        add(nextFigureFieldView);
        add(infoView);
    }

    public void setCurrentFigure(AbstractFigure f) {
        currentFigureView.setFigure(f);
    }

    public void setNextFigure(AbstractFigure f) {
        currentFigureView.setFigure(f);
    }

    public void hideBlocks(boolean bool) {
        blockView.setBlockMuting(bool);
    }
}
