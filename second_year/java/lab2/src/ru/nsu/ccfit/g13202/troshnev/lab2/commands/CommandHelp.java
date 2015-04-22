package ru.nsu.ccfit.g13202.troshnev.lab2.commands;

import ru.nsu.ccfit.g13202.troshnev.lab2.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;

import java.io.IOException;


public class CommandHelp extends Command {

    public CommandHelp(Context ctx) {
        super(ctx);
    }

    @Override
    public void execute(String[] arguments) throws Exception {
        calcContext.println("Help command executed.");
    }
}
