
import static java.lang.Math.abs;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
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
public class Server extends UnicastRemoteObject implements RMI{
    public Server() throws RemoteException{
        super();
    }
    
    public static void main(String args[]){
        try{
            // using port 8083 and a localhost
            Registry reg = LocateRegistry.createRegistry(8056);
            reg.rebind("server", new Server());
            System.out.print("Server started");
        }
        catch(Exception e){
            System.out.println(e);
        }
    }

    @Override
    public Vector powVector(Vector<Double> myvector, double power) throws RemoteException {
        // Return a vector result, where each element is equal to myvector[i]^power 
        Vector<Double> result = myvector;
        int i;
        for(i = 0;i < result.size();i++){
            result.set(i, (double)Math.pow(result.get(i), power));
        }
        return result;
    }

    @Override
    public Vector shiftVector(Vector<Double> myvector, double base) throws RemoteException {
        // Return a vector result, where each element is equal to myvector[i]  + base
        Vector<Double> result = myvector;
        int i;
        for(i = 0;i < result.size();i++){
            result.set(i, result.get(i) + base);
        }
        return result;
    }

    @Override
    public Vector multiplyVector(Vector<Double>myvector, double n) throws RemoteException {
        // Return a vector result, where each element is equal to myvector[i] multiply by n
        Vector<Double> result = myvector;
        int i;
        for(i = 0;i < result.size();i++){
            double number = result.get(i);
            result.set(i, number * n);
        }
        return result;
    }

    @Override
    public int sumVector(Vector myvector, int abs) throws RemoteException {
        // Return the sum of all elements in myvector. If abs = true return the sum of the absolute values
        int result = 0;
        int i;
        if(abs == 0){
            for(i = 0;i < myvector.size();i++){
                result = (int)myvector.get(i) + result;
            }
        }
        else{
             for(i = 0;i < myvector.size();i++){
             result = result + abs((int)myvector.get(i));
            }
        }
        return result;
    }

    @Override
    public int thresholdVector(Vector myvector, int k)throws RemoteException {
        int result = 0;
        int i;
        for(i = 0;i < myvector.size();i++){
            if((int)myvector.get(i) > k){
                result = result + 1;
            }
        }
        return result;
    }
    @Override
    public int evenVector(Vector myvector, int type) throws RemoteException {
        int odd = 0;
        int even = 0;
        int number;
        int i;
        for(i = 0;i < myvector.size();i++){
            if((int)myvector.get(i) % 2 == 0){
               even = even +1;
            }
            else{
               odd = odd +1;
            }
        }
        if(type == 1){
            return even;
        }
        else{
            return odd;
        }

    }
}
