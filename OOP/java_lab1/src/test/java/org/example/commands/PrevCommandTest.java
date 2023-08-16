package org.example.commands;

import org.example.logic.Context;
import static org.junit.Assert.*;
import org.junit.Test;

public class PrevCommandTest {
    private Context context;
    void init(){
        context = new Context("", null);
    }
    @Test
    public void firstMoveTest() {
        init();
        context.incrementPointerOfCells();
        context.setCell((byte) 3);

        PrevCommand command = new PrevCommand();
        command.execute(context);
        assertTrue(((byte) 0 == context.getCell()));
    }

    @Test
    public void secondMoveTest() {
        init();
        context.incrementPointerOfCells();
        context.setCell((byte) 3);
        context.incrementPointerOfCells();
        context.setCell((byte) 2);

        PrevCommand command = new PrevCommand();
        command.execute(context);
        assertTrue(((byte) 3 == context.getCell()));
    }
}