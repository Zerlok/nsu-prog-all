package ru.nsu.ccfit.g13202.troshnev.tests;


import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;
import ru.nsu.ccfit.g13202.troshnev.lab2.*;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandDefine;


public class CommandDefineTest {

    private ValueStorage values;
    private VariableStorage variables;
    private View view;
    private Context calcContext;
    private Command cmd;

    @Before
    public void setUp() throws Exception {
        values = new ValueStorage();
        variables = new VariableStorage();
        view = new View(new OutputWriter(System.out));
        calcContext = new Context(values, variables, view);
        cmd = new CommandDefine(calcContext);
    }

    @Test
    public void testIsValid() throws Exception {
        assertFalse(cmd.isValid(new String[]{}));
        assertFalse(cmd.isValid(new String[]{"DEFINE"}));
        assertFalse(cmd.isValid(new String[]{"DEFINE", "foo"}));
        assertFalse(cmd.isValid(new String[]{"DEFINE", "foo", "bar"}));
        assertTrue(cmd.isValid(new String[]{"DEFINE", "one", "1"}));
    }

    @Test
    public void testExecute() throws Exception {
        assertTrue(cmd.isValid(new String[] {"DEFINE", "one", "1"}));
        cmd.execute();
    }

    @Test
    public void testRedefinition() throws Exception {
        assertTrue(cmd.isValid(new String[]{"DEFINE", "two", "2"}));
        assertTrue(cmd.isValid(new String[]{"DEFINE", "two", "2"}));

        assertTrue(cmd.isValid(new String[] {"DEFINE", "two", "2"}));
        cmd.execute();
        assertFalse(cmd.isValid(new String[]{"DEFINE", "two", "2"}));
    }
}