// idea is to collect input from some embedded device (i dunno say some motion/thermal sensor or something) and track a rolling average
// 
// 

#include <iostream>
#include <vector>
using namespace std;

class movAvgFilter
{
	public:
		double gprIn; // gpr input

		double weight;
		double runTot; // running total
		int cols ; // number of expected traces for example - realistically this is unknown
		int N; // filter size, for this excercise test with 3 and 5
		int ppTrace;// points per trace measurements

		vector<vector<double> > v; //main vector
		vector<vector<double> >v_bgs;// background subtracted vector

		// constructor and member function
		movAvgFilter();
		double subFilter(); //moving subtraction 


};

movAvgFilter::movAvgFilter()
{

	cout<<"input filter size window, N"<<endl;
	cin>>N; // 5
	cout<<" input points per trace"<<endl; // realistically we wouldnt restrict it like this for GPR
	 cin>>ppTrace; // 4
}


double movAvgFilter::subFilter()
{
	//Write a function/method to be called as each new measurement is received from the GPR
// the next step would be to properly format this function to recieve GPR input measurements
	// current stand-in is using cin>> method for input
	runTot = 0;
	cols = 5;

for(int i = 0; i < cols;i++){	
	vector<double> vtemp; //to build 2d array

	for(int k = 0; k< ppTrace;k++){

		cout<<"gpr trace elements for trace #"<< i+1<<endl;
		cin>>gprIn;
		vtemp.push_back(gprIn);
		}

	v.push_back(vtemp); //array constructed with GPR value for trace i+1 (row by row)

	vector<double> vAvgTemp;
	for(int k =0; k< ppTrace;k++){
		
		runTot = 0.;
		for(int j = 0;j<i+1;j++){
			// linear weighting scheme. At 5th trace returns the given example of [0.2 ... 1], in increments of 0.2
			weight = double(j)/double(i+1); 
			runTot += weight*v[j][k];
			
		}
			if (i< N){
				// cout<<"yo" << ( - runTot/(i+1))<< endl;
				vAvgTemp.push_back(v[i][k] - runTot/(i+1));
			} else {
				runTot -= v[i-N][k];
				vAvgTemp.push_back(v[i][k]- runTot/N);
			}
			// cout<<v[j][k]<<" "	;
			// cout<<runningTotal;
		
		// cout<<runningTotal;

	}
	v_bgs.push_back(vAvgTemp);
}

//test output for comparison
// print out running subtraction of all traces provided
for(int k = 0;k<ppTrace;k++){
	for (int i = 0;i<cols;i++){
		cout<<v_bgs[i][k]<<" ";
	}
	cout<<endl;
}
return 0;
}


int main(){

	movAvgFilter test;

	test.subFilter();


	return 0;
}
