package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;

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
    public boolean isValid(String[] arguments) throws IOException {
        value = calcContext.getValues(1)[0];

        // TODO: Throw exception (negative value).
        if (value < 0.0)
            return false;

        return true;
    }

    @Override
    public void execute(String[] arguments) throws IOException {
        calcContext.pushValue(Math.sqrt(value));
    }

    @Override
    public void revert() {
        calcContext.pushValue(value);
    }
}
