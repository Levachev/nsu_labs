package org.example;
import org.example.factory.FactoryInitException;
import org.example.logic.Process;
import org.example.factory.Factory;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.example.logic.ProcessFailedException;
import org.jetbrains.annotations.NotNull;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {
    public static final Logger logger = LogManager.getLogger(Main.class);
    public static @NotNull String parseInput(String fileName){
        StringBuilder code = new StringBuilder();
        File file =new File(fileName);
        try {
            logger.info("Open scanner");
            Scanner scanner =new Scanner(file);
            logger.info("Reading lines in cycle, creating main line");
            while(scanner.hasNextLine()){
                String line = scanner.nextLine();
                code.append(line);
            }
            logger.info("Close scanner");
            scanner.close();
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        return code.toString();
    }
    public static void main(String @NotNull [] args){
        
        String configFileName = null;
        String executeFileName = null;
        if(args.length == 2){
            executeFileName = args[0];
            configFileName = args[1];
        } else if(args.length == 1){
            executeFileName = args[0];
            Scanner in = new Scanner(System.in);
            System.out.println("Input name of config file please");
            configFileName = in.nextLine();
            in.close();
        }
        else if(args.length == 0){
            Scanner in = new Scanner(System.in);
            System.out.println("Input name of execute file please");
            executeFileName = in.nextLine();
            System.out.println("Input name of config file please");
            configFileName = in.nextLine();
            in.close();
        } else {
            System.out.println("too much arguments, error!!!");
            return;
        }

         
        logger.info("Begin of main method");
        File file = new File(configFileName);

        try (Scanner scanner = new Scanner(file)){
            logger.info("Begin of creating factory");
            Factory factory = new Factory(scanner);
            logger.info("End of creating factory");
            logger.info("Begin of initialization factory");
            //initFactory();
            logger.info("End of initialization factory");
            logger.info("Begin of parsing file with content");
            String code = parseInput(executeFileName);
            logger.info("End of parsing file with content");

            logger.info("Begin of initialization process");
            Process p = new Process(code, factory);
            logger.info("End of initialization process");
            logger.info("Begin of running process");
            try {
                p.run();
            } catch (ProcessFailedException e){
                System.out.println("process failed, error!");
                return;
            }
            logger.info("End of running process");
            logger.info("Finish of main method");
        } catch (FactoryInitException e){
            System.out.println("wrong config file, error!");
        } catch (FileNotFoundException e) {
            System.out.println("this config file not exist, error!");
        }
    }
}