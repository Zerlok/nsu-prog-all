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
    private HashMap<String, Figure > figuresMap;

    public FigureFactory() {
        figuresMap = new HashMap<String, Figure >();
    }

    public Figure createRandomFigure() {
        Figure figure = null;

        int size = figuresMap.size();
        int item_num = new Random().nextInt(size);
        int indx = 0;

        for (Figure figurePrototype : figuresMap.values())
        {
            if (indx == item_num) {
                figure = figurePrototype.clone();
                break;
            }

            indx++;
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
        Figure figurePrototype;

        for (String key : prop.stringPropertyNames()) {
            if (!key.contentEquals("folder")) {
                figurePrototype = null;
                String value = prop.getProperty(key);

                try {
                    figurePrototype = (Figure)Class.forName(String.format("%1$s.%2$s", figuresFolderPath, value)).newInstance();

                } catch (InstantiationException e) {
                    e.printStackTrace();
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (ClassNotFoundException e) {
                    e.printStackTrace();
                }

                if (figurePrototype != null)
                    figuresMap.put(key, figurePrototype);
            }
        }
    }
}
