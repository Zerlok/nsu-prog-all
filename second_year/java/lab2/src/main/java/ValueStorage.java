import java.util.Stack;


public class ValueStorage {

    private Stack<Double> storage;

    public void push(Double value) {
        storage.push(value);
    }

    public Double pop() {
        return storage.pop();
    }
}
