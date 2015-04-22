package ru.nsu.ccfit.g13202.troshnev.lab2;

import java.util.EmptyStackException;
import java.util.Stack;


public class ValueStorage {

    private Stack<Double> storage;

    public ValueStorage() {
        storage = new Stack<Double>();
    }

    public void push(Double value) {
        storage.push(value);
    }

    public Double pop() throws EmptyStorageException {
        try {
            return storage.pop();

        } catch (EmptyStackException e) {
            throw new EmptyStorageException();
        }
    }
}

