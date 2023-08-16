package org.example.commands;

import org.example.logic.Context;
import static org.junit.Assert.*;
import org.junit.Test;

public class EndOfCycleCommandTest {
    private Context context;
    void init(){
        context = new Context("[[-[+]]]", null);
    }
    @Test
    public void firstMoveTest() {
        init();
        context.setCell((byte) 1);
        context.incrementPointerOfCode();
        context.incrementPointerOfCode();
        context.incrementPointerOfCode();
        context.incrementPointerOfCode();
        context.incrementPointerOfCode();

        EndOfCycleCommand command = new EndOfCycleCommand();
        command.execute(context);
        context.incrementPointerOfCode();
        assertEquals('+', context.getCodeSymbol());
    }

    @Test
    public void secondMoveTest() {
        init();
        context.setCell((byte) 1);
        context.incrementPointerOfCode();
        context.incrementPointerOfCode();
        context.incrementPointerOfCode();
        context.incrementPointerOfCode();
        context.incrementPointerOfCode();
        context.incrementPointerOfCode();

        EndOfCycleCommand command = new EndOfCycleCommand();
        command.execute(context);
        context.incrementPointerOfCode();
        assertEquals('-', context.getCodeSymbol());
    }
}