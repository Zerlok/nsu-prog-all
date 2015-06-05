package ru.nsu.ccfit.g13202.troshnev.lab2.kernel;


/**
 * Created by zerlok on 4/22/15.
 */


public class UndefinedVariableException extends CalculatorException {
    private String varname;

    public UndefinedVariableException(String name) {
        varname = name;
    }

    @Override
    public String getMessage() {
        return String.format("The variable '%1$s' was not defined!", varname);
    }
}
