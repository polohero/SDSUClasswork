
/**
 * The class that runs the first assignment for CS 310.
 * 
 * @author cwixom (masc0582)
 * @since  01/24/2012
 */
public class Assignment0 {

	/**
	 * The main method in the Assignment0 class
	 * that runs Assignment0.
	 * 
	 * @param args The arguments passed to the main method.
	 */
	public static void main(String[] args) { 
		
        long elapsed, time=0;                        

        for (int n=100; n < 1000; n *= 2) { 
        		// Set the time variable. This will be used
        		// later to output the time the loops have run.
                time = System.nanoTime();     
                int [] x = new int[n];   
                
                // Loop through x.
                for (int i=1; i<n; i++)       
                        x[i]=x[i-1]*2;               

                // Set the time that was elapsed for the loop
                // and print it out.
                elapsed = System.nanoTime() - time;  
                System.out.print(n + "\t" + elapsed); 

                // Reset time. We will run another loop to measure
                // the time again.
                time = System.nanoTime();    

                x=new int[n];  
                
                // Loop again. 
                for (int i=1; i<n; i++)    
                        for (int j=1; j<n; j++)  
                                x[j]=x[j-1]*2;  

                // Set the elapsed time for the 
                // nested loops and print it out.
                elapsed = System.nanoTime() - time;  
                System.out.println("\t" + elapsed);  
        }   
	}   
}
