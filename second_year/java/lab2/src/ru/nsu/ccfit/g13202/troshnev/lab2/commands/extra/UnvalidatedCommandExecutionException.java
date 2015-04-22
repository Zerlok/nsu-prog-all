package ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra;


import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandException;

/**
 * Created by zerlok on 4/22/15.
 */


public class UnvalidatedCommandExecutionException extends CommandException {
    @Override
    public String getMessage() {
        return "Calculator cannot execute unvalidated command!";
    }
}
