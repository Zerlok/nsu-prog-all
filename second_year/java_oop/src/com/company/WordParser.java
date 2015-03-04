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
                    wordsCounter.pushWord(word);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String spacesPattern = "((\\W|[_])*\\s+(\\W|[_])*)|((\\W|[_])+$)";

    private BufferedReader fileBuffer;
    private WordCounter wordsCounter;
}
