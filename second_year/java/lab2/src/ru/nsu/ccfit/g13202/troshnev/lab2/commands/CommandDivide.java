package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;

import java.io.IOException;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandDivide extends Command {

    private Double numerator;
    private Double denominator;

    public CommandDivide(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws IOException {
        Double[] values = calcContext.getValues(2);
        numerator = values[0];
        denominator = values[1];

        // TODO: throw zero division exception.
        if (denominator == 0.0) {
            return false;
        }

        return true;
    }

    @Override
    public void execute(String[] arguments) throws IOException {
        calcContext.pushValue((numerator / denominator));
    }

    @Override
    public void revert() {
        calcContext.pushValue(denominator);
        calcContext.pushValue(numerator);
    }
}
