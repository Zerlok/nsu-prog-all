package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEvent;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventController;
import ru.nsu.ccfit.g13202.troshnev.tetris.events.TetrisEventListener;
import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.Field;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.HighscoreTable;
import ru.nsu.ccfit.g13202.troshnev.tetris.player.Player;
import ru.nsu.ccfit.g13202.troshnev.tetris.views.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by zerlok on 4/29/15.
 */
public class GamePanel extends JPanel implements TetrisEventListener {
    private BlockView blockView;

    private FigureView currentFigureView;
    private FieldView gameFieldView;

    private FigureView nextFigureView;
    private FieldView nextFigureFieldView;

    private PlayerInfoView infoView;

    private HighscoreTable scoresTable;
    private Player currentPlayer;

    private JSplitPane mainPane;

    public GamePanel(Field gameField, Field previewField, Player player, HighscoreTable table) {
        scoresTable = table;
        currentPlayer = player;

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

        infoView = new PlayerInfoView(player, table);

        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, nextFigureFieldView, infoView);
        mainPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, gameFieldView, splitPane);

        splitPane.setDividerLocation(previewField.getFieldRowsNum() * blockPixelWidth);
        splitPane.setDividerSize(5);
        splitPane.setEnabled(false);
        mainPane.setDividerLocation(gameField.getFieldColumnsNum() * blockPixelWidth);
        mainPane.setDividerSize(5);
        mainPane.setEnabled(false);

        setLayout(new BorderLayout());
        add(mainPane, BorderLayout.CENTER);
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
        eventController.addListener(infoView);
        eventController.addListener(this);
    }

    @Override
    public void handleTetrisEvent(TetrisEvent event) {
        String cmd = event.getEventCommand();

        if (cmd == "GAME-OVER") {
            remove(mainPane);
            GameOverView gov = new GameOverView(scoresTable, currentPlayer.getScorePoints());
            gov.setPreferredSize(new Dimension(250, 400));
            add(gov, BorderLayout.CENTER);
        }
    }
}
