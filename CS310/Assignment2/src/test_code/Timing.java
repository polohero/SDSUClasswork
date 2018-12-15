package test_code;

public class Timing{
	public Timing(){
		average = 0;
		max = 0;
		min = 0;
		stdDev = 0;
		iterations = 0;
	}
	public long average;
	public long max;
	public long min;
	public long stdDev;
	public long iterations;
	public long totalTime;
	
	public String toString(){
		String returnString = "Timing:\n";
		returnString += "Average: " + average;
		returnString += "\nMax: " + max;
		returnString += "\nMin: " + min;
		returnString += "\nstdDev: " + stdDev;
		returnString += "\niterations: " + iterations;
		
		return returnString;
	}
}