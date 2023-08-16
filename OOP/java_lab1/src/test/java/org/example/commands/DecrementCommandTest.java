package org.example.commands;

import org.example.logic.Context;
import static org.junit.Assert.*;
import org.junit.Test;

public class DecrementCommandTest {
    private Context context;
    void init(){
        context = new Context("", null);
    }
    @Test
    public void firstMoveTest() {
        init();
        context.setCell((byte) 3);

        DecrementCommand command = new DecrementCommand();
        command.execute(context);
        assertTrue(((byte) 2 == context.getCell()));
    }

    @Test
    public void secondMoveTest() {
        init();
        context.setCell((byte) 101);

        DecrementCommand command = new DecrementCommand();
        command.execute(context);
        assertTrue(((byte) 100 == context.getCell()));
    }
}