package ru.nsu.ccfit.g13202.troshnev.lab1;


import java.util.HashMap;
import java.util.Map;


/**
 * WordCounter class is a container, which holds information
 * about words frequency and amount of them.
 */
public class WordCounter {

    private int wordsNum;
    private Map<String, Integer> wordsMap;

    public WordCounter() {
        wordsNum = 0;

        // String: word, Integer: word frequency.
        wordsMap = new HashMap<String, Integer>();
    }

    /**
     * Pushes word into the storage.
     */
    public void pushWord(String word) {
        // Increase the words counter.
        wordsNum += 1;

        // Convert word into lowercase.
        word = word.toLowerCase();

        // If this word already placed in the storage, increase the counter.
        if (wordsMap.containsKey(word)) {
            wordsMap.put(word, wordsMap.get(word) + 1);

        // Otherwise, put word into the storage with a counter: 1.
        } else {
            wordsMap.put(word, 1);
        }
    }

    /**
     * Returns word storage.
     */
    public Map getWordsTable() {
        return wordsMap;
    }

    /**
     * Returns word's amount number.
     */
    public int getWordsNum() {
        return wordsNum;
    }
}