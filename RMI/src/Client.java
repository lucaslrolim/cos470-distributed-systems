
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
    public static Vector<Integer> resultVEC;
    public static void main(String args[]) throws RemoteException{
        Vector myvector = new Vector();
        int function = Integer.parseInt(args[0]);
        int functionArgument = Integer.parseInt(args[1]);
//        int n = 100000000;
        int n = 100;
        int threads = 10;
        int chunkSize = 10;
        int i = 0;
        int j;
        Vector<Vector<Integer>> chunks = new Vector<Vector<Integer>>();
          while(i < n){
              Vector<Integer> tempChunck = new Vector<Integer>();
              for(j = 0;j < chunkSize;j++){
                    int randomNum = ThreadLocalRandom.current().nextInt(1, 30 + 1);
                    myvector.add(randomNum);
                    tempChunck.add(randomNum);
              }
              chunks.add(tempChunck);
              i = i + chunkSize;
          }
          System.out.println(myvector);
          System.out.println("----");
          System.out.println(chunks);
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
                // waits for this thread to die
                t.join();
            } catch (InterruptedException ex) {
                Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
            }
          }
          long estimatedTime = System.currentTimeMillis() - startTime;
          
          System.out.println("Estimated time: "+ estimatedTime + " milissegundos");
          System.out.println("Resultado: "+ resultINT);
    }

}
