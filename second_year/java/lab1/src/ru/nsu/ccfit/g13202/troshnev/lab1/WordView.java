package ru.nsu.ccfit.g13202.troshnev.lab1;


import java.io.IOException;
import java.util.Map;
import java.util.TreeMap;


/**
 * WordView class writes word storage information
 * into the WordWriter (output).
 */
public class WordView {

    private WordCounter wordsCounter;
    private WordWriter wordWriter;

    public WordView(WordWriter writer, WordCounter counter) {
        wordWriter = writer;
        wordsCounter = counter;
    }

    public void printToCSV() throws IOException {
        // Temp array of strings.
        String[] stringPair;

        // Get words amount number in float (required for divination).
        Double wordsNum = new Double(wordsCounter.getWordsNum());

        // Write each pair (word, frequency) into the output.
        for (Object pair : getSortedTable().entrySet()) {

            // Split pair by equals symbol.
            stringPair = pair.toString().split("=");

            // Write info into output (format: word|frequency|percentage).
            wordWriter.write(String.format("%1$s|%2$s|%3$.4f\n", stringPair[0], stringPair[1], Double.parseDouble(stringPair[1]) / wordsNum * 100.0));
        }

        wordWriter.closeWriter();
    }

    /**
     * Returns the table of words, ordered by word frequency.
     */
    private Map getSortedTable() {
        // Get the table from the word storage.
        Map wordsMap = wordsCounter.getWordsTable();

        // Create a new table, which uses WordComparator,
        // when pushes data into it.
        Map<String, Integer> sortedTable = new TreeMap<String, Integer>(new WordComparator(wordsMap));

        // Push whole word table into sortedTable.
        sortedTable.putAll(wordsMap);

        return sortedTable;
    }

}
