
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;
import java.util.Vector;
import java.util.concurrent.ThreadLocalRandom;
import java.util.logging.Level;
import java.util.logging.Logger;


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

public class Client {
    public static int resultINT;
    public static Vector<Vector<Double>> resultVEC = new Vector<Vector<Double>>();
    public static void main(String args[]) throws RemoteException{
        Vector myvector = new Vector();
        int threads = Integer.parseInt(args[0]);
        int function = Integer.parseInt(args[1]);
        int functionArgument = Integer.parseInt(args[2]);
        int n = 10000000;
        int chunkSize = n/threads;
        int i = 0;
        int j;
        Vector<Vector<Double>> chunks = new Vector<Vector<Double>>();
          while(i < n){
              Vector<Double> tempChunck = new Vector<Double>();
              for(j = 0;j < chunkSize;j++){
                    double randomNum = ThreadLocalRandom.current().nextInt(1, 100 + 1);
                    myvector.add(randomNum);
                    tempChunck.add(randomNum);
              }
              chunks.add(tempChunck);
              i = i + chunkSize;
          }
          List<Thread> threadList = new ArrayList<Thread>();
          long startTime = System.currentTimeMillis();
          for(i = 0;i< threads;i++){
            ServerCall s = new ServerCall();
            s.setFunction(function);
            s.setFunctionParameter(functionArgument);
            s.setVector(chunks.get(i));
            Thread t1 = new Thread(s);
            t1.start();
            threadList.add(t1);
          }
          for(Thread t : threadList) {
            try {
                t.join();
            } catch (InterruptedException ex) {
                Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
            }
          }
          long estimatedTime = System.currentTimeMillis() - startTime;
          
          System.out.println("Estimated time: "+ estimatedTime + " milissegundos");
//          if(function < 3){
//            System.out.println("Resultado: "+ resultVEC);
//          }
//          else{
//            System.out.println("Resultado: "+ resultINT);
//          }
    }

}
