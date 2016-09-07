package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.CalculatorException;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.UndefinedVariableException;

import java.io.IOException;


/**
 * Created by zerlok on 3/25/15.
 */


public abstract class Command {

    protected Context calcContext;

    public Command(Context ctx) {
        calcContext = ctx;
    }

    public boolean isValid(String[] arguments) throws IOException, CommandException, UndefinedVariableException {
        return true;
    }

    public void execute() throws IOException, CommandException {
        calcContext.println("Command doesn't have the declaration what to do.");
    }

    public void revert() {}
}
