package org.example.factory;

import org.example.commands.*;
import org.junit.Test;
import java.util.Scanner;
import static org.junit.Assert.*;
public class FactoryTest {

    @Test
    public void firstMoveTest() throws CreatingCommandException, UnknownCommandNameException, FactoryInitException {
        try(Scanner scanner = new Scanner("[ -> org.example.commands.BeginOfCycleCommand\n" +
                    "] -> org.example.commands.EndOfCycleCommand\n" +
                    "> -> org.example.commands.NextCommand\n" +
                    "< -> org.example.commands.PrevCommand\n" +
                    ". -> org.example.commands.OutputCommand\n" +
                    ", -> org.example.commands.InputCommand\n" +
                    "- -> org.example.commands.DecrementCommand\n" +
                    "+ -> org.example.commands.IncrementCommand")){

            Factory factory = new Factory(scanner);

            ICommand command = factory.create('.');
            OutputCommand outputCommand = new OutputCommand();
            Class firstClass = command.getClass();
            Class secondClass = outputCommand.getClass();
            assertTrue((firstClass == secondClass));
        } catch (FactoryInitException e){
        System.out.println("factory creating failed");
        }
    }

    @Test
    public void secondMoveTest() throws CreatingCommandException, UnknownCommandNameException, FactoryInitException {
        try(Scanner scanner = new Scanner("[ -> org.example.commands.BeginOfCycleCommand\n" +
                "] -> org.example.commands.EndOfCycleCommand\n" +
                "> -> org.example.commands.NextCommand\n" +
                "< -> org.example.commands.PrevCommand\n" +
                ". -> org.example.commands.OutputCommand\n" +
                ", -> org.example.commands.InputCommand\n" +
                "- -> org.example.commands.DecrementCommand\n" +
                "+ -> org.example.commands.IncrementCommand")){

            Factory factory = new Factory(scanner);

            ICommand command = factory.create('+');
            IncrementCommand incrementCommand = new IncrementCommand();
            Class firstClass = command.getClass();
            Class secondClass = incrementCommand.getClass();
            assertTrue((firstClass == secondClass));
        } catch (FactoryInitException e){
            System.out.println("factory creating failed");
        }
    }

    @Test(expected = CreatingCommandException.class)
    public void fourthCreateTest() throws CreatingCommandException, UnknownCommandNameException, FactoryInitException {
        try(Scanner scanner = new Scanner("[ -> org.example.commands.BeginO1fCycleCommand\n" +
                "] -> org.example.commands.EndOf1CycleCommand\n" +
                "> -> org.example.commands.NextC1ommand\n" +
                "< -> org.example.commands.Prev1Command\n" +
                ". -> org.example1.commands.OutputCommand\n" +
                ", -> org.example.commands.Inpu1tCommand\n" +
                "- -> org.example.comma1nds.DecrementCommand\n" +
                "+ -> org.exam1ple.commands.Incremen1tCommand")){

            Factory factory = new Factory(scanner);
            assertNull(factory.create(']'));
        } catch (FactoryInitException e){
            System.out.println("factory creating failed");
        }
    }
    @Test(expected = UnknownCommandNameException.class)
    public void fifthCreateTest() throws CreatingCommandException, UnknownCommandNameException, FactoryInitException {
        try(Scanner scanner = new Scanner("[ -> org.example.commands.BeginO1fCycleCommand\n" +
                "] -> org.example.commands.EndOf1CycleCommand\n" +
                "> -> org.example.commands.NextC1ommand\n" +
                "< -> org.example.commands.Prev1Command\n" +
                ". -> org.example1.commands.OutputCommand\n" +
                ", -> org.example.commands.Inpu1tCommand\n" +
                "- -> org.example.comma1nds.DecrementCommand\n" +
                "+ -> org.exam1ple.commands.Incremen1tCommand")){

            Factory factory = new Factory(scanner);
            assertNull(factory.create('*'));
        } catch (FactoryInitException e){
            System.out.println("factory creating failed");
        }
    }
    @Test(expected = FactoryInitException.class)
    public void sixthCreateTest() throws CreatingCommandException, UnknownCommandNameException, FactoryInitException {
        try(Scanner scanner = new Scanner("[fgergfu")){
            Factory factory = new Factory(scanner);
        } catch (FactoryInitException e){
            throw new FactoryInitException();
        }
    }
}