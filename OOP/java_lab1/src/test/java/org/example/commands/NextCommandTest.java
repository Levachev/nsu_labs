package org.example.commands;

import org.example.logic.Context;
import static org.junit.Assert.*;
import org.junit.Test;

public class NextCommandTest {
    private Context context;
    void init(){
        context = new Context("", null);
    }
    @Test
    public void firstMoveTest() {
        init();
        NextCommand command = new NextCommand();
        command.execute(context);
        assertTrue(((byte) 0 == context.getCell()));
    }

    @Test
    public void secondMoveTest() {
        init();
        context.incrementPointerOfCells();
        context.setCell((byte) 3);
        context.decrementPointerOfCells();

        NextCommand command = new NextCommand();
        command.execute(context);
        assertTrue(((byte) 3 == context.getCell()));
    }
}