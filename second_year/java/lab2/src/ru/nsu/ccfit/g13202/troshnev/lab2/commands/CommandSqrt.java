package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.EmptyStorageException;

import java.io.IOException;


/**
 * Created by zerlok on 4/22/15.
 */


public class CommandSqrt extends Command {
    private Double value;

    public CommandSqrt(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws Exception {
        value = calcContext.getValues(1)[0];

        if (value < 0.0)
            throw new NegativeValueException();

        return true;
    }

    @Override
    public void execute(String[] arguments) throws Exception {
        calcContext.pushValue(Math.sqrt(value));
    }

    @Override
    public void revert() {
        calcContext.pushValue(value);
    }
}
