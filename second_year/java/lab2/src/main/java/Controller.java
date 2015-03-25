import java.io.IOException;


/**
 * The Controller class is a logic of the calculator program.
 */


public class Controller {

    private InputParser parser;
    private View viewer;

    public Controller(InputReader reader, OutputWriter writer) {
        System.out.println("Creating the controller.");

        parser = new InputParser(reader);
        viewer = new View(writer);
    }

    public void run() throws IOException {
        boolean isWorking = true;

//        while (isWorking) {
//
//        }
    }
}