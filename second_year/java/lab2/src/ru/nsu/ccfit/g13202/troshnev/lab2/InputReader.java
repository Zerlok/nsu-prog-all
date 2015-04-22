package ru.nsu.ccfit.g13202.troshnev.lab2;

import java.io.*;


/**
 * Created by zerlok on 3/25/15.
 */


public class InputReader {

    private BufferedReader fileBuffer;

    public InputReader(File input) throws FileNotFoundException {
        fileBuffer = new BufferedReader(new FileReader(input.getAbsolutePath()));
    }

    public String getLine() throws IOException {
        return fileBuffer.readLine();
    }

    public void closeReader() throws IOException {
        fileBuffer.close();
    }
}
