import java.io.*;


/**
 * Created by zerlok on 3/25/15.
 */


public class InputReader {

    private BufferedReader fileBuffer;

    public InputReader(File input) throws FileNotFoundException {
        fileBuffer = new BufferedReader(new FileReader(input.getAbsolutePath()));
    }

    public int getNextChar() throws IOException {
        return fileBuffer.read();
    }

    public void closeReader() throws IOException {
        fileBuffer.close();
    }
}
