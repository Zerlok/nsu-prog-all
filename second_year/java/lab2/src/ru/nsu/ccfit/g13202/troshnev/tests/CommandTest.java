package ru.nsu.ccfit.g13202.troshnev.tests;

import org.junit.Before;
import org.junit.Test;
import ru.nsu.ccfit.g13202.troshnev.lab2.*;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.Command;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.CommandDefine;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.NegativeValueException;
import ru.nsu.ccfit.g13202.troshnev.lab2.commands.ZeroDivisionException;

import java.io.IOException;

import static org.junit.Assert.*;

public class CommandTest {

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
        cmd = new Command(calcContext) {
            @Override
            public boolean isValid(String[] arguments) throws Exception {
                return super.isValid(arguments);
            }

            @Override
            public void execute(String[] arguments) throws Exception {
                super.execute(arguments);
            }

            @Override
            public void revert() {
                super.revert();
            }
        };
    }

    @Test
    public void testIsValid() throws Exception {
        assertTrue(cmd.isValid(new String[] {}));
        assertTrue(cmd.isValid(new String[] {"Hello"}));
        assertTrue(cmd.isValid(new String[] {"Hello", "World!"}));
        assertTrue(cmd.isValid(new String[] {"Calculator", "1.1"}));
    }

    @Test
    public void testExecute() throws Exception {
        cmd.execute(new String[]{});
        cmd.execute(new String[] {"One"});
    }
}