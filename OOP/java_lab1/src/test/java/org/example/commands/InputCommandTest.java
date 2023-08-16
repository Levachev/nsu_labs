package org.example.commands;

import org.example.logic.Context;
import static org.junit.Assert.*;
import org.junit.Test;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.Scanner;

public class InputCommandTest {
    private Context context;
    @Test
    public void firstMoveTest() {
        InputStream sysInBackup = System.in;
        ByteArrayInputStream in = new ByteArrayInputStream("122".getBytes());
        System.setIn(in);
        Scanner scanner = new Scanner(System.in);

        context = new Context("", scanner);

        InputCommand command = new InputCommand();
        command.execute(context);

        assertTrue(((byte) 122 == context.getCell()));
        System.setIn(sysInBackup);
        scanner.close();
    }

    @Test
    public void secondMoveTest() {
        InputStream sysInBackup = System.in;
        ByteArrayInputStream in = new ByteArrayInputStream("72".getBytes());
        System.setIn(in);
        Scanner scanner = new Scanner(System.in);

        context = new Context("", scanner);

        InputCommand command = new InputCommand();
        command.execute(context);

        assertTrue(((byte) 72 == context.getCell()));
        System.setIn(sysInBackup);
        scanner.close();
    }
}