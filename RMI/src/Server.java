
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
            // using port 8081 and a localhost
            Registry reg = LocateRegistry.createRegistry(8083);
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
            result.set(i, Math.pow((double) result.get(i), power));
        }
        return result;
    }

    @Override
    public Vector logVector(Vector<Double> myvector, double base) throws RemoteException {
        // Return a vector result, where each element is equal to log in base "base" of myvector[i] 
        if (base < 1){
            System.out.println("Error, base must be > 1");
        }
        Vector<Double> result = myvector;
        int i;
        for(i = 0;i < result.size();i++){
            // uses the log's proprety: logb(n) = ln(n) / ln(b), where the ln uses the neperian basis
            result.set(i, Math.log((double) result.get(i))/Math.log(base));
        }
        return result;
    }

    @Override
    public Vector multiplyVector(Vector<Double> myvector, double n) throws RemoteException {
        // Return a vector result, where each element is equal to myvector[i] multiply by n
        Vector<Double> result = myvector;
        int i;
        for(i = 0;i < result.size();i++){
            double number = (double) result.get(i);
            result.set(i, number * n);
        }
        return result;
    }

    @Override
    public double sumVector(Vector myvector, double abs) throws RemoteException {
        // Return the sum of all elements in myvector. If vector = true return the sum of the absolute values
        double result = 0;
        int i;
        if(abs == 0){
            for(i = 0;i < myvector.size();i++){
                result = result + (double) myvector.get(i);
            }
        }
        else{
             for(i = 0;i < myvector.size();i++){
             result = result + abs((double) myvector.get(i));
            }
        }
        return result;
    }

    @Override
    public double normVector(Vector myvector, double norm) throws RemoteException {
        // return the n norm os myvector
        double result = 0;
        int i;
        for(i = 0;i < myvector.size();i++){
            result = result + Math.pow((double) myvector.get(i),norm);
        }
        result = Math.pow(result,1.0/norm);
        return result;
    }

    @Override
    public double edgeVector(Vector myvector, double edge) throws RemoteException {
        // return the min or max value of the value
        // edge = 1 o return max
        // other values of edge will return min
        double result = (double) myvector.get(0);
        int i;
        if(edge == 1){
            for(i = 0;i < myvector.size();i++){
                double number = (double) myvector.get(i);
                if(number > result){
                    result =  number;
                }   
            }
        }
        else{
            for(i = 0;i < myvector.size();i++){
                double number = (double) myvector.get(i);
                if(number < result){
                    result =  number;
                }   
            }
            
        }
        return result;
    }
}
