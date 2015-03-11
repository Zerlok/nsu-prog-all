package WordCounter;


import java.io.*;


/**
 * Created by zerlok on 3/11/15.
 */


public class WordReader {

    public WordReader(File input) throws FileNotFoundException {
        fileBuffer = new BufferedReader(new FileReader(input.getAbsolutePath()));
    }

    public int getNextChar() throws IOException {
        return fileBuffer.read();
    }

    public void closeReader() throws IOException {
        fileBuffer.close();
    }

    private BufferedReader fileBuffer;
}
