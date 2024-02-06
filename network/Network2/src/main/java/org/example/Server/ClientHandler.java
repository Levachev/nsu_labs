package org.example.Server;

import java.io.*;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;
import java.util.Timer;
import java.util.TimerTask;

public class ClientHandler implements Runnable {
    private InputStream inputStream;
    private OutputStream outputStream;
    private LocalDateTime beginTime;
    private double currentGetBytes;
    private double allGetBytes;
    private int windowBuff;
    private final Socket socket;
    private final int number;

    public ClientHandler(Socket socket, int number) {
        this.number=number;
        this.socket=socket;
        currentGetBytes=0;
        allGetBytes = 0;
        try {
            windowBuff = socket.getReceiveBufferSize();
            inputStream = socket.getInputStream();
            outputStream = socket.getOutputStream();
        } catch (IOException ex) {
            ex.printStackTrace();
        }


    }

    @Override
    public void run() {
        //System.out.println("number start "+number);;

        beginTime = LocalDateTime.now();

        Timer timer = new Timer();
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                double mngnoven = currentGetBytes / 3d;

                double mainDiff = ChronoUnit.SECONDS.between(beginTime, LocalDateTime.now());
                double sred = allGetBytes / mainDiff;

                System.out.println("mngnoven - " + mngnoven/1024);
                System.out.println("sred - " + sred/1024);
                currentGetBytes = 0;
            }
        };
        timer.schedule(task, 0, 3 * 1000L);

        if (!getRequest()) {
            System.out.println("close1");
            return;
        }

        long fileLen = getFileLen();

        //System.out.println("fileLen " + fileLen);
        if (fileLen == -1) {
            System.out.println("close2");
            return;
        }

        String origFileName = getFileName();

        if(origFileName!=null){
            send(1);
        } else{
            send(0);
        }

        //System.out.println(origFileName);

        String fileName = origFileName;

        try {
            int tmp = 1;
            File myObj = new File("./uploads/" + fileName);
            while (!myObj.createNewFile()) {
                fileName = origFileName + "(" + tmp + ")";
                myObj = new File("./uploads/" + fileName);
                tmp++;
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        FileOutputStream fileReader;

        try {
            fileReader = new FileOutputStream("./uploads/" + fileName);
        } catch (FileNotFoundException e) {
            send(0);
            try {
                System.out.println("close3");
                allClose();
            } catch (IOException ignored) {
            }
            throw new RuntimeException(e);
        }


        long fullGetLen = 0;
        beginTime = LocalDateTime.now();
        while (true) {
            //System.out.println("in while");
            if (fullGetLen >= fileLen) {
                break;
            }
            byte[] byteLen;
            try {
                byteLen = new byte[4];
                //System.out.println("before 1read "+number);
                int len = inputStream.read(byteLen, 0, 4);
                //System.out.println("after 1read "+number);
                //System.out.println("data len - " + len);
                if (len != 4) {
                    try {
                        System.out.println("close4");
                        allClose();
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }

                    return;
                }
            } catch (IOException e) {
                try {
                    allClose();
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
                throw new RuntimeException(e);
            }
            int len = getInt(byteLen);

            //System.out.println("while len " + len);

            byte[] message = new byte[len];
            try {
                int getLen=0;
                //System.out.println("before 2read "+number);
                while(getLen!=len){
                    getLen += inputStream.read(message, getLen, len-getLen);
                }
                //System.out.println("after 2read "+number);
                if (getLen != len) {
                    System.out.println(getLen + " " + len);
                    try {
                        System.out.println("close5");
                        allClose();
                    } catch (IOException ex) {
                        throw new RuntimeException(ex);
                    }
                    return;
                }
                fullGetLen += getLen;
                //System.out.println("fullGetLen " + fullGetLen);
                currentGetBytes += (getLen + 4);
                allGetBytes += (getLen + 4);
                fileReader.write(message, 0, len);
            } catch (IOException e) {
                try {
                    System.out.println("close6");
                    allClose();
                } catch (IOException ex) {
                    throw new RuntimeException(ex);
                }
                throw new RuntimeException(e);
            }
        }

        double mngnoven = currentGetBytes / 3000d;

        double mainDiff = ChronoUnit.MILLIS.between(beginTime, LocalDateTime.now());
        double sred = allGetBytes / mainDiff;

        /*System.out.println("allGetBytes "+allGetBytes);
        System.out.println("mainDiff "+mainDiff);*/

        System.out.println("mngnoven - " + mngnoven/1024);
        System.out.println("sred - " + sred/1024);

        //System.out.println("fullGetLen " + fullGetLen);

        //System.out.println("before send");
        if (fullGetLen == fileLen){
            send(1);
        } else{
            send(0);
        }
        //System.out.println("after send");
        Server.number.decrementAndGet();

        //System.out.println("end of "+number);

        System.out.println();

        timer.cancel();

        try {
            allClose();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void send(int request){
        try {
            outputStream.write(ByteBuffer.allocate(4).putInt(request).array());
            outputStream.flush();
        } catch (IOException e) {
            throw new RuntimeException();
        }
    }

    private long getFileLen(){
        byte[] fileLen;
        try {
            fileLen = new byte[8];
            int len = inputStream.read(fileLen, 0, 8);
            //System.out.println("len - " + len);
            if(len!=8){
                return -1;
            }
        } catch (IOException e) {
            return -1;
        }
        return ByteBuffer.wrap(fileLen).getLong();
    }

    private void allClose() throws IOException {
        socket.close();
        inputStream.close();
        outputStream.close();
    }

    private String getFileName(){
        byte[] fileByteLen;
        try {
            fileByteLen = new byte[4];
            int len = inputStream.read(fileByteLen, 0, 4);
            //System.out.println("len - " + len);
            if(len!=4){
                return null;
            }
        } catch (IOException e) {
            send(0);
            try {
                allClose();
            } catch (IOException ignored) {
            }
            return null;
        }
        int FileLen = getInt(fileByteLen);

        //System.out.println("file name len "+FileLen);

        byte[] fileNameMessage = new byte[FileLen];
        try {
            inputStream.read(fileNameMessage, 0, FileLen);
        } catch (IOException e) {
            send(0);
            try {
                allClose();
            } catch (IOException ignored) {
            }
            throw new RuntimeException(e);
        }
        return new String(fileNameMessage);
    }

    private boolean getRequest(){
        byte[] request;
        try {
            request = new byte[4];
            int len = inputStream.read(request, 0, 4);
            //System.out.println("len - " + len);
            if(len!=4){
                return false;
            }
        } catch (IOException e) {
            send(0);
            try {
                allClose();
            } catch (IOException ignored) {
            }
            return false;
        }
        int requestCode = getInt(request);
        //System.out.println(requestCode);
        //System.out.println(windowBuff);
        if(requestCode == -1){
            try {
                outputStream.write(ByteBuffer.allocate(4).putInt(windowBuff).array());
                outputStream.flush();
            } catch (IOException e) {
                return false;
            }
        }
        return true;
    }

    private void allClose(FileOutputStream fileReader) {
        if(fileReader!=null){
            try {
                fileReader.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        try {
            inputStream.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private int getInt(byte[] bytes){
        return ByteBuffer.wrap(bytes).getInt();
    }
}