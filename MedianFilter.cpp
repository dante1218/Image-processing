#include <iostream>
#include <fstream>
using namespace std;

class MedianFilter{
	private:
		int numRow;
		int numCol;
		int minVal;
		int maxVal;
		int newMin;
		int newMax;
		int** mirrorFramedAry;
		int** tempAry;
		int newghborAry[9];
		ifstream in;
	    ofstream out;
		string file1, file2;
	
	public:
		MedianFilter(string input, string output){
			file1 = input;
			file2 = output;
			in.open(file1.c_str());
			out.open(file2.c_str());
			
			int value;	
			if(in>>value) numRow = value;
		    if(in>>value) numCol = value;
			if(in>>value) minVal = value;
			if(in>>value) maxVal = value;
			
			mirrorFramedAry = new int*[numRow+2];
			tempAry = new int*[numRow+2];
			for(int i=0; i<numRow+2; i++) {
				mirrorFramedAry[i] = new int[numCol+2];
				tempAry[i] = new int[numCol+2];
			}
		}
		
		~MedianFilter(){
			for(int i=0 ; i<numRow+2; i++) {
				delete[] mirrorFramedAry[i];
				delete[] tempAry[i];
			}
			delete[] mirrorFramedAry;
			delete[] tempAry;
		}
		
		void loadImage(){
			int input;
			for(int i=1; i<=numRow; i++){
				for(int j=1; j<=numCol; j++){
					if(in>>input) mirrorFramedAry[i][j] = input;
				}
			}
		}
		
		void mirrorFramed(){
			for(int i=0; i<=numRow+1; i++){
				mirrorFramedAry[i][0] = mirrorFramedAry[i][1];
				mirrorFramedAry[i][numCol+1] = mirrorFramedAry[i][numCol];
			}
			
			for(int i=0; i<=numCol+1; i++){
				mirrorFramedAry[0][i] = mirrorFramedAry[1][i];
				mirrorFramedAry[numRow+1][i] = mirrorFramedAry[numRow][i];
			}
			
			for(int i=0; i<=numRow+1; i++){
				for(int j=0; j<=numCol+1; j++){
					cout<<mirrorFramedAry[i][j]<<" ";
				}
				cout<<endl;
			}
		}
		
		void loadNeighbors(){
			int result;
			bool check = true;
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
			out<<numRow<<" "<<numCol<<" "<<newMin<<" "<<newMax<<endl;
			
			for(int i=1; i<numRow+1; i++){
				for(int j=1; j<numCol+1; j++){
					 out<<tempAry[i][j]<<" ";
				}
				out<<endl;
			}
			in.close();
		    out.close();
		}
		
};

int main(int argc, char* argv[]){
	if(argc < 3){
		cout << "usage : " << argv[0] << " <input file>\n";
		return -1;
	}//check the command-line arguments
	
	string f1, f2;
	f1 = argv[1];
	f2 = argv[2];
	
	MedianFilter m(f1, f2);
	m.loadImage();
	m.mirrorFramed();
	m.loadNeighbors();
	m.printResult();
	return 0;
}
