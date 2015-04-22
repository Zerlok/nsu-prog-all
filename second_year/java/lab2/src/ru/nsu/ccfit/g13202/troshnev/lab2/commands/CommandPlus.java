package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;

import java.io.IOException;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandPlus extends Command {

    private Double first_summand;
    private Double second_summand;

    public CommandPlus(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws IOException {
        Double[] values = calcContext.getValues(2);

        first_summand = values[0];
        second_summand = values[1];

        return true;
    }

    @Override
    public void execute(String[] arguments) throws IOException {
        calcContext.pushValue((first_summand + second_summand));
    }
}
