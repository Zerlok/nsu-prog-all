package WordCounter;


import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;


/**
 * Created by zerlok on 3/11/15.
 */


public class Controller {

    static public void run(String[] args)
    {
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

            if (!output.exists())
                output.createNewFile();

            WordCounter counter = new WordCounter();
            WordParser parser = new WordParser(input, counter);
            WordFormatter formatter = new WordFormatter(counter);
            WordView view = new WordView(counter, formatter);

            parser.readWords();

            view.printToFile(output);

            System.out.println("Done.");

        } catch (FileNotFoundException e) {
            System.out.println("File not found!");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
