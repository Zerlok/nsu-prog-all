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
    private GameOverView gameOverView;

    public GamePanel(Field gameField, Field previewField, PlayerInfoView info, GameOverView endView) {
        blockView = new BlockView(25, 5, 1);
        int blockPixelWidth = blockView.getPixelOffset();

        // setup main game view (current figure and field blocks).
        currentFigureView = new FigureView(blockView);
        gameFieldView = new FieldView(gameField, blockView, currentFigureView);
        gameFieldView.setPreferredSize(new Dimension(
                gameField.getFieldColumnsNum() * blockPixelWidth,
                gameField.getFieldRowsNum() * blockPixelWidth
        ));

        // setup next figure preview.
        nextFigureView = new FigureView(blockView);
        nextFigureFieldView = new FieldView(previewField, blockView, nextFigureView);
        nextFigureFieldView.setPreferredSize(new Dimension(
                previewField.getFieldColumnsNum() * blockPixelWidth,
                previewField.getFieldRowsNum() * blockPixelWidth
        ));

        // create info and game over views.
        infoView = info;
        gameOverView = endView;

        // create split panes for game view.
        JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, nextFigureFieldView, infoView);
        JSplitPane mainPane = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT, gameFieldView, splitPane);

        splitPane.setDividerLocation(previewField.getFieldRowsNum() * blockPixelWidth);
        splitPane.setDividerSize(5);
        splitPane.setEnabled(false);
        mainPane.setDividerLocation(gameField.getFieldColumnsNum() * blockPixelWidth);
        mainPane.setDividerSize(5);
        mainPane.setEnabled(false);

        // setup layout.
        setLayout(new BorderLayout());
        add(mainPane, BorderLayout.CENTER);

        validate();
    }

    private void switchToGameOverView() {
        removeAll();
        add(gameOverView);
        validate();
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

    @Override
    public void handleTetrisEvent(TetrisEvent event) {
        String cmd = event.getEventCommand();

        if ((cmd == "TETRIS-FIGURE-NEW")
                || (cmd == "TETRIS-ROWS-REMOVED"))
            infoView.updateStatistics();

        if (cmd == "GAME-OVER") {
            gameOverView.refreshMessage();
            switchToGameOverView();
        }
    }
}
