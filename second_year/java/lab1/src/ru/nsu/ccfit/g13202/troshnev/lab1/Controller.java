package ru.nsu.ccfit.g13202.troshnev.lab1;


import java.io.IOException;


/**
 * The Controller class is a logic of the word counter program.
 * It takes WordReader object to take data from it and
 * WordWriter object to put data into it.
 */
public class Controller {

    private WordReader inputReader;
    private WordWriter outputWriter;

    public Controller(WordReader input, WordWriter output) {
        inputReader = input;
        outputWriter = output;
    }

    public void run() throws IOException {
        // Create the word-storage object.
        WordCounter counter = new WordCounter();

        // Create the word parser (takes data-input and word-storage objects).
        WordParser parser = new WordParser(inputReader, counter);

        // Create a word viewer (takes data-output and word-storage objects).
        WordView view = new WordView(outputWriter, counter);

        // Parse words from input.
        parser.readWords();

        // Show parsed words in CSV format.
        view.printToCSV();
    }
}
