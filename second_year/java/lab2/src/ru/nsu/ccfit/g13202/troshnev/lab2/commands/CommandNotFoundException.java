package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

/**
 * Created by zerlok on 4/29/15.
 */
public class CommandNotFoundException extends CommandException {
    @Override
    public String getMessage() {
        return "Command was not found!";
    }
}
