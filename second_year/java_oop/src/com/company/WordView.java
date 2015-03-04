package com.company;


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

    private WordCounter wordsCounter;
}
