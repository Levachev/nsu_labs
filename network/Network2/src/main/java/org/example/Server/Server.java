package org.example.Server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.atomic.AtomicInteger;


public class Server {
    private ServerSocket serverSocket;
    public static AtomicInteger number = new AtomicInteger(0);

    public Server(int port) {
        Socket clientSocket = null;

        try {
            serverSocket = new ServerSocket(port);
            while (true) {
                while(number.get() >=5){
                    Thread.sleep(1);
                }
                clientSocket = serverSocket.accept();
                number.incrementAndGet();
                ClientHandler client = new ClientHandler(clientSocket, number.get());
                new Thread(()->{

                }).start();
            }
        }
        catch (IOException ex) {
            ex.printStackTrace();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        } finally {
            try {
                clientSocket.close();
                System.out.println("Сервер остановлен");
                serverSocket.close();
            }
            catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }

}