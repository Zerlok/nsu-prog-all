package ru.nsu.ccfit.g13202.troshnev.lab2.kernel;


/**
 * Created by zerlok on 4/22/15.
 */


public class CalculatorException extends Exception {
    @Override
    public String getMessage() {
        return "Calculator crashed!";
    }
}
