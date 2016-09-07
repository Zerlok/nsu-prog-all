package ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra;

import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandException;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.CalculatorException;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;

import java.io.IOException;


/**
 * Created by zerlok on 4/22/15.
 */


public class CommandSqrt extends Command {
    private Double value;

    public CommandSqrt(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws NegativeValueException, IOException {
        Double[] values = calcContext.getValues(1);

        if (values == null)
            return false;

        value = values[0];

        if (value < 0.0)
            throw new NegativeValueException();

        return true;
    }

    @Override
    public void execute() throws UnvalidatedCommandExecutionException {
        if (value == null)
            throw new UnvalidatedCommandExecutionException();

        calcContext.pushValue(Math.sqrt(value));
    }

    @Override
    public void revert() {
        if (value != null)
            calcContext.pushValue(value);
    }
}
