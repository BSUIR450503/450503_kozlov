import java.net.*;
import java.io.*;

public class ServerThread extends Thread {
  private Socket socket = null;
  private int ID = -1;
  private Server callback = null;
  OutputStream outStream;
  DataOutputStream outDataStream;
  InputStream inStream;
  DataInputStream inDataStream;

  // passes the socket and the server object to the thread
  public ServerThread(Server _server, Socket socket) {
    super("CarServerThread");
    this.socket = socket;
    this.callback = _server;
    this.ID = socket.getPort();
  }

  // sends the message
  public void send(String message) {
    try {
      outDataStream.writeUTF(message);
      outDataStream.flush();
    } catch (IOException ioe) {
      // System.out.println(ID + " ERROR sending: " + ioe.getMessage());
    }
  }

  public int getID() {
    return ID;
  }

  // runs thread to receive and send the message
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
