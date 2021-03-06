import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class MedianFilter {
	private int numRow;
	private int numCol;
	private int minVal;
	private int maxVal;
	private int newMin;
	private int newMax;
	private int[][] mirrorFramedAry;
    private int[][] tempAry;
    private int newghborAry[] = new int[9];
	private File file1, file2;
    private Scanner scan;
    private java.io.PrintStream out;
    
    public MedianFilter(String input, String output){
    	file1 = new File(input);
    	file2 = new File(output);
    	
    	try {
			scan = new Scanner(file1);
			if(scan.hasNextInt()) numRow = scan.nextInt();
			if(scan.hasNextInt()) numCol = scan.nextInt();
			if(scan.hasNextInt()) minVal = scan.nextInt();
			if(scan.hasNextInt()) maxVal = scan.nextInt();
			
			mirrorFramedAry = new int[numRow+2][numCol+2];
			tempAry = new int[numRow+2][numCol+2];

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
    }
    
    public void loadImage(){
    	for(int i=1; i<=numRow; i++){
			for(int j=1; j<=numCol; j++){
				if(scan.hasNextInt()) mirrorFramedAry[i][j] = scan.nextInt();
			}
		}		
    }
    
    public void mirrorFramed(){
		for(int i=0; i<=numRow+1; i++){
			mirrorFramedAry[i][0] = mirrorFramedAry[i][1];
			mirrorFramedAry[i][numCol+1] = mirrorFramedAry[i][numCol];
		}
		
		for(int i=0; i<=numCol+1; i++){
			mirrorFramedAry[0][i] = mirrorFramedAry[1][i];
			mirrorFramedAry[numRow+1][i] = mirrorFramedAry[numRow][i];
		}
	}
    
	void loadNeighbors(){
		int result;
		boolean check = true;
		for(int i=1; i<=numRow; i++){
			for(int j=1; j<=numCol; j++){
				int count = 0;
				for(int m=i-1; m<=i+1; m++){
					for(int n=j-1; n<=j+1; n++) {
						newghborAry[count] = mirrorFramedAry[m][n];
						count++;
					}
				}		
				result = getMedian();				
				tempAry[i][j] = result;
				if(check) {
					newMin = result;
					newMax = result;
					check = false;
				}
				else {
					if(result < newMin) newMin = result;
					if(result > newMax) newMax = result;
				}
			}
		}
	}
	
	int getMedian(){
		for (int j = 0; j < 5; j++) {
			int min = j;
			for (int i = j+1; i < 9; i++) if (newghborAry[i] < newghborAry[min]) min = i;
			if(min != j) swap(j, min);
		}						
		return newghborAry[4];
	}//selection sort
	
	void swap(int x, int y){
		int temp = newghborAry[x];
		newghborAry[x] = newghborAry[y];
		newghborAry[y] = temp;
	}
	
	void printResult(){
		try {
			out = new java.io.PrintStream(file2);
			out.println(numRow+" "+numCol+" "+newMin+" "+newMax);
			for(int i=1; i<numRow+1; i++){
				for(int j=1; j<numCol+1; j++){
					 out.print(tempAry[i][j]+" ");
				}
				out.println();
			}
			out.close();
			scan.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

}
