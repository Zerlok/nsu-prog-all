package ru.nsu.ccfit.g13202.troshnev.lab2;

import java.io.IOException;

/**
 * Created by zerlok on 3/25/15.
 */
public class View {

    private OutputWriter streamOutput;

    public View(OutputWriter writer) {
        streamOutput = writer;
    }

    public void show(String line) throws IOException{
        streamOutput.write(line);
    }
}
