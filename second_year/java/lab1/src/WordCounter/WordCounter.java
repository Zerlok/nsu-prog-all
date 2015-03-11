package WordCounter;

import java.util.Comparator;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;


/**
 * Created by zerlok on 3/4/15.
 */


public class WordCounter {

    private int wordsNum;
    private Map<String, Integer> wordsMap;

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
        return wordsMap;
    }

    public int getWordsNum() {
        return wordsNum;
    }
}