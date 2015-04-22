package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import org.apache.log4j.Logger;
import ru.nsu.ccfit.g13202.troshnev.lab2.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.UndefinedVariableException;

import java.io.IOException;


/**
 * Created by zerlok on 4/22/15.
 */


public class CommandPush extends Command {

    private static final Logger LOG = Logger.getLogger(CommandDefine.class.getName());

    public CommandPush(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws Exception {
        if (arguments.length != 2)
            return false;

        return true;
    }

    @Override
    public void execute(String[] arguments) throws Exception {
        LOG.info(String.format("Pushing %1$s into stack", arguments[1]));

        Double value;

        try {
            value = (double) Double.valueOf(arguments[1]);

        } catch (NumberFormatException e) {
            value = calcContext.getVarValue(arguments[1]);
        }

        calcContext.pushValue(value);
    }
}
