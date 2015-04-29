package ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra;


import java.io.IOException;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;


/**
 * Created by zerlok on 4/22/15.
 */

public class CommandMinus extends Command {

    private Double minuend;
    private Double subtrahend;

    public CommandMinus(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws IOException {
        Double[] values = calcContext.getValues(2);

        if (values == null)
            return false;

        minuend = values[0];
        subtrahend = values[1];

        return true;
    }

    @Override
    public void execute() throws UnvalidatedCommandExecutionException {
        if ((minuend == null) || (subtrahend == null))
            throw new UnvalidatedCommandExecutionException();

        calcContext.pushValue((minuend - subtrahend));
    }
}
