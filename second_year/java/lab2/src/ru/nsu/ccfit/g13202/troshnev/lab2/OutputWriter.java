package ru.nsu.ccfit.g13202.troshnev.lab2;

import java.io.*;


/**
 * Created by zerlok on 3/25/15.
 */


public class OutputWriter {

    private BufferedWriter bufferWriter;

    public OutputWriter(OutputStream output) {
        bufferWriter = new BufferedWriter(new OutputStreamWriter(output));
    }

    public OutputWriter(File output) throws IOException {
        bufferWriter = new BufferedWriter(new FileWriter(output.getAbsoluteFile()));;
    }

    public void write(String str) throws IOException {
        bufferWriter.write(str);
    }

    public void closeWriter() throws IOException {
        bufferWriter.close();
    }
}


