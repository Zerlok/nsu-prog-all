import java.io.IOException;
import java.util.LinkedList;
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
        calcValues = values;
        calcVars = variables;
        calcView = view;
    }

    public LinkedList<Double> getValues(int amount) {
        LinkedList<Double> list = new LinkedList<Double>();
        list.push(calcValues.pop());

        LOG.debug("Returning %1$d values ...".format(String.valueOf(amount)));
        return list;
    }

    public Double getVarValue(String name) {
        LOG.debug("Returning value of %1$s variable ...".format(name));
        return calcVars.pop(name);
    }

    public void pushValue(Double value) {
        LOG.debug("Pushing %1f.2 value ...".format(value.toString()));
        calcValues.push(value);
    }

    public void pushVariable(String name, Double value) {
        LOG.debug("Pushing %1$s variable with %2$f.2 value ...".format(name, value));
        calcVars.push(name, value);
    }

    public void show(String line) throws IOException {
        calcView.show(line);
    }
}
