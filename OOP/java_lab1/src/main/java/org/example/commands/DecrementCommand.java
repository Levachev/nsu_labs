package org.example.commands;

import org.example.logic.Context;
import org.jetbrains.annotations.NotNull;

public class DecrementCommand implements ICommand {
    public void execute(@NotNull Context context) {
        context.setCell((byte) ((context.getCell()-1)%256));
    }
}
