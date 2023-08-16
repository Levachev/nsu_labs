package org.example.commands;

import org.example.logic.Context;
import org.jetbrains.annotations.NotNull;

public class BeginOfCycleCommand implements ICommand {
    public void execute(@NotNull Context context) {
        if(context.getCell() == 0){
            int flagOfAmountSame=0;
            context.incrementPointerOfCode();
            while(context.getCodeSymbol() != ']' || flagOfAmountSame != 0){
                if (context.getCodeSymbol() == '['){
                    flagOfAmountSame++;
                }
                if (context.getCodeSymbol() == ']'){
                    flagOfAmountSame--;
                }
                context.incrementPointerOfCode();
            }
        }
    }
}
