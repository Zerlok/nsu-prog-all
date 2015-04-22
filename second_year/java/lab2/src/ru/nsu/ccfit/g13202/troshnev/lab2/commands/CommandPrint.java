package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;

import java.io.IOException;
import java.util.LinkedList;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandPrint extends Command {
    private Double value;

    public CommandPrint(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws IOException {
        value = calcContext.getValues(1)[0];
        return true;
    }

    @Override
    public void execute(String[] arguments) throws IOException {
        calcContext.println(String.valueOf(value));
    }
}
