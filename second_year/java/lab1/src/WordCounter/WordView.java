package WordCounter;


import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Set;


/**
 * Created by zerlok on 3/4/15.
 */


public class WordView {

    public WordView(WordCounter counter, WordFormatter formatter) {
        wordsCounter = counter;
        wordFormatter = formatter;
    }

    public void printToScreen() {
        String[] stringPair;
        Set wordsArray = wordsCounter.getWordsTable().entrySet();

        for (Object pair : wordsArray) {
            stringPair = pair.toString().split("=");
            System.out.println(wordFormatter.toScreen(stringPair[0], stringPair[1]));
        }

        System.out.println("Unique words num: " + wordsArray.size());
        System.out.println("Total words num: " + wordsCounter.getWordsNum());
    }

    public void printToFile(File file) throws IOException {
        String[] stringPair;
        BufferedWriter bufferWriter = new BufferedWriter(new FileWriter(file.getAbsoluteFile()));
        Set wordsArray = wordsCounter.getWordsTable().entrySet();

        for (Object pair : wordsArray) {
            stringPair = pair.toString().split("=");
            bufferWriter.write(String.format(wordFormatter.toCSV(stringPair[0], stringPair[1])));
        }

        bufferWriter.close();
    }

    private WordCounter wordsCounter;
    private WordFormatter wordFormatter;
}
