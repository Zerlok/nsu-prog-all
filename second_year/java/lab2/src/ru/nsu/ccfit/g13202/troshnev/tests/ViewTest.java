package ru.nsu.ccfit.g13202.troshnev.tests;

import org.junit.Before;
import org.junit.Test;
import ru.nsu.ccfit.g13202.troshnev.lab2.OutputWriter;
import ru.nsu.ccfit.g13202.troshnev.lab2.kernel.View;

public class ViewTest {

    private View view;

    @Before
    public void setUp() throws Exception {
        view = new View(new OutputWriter(System.out));
    }

    @Test
    public void testShow() throws Exception {
        view.show("Hello from test!\n");
    }
}