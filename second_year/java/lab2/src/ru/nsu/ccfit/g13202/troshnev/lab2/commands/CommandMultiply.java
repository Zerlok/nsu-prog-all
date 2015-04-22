package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;

import java.io.IOException;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandMultiply extends Command {

    private Double first_multiplicand;
    private Double second_multiplicand;

    public CommandMultiply(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws IOException {
        Double[] values = calcContext.getValues(2);

        first_multiplicand = values[0];
        second_multiplicand = values[1];

        return true;
    }

    @Override
    public void execute(String[] arguments) throws IOException {
        calcContext.pushValue((first_multiplicand * second_multiplicand));
    }
}
