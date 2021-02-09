import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

class Hacker implements Runnable {
    @Override
    public void run() {
        // TODO do as the problem description
        while (true) {
            try (Socket socket = new Socket(InetAddress.getLoopbackAddress(), 11111);
                 PrintWriter pw = new PrintWriter(socket.getOutputStream())) {
                int key = Cloud.getKey(), data = Cloud.getData();
                pw.println(key ^ data);
                pw.flush();
                synchronized (Cloud.class){
                    Cloud.class.wait();
                }
            } catch (IOException | InterruptedException e) {
               break;
            }
        }
    }
}
