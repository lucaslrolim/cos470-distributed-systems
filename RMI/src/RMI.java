
import java.rmi.Remote;
import java.rmi.RemoteException;
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
public interface RMI extends Remote {
    // Methods of type 1
    public Vector powVector(Vector<Integer> myvector,int power) throws RemoteException;
    public Vector shiftVector(Vector<Integer> myvector,int base) throws RemoteException;
    public Vector multiplyVector(Vector<Integer> myvector,int n) throws RemoteException;
    //public Vector getChunckVector(Vector<Integer> myvector,int sIndex,int eIndex) throws RemoteException;
    // Methods of type 2
    public int sumVector(Vector myvector, int abs) throws RemoteException;
    public int thresholdVector(Vector myvector, int norm) throws RemoteException;
    public int evenVector(Vector myvector,int edge) throws RemoteException;
} 