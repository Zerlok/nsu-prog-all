import java.io.IOException;
import org.apache.log4j.Logger;


/**
 * The Controller class is a logic of the calculator program.
 */


public class Controller {

    private static final Logger LOG = Logger.getLogger(Controller.class.getName());

    private InputParser calcParser;
    private View calcViewer;
    private Context calcContext;
    private CommandFactory calcCommandFactory;

    public Controller(InputReader reader, OutputWriter writer) {
        LOG.debug("Creating the controller.");

        calcParser = new InputParser(reader);
        calcViewer = new View(writer);
        calcContext = new Context(new ValueStorage(), new VariableStorage(), calcViewer);
        calcCommandFactory = new CommandFactory(calcContext);

        LOG.info("Start commands registration ...");
        calcCommandFactory.registerCommand("HELP", HelpCommand.class);
    }

    public void run() throws IOException {
        Command calcCmd;

        while (calcParser.isIntact()) {
            String[] args = calcParser.parseLine();

            if (args.length == 0)
                continue;

            calcCmd = calcCommandFactory.createCommand(args[0]);

            // Execute the command if it is valid.
            if (calcCmd.isValid()) {
                LOG.info("Executing the %1s command ...".format(calcCmd.getClass().getName()));
                calcCmd.execute(args);

            // Return values back, if command is invalid.
            } else {
                LOG.info("Reverting the values back into the stack ...");
                calcCmd.revert();
            }
        }

        LOG.info("Done.");
    }
}