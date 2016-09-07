package ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra;

import java.io.IOException;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;


/**
 * Created by zerlok on 4/22/15.
 */

public class CommandPop extends Command {
    public CommandPop(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws IOException {
        Double[] value = calcContext.getValues(1);

        if (value == null)
            return false;

        calcContext.pushValue(value[0]);
        return true;
    }

    @Override
    public void execute() {
        calcContext.getValues(1);
    }
}
