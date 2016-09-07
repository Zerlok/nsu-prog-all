package ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra;

import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandException;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;

import java.io.IOException;


public class CommandPrint extends Command {
    private Double value;

    public CommandPrint(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws IOException {
        Double[] values = calcContext.getValues(1);

        if (values == null)
            return false;

        value = values[0];

//        Push the value back.
        calcContext.pushValue(value);
        return true;
    }

    @Override
    public void execute() throws UnvalidatedCommandExecutionException, IOException {
        if (value == null)
            throw new UnvalidatedCommandExecutionException();

        calcContext.println(String.valueOf(value));
    }
}
