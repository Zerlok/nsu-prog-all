package com.company;


import com.sun.xml.internal.ws.api.pipe.ServerPipeAssemblerContext;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Set;


/**
 * Created by zerlok on 3/4/15.
 */


public class WordView {

    public WordView(WordCounter counter) {
        wordsCounter = counter;
    }

    public void summarize() {
        Set wordsArray = wordsCounter.getWordsTable().entrySet();

        for (Object pair : wordsArray) {
            System.out.println(pair.toString().replace("=", " : "));
        }

        System.out.println("\nUnique words num: " + wordsArray.size());
        System.out.println("Total words num: " + wordsCounter.getWordsNum());
    }

    public void summarizeIntoFile(File file) throws IOException {
        String[] stringPair;
        BufferedWriter bufferWriter = new BufferedWriter(new FileWriter(file.getAbsoluteFile()));
        Set wordsArray = wordsCounter.getWordsTable().entrySet();
        Double wordsNum = new Double(wordsCounter.getWordsNum());

        for (Object pair : wordsArray) {
            stringPair = pair.toString().split("=");
            bufferWriter.write(stringPair[0] + SEPARATOR + stringPair[1] + SEPARATOR + Double.parseDouble(stringPair[1]) / wordsNum * 100.0 + LINE_END);
        }

        bufferWriter.close();
    }

    private static String SEPARATOR = "|";
    private static String LINE_END = "\n";
    private WordCounter wordsCounter;
}
