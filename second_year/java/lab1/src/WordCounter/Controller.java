package WordCounter;


import java.io.IOException;


/**
 * Created by zerlok on 3/11/15.
 */


public class Controller {

    private WordReader inputReader;
    private WordWriter outputWriter;

    public Controller(WordReader input, WordWriter output) {
        inputReader = input;
        outputWriter = output;
    }

    public void run() throws IOException {
        WordCounter counter = new WordCounter();
        WordParser parser = new WordParser(inputReader, counter);
        WordView view = new WordView(counter, outputWriter);

        parser.readWords();

        view.printToCSV();
    }
}
