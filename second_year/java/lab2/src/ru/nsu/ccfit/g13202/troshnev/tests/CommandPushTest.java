package ru.nsu.ccfit.g13202.troshnev.tests;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import ru.nsu.ccfit.g13202.troshnev.lab2.*;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandMultiply;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandPush;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.UnvalidatedCommandExecutionException;

import java.lang.reflect.Array;
import java.util.HashMap;

import static org.junit.Assert.*;

public class CommandPushTest {

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
        cmd = new CommandPush(calcContext);
        defaults = new String[] {};
    }

    @Test
    public void testNoArguments() throws Exception {
//        No values in stack.
        assertFalse(cmd.isValid(new String[] {}));
    }

    @Test
    public void testIsValid() throws Exception {
//        Two values in stack is enough.
        assertTrue(cmd.isValid(new String[] {"push", "0.0"}));
    }

    @Test
    public void testPushingValues() throws Exception {
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

//    @Test
//    public void testPushingVariables() throws Exception {
//        String[] varNames = new String[] {"a", "b", "c", "d"};
//        Double[] varValues = new Double[] {0.0, 0.0, -12.34, 20.0};
//
//        for (int i = 0; i < varNames.length; i++)
//            calcContext.defineVar(varNames[i], varValues[i]);
//
//        String[][] arguments = new String[][] {
//                {"push", "a"},
//                {"push", "a"},
//                {"push", "b"},
//                {"push", "c"},
//                {"push", "d"},
//                {"push", "d"},
//        };
//
//        Double[] expected_values = new Double[arguments.length];
//
//        for (int i = 0; i < arguments.length; i++) {
//            assertTrue(cmd.isValid(arguments[i]));
//            cmd.execute();
//        }
//
//
//    }
}