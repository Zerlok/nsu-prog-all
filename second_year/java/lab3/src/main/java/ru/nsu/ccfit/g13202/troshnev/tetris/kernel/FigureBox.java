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
    private int size;
    private Random rnd;

    public FigureBox(int capacity) {
        figuresArray = new Vector<Figure>(capacity);
        index = 0;
        size = capacity;
        rnd = new Random();
    }

    public void push(Figure figure) {
        figuresArray.add(figure);
    }

    public Figure pop() {
        if (index == size)
            shuffle();

        Figure figure = figuresArray.get(index).clone();
        ++index;
        figure.setRotation(rnd.nextInt());
        return figure;
    }

    public void shuffle() {
        Figure figurePrototype;
        Vector<Figure> shuffledArray = new Vector<Figure>(size);

        for (int i = 0; i < size; i++) {
            int randomIndex = rnd.nextInt(size - i);
            figurePrototype = figuresArray.get(randomIndex);

            while (figurePrototype == null) {
                randomIndex = (randomIndex + 1) % size;
                figurePrototype = figuresArray.get(randomIndex);
            }

            shuffledArray.add(figurePrototype);
            figuresArray.remove(randomIndex);
        }

        figuresArray = new Vector<Figure>(shuffledArray);
        index = 0;
    }
}
