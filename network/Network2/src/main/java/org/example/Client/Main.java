package org.example.Client;

import java.io.IOException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {

        String hostName = null;
        int port = -1;
        String fileName = null;


        try(Scanner scanner = new Scanner(System.in)){
            System.out.println("enter file name");
            fileName = scanner.nextLine();
// /home/roman/tmp.txt
            System.out.println("enter host name and port");
            hostName = scanner.next();
            port = scanner.nextInt();
        } catch (NoSuchElementException e){
            System.out.println("bad input???");
        }

        Client client = new Client(hostName, port, fileName);

        client.execute();
    }

}
