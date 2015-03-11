package WordCounter;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {
        try {
            if (args.length > 2) {
                System.out.println("Too many arguments, required file paths: [input] [output]");
                return;

            } else if (args.length < 2) {
                System.out.println("Too few arguments, required file paths: [input] [output]");
                return;
            }

            File input = new File(args[0]);
            File output = new File(args[1]);

            if (!input.exists())
                throw new FileNotFoundException(input.getAbsolutePath());

            if (!input.canRead())
                throw new Exception("Can't read file: " + input.getAbsolutePath());

            if (!output.exists())
                output.createNewFile();

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