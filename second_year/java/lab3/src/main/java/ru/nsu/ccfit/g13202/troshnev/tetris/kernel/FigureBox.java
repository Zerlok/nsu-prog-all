package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;

import java.util.Random;
import java.util.Vector;

/**
 * Created by zerlok on 5/13/15.
 */
public class FigureBox {
    private Vector<AbstractFigure> figuresArray;
    private int index;
    private Random rnd;

    public FigureBox() {
        figuresArray = new Vector<AbstractFigure>();
        index = 0;
        rnd = new Random();
    }

    public void push(AbstractFigure figure) {
        figuresArray.addElement(figure);
    }

    public AbstractFigure pop() {
        if (index == figuresArray.size())
            shuffle();

        AbstractFigure figure = figuresArray.get(index).clone();
        ++index;
        figure.setRotation(rnd.nextInt(4));
        return figure;
    }

    public void shuffle() {
        int size = figuresArray.size();
        AbstractFigure figurePrototype;
        Vector<AbstractFigure> shuffledArray = new Vector<AbstractFigure>(size);

        for (int i = 0; i < size; i++) {
            int randomIndex = rnd.nextInt(size - i);
            figurePrototype = figuresArray.get(randomIndex);

            while (figurePrototype == null) {
                randomIndex = (randomIndex + 1) % size;
                figurePrototype = figuresArray.get(randomIndex);
            }

            shuffledArray.addElement(figurePrototype);
            figuresArray.removeElementAt(randomIndex);
        }

        figuresArray = new Vector<AbstractFigure>(shuffledArray);
        index = 0;
    }
}
