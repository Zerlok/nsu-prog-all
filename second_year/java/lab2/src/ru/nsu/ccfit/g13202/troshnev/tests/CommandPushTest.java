package ru.nsu.ccfit.g13202.troshnev.tests;

import java.util.Map;
import java.util.HashMap;
import java.io.IOException;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.rules.ExpectedException;
import ru.nsu.ccfit.g13202.troshnev.lab2.*;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra.CommandPush;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.*;


public class CommandPushTest {

    private ValueStorage values;
    private VariableStorage variables;
    private View view;
    private Context calcContext;
    private Command cmd;

    @Rule
    public ExpectedException thrown = ExpectedException.none();

    @Before
    public void setUp() {
        values = new ValueStorage();
        variables = new VariableStorage();
        view = new View(new OutputWriter(System.out));
        calcContext = new Context(values, variables, view);
        cmd = new CommandPush(calcContext);
    }

    @Test
    public void testNoArguments() throws CalculatorException, IOException {
//        No values in stack.
        assertFalse(cmd.isValid(new String[] {}));
    }

    @Test(expected = UndefinedVariableException.class)
    public void testUndefinedPush() throws CalculatorException, IOException {
        cmd.isValid(new String[] {"push", "bar"});
    }

    @Test
    public void testIsValidForValue() throws CalculatorException, IOException {
//        Two values in stack is enough.
        assertTrue(cmd.isValid(new String[] {"push", "0.0"}));
    }

    @Test
    public void testIsValidForVariable() throws CalculatorException, IOException {
        calcContext.defineVar("foo", 4.0);
        assertTrue(cmd.isValid(new String[]{"push", "foo"}));
    }

    @Test
    public void testPushingValues() throws CalculatorException, IOException {
        Double[] expected_results = new Double[] {
                1.0,
                100.0,
                10.0,
                1.0,
                0.0,
                24.0,
                -1.0,
                -0.0,
                -10.0,
        };

        for (int i = 0; i < expected_results.length; i++) {
            assertTrue(cmd.isValid(new String[]{"push", String.valueOf(expected_results[i])}));
            cmd.execute();
        }

        Double[] actual_results = calcContext.getValues(expected_results.length);

        for (int i = 0; i < expected_results.length; i++)
            assertEquals(expected_results[i], actual_results[expected_results.length - i - 1]);

//        Stack is empty (last value is null)
        assertNull(calcContext.getValues(1));
    }

    @Test
    public void testPushingVariables() throws CalculatorException, IOException {
        HashMap<String, Double> vars = new HashMap<String, Double>();

        vars.put("a", 0.0);
        vars.put("b", 0.0);
        vars.put("c", -12.34);
        vars.put("d", 20.0);
        vars.put("pi", 3.1415);

        for (Map.Entry<String, Double> pair : vars.entrySet()) {
            calcContext.defineVar(pair.getKey(), pair.getValue());
        }

        String[] queue = {"a", "pi", "d", "c", "b", "a", "pi"};
        Double[] expected_values = new Double[queue.length];

        for (int i = 0; i < queue.length; i++) {
            expected_values[i] = vars.get(queue[i]);
            assertTrue(cmd.isValid(new String[] {"push", queue[i]}));
            cmd.execute();
        }

        Double[] actual_values = calcContext.getValues(expected_values.length);

        for (int i = 0; i < expected_values.length; i++) {
            assertEquals(expected_values[i], actual_values[expected_values.length - i - 1]);
        }

//        Stack is empty (last value is null)
        assertNull(calcContext.getValues(1));
    }
}