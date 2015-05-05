package ru.nsu.ccfit.g13202.troshnev.tetris.figures;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.Figure;
import ru.nsu.ccfit.g13202.troshnev.tetris.kernel.UnknownFigureException;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Properties;

/**
 * Created by zerlok on 4/29/15.
 */

public class FigureFactory {
    private HashMap<String, Class<? extends Figure> > figuresMap;

    public FigureFactory() {
        figuresMap = new HashMap<String, Class<? extends Figure> >();
    }

    public Figure createFigure(String figureName) throws UnknownFigureException {
        Figure figure = null;

        try {
            if (figuresMap.containsKey(figureName)) {
                Class figureClass = (Class) figuresMap.get(figureName);
                figure = (Figure)figureClass.getConstructor().newInstance();

            } else {
                throw new UnknownFigureException(figureName);
            }

        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }

        return figure;
    }

    public void configure() throws IOException {
        Properties prop = new Properties();
        InputStream inputStream = getClass().getClassLoader().getResourceAsStream("cmd.properties");

        if (inputStream == null) {
            throw new FileNotFoundException("Cannot find cmd.properties file.");
        }

        prop.load(inputStream);
        String cmdFolderPath = prop.getProperty("folder");

        for (String key : prop.stringPropertyNames()) {
            if (!key.contentEquals("folder")) {
                String value = prop.getProperty(key);
                try {
                    figuresMap.put(key, (Class<Figure>) Class.forName(cmdFolderPath + "." + value));

                } catch (ClassNotFoundException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
