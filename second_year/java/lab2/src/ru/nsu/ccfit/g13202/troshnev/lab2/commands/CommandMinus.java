package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.EmptyStorageException;

import java.io.IOException;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandMinus extends Command {

    private Double minuend;
    private Double subtrahend;

    public CommandMinus(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws Exception {
        Double[] values = calcContext.getValues(2);

        if (values == null)
            return false;

        minuend = values[0];
        subtrahend = values[1];

        return true;
    }

    @Override
    public void execute(String[] arguments) throws Exception {
        if ((minuend == null) || (subtrahend == null))
            throw new UnvalidatedCommandExecutionException();

        calcContext.pushValue((minuend - subtrahend));
    }
}
