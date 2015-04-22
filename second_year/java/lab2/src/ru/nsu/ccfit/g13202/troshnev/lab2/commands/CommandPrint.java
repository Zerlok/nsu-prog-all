package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;


public class CommandPrint extends Command {
    private Double value;

    public CommandPrint(Context ctx) {
        super(ctx);
    }

    @Override
    public boolean isValid(String[] arguments) throws Exception {
        // TODO: rewrite validation without pops.
        Double[] values = calcContext.getValues(1);

        if (values == null)
            return false;

        value = values[0];

//        Push the value back.
        calcContext.pushValue(value);
        return true;
    }

    @Override
    public void execute() throws Exception {
        if (value == null)
            throw new UnvalidatedCommandExecutionException();

        calcContext.println(String.valueOf(value));
    }
}
