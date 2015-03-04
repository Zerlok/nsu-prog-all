package com.company;


import java.io.*;


/**
 * Created by zerlok on 3/4/15.
 */


public class WordParser {

    public WordParser(File inputFile, WordCounter counter) {
        file = inputFile;
        wordsCounter = counter;
    }

    public void readWords() {
        try {
            String line;
            String[] wordsArray;
            BufferedReader fileBuffer = new BufferedReader(new FileReader(file.getAbsolutePath()));

            while ((line = fileBuffer.readLine()) != null) {
                if (line.isEmpty()) continue;

                wordsArray = line.split(spacesPattern);

                for (String word : wordsArray) {
                    if (!word.isEmpty()) {
                        wordsCounter.pushWord(word);
                    }
                }
            }

        } catch (FileNotFoundException e) {
            System.out.println("File " + file.getAbsolutePath() + " not found!");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String spacesPattern = "(^(\\W|[_])+)|((\\W|[_])*\\s+(\\W|[_])*)|((\\W|[_])+$)";
    // The following spacesPattern does not work,
    // because the underscore symbol represents as a word symbol O_o
    // private static String spacesPattern = "(^\\W+)|(\\W*\\s+\\W*)|(\\W+$)";

    private File file;
    private WordCounter wordsCounter;
}
