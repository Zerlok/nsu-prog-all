package WordCounter;


import java.io.*;


/**
 * The WordParser class parses words from input and
 * inserts them into the word-storage.
 */
public class WordParser {

    private WordReader inputReader;
    private WordCounter wordsCounter;

    public WordParser(WordReader input, WordCounter counter) {
        inputReader = input;
        wordsCounter = counter;
    }

    /**
     * Parses words from input and inserts them into word-storage.
     */
    public void readWords() throws IOException {
        // Temp char.
        int chr;

        // Temp word.
        StringBuilder word = new StringBuilder();

        // Do parsing, while inputReader returns valid chars.
        while ((chr = inputReader.getNextChar()) != -1) {

            // If the char is a letter or digit, insert it into the word.
            if (Character.isLetterOrDigit(chr)) {
                word.append((char) chr);

            // Otherwise, if length of the word not zero,
            // push the word into the storage
            } else if (word.length() != 0) {
                wordsCounter.pushWord(word.toString());

                // Create an empty string.
                word = new StringBuilder();
            }
        }

        inputReader.closeReader();
    }
}
