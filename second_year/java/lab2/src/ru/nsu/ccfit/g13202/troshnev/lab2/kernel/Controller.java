package ru.nsu.ccfit.g13202.troshnev.lab2.kernel;

import java.io.IOException;
import org.apache.log4j.Logger;
import ru.nsu.ccfit.g13202.troshnev.lab2.InputParser;
import ru.nsu.ccfit.g13202.troshnev.lab2.InputReader;
import ru.nsu.ccfit.g13202.troshnev.lab2.OutputWriter;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.*;

/**
 * The Controller class is a logic of the calculator program.
 */

public class Controller {

    private static final Logger LOG = Logger.getLogger(Controller.class.getName());

    private InputParser calcParser;
    private View calcViewer;
    private Context calcContext;
    private CommandFactory calcCommandFactory;

    public Controller(InputReader reader, OutputWriter writer) throws IOException {
        LOG.info("Creating the calculator controller ...");

        calcParser = new InputParser(reader);
        calcViewer = new View(writer);
        calcContext = new Context(new ValueStorage(), new VariableStorage(), calcViewer);
        calcCommandFactory = new CommandFactory(calcContext);
        calcCommandFactory.configure();

        LOG.info("Calculator controller created.");
    }

    public void run() throws IOException {
        LOG.info("Running the calculator ...");
        Command calcCmd;

        try {
            while (calcParser.isIntact()) {
                String[] args = calcParser.parseLine();

                if (args.length == 0)
                    continue;

                try {
                    // Create the command.
                    calcCmd = calcCommandFactory.createCommand(args[0]);

                    // Execute the command if it is valid.
                    if (calcCmd.isValid(args)) {
                        LOG.info(String.format("Executing the %1s command ...", calcCmd.getClass().getName()));
                        calcCmd.execute();

                    // Return values back, if command is invalid.
                    } else {
                        LOG.warn("Command validation failed - reverting values back in storage.");
                        calcCmd.revert();
                    }

                } catch (CommandException e) {
                    calcContext.println(e.getMessage());
                }
            }

        } catch (CalculatorException e) {
            e.printStackTrace();
        }

        LOG.info("Calculator stopped.");
    }
}