package org.example.logic;

import org.example.factory.Factory;
import org.example.factory.FactoryInitException;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.Scanner;

import static org.junit.Assert.*;

public class ProcessTest {

    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;

    @Before
    public void setUpStreams() {
        System.setOut(new PrintStream(outContent));
    }
    @After
    public void restoreStreams() {
        System.setOut(originalOut);
    }
    @Test
    public void firstHelloWorldTestMethod() throws ProcessFailedException, FactoryInitException {
        try(Scanner scanner = new Scanner("[ -> org.example.commands.BeginOfCycleCommand\n" +
                "] -> org.example.commands.EndOfCycleCommand\n" +
                "> -> org.example.commands.NextCommand\n" +
                "< -> org.example.commands.PrevCommand\n" +
                ". -> org.example.commands.OutputCommand\n" +
                ", -> org.example.commands.InputCommand\n" +
                "- -> org.example.commands.DecrementCommand\n" +
                "+ -> org.example.commands.IncrementCommand")){

            Factory factory = new Factory(scanner);

            Process p = new Process("++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.", factory) ;
            p.run();
        assertEquals("Hello World!\n", outContent.toString());
        } catch (FactoryInitException e){
            System.out.println("factory creating failed");
        }
    }
    @Test
    public void secondHelloWorldTestMethod() throws ProcessFailedException, FactoryInitException {
        try(Scanner scanner = new Scanner("[ -> org.example.commands.BeginOfCycleCommand\n" +
                "] -> org.example.commands.EndOfCycleCommand\n" +
                "> -> org.example.commands.NextCommand\n" +
                "< -> org.example.commands.PrevCommand\n" +
                ". -> org.example.commands.OutputCommand\n" +
                ", -> org.example.commands.InputCommand\n" +
                "- -> org.example.commands.DecrementCommand\n" +
                "+ -> org.example.commands.IncrementCommand")){

            Factory factory = new Factory(scanner);

            Process p = new Process("++++++   ++[>++++[>++> +++>+++>+<<<<-]>+>+>\n->>+[<]<-]>>.>---.+++++++..+++.>>  .<-.<.+++.------\n\n\n.--------.>>+.>++.", factory) ;
            p.run();
        assertEquals("Hello World!\n", outContent.toString());
        } catch (FactoryInitException e){
            System.out.println("factory creating failed");
        }
    }
    @Test(expected = ProcessFailedException.class)
    public void firstBadHelloWorldTestMethod() throws ProcessFailedException, FactoryInitException {
        try(Scanner scanner = new Scanner("[ -> org.example.commands.BeginOfCycleCommand\n" +
                "] -> org.example.commands.EndOfCycleCommand\n" +
                "> -> org.example.commands.NextCommand\n" +
                "< -> org.example.commands.PrevCommand\n" +
                ". -> org.example.commands.OutputCommand\n" +
                ", -> org.example.commands.InputCommand\n" +
                "- -> org.example.commands.DecrementCommand\n" +
                "+ -> org.example.commands.IncrementCommand")){

            Factory factory = new Factory(scanner);

            Process p = new Process("+++*&^$+++   ++[>++++[>++> +++>+++>+<<<<-]>+>+>\n->>+[<]<-]>>.>---.+++++++..+++.>>  .<-.<.+++.------\n\n\n.--------.>>+.>++.", factory) ;
            p.run();
        } catch (FactoryInitException e){
            System.out.println("factory creating failed");
        }
    }
    @Test(expected = ProcessFailedException.class)
    public void secondBadHelloWorldTestMethod() throws ProcessFailedException, FactoryInitException {
        try(Scanner scanner = new Scanner("[ -> org.example.commands.BeginOfCyc1leCommand\n" +
                "] -> org.example.commands.EndOfCy1cleCommand\n" +
                "> -> org.example.commands.NextCo1mmand\n" +
                "< -> org.example.commands.PrevC1ommand\n" +
                ". -> org.example.commands.Output1Command\n" +
                ", -> org.example.commands.InputC1ommand\n" +
                "- -> org.example.commands.Decre1mentCommand\n" +
                "+ -> org.example.commands.Increm1entCommand")){

            Factory factory = new Factory(scanner);

            Process p = new Process("++++++   ++[>++++[>++> +++>+++>+<<<<-]>+>+>\n->>+[<]<-]>>.>---.+++++++..+++.>>  .<-.<.+++.------\n\n\n.--------.>>+.>++.", factory) ;
            p.run();
        } catch (FactoryInitException e){
            System.out.println("factory creating failed");
        }
    }
}