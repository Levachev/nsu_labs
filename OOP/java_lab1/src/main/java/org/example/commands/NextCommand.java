package org.example.commands;

import org.example.logic.Context;
import org.jetbrains.annotations.NotNull;

public class NextCommand implements ICommand {
    public void execute(@NotNull Context context) {
        context.incrementPointerOfCells();
    }
}
