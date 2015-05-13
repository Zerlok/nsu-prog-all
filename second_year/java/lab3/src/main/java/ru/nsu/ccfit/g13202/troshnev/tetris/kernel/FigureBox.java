package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;

import java.util.Random;
import java.util.Vector;

/**
 * Created by zerlok on 5/13/15.
 */
public class FigureBox {
    private Vector<Figure> figuresArray;
    private int index;
    private Random rnd;

    public FigureBox() {
        figuresArray = new Vector<Figure>();
        index = 0;
        rnd = new Random();
    }

    public void push(Figure figure) {
        figuresArray.addElement(figure);
    }

    public Figure pop() {
        if (index == figuresArray.size())
            shuffle();

        Figure figure = figuresArray.get(index).clone();
        ++index;
        figure.setRotation(rnd.nextInt());
        return figure;
    }

    public void shuffle() {
        int size = figuresArray.size();
        Figure figurePrototype;
        Vector<Figure> shuffledArray = new Vector<Figure>(size);

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

        figuresArray = new Vector<Figure>(shuffledArray);
        index = 0;
    }
}
