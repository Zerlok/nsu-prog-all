package WordCounter;


import java.io.*;


/**
 * WordReader class represents as a bufferedReader, but
 * it may have rewritten methods, to read data from other input.
 */
public class WordReader {

    private BufferedReader fileBuffer;

    public WordReader(File input) throws FileNotFoundException {
        fileBuffer = new BufferedReader(new FileReader(input.getAbsolutePath()));
    }

    public int getNextChar() throws IOException {
        return fileBuffer.read();
    }

    public void closeReader() throws IOException {
        fileBuffer.close();
    }
}
