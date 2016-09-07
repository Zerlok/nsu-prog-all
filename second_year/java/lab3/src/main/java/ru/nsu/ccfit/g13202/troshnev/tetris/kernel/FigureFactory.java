package ru.nsu.ccfit.g13202.troshnev.tetris.kernel;

import ru.nsu.ccfit.g13202.troshnev.tetris.figures.AbstractFigure;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/**
 * Created by zerlok on 4/29/15.
 */

public class FigureFactory {
    private FigureBox figureBox;

    public FigureFactory() {
        figureBox = new FigureBox();
    }

    public AbstractFigure createRandomFigure() {
        return figureBox.pop();
    }

    public void configure() throws IOException {
        Properties prop = new Properties();
        InputStream inputStream = getClass().getClassLoader().getResourceAsStream("figures.properties");

        if (inputStream == null)
            throw new FileNotFoundException("Cannot find figures.properties file.");

        prop.load(inputStream);
        System.out.println(String.format("figure.properties size: %1$d", prop.size()));
        String figuresFolderPath = prop.getProperty("folder");
        AbstractFigure figurePrototype;

        for (String key : prop.stringPropertyNames()) {
            if (!key.contentEquals("folder")) {
                figurePrototype = null;
                String value = prop.getProperty(key);

                try {
                    figurePrototype = (AbstractFigure)Class.forName(String.format("%1$s.%2$s", figuresFolderPath, value)).newInstance();

                } catch (InstantiationException e) {
                    e.printStackTrace();
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                } catch (ClassNotFoundException e) {
                    e.printStackTrace();
                }

                if (figurePrototype != null)
                    figureBox.push(figurePrototype);
            }
        }

        figureBox.shuffle();
    }
}
