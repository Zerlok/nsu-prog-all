package ru.nsu.ccfit.g13202.troshnev.lab2;

import org.apache.log4j.Logger;

import java.io.IOException;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.LinkedList;


/**
 * Created by zerlok on 3/25/15.
 */


public class Context {

    private static final Logger LOG = Logger.getLogger(Context.class.getName());

    private ValueStorage calcValues;
    private VariableStorage calcVars;
    private View calcView;

    public Context(ValueStorage values, VariableStorage variables, View view) {
        calcValues = values;
        calcVars = variables;
        calcView = view;
    }

    public Double[] getValues(int amount) {
        Double[] valuesArray = new Double[amount];

        for (int i = 0; i < amount; i++)
            valuesArray[i] = calcValues.pop();

        LOG.debug(String.format("Returning %1$d values ...", amount));
        return valuesArray;
    }

    public Double getVarValue(String name) {
        LOG.debug(String.format("Returning value of %1$s variable ...", name));
        return calcVars.getVar(name);
    }

    public void pushValue(Double value) {
        LOG.debug(String.format("Pushing %1$f value ...", value));
        calcValues.push(value);
    }

    public void defineVar(String name, Double value) {
        LOG.debug(String.format("Pushing %1$s variable with %2$f value ...", name, value));
        calcVars.setVar(name, value);
    }

    public void print(String line) throws IOException {
        calcView.show(line);
    }

    public void println(String line) throws IOException {
        calcView.show(String.format("%1$s\n", line));
    }
}
