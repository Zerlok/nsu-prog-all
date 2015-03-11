package WordCounter;


import java.io.IOException;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;


/**
 * Created by zerlok on 3/4/15.
 */


public class WordView {

    private WordCounter wordsCounter;
    private WordWriter wordWriter;

    public WordView(WordCounter counter, WordWriter writer) {
        wordsCounter = counter;
        wordWriter = writer;
    }

    public void printToCSV() throws IOException {
        String[] stringPair;
        Double wordsNum = new Double(wordsCounter.getWordsNum());
        Set wordsArray = getSortedTabe().entrySet();

        for (Object pair : wordsArray) {
            stringPair = pair.toString().split("=");
            wordWriter.write(String.format("%1$s|%2$s|%3$.4f\n", stringPair[0], stringPair[1], Double.parseDouble(stringPair[1]) / wordsNum * 100.0));
        }

        wordWriter.closeWriter();
    }

    private Map getSortedTabe() {
        Map wordsMap = wordsCounter.getWordsTable();
        Map<String, Integer> sortedTable = new TreeMap<String, Integer>(new WordComparator(wordsMap));
        sortedTable.putAll(wordsMap);

        return sortedTable;
    }

}
