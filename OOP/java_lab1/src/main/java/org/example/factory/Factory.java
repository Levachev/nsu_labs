package org.example.factory;

import org.example.commands.ICommand;
import org.jetbrains.annotations.NotNull;

import java.util.HashMap;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Factory {
    private final Map<Character, String> configMap;

    public Factory(@NotNull Scanner scanner) throws FactoryInitException {
        try {
            configMap = new HashMap<>();
            while (scanner.hasNext()) {
                String firstLine = scanner.next();
                scanner.next();
                String secondLine = scanner.next();
                configMap.put(firstLine.charAt(0), secondLine);
            }
        } catch (NoSuchElementException e){
            throw new FactoryInitException();
        }
    }

    public ICommand create(Character commandName) throws CreatingCommandException, UnknownCommandNameException {
        String className = configMap.get(commandName);
        try {
            return (ICommand)(Class.forName(className).getClassLoader().loadClass(className).newInstance());
        } catch (InstantiationException | IllegalAccessException | ClassNotFoundException e) {
            throw new CreatingCommandException();
        } catch (NullPointerException e) {
            throw new UnknownCommandNameException();
        }
    }
}
