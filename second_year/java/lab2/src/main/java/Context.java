import java.io.IOException;
import java.util.LinkedList;


/**
 * Created by zerlok on 3/25/15.
 */


public class Context {

    private ValueStorage calcValues;
    private VariableStorage calcVars;
    private View calcView;

    public Context(ValueStorage values, VariableStorage variables, View view) {
        calcValues = values;
        calcVars = variables;
        calcView = view;
    }

    public LinkedList<Double> getValues(int amount) {
        LinkedList<Double> list = new LinkedList<Double>();
        list.push(calcValues.pop());

        return list;
    }

    public Double getVarValue(String name) {
        return calcVars.pop(name);
    }

    public void pushValue(Double value) {
        calcValues.push(value);
    }

    public void pushVariable(String name, Double value) {
        calcVars.push(name, value);
    }

    public void show(String line) throws IOException {
        calcView.show(line);
    }
}
