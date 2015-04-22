package ru.nsu.ccfit.g13202.troshnev.lab2.commands;


/**
 * Created by zerlok on 4/22/15.
 */


public class ZeroDivisionException extends Exception {
    @Override
    public String getMessage() {
        return "Calculator cannot divide by zero!";
    }
}
