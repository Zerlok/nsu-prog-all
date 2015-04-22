package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;

import java.io.IOException;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandPop extends Command {
    public CommandPop(Context ctx) {
        super(ctx);
    }

    @Override
    public void execute(String[] arguments) throws IOException {
        calcContext.getValues(1);
    }
}
