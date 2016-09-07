package ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra;

import java.io.IOException;
import org.apache.log4j.Logger;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;


/**
 * Created by zerlok on 4/22/15.
 */

public class CommandDefine extends Command {

    private static final Logger LOG = Logger.getLogger(CommandDefine.class.getName());
    private String name;
    private Double value;

    public CommandDefine(Context ctx) {
        super(ctx);
    }

    public boolean isValid(String[] arguments) throws IOException {
        if ((arguments.length != 3)
                || calcContext.isDefined(arguments[1]))
            return false;

        try {
            value = Double.valueOf(arguments[2]);
            name = arguments[1];

        } catch (NumberFormatException e) {
            return false;
        }

        return true;
    }

    public void execute() {
        LOG.info(String.format("New variable definition: %1$s = %2$f", name, value));
        calcContext.defineVar(name, value);
    }
}
