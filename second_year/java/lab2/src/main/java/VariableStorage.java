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

    public void push(String name, Double value) {
        storage.put(name, value);
    }

    public Double pop(String name) {
        return storage.get(name);
    }
}