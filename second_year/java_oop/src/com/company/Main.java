package com.company;


import java.io.*;


public class Main {

    public static void main(String[] args) {
        if (args.length > 2) {
            System.out.println("Too many arguments, required file paths: [input] [output]");
            return;

        } else if (args.length < 2) {
            System.out.println("Too few arguments, required file paths: [input] [output]");
            return;
        }

        try {
            File input= new File(args[0]);
            File output = new File(args[1]);

            if (!output.exists()){
                output.createNewFile();
            }

            WordCounter counter = new WordCounter();
            WordParser parser = new WordParser(input, counter);
            WordView view = new WordView(counter);

            parser.readWords();

            view.summarizeIntoFile(output);

            System.out.println("Done.");

        } catch (FileNotFoundException e) {
            System.out.println("File not found!");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}