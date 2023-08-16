package org.example.logic;

import org.junit.Test;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.util.Scanner;

import static org.junit.Assert.*;

public class ContextTest {
    private Context context;
    void init(){
        context = new Context("+-[].", null);
    }
    @Test
    public void getCell() {
        init();
        assertEquals((byte) 0, (byte) context.getCell());
    }

    @Test
    public void setCell() {
        init();
        context.setCell((byte) 2);
        assertEquals((byte) 2, (byte) context.getCell());
    }

    @Test
    public void addCell() {
        init();
        context.incrementPointerOfCells();
        context.setCell((byte) 2);
        assertEquals((byte) 2, (byte) context.getCell());
    }

    @Test
    public void incrementPointerOfCode() {
        init();
        context.incrementPointerOfCode();
        assertEquals('-', context.getCodeSymbol());
    }

    @Test
    public void decrementPointerOfCode() {
        init();
        context.incrementPointerOfCode();
        context.decrementPointerOfCode();
        assertEquals('+', context.getCodeSymbol());
    }

    @Test
    public void getCodeSymbol() {
        init();
        assertEquals('+', context.getCodeSymbol());
    }

    @Test
    public void hasNextCommand() {
        init();
        assertTrue(context.hasNextCommand());
    }

    @Test
    public void byteReadScanner() {
        InputStream sysInBackup = System.in;
        ByteArrayInputStream in = new ByteArrayInputStream("72".getBytes());
        System.setIn(in);

        Scanner scanner = new Scanner(System.in);

        context = new Context("+-[].", scanner);

        assertTrue(((byte) 72 == context.byteReadScanner()));
        System.setIn(sysInBackup);
        scanner.close();
    }
}