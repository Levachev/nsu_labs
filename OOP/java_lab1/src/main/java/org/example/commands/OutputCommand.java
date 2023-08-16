package org.example.commands;

import org.example.logic.Context;
import org.jetbrains.annotations.NotNull;

public class OutputCommand implements ICommand {
    public void execute(@NotNull Context context) {
        byte tmp = context.getCell();
        char symbol = (char) (tmp & 0xFF);
        System.out.print(symbol);
    }
}
