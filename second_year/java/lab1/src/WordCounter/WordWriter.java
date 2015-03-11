package WordCounter;


import java.io.*;


/**
 * Created by zerlok on 3/11/15.
 */


public class WordWriter {

    public WordWriter(File output) throws IOException {
        bufferWriter = new BufferedWriter(new FileWriter(output.getAbsoluteFile()));;
    }

    public void write(String str) throws IOException {
        bufferWriter.write(str);
    }

    public void closeWriter() throws IOException {
        bufferWriter.close();
    }

    private BufferedWriter bufferWriter;
}
