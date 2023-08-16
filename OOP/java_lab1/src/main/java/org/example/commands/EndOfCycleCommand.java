package org.example.commands;

import org.example.logic.Context;
import org.jetbrains.annotations.NotNull;

public class EndOfCycleCommand implements ICommand {
    public void execute(@NotNull Context context) {
        if(context.getCell() != 0){
            int flagOfAmountSame=0;
            context.decrementPointerOfCode();
            while (flagOfAmountSame != 0 || context.getCodeSymbol() != '[') {
                if (context.getCodeSymbol() == ']') {
                    flagOfAmountSame++;
                }
                if (context.getCodeSymbol() == '[') {
                    flagOfAmountSame--;
                }
                context.decrementPointerOfCode();
            }
        }
    }
}
