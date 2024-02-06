package org.example.Server;

import java.util.Scanner;

public class Main {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        System.out.println("enter port");
        //int port = scanner.nextInt();
        int port = 2000;
        Server server = new Server(port);
    }
}
