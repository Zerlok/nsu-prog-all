package ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra;

import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.UndefinedVariableException;

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
    public boolean isValid(String[] arguments) throws IOException, UndefinedVariableException {
        if (arguments.length != 2)
            return false;

        try {
            value = (double) Double.valueOf(arguments[1]);

        } catch (NumberFormatException e) {
            value = calcContext.getVarValue(arguments[1]);
        }

        return true;
    }

    @Override
    public void execute() throws UnvalidatedCommandExecutionException {
        if (value == null)
            throw new UnvalidatedCommandExecutionException();

        calcContext.pushValue(value);
    }
}
