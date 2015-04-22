package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import org.apache.log4j.Logger;
import ru.nsu.ccfit.g13202.troshnev.lab2.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.UndefinedVariableException;

import java.io.IOException;


/**
 * Created by zerlok on 4/22/15.
 */


public class CommandPush extends Command {

    Double value;

    public CommandPush(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws Exception {
        if (arguments.length != 2)
            return false;

        try {
            value = (double) Double.valueOf(arguments[1]);

        } catch (NumberFormatException e) {
            value = calcContext.getVarValue(arguments[1]);
        }

        return true;
    }
}
