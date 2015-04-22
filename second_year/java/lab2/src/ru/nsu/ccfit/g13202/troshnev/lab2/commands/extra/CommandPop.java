package ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra;

import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandException;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;

import java.io.IOException;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandPop extends Command {
    public CommandPop(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws IOException {
        if (calcContext.getValues(1) == null)
            return false;

        return true;
    }

    @Override
    public void execute() throws CommandException {}
}
