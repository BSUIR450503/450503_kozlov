import java.net.*;
import java.io.*;

public class ServerThread extends Thread {
  private Socket socket;
  private int ID;
  private Server callback;
  OutputStream outStream;
  DataOutputStream outDataStream;
  InputStream inStream;
  DataInputStream inDataStream;

  public ServerThread(Server server, Socket socket) {
    this.socket = socket;
    this.callback = server;
    this.ID = socket.getPort();
  }

  public void send(String message) {
    try {
      outDataStream.writeUTF(message);
      outDataStream.flush();
    } catch (IOException ioe) {
    }
  }

  public int getID() {
    return ID;
  }

  public void run() {
    try {
      outStream = socket.getOutputStream();
      outDataStream = new DataOutputStream(outStream);
      inStream = socket.getInputStream();
      inDataStream = new DataInputStream(inStream);

      String inputLine;

      while ((inputLine = inDataStream.readUTF()) != null) {
        callback.handle(ID, inputLine);
      }
      socket.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}
