package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import java.io.IOException;
import org.apache.log4j.Logger;
import ru.nsu.ccfit.g13202.troshnev.lab2.Context;


/**
 * Created by zerlok on 4/22/15.
 */

public class CommandDefine extends Command {

    private static final Logger LOG = Logger.getLogger(CommandDefine.class.getName());

    public CommandDefine(Context ctx) {
        super(ctx);
    }

    public boolean isValid(String[] arguments) throws IOException {
        if (arguments.length != 3)
            return false;

        return true;
    }

    public void execute(String[] arguments) throws IOException {
        LOG.info(String.format("New variable definition: %1$s = %2$s", arguments[1], arguments[2]));
        calcContext.defineVar(arguments[1], Double.valueOf(arguments[2]));
    }
}
