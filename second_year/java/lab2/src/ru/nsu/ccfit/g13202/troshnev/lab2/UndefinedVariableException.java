package ru.nsu.ccfit.g13202.troshnev.lab2;


/**
 * Created by zerlok on 4/22/15.
 */


public class UndefinedVariableException extends Exception {
    @Override
    public String getMessage() {
        return "The variable was not defined!";
    }
}
