
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author lucas
 */
public class Client {
    public static void main(String args[]) throws RemoteException{
        Client client = new Client();
        client.connectServer();
    }

    private void connectServer() throws RemoteException {
      try{
          // Conecting to the server
          Registry reg = LocateRegistry.getRegistry("127.0.0.1",8083);
          RMI rmi = (RMI) reg.lookup("server");
          //
          
          System.out.println("Connected to the server");
          Vector myvector = new Vector();
          myvector.add((double)1);
          myvector.add((double)2);
          myvector.add((double)3);
          double pow = 2;
          double resultVector = rmi.sumVector(myvector,false);
          //Enumeration e = resultVector.elements();
          //while (e.hasMoreElements()) {         
          //   System.out.println("Number = " + e.nextElement());
          //} 
          System.out.println(resultVector);
    }
      catch(Exception e){
          System.out.println(e);
      }
    }
}
