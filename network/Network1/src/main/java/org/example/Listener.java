package org.example;

import sun.misc.Signal;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.HashMap;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

public class Listener {
    private Map<InetAddress, LocalDateTime> members = new HashMap<>();
    private int port;
    private InetAddress groupAddr;
    private int timeOut=5;
    private MulticastSocket multicastSocket;
    Listener(InetAddress groupAddr, int port) throws IOException {
        this.groupAddr=groupAddr;
        this.port=port;

        multicastSocket = new MulticastSocket(port);
        multicastSocket.joinGroup(groupAddr);
        Send((byte) 1, multicastSocket);

        Timer timer = new Timer();
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                Send((byte) 1, multicastSocket);
                deleteInactiveMembers();
                printMembers();
            }
        };
        timer.schedule(task, 0, timeOut* 1000L);

        Signal.handle(new Signal("INT"), signal -> leave(multicastSocket));
        listener();
    }

    private void listener() throws IOException {
        byte[] message = new byte[256];

        while(true){
            DatagramPacket datagramPacket = new DatagramPacket(message, message.length);
            multicastSocket.receive(datagramPacket);

            if(message[0]==1) {
                members.put(datagramPacket.getAddress(), LocalDateTime.now());
            } else{
                members.remove(datagramPacket.getAddress());
                printMembers();
            }
        }
    }

    private void Send(Byte message, MulticastSocket multicastSocket){
        DatagramPacket datagramPacket = new DatagramPacket(
                new byte[]{message}, 1, groupAddr, port);
        try {
            multicastSocket.send(datagramPacket);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void deleteInactiveMembers(){
        members.entrySet().removeIf(item -> ChronoUnit.SECONDS.between(item.getValue(), LocalDateTime.now()) > 2L *timeOut);
    }

    private void printMembers(){
        System.out.println("\n\n\n");
        System.out.println("members:");
        for(var item : members.entrySet()){
            System.out.println("\t"+item.getKey());
        }
        System.out.println("\n\n\n");
    }

    private void leave(MulticastSocket multicastSocket){
        Send((byte) 2, multicastSocket);
        System.exit(0);
    }
}
