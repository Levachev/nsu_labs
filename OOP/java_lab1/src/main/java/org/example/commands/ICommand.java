package org.example.commands;

import org.example.logic.Context;

public interface ICommand {
    void execute(Context context);
}
