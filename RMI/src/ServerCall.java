
import java.util.Vector;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ServerCall implements Runnable{
    private Vector<Integer> vector = new Vector<Integer>();
    private int function;
    private int functionParameter;
    public Vector<Integer> resultVec;
    public int resultINT;
    // Setters
    public void setFunction(int function){
        this.function = function;
    }
    public void setFunctionParameter(int functionParameter){
        this.functionParameter = functionParameter;
    }
    public void setVector(Vector<Integer> vector){
        this.vector = vector;
    }
    
    // gettlers
    
    public int getFunction(){
        return function;
    }
    public int getFunctionParameter(){
        return functionParameter;
    }
    public Vector<Integer> getVector(){
        return vector;
    }
    public Vector<Integer> getResultVector(){
        return resultVec;
    }
    public int getResultInt(){
        return resultINT;
    }
            
    @Override
    public void run() {
        try {
            connectServer(function,functionParameter,vector);
        } catch (RemoteException ex) {
            Logger.getLogger(ServerCall.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    private void connectServer(int function, int functionArgument,Vector<Integer> myvector) throws RemoteException {
      try{
          
        //  function = 0  powVector
        //  function = 1 public shiftVector
        //  function = 2  public multiplyVector
        //  Methods of type 2
        //  function = 3 sumVector
        //  function = 4 normVector
        //  function = 5 edgeVector
        
          // Conecting to the server
          Registry reg = LocateRegistry.getRegistry("127.0.0.1",8056);
          RMI rmi = (RMI) reg.lookup("server");
          //

          switch(function){
              case 0:
                Vector<Integer> resultVector = rmi.powVector(myvector,functionArgument);
                this.resultVec = resultVector;
                break;
              case 1:
                Vector<Integer> resultVector1 = rmi.shiftVector(myvector,functionArgument);
                this.resultVec = resultVector1;
                break;
              case 2:
                Vector<Integer> resultVector2 = rmi.multiplyVector(myvector,functionArgument);
                System.out.println(resultVector2);
                this.resultVec = resultVector2;
                break;
              case 3:
                int resultVector3 = rmi.sumVector(myvector,functionArgument);
                Client.resultINT = Client.resultINT + resultVector3;
                 System.out.println("sumVector");
                break;
              case 4:
                int resultVector4 = rmi.thresholdVector(myvector,functionArgument);
                Client.resultINT = Client.resultINT + resultVector4 ;
                break;
              case 5:
                int resultVector5 = rmi.evenVector(myvector,functionArgument);
                Client.resultINT = Client.resultINT + resultVector5;
                System.out.println("evenVector");
                break;
              case 6:        
                 break;
          }

                
    }
      catch(Exception e){
          System.out.println(e);
      }
    }
    
}
