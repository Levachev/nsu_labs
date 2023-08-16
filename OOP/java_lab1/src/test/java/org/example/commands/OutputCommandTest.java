package org.example.commands;

import org.example.logic.Context;
import static org.junit.Assert.*;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;


public class OutputCommandTest {
    private Context context;
    void init(){
        context = new Context("", null);
    }
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;

    @Test
    public void firstMoveTest() {
        init();
        context.incrementPointerOfCells();
        context.setCell((byte) 72);

        System.setOut(new PrintStream(outContent));

        OutputCommand command = new OutputCommand();
        command.execute(context);
        System.setOut(originalOut);

        assertEquals("H", outContent.toString());
    }

    @Test
    public void secondMoveTest() {
        init();
        context.incrementPointerOfCells();
        context.setCell((byte) 3);
        context.incrementPointerOfCells();
        context.setCell((byte) 33);

        System.setOut(new PrintStream(outContent));

        OutputCommand command = new OutputCommand();
        command.execute(context);
        System.setOut(originalOut);

        assertEquals("!", outContent.toString());
    }
}