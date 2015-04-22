package ru.nsu.ccfit.g13202.troshnev.lab2;

import org.apache.log4j.Logger;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.*;

import java.io.IOException;


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
        LOG.info("Creating the calculator controller ...");

        calcParser = new InputParser(reader);
        calcViewer = new View(writer);
        calcContext = new Context(new ValueStorage(), new VariableStorage(), calcViewer);
        calcCommandFactory = new CommandFactory(calcContext);

        LOG.info("Start commands registration ...");
        calcCommandFactory.registerCommand("+", CommandPlus.class);
        calcCommandFactory.registerCommand("-", CommandMinus.class);
        calcCommandFactory.registerCommand("*", CommandMultiply.class);
        calcCommandFactory.registerCommand("/", CommandDivide.class);
        calcCommandFactory.registerCommand("SQRT", CommandSqrt.class);
        calcCommandFactory.registerCommand("DEFINE", CommandDefine.class);
        calcCommandFactory.registerCommand("PRINT", CommandPrint.class);
        calcCommandFactory.registerCommand("PUSH", CommandPush.class);
        calcCommandFactory.registerCommand("POP", CommandPop.class);
        calcCommandFactory.registerCommand("HELP", CommandHelp.class);

        LOG.info("Calculator controller created.");
    }

    public void run() throws IOException {
        LOG.info("Running the calculator ...");
        Command calcCmd;

        while (calcParser.isIntact()) {
            String[] args = calcParser.parseLine();

            if (args.length == 0)
                continue;

            calcCmd = calcCommandFactory.createCommand(args[0]);

            try {
                // Execute the command if it is valid.
                if (calcCmd.isValid(args)) {
                    LOG.info(String.format("Executing the %1s command ...", calcCmd.getClass().getName()));
                    calcCmd.execute(args);

                // Return values back, if command is invalid.
                } else {
                    LOG.info("Reverting the values back into the stack ...");
                    calcCmd.revert();
                }

            } catch (Exception e) {
                calcContext.println(e.getMessage());
            }
        }

        LOG.info("Calculator stopped.");
    }
}