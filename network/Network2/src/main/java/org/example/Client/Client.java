package org.example.Client;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;

public class Client {
    private final Socket clientSocket;
    private FileInputStream fileReader;
    private BufferedOutputStream output;
    private BufferedInputStream input;
    private String fileName;
    private String fileFullName;

    Client(String host_name, int port, String fileName) throws IOException {
        fileFullName = fileName;
        clientSocket = new Socket(host_name, port);

        try {
            output = new BufferedOutputStream(clientSocket.getOutputStream());
            input = new BufferedInputStream(clientSocket.getInputStream());
        } catch (IOException e){
            e.printStackTrace();
        }

        try {
            fileReader = new FileInputStream(fileName);
        } catch (FileNotFoundException e){
            System.out.println("bad file???");
        }

        this.fileName = new File(fileName).getName();
    }

    public void execute() throws IOException {
        int minByteLen = getMinBufSize();

        //System.out.println("minByteLen - " + minByteLen);

        //System.out.println("file name - "+fileName);

        long fileLen = Files.size(Path.of(fileFullName));

        System.out.println(fileLen);

        send(ByteBuffer.allocate(Long.BYTES).putLong(fileLen).array(), 0, 8);

        byte[] name = fileName.getBytes();

        send(ByteBuffer.allocate(Integer.BYTES).putInt(fileName.length()).array(), 0, 4);

        send(name, 0, name.length);
        //System.out.println("fileLen "+fileLen);

        byte[] buff1;
        try {
            buff1 = new byte[4];
            int len = input.read(buff1, 0, 4);
            //System.out.println("len "+len);
            if(len!=4){
                System.out.println("1close3");
                clientSocket.close();
                return;
            }
        } catch (IOException e) {
            System.out.println("1close4");
            clientSocket.close();
            return;
        }

        if(ByteBuffer.wrap(buff1).getInt() != 1){
            System.out.println("not success");
            clientSocket.close();
            return;
        }


        try {
            for(int i=0;i<fileLen/minByteLen;i++){
                byte[] buff = new byte[(int) minByteLen];
                int len = fileReader.read(buff, 0, minByteLen);
                if(len!=minByteLen){
                    System.out.println("close");
                    allClose();
                    return;
                }
                sendContent(buff, minByteLen);
            }
            //System.out.println("ost "+fileLen%minByteLen);
            if(fileLen%minByteLen!=0){
                byte[] buff = new byte[(int) (fileLen%minByteLen)];
                int len = fileReader.read(buff, 0, (int) (fileLen%minByteLen));
                //System.out.println("file len "+len);
                if(len!=fileLen%minByteLen){
                    System.out.println("close2");
                    allClose();
                    return;
                }
                sendContent(buff, minByteLen);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        //System.out.println("end((((");

        byte[] buff;
        try {
            buff = new byte[4];
            int len = input.read(buff, 0, 4);
            //System.out.println("len "+len);
            if(len!=4){
                System.out.println("close3");
                return;
            }
        } catch (IOException e) {
            System.out.println("close4");
            return;
        }

        int request = ByteBuffer.wrap(buff).getInt();

        if(request==1){
            System.out.println("success");
        } else{
            System.out.println("not success");
        }
    }

    private void allClose() throws IOException {
        clientSocket.close();
        fileReader.close();
        input.close();
        output.close();
    }

    private void sendContent(byte[] buff, int minByteLen){
        for(int i=0;i<buff.length/minByteLen;i++){
            //System.out.println();
            send(ByteBuffer.allocate(Integer.BYTES).putInt(minByteLen).array(), 0, 4);
            //output.write(minByteLen);
            send(buff, i*minByteLen, minByteLen);
            //output.write(buff, 0, minByteLen);
        }
        if(buff.length%minByteLen!=0){
            send(ByteBuffer.allocate(Integer.BYTES).putInt(buff.length%minByteLen).array(), 0, 4);
            //output.write(buff.length%minByteLen);
            send(buff, (buff.length/minByteLen)*minByteLen, buff.length%minByteLen);
            //output.write(buff, 0, buff.length%minByteLen);
        }
    }

    private int send(byte[] buff, int offset, int len){
        try {
            output.write(buff, offset, len);
            output.flush();
            return 1;
        } catch (IOException e) {
            return -1;
        }
    }

    private byte[] read(int getLen){
        byte[] buff;
        try {
            buff = new byte[getLen];
            int len = input.read(buff, 0, getLen);
            if(len!=getLen){
                return null;
            }
            return buff;
        } catch (IOException e) {
            return null;
        }
    }

    private int getMinBufSize(){
        try {
            int code = -1;
            output.write(ByteBuffer.allocate(4).putInt(code).array(), 0, 4);
            output.flush();

            byte[] buff;
            try {
                buff = new byte[4];
                int len = input.read(buff, 0, 4);
                if(len!=4){
                    return -1;
                }
            } catch (IOException e) {
                return -1;
            }

            return ByteBuffer.wrap(buff).getInt();
        } catch (IOException e) {
            return -1;
        }
    }

}
