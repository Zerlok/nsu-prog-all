package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.UnknownFigureException;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Properties;
import java.util.Random;

/**
 * Created by zerlok on 4/29/15.
 */

public class FigureFactory {
    private HashMap<String, String > figuresMap;

    public FigureFactory() {
        figuresMap = new HashMap<String, String >();
    }

    public Figure createFigure(String figureName) throws UnknownFigureException {
        Figure figure = null;

        try {
            if (figuresMap.containsKey(figureName)) {
                Class figureClass = Class.forName(figuresMap.get(figureName));
                figure = (Figure)figureClass.newInstance();

            } else {
                throw new UnknownFigureException(figureName);
            }

        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        return figure;
    }

    public Figure createRandomFigure() {
//        TODO: copy figure from prototype.
        Figure figure = null;

        try {
            int size = figuresMap.size();
            int item_num = new Random().nextInt(size);
            int indx = 0;

            for (String figureClassName : figuresMap.values())
            {
                if (indx == item_num) {
                    figure = (Figure)Class.forName(figureClassName).newInstance();
//                    figure.copy();
                    break;
                }

                indx++;
            }
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        return figure;
    }

    public void configure() throws IOException {
        Properties prop = new Properties();
        InputStream inputStream = getClass().getClassLoader().getResourceAsStream("figures.properties");

        if (inputStream == null) {
            throw new FileNotFoundException("Cannot find figures.properties file.");
        }

        prop.load(inputStream);
        String figuresFolderPath = prop.getProperty("folder");

        for (String key : prop.stringPropertyNames()) {
            if (!key.contentEquals("folder")) {
                String value = prop.getProperty(key);
                figuresMap.put(key, String.format("%1$s.%2$s", figuresFolderPath, value));
            }
        }
    }
}
