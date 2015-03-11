package WordCounter;


import java.util.Comparator;
import java.util.Map;


/**
 * WordComparator class compares two words by theirs
 * frequency number.
 */
class WordComparator implements Comparator<String> {

    private Map<String, Integer> baseMap;

    public WordComparator(Map<String, Integer> base) {
        baseMap = base;
    }

    // Compare words decreasingly (from bigger to lower).
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
