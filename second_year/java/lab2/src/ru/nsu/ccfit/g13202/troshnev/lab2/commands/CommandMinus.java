package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;

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
    public boolean isValid(String[] arguments) throws IOException {
        Double[] values = calcContext.getValues(2);

        minuend = values[0];
        subtrahend = values[1];

        return true;
    }

    @Override
    public void execute(String[] arguments) throws IOException {
        calcContext.pushValue((minuend - subtrahend));
    }
}
