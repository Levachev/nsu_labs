package org.example.commands;

import org.example.logic.Context;
import static org.junit.Assert.*;
import org.junit.Test;

public class BeginOfCycleCommandTest {
    private Context context;
    void init(){
        context = new Context("[[-]+]", null);
    }
    @Test
    public void firstMoveTest() {
        init();
        BeginOfCycleCommand command = new BeginOfCycleCommand();
        command.execute(context);
        context.decrementPointerOfCode();
        assertEquals('+', context.getCodeSymbol());
    }

    @Test
    public void secondMoveTest() {
        init();
        context.incrementPointerOfCode();

        BeginOfCycleCommand command = new BeginOfCycleCommand();
        command.execute(context);
        context.decrementPointerOfCode();
        assertEquals('-', context.getCodeSymbol());
    }
}