import java.net.*;

import javax.swing.JOptionPane;

import java.awt.Component;
import java.io.*;

public class Server {

  private static final Component JFrame = null;
  ServerSocket listenSocket;
  Socket connection;
  private ServerThread clients[] = new ServerThread[2];// array to keep clients
  private int counter;
  OutputStream outStream;
  DataOutputStream outDataStream;
  InputStream inStream;
  DataInputStream inDataStream;
  String message;

  boolean listening = true;

  // checks the client
  private int findClient(int ID) {
    for (int i = 0; i < counter; i++)
      if (clients[i].getID() == ID)
        return i;
    return -1;
  }

  // checks the client and forwards the message other than sender
  public synchronized void handle(int ID, String input) {
    int index = findClient(ID);
    if (input.equals(".bye")) {
      clients[index].send(".bye");
    }
    // remove(ID); }
    else
      for (int i = 0; i < counter; i++) {
        if (index != i)
          clients[i].send(input);
      }
  }

  // creates socket connection at the specified port
  public void runServer() {
    try {
      listenSocket = new ServerSocket(8930);

      try {
        InetAddress here = InetAddress.getLocalHost();
        String host = here.getHostName();
        JOptionPane.showMessageDialog(JFrame, host + ", port 8930\n Server Started");
      } catch (UnknownHostException e) {
        // System.out.println ( "Problem with local host\n" );
      }
    } 

    catch (IOException except) {
      except.printStackTrace();
    }

    while (listening) {
      try {
        clients[counter] = new ServerThread(this, listenSocket.accept());
        clients[counter].start();
      } catch (IOException e) {
        e.printStackTrace();
      }
      counter++;
    }

    try {
      listenSocket.close();
    } catch (IOException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }
  } 

  public static void main(String[] args) {
    Server server = new Server();
    server.runServer();
  }
}
