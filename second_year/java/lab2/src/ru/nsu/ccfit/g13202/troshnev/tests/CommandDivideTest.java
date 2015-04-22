package ru.nsu.ccfit.g13202.troshnev.tests;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.rules.ExpectedException;
import ru.nsu.ccfit.g13202.troshnev.lab2.*;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandDivide;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.UnvalidatedCommandExecutionException;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.ZeroDivisionException;


public class CommandDivideTest {

    private ValueStorage values;
    private VariableStorage variables;
    private View view;
    private Context calcContext;
    private Command cmd;
    private String[] defaults;

    @Rule
    public ExpectedException thrown = ExpectedException.none();

    @Before
    public void setUp() throws Exception {
        values = new ValueStorage();
        variables = new VariableStorage();
        view = new View(new OutputWriter(System.out));
        calcContext = new Context(values, variables, view);
        cmd = new CommandDivide(calcContext);
        defaults = new String[] {};
    }

    @Test(expected = UnvalidatedCommandExecutionException.class)
    public void testUnvalidatedExecution() throws Exception {
        cmd.execute();
    }

    @Test
    public void testNoArguments() throws Exception {
//        No values in stack.
        assertFalse(cmd.isValid(defaults));
    }

    @Test
    public void testOneArgument() throws Exception {
//        Only one value in stack.
        calcContext.pushValue(1.0);
        assertFalse(cmd.isValid(defaults));
    }

    @Test
    public void testIsValid() throws Exception {
//        Two values in stack is enough.
        calcContext.pushValue(1.0);
        calcContext.pushValue(1.0);
        assertTrue(cmd.isValid(defaults));
    }

    @Test(expected = ZeroDivisionException.class)
    public void testZeroDivision() throws Exception {
//        Zero division.
        calcContext.pushValue(0.0);
        calcContext.pushValue(1.0);
        cmd.isValid(defaults);
    }

    @Test
    public void testExecute() throws Exception {
        Double[][] equations = new Double[][] {
                {1.0, 1.0},
                {100.0, 10.0},
                {10.0, 100.0},
                {1.0, 0.01},
                {0.0, 1234.5678},
                {24.0, 7.0},
        };
        Double[] expected_results = new Double[equations.length];

        for (int i = 0; i < equations.length; i++) {
            calcContext.pushValue(equations[i][1]);
            calcContext.pushValue(equations[i][0]);
            cmd.isValid(defaults);
            cmd.execute();
            expected_results[i] = (equations[i][0] / equations[i][1]);
        }

        Double[] actual_results = calcContext.getValues(equations.length);

        for (int i = 0; i < equations.length; i++)
            assertEquals(expected_results[i], actual_results[equations.length - i - 1]);
    }

    @Test
    public void testRevert() throws Exception {
        Double[] expected_values = new Double[] {1.0, 0.0};

        try {
            cmd.isValid(defaults);
        } catch (EmptyStorageException e) {
            cmd.revert();
        }

        try {
            calcContext.pushValue(0.0);
            calcContext.pushValue(1.0);
            cmd.isValid(defaults);
        } catch (ZeroDivisionException e) {
            cmd.revert();
        }

        Double[] actual_values = calcContext.getValues(expected_values.length);

        for (int i = 0; i < expected_values.length; i++)
            assertEquals(expected_values[i], actual_values[i]);
    }
}