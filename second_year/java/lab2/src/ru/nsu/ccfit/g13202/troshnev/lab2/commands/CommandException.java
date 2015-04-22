package ru.nsu.ccfit.g13202.troshnev.lab2.commands;


import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.CalculatorException;

/**
 * Created by zerlok on 4/22/15.
 */


public class CommandException extends CalculatorException {
    @Override
    public String getMessage() {
        return "Command failed!";
    }
}
