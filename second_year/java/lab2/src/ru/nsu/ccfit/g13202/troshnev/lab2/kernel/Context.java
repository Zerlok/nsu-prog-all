package ru.nsu.ccfit.g13202.troshnev.lab2.kernel;

import java.io.IOException;
import org.apache.log4j.Logger;


/**
 * Created by zerlok on 3/25/15.
 */


public class Context {

    private static final Logger LOG = Logger.getLogger(Context.class.getName());

    private ValueStorage calcValues;
    private VariableStorage calcVars;
    private View calcView;

    public Context(ValueStorage values, VariableStorage variables, View view) {
        LOG.info("Setting up the context ...");
        calcValues = values;
        calcVars = variables;
        calcView = view;
    }

    public Double[] getValues(int amount) {
        LOG.debug(String.format("Request for %1d values", amount));

        int i = 0;
        Double val;
        Double[] valuesArray = new Double[amount];

        try {
            for (; i < amount; i++) {
                val = calcValues.pop();

                if (val == null)
                    val = 0.0;

                valuesArray[i] = val;
            }

        } catch (EmptyStorageException e) {
            LOG.warn("Too many values to pop, reverting back!");
            for (; i > 0; i--)
                calcValues.push(valuesArray[i]);

            return null;
        }

        LOG.debug(String.format("Returning %1$d values ...", amount));
        return valuesArray;
    }

    public Double getVarValue(String name) throws UndefinedVariableException {
        LOG.debug(String.format("Returning value of %1$s variable ...", name));
        return calcVars.getVar(name);
    }

    public void pushValue(Double value) {
        calcValues.push(value);
        LOG.debug(String.format("Pushed value %1$f.", value));
    }

    public boolean isDefined(String name) {
        return calcVars.hasVar(name);
    }

    public void defineVar(String name, Double value) {
        calcVars.setVar(name, value);
        LOG.debug(String.format("Defined variable %1$s = %2$f.", name, value));
    }

    public void print(String line) throws IOException {
        calcView.show(line);
    }

    public void println(String line) throws IOException {
        calcView.show(String.format("%1$s\n", line));
    }
}
