package org.example;

import java.io.IOException;
import java.net.*;


public class Main {

    public static void main(String[] args) throws IOException {
        String groupIP;
        InetAddress groupAddr;
        int port;

        if(args.length != 2){
            System.out.println("not correct input");
            return;
        } else {
            groupIP = args[0];
            port = Integer.parseInt(args[1]);
        }

        try {
            groupAddr = InetAddress.getByName(groupIP);
        } catch (UnknownHostException e) {
            System.out.println("not correct group address");
            return;
        }

        if(!isAddrValid(groupAddr)){
            System.out.println("not correct group address");
            return;
        }

        Listener listener = new Listener(groupAddr, port);
    }

    private static boolean isAddrValid(InetAddress address) {
        if (address instanceof Inet6Address) {
            String addr = address.getHostAddress();
            return addr.startsWith("ff02");
        } else if (address instanceof Inet4Address) {

            byte[] bytes = address.getAddress();
            return (bytes[0] & 0xFF) == 224 && (bytes[1] & 0xFF) == 0 &&
                    (bytes[2] & 0xFF) == 0 && (bytes[3] & 0xFF) > 0;
        } else {
            return false;
        }
    }
}