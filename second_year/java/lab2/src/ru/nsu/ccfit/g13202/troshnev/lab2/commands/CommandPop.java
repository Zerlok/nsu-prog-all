package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.EmptyStorageException;

import java.io.IOException;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandPop extends Command {
    public CommandPop(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws Exception {
        calcContext.getValues(1);
        return true;
    }
}
