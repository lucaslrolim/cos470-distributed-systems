
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Vector;
import java.util.concurrent.ThreadLocalRandom;
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
        Vector myvector = new Vector();
        int function = Integer.parseInt(args[0]);
        double functionArgument = Double.parseDouble(args[1]);
        int n = 100000000;
        int i;
        for(i =0; i < n;i++){
            double randomNum = ThreadLocalRandom.current().nextInt(1, 30 + 1);
            myvector.add(randomNum);
        }
        client.connectServer(function,functionArgument,myvector);
    }

    private void connectServer(int function, double functionArgument,Vector<Double> myvector) throws RemoteException {
      try{
          
        //  function = 0  powVector
        //  function = 1 public logVector
        //  function = 2  public multiplyVector
        //  Methods of type 2
        //  function = 3 sumVector
        //  function = 4 normVector
        //  function = 5 edgeVector
        
          // Conecting to the server
          Registry reg = LocateRegistry.getRegistry("127.0.0.1",8083);
          RMI rmi = (RMI) reg.lookup("server");
          //

          System.out.println("Connected to the server");
          long startTime = System.currentTimeMillis();
          switch(function){
              case 0:
                Vector<Double> resultVector = rmi.powVector(myvector,functionArgument);
                System.out.println(resultVector);
                break;
              case 1:
                Vector<Double> resultVector1 = rmi.logVector(myvector,functionArgument);
                System.out.println(resultVector1);
                break;
              case 2:
                Vector<Double> resultVector2 = rmi.multiplyVector(myvector,functionArgument);
                System.out.println(resultVector2);
                break;
              case 3:
                double resultVector3 = rmi.sumVector(myvector,functionArgument);
                System.out.println(resultVector3);
                break;
              case 4:
                double resultVector4 = rmi.normVector(myvector,functionArgument);
                System.out.println(resultVector4);
                break;
              case 5:
                double resultVector5 = rmi.edgeVector(myvector,functionArgument);
                System.out.println(resultVector5);
                break;                
          }
          long estimatedTime = System.currentTimeMillis() - startTime;
          System.out.println("Estimated time: "+ estimatedTime + " milissegundos");
                
    }
      catch(Exception e){
          System.out.println(e);
      }
    }
}
