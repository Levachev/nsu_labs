package org.example.commands;

import org.example.logic.Context;
import org.jetbrains.annotations.NotNull;

public class InputCommand implements ICommand {
    public void execute(@NotNull Context context) {
        byte val = context.byteReadScanner();
        context.setCell((byte) (val%256));
    }
}
