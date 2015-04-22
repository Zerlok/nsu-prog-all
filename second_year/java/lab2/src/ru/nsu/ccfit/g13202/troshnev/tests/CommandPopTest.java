package ru.nsu.ccfit.g13202.troshnev.tests;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import ru.nsu.ccfit.g13202.troshnev.lab2.*;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.extra.CommandPop;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.Context;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.ValueStorage;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.VariableStorage;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.View;

import static org.junit.Assert.*;

public class CommandPopTest {

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
        cmd = new CommandPop(calcContext);
        defaults = new String[] {};
    }

    @Test
    public void testNoArguments() throws Exception {
//        No values in stack.
        assertFalse(cmd.isValid(defaults));
    }

    @Test
    public void testIsValid() throws Exception {
//        One value in stack is enough.
        calcContext.pushValue(1.0);
        assertTrue(cmd.isValid(defaults));
    }

    @Test
    public void testExecute() throws Exception {
        Double[] expected_values = new Double[] {0.0, 1.0, -0.1, 0.11};

        for (Double d : expected_values) {
            calcContext.pushValue(d);
        }

        for (int i = 0; i < expected_values.length; i++) {
            assertTrue(cmd.isValid(defaults));
            cmd.execute();
        }

//        The stack is empty (last value is null)
        assertNull(calcContext.getValues(1));
    }
}