package WordCounter;


import java.io.*;


/**
 * WordWriter class represents as a bufferedWriter, but
 * it may have rewritten methods, to write data into other output.
 */
public class WordWriter {

    private BufferedWriter bufferWriter;

    public WordWriter(File output) throws IOException {
        bufferWriter = new BufferedWriter(new FileWriter(output.getAbsoluteFile()));;
    }

    public void write(String str) throws IOException {
        bufferWriter.write(str);
    }

    public void closeWriter() throws IOException {
        bufferWriter.close();
    }
}
