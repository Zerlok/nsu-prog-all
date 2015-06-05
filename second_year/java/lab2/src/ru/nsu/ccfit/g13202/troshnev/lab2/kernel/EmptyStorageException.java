package ru.nsu.ccfit.g13202.troshnev.lab2.kernel;


public class EmptyStorageException extends CalculatorException {
    @Override
    public String getMessage() {
        return "Calculator cannot get more values from empty stack!";
    }
}
