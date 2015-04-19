import java.io.IOException;
import java.util.Vector;


/**
 * Created by zerlok on 3/25/15.
 */


public class InputParser {

    private boolean isIntact = true;
    private InputReader streamReader;

    public InputParser(InputReader reader) {
        streamReader = reader;
    }

    public boolean isIntact() {
        return isIntact;
    }

    public String[] parseLine() throws IOException {
        String line = streamReader.getLine();

        if (line == null) {
            isIntact = false;
            return new String[] {};
        }

        return line.split(" ");
    }
}
