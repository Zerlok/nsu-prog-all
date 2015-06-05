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
        blockView = new BlockView(25, 5, 1);

        currentFigureView = new FigureView(blockView);
        gameFieldView = new FieldView(gameField, blockView, currentFigureView);
        gameFieldView.setPreferredSize(new Dimension(260, 18*26));
//        gameFieldView.setBorder(BorderFactory.createTitledBorder("Game Field"));

        nextFigureView = new FigureView(blockView);
        nextFigureFieldView = new FieldView(new Field(6, 6), new BlockView(blockView), nextFigureView);
        nextFigureFieldView.setPreferredSize(new Dimension(240, 240));
//        nextFigureFieldView.setBorder(BorderFactory.createTitledBorder("Next Figure"));

        infoView = new PlayerInfoView(new Player());
        infoView.setPreferredSize(new Dimension(240, 400));
//        infoView.setBorder(BorderFactory.createTitledBorder("Info"));

        setLayout(new BorderLayout());

        JSplitPane splitPane2 = new JSplitPane(JSplitPane.VERTICAL_SPLIT, nextFigureFieldView, infoView);
        JSplitPane splitPane1 = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, gameFieldView, splitPane2);

        splitPane2.setDividerLocation(200);
        splitPane2.setDividerSize(4);
        splitPane1.setDividerLocation(300);
        splitPane1.setDividerSize(4);
        add(splitPane1, BorderLayout.CENTER);
    }

    public void setCurrentFigure(AbstractFigure f) {
        currentFigureView.setFigure(f);
    }

    public void setNextFigure(AbstractFigure f) {
        nextFigureView.setFigure(f);
    }

    public void hideBlocks(boolean bool) {
        System.out.println("mutting blocks " + bool);
        blockView.setBlockMuting(bool);
    }
}
