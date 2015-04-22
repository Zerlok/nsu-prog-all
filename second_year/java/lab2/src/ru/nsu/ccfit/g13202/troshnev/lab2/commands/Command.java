package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;

import java.io.IOException;


/**
 * Created by zerlok on 3/25/15.
 */


public abstract class Command {

    protected Context calcContext;

    public Command(Context ctx) {
        calcContext = ctx;
    }

    public boolean isValid(String[] arguments) throws IOException{
        return true;
    }

    public void execute(String[] arguments) throws IOException {
        calcContext.println("Command doesn't have the declaration what to do.");
    }

    public void revert() {}
}
