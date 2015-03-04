package com.company;


import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;


/**
 * Created by zerlok on 3/4/15.
 */


public class WordCounter {

    public WordCounter() {
        wordsNum = 0;
        wordsMap = new HashMap<String, Integer>();
    }

    public void pushWord(String word) {
        wordsNum += 1;

        word = word.toLowerCase();

        if (wordsMap.containsKey(word)) {
            wordsMap.put(word, wordsMap.get(word) + 1);

        } else {
            wordsMap.put(word, 1);
        }
    }

    public Map getWordsTable() {
        Map<String, Integer> sortedTable = new TreeMap<String, Integer>(new ValueComparator(wordsMap));
        sortedTable.putAll(wordsMap);

        return sortedTable;
    }

    public int getWordsNum() {
        return wordsNum;
    }

    private int wordsNum;
    private Map<String, Integer> wordsMap;
}


// Thanks for stackoverflow (compare method was rewrited):
// http://stackoverflow.com/questions/109383/how-to-sort-a-mapkey-value-on-the-values-in-java
class ValueComparator implements Comparator<String> {

    public ValueComparator(Map<String, Integer> base) {
        baseMap = base;
    }

    public int compare(String keyA, String keyB) {
        int valA = baseMap.get(keyA);
        int valB = baseMap.get(keyB);

        if (valA > valB) {
            return -1;

        } else if (valA < valB){
            return 1;

        } else {
            return (keyA.compareTo(keyB));
        }
    }

    private Map<String, Integer> baseMap;
}
