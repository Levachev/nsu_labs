package org.example.commands;

import org.example.logic.Context;
import static org.junit.Assert.*;
import org.junit.Test;

public class IncrementCommandTest {
    private Context context;
    void init(){
        context = new Context("", null);
    }
    @Test
    public void firstMoveTest() {
        init();
        context.setCell((byte) 3);

        IncrementCommand command = new IncrementCommand();
        command.execute(context);
        assertTrue(((byte) 4 == context.getCell()));
    }

    @Test
    public void secondMoveTest() {
        init();
        context.setCell((byte) 101);

        IncrementCommand command = new IncrementCommand();
        command.execute(context);
        assertTrue(((byte) 102 == context.getCell()));
    }
}