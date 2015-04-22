package ru.nsu.ccfit.g13202.troshnev.lab2;

import java.util.HashMap;
import java.util.Map;


/**
 * Created by zerlok on 3/18/15.
 */


public class VariableStorage {

    private Map<String, Double> storage;

    public VariableStorage() {
        storage = new HashMap<String, Double>();
    }

    public void setVar(String name, Double value) {
        storage.put(name, value);
    }

    public Double getVar(String name) throws UndefinedVariableException {
        if (!storage.containsKey(name))
            throw new UndefinedVariableException();

        return storage.get(name);
    }

    public boolean hasVar(String name) {
        return storage.containsKey(name);
    }
}