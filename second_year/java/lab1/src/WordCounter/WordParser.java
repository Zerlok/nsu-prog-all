package WordCounter;


import java.io.*;


/**
 * Created by zerlok on 3/4/15.
 */


public class WordParser {

    public WordParser(WordReader input, WordCounter counter) {
        inputReader = input;
        wordsCounter = counter;
    }

    public void readWords() throws IOException {
        int chr;
        StringBuilder word = new StringBuilder();

        while ((chr = inputReader.getNextChar()) != -1) {
            if (Character.isLetterOrDigit(chr)) {
                word.append((char) chr);

            } else if (word.length() != 0) {
                wordsCounter.pushWord(word.toString());
                word = new StringBuilder();
            }
        }

        inputReader.closeReader();
    }

    private WordReader inputReader;
    private WordCounter wordsCounter;
}
