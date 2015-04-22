package ru.nsu.ccfit.g13202.troshnev.lab2;

public class EmptyStorageException extends Exception {
    @Override
    public String getMessage() {
        return "Calculator cannot get more values from empty stack!";
    }
}
