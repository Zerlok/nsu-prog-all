package ru.nsu.ccfit.g13202.troshnev.lab2.commands;


/**
 * Created by zerlok on 4/22/15.
 */


public class NegativeValueException extends Exception {
    @Override
    public String getMessage() {
        return "Calculator command cannot work with negative value!";
    }
}
