package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.EmptyStorageException;

import java.io.IOException;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandPrint extends Command {
    private Double value;

    public CommandPrint(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws Exception {
        // TODO: rewrite validation without pops.
        value = calcContext.getValues(1)[0];
        calcContext.pushValue(value);
        return true;
    }

    @Override
    public void execute(String[] arguments) throws Exception {
        calcContext.println(String.valueOf(value));
    }
}
