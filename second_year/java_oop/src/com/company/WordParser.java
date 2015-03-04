package com.company;


import java.io.BufferedReader;
import java.io.IOException;


/**
 * Created by zerlok on 3/4/15.
 */


public class WordParser {

    public WordParser(BufferedReader buffer, WordCounter counter) {
        fileBuffer = buffer;
        wordsCounter = counter;
    }

    public void readWords() {
        try {
            String line;
            String[] wordsArray;

            while ((line = fileBuffer.readLine()) != null) {
                if (line.isEmpty()) continue;

                wordsArray = line.split(spacesPattern);

                for (String word : wordsArray) {
                    if (!word.isEmpty()) {
                        wordsCounter.pushWord(word);
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String spacesPattern = "(^(\\W|[_])+)|((\\W|[_])*\\s+(\\W|[_])*)|((\\W|[_])+$)";
    // The following spacesPattern does not work,
    // because the underscore symbol represents as a word symbol O_o
    // private static String spacesPattern = "(^\\W+)|(\\W*\\s+\\W*)|(\\W+$)";

    private BufferedReader fileBuffer;
    private WordCounter wordsCounter;
}
