package ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra;

import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandException;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.CalculatorException;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;

import java.io.IOException;

/**
 * Created by zerlok on 4/22/15.
 */

public class CommandDivide extends Command {

    private Double numerator;
    private Double denominator;

    public CommandDivide(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws IOException, ZeroDivisionException {
        Double[] values = calcContext.getValues(2);

        if (values == null)
            return false;

        numerator = values[0];
        denominator = values[1];

        if (denominator == 0.0)
            throw new ZeroDivisionException();

        return true;
    }

    @Override
    public void execute() throws UnvalidatedCommandExecutionException {
        if ((numerator == null)
                || (denominator == null))
            throw new UnvalidatedCommandExecutionException();

        calcContext.pushValue((numerator / denominator));
    }

    @Override
    public void revert() {
        if ((denominator != null) && (numerator != null)) {
            calcContext.pushValue(denominator);
            calcContext.pushValue(numerator);
        }
    }
}
