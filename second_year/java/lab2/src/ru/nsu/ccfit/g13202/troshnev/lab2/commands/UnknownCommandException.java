package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.CalculatorException;

/**
 * Created by zerlok on 4/29/15.
 */

public class UnknownCommandException extends CalculatorException {
    private String cmdname;

    public UnknownCommandException(String name) {
        cmdname = name;
    }

    @Override
    public String getMessage() {
        return String.format("Command '%1$s' unknown!", cmdname);
    }
}
