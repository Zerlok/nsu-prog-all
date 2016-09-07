package ru.nsu.ccfit.g13202.troshnev.tetris.windows;

import ru.nsu.ccfit.g13202.troshnev.tetris.views.ScoresView;

import javax.swing.*;
import java.awt.*;

/**
 * Created by zerlok on 4/29/15.
 */
public class ScoresPanel extends JPanel {

    public ScoresPanel(ScoresView view) {
        setPreferredSize(new Dimension(300, 500));
        add(view);
        validate();
    }
}
