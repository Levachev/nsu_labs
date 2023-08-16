package org.example.logic;

import java.util.ArrayList;
import java.util.Scanner;

public class Context {
    private final ArrayList<Byte> cells;
    private final String code;
    private int pointerOfCells;
    private int pointerOfCode;
    private final Scanner scanner;
    public Context(String inputCode, Scanner inputScanner){
        code = inputCode;
        pointerOfCells = 0;
        pointerOfCode = 0;
        cells = new ArrayList<>();
        cells.add((byte) 0);
        scanner = inputScanner;
    }
    public Byte getCell(){
        return cells.get(pointerOfCells);
    }
    private int getCellsSize(){
        return cells.size();
    }
    public void setCell(Byte value){
        cells.set(pointerOfCells, value);
    }
    private void addCell(Byte value){
        cells.add(value);
    }
    public Byte byteReadScanner(){
        return scanner.nextByte();
    }

    public void incrementPointerOfCells(){
        pointerOfCells++;
        if(getCellsSize() == pointerOfCells){
            addCell((byte) 0);
        }
    }
    public void decrementPointerOfCells(){
        pointerOfCells--;
    }
    public void incrementPointerOfCode(){
        pointerOfCode++;
    }
    public void decrementPointerOfCode(){
        pointerOfCode--;
    }
    public char getCodeSymbol(){
        return code.charAt(pointerOfCode);
    }
    public boolean hasNextCommand(){
        return (code.length() != pointerOfCode);
    }
}
