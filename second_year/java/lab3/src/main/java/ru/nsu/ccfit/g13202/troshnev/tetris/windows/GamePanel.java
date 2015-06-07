package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventController;
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

    public GamePanel(Field gameField, Field previewField) {
        blockView = new BlockView(25, 5, 1);
        int blockPixelWidth = blockView.getPixelOffset();

        currentFigureView = new FigureView(blockView);
        gameFieldView = new FieldView(gameField, blockView, currentFigureView);
        gameFieldView.setPreferredSize(new Dimension(
                gameField.getFieldColumnsNum() * blockPixelWidth,
                gameField.getFieldRowsNum() * blockPixelWidth
        ));

        nextFigureView = new FigureView(blockView);
        nextFigureFieldView = new FieldView(previewField, blockView, nextFigureView);
        nextFigureFieldView.setPreferredSize(new Dimension(
                previewField.getFieldColumnsNum() * blockPixelWidth,
                previewField.getFieldRowsNum() * blockPixelWidth
        ));

        infoView = new PlayerInfoView(new Player());

        setLayout(new BorderLayout());

        JSplitPane splitPane2 = new JSplitPane(JSplitPane.VERTICAL_SPLIT, nextFigureFieldView, infoView);
        JSplitPane splitPane1 = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, gameFieldView, splitPane2);

        splitPane2.setDividerLocation(previewField.getFieldRowsNum() * blockPixelWidth);
        splitPane2.setDividerSize(4);
        splitPane2.setEnabled(false);
        splitPane1.setDividerLocation(gameField.getFieldColumnsNum() * blockPixelWidth);
        splitPane1.setDividerSize(4);
        splitPane1.setEnabled(false);
        add(splitPane1, BorderLayout.CENTER);
    }

    public void setCurrentFigure(AbstractFigure f) {
        currentFigureView.setFigure(f);
    }

    public void setNextFigure(AbstractFigure f) {
        nextFigureView.setFigure(f);
    }

    public void hideBlocks(boolean bool) {
        blockView.setBlockMuting(bool);
    }

    public void registerListeners(TetrisEventController eventController) {
        eventController.addActionListener(infoView);
    }
}
