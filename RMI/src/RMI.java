
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
    public Vector powVector(Vector<Double> myvector,double power) throws RemoteException;
    public Vector logVector(Vector<Double> myvector,double base) throws RemoteException;
    public Vector multiplyVector(Vector<Double> myvector,double n) throws RemoteException;
    // Methods of type 2
    public double sumVector(Vector myvector, double abs) throws RemoteException;
    public double normVector(Vector myvector, double norm) throws RemoteException;
    public double edgeVector(Vector myvector,double edge) throws RemoteException;
} 