package org.example.logic;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.commands.ICommand;
import org.example.factory.CreatingCommandException;
import org.example.factory.Factory;
import org.example.factory.UnknownCommandNameException;
import org.jetbrains.annotations.NotNull;

import java.util.Scanner;

public class Process {
    public static final Logger logger = LogManager.getLogger(Process.class);
    private final Context context;
    private final Factory myFactory;
    private final Scanner scanner;
    public Process(@NotNull String inputCode, Factory inputFactory) {
        logger.info("Begin of constructor");
        logger.info("Begin of initialization fields of Process class");
        scanner = new Scanner(System.in);
        context = new Context(inputCode, scanner);
        myFactory=inputFactory;
        logger.info("End of initialization fields of Process class");
        logger.info("End of constructor");
    }
    public void run() throws ProcessFailedException {
        logger.info("Begin of method run in class Process");
        logger.info("Start interpreting program");
        while(context.hasNextCommand()){
            char command = context.getCodeSymbol();
            if(command == ' ' || command == '\n'){
                context.incrementPointerOfCode();
                continue;
            }
            try {
                ICommand outputCommand = myFactory.create(command);
                outputCommand.execute(context);
            } catch(CreatingCommandException e){
                System.out.println("config file has name of class, which not exist, error!");
                scanner.close();
                throw new ProcessFailedException();

            } catch(UnknownCommandNameException e){
                System.out.println("unknown command symbol in execute file, error!");
                scanner.close();
                throw new ProcessFailedException();
            }
            context.incrementPointerOfCode();
        }
        logger.info("Finish interpreting program");
        logger.info("Close scanner of context");
        scanner.close();
        logger.info("End of method run in class Process");
    }
}
