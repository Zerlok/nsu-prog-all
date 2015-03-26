import java.io.IOException;


/**
 * The Controller class is a logic of the calculator program.
 */


public class Controller {

    private InputParser calcParser;
    private View calcViewer;
    private Context calcContext;
    private CommandFactory calcCommandFactory;

    public Controller(InputReader reader, OutputWriter writer) {
        System.out.println("Creating the controller.");

        calcParser = new InputParser(reader);
        calcViewer = new View(writer);
        calcContext = new Context(new ValueStorage(), new VariableStorage(), calcViewer);
        calcCommandFactory = new CommandFactory(calcContext);

        calcCommandFactory.registerCommand("HELP", HelpCommand.class);
    }

    public void run() throws IOException {
        Command calcCmd;

        while (calcParser.isIntact()) {
            calcCmd = calcCommandFactory.createCommand(calcParser.parseLine());

            // If command is valid, then execute it.
            if (calcCmd.isValid()) {
                calcCmd.execute();

            // If command is invalid, then return values back.
            } else {
                calcCmd.revert();
            }
        }
    }
}