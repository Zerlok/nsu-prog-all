package WordCounter;


/**
 * Created by zerlok on 3/11/15.
 */


public class WordFormatter {

    public WordFormatter(WordCounter counter) {
        wordsCounter = counter;
    }

    public String toScreen(String word, String freq) {
        return String.format(formatScreen,
                word,
                freq);
    }

    public String toCSV(String word, String freq) {
        return String.format(formatCSV,
                word,
                freq,
                Double.parseDouble(freq) / new Double(wordsCounter.getWordsNum()) * 100.0);
    }

    static private String formatScreen = "%1$s : %2$s\n";
    static private String formatCSV = "%1$s|%2$s|%3$.2f\n";

    private WordCounter wordsCounter;
}
