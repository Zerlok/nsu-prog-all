package com.company;


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;


public class Main {

    public static void main(String[] args) {
        try {
            FileReader file = new FileReader(args[0]);
            BufferedReader buffer = new BufferedReader(file);

            WordCounter counter = new WordCounter();
            WordParser parser = new WordParser(buffer, counter);
            WordView view = new WordView(counter);

            parser.readWords();

            view.summarize();

        } catch (FileNotFoundException e) {
            e.printStackTrace();

        }
    }
}