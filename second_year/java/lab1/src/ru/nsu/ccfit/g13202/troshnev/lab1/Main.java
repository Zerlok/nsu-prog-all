package ru.nsu.ccfit.g13202.troshnev.lab1;


import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;


/**
 * The main class checks input arguments and
 * creates WordReader and WordWriter, then sends
 * them into Controller, which will do the rest.
 */
public class Main {

    public static void main(String[] args) {
        try {
            // Check arguments length (two arguments required)
            if (args.length > 2) {
                System.out.println("Too many arguments, required file paths: [input] [output]");
                return;

            } else if (args.length < 2) {
                System.out.println("Too few arguments, required file paths: [input] [output]");
                return;
            }

            // Create input and output file for WordReader and WordWriter accordingly.
            File input = new File(args[0]);
            File output = new File(args[1]);

            // Check for input file existence.
            if (!input.exists())
                throw new FileNotFoundException(input.getAbsolutePath());

            // Check for input file read permission.
            if (!input.canRead())
                throw new Exception("Can't read file: " + input.getAbsolutePath());

            // Check for output file existence.
            if (!output.exists())
                // Create a new output file, if not exists.
                output.createNewFile();

            // Check for output file write permission.
            if (!output.canWrite())
                throw new Exception("Can't write into file: " + output.getAbsolutePath());

            // Create and run the controller.
            Controller wordController = new Controller(new WordReader(input), new WordWriter(output));
            wordController.run();

            System.out.println("Done.");

        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + e.getMessage());

        } catch (IOException e) {
            System.out.println("I/O Exception: " + e.getMessage());

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}