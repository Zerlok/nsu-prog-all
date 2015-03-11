package WordCounter;


import java.util.Comparator;
import java.util.Map;


/**
 * Created by zerlok on 3/11/15.
 */


// Thanks for stackoverflow (compare method was rewrited):
// http://stackoverflow.com/questions/109383/how-to-sort-a-mapkey-value-on-the-values-in-java
class WordComparator implements Comparator<String> {

    private Map<String, Integer> baseMap;

    public WordComparator(Map<String, Integer> base) {
        baseMap = base;
    }

    public int compare(String keyA, String keyB) {
        int valA = baseMap.get(keyA);
        int valB = baseMap.get(keyB);

        if (valA > valB) {
            return -1;

        } else {
            return 1;
        }
    }
}
