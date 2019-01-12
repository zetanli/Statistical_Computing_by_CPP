#include <cmath>
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

int main(int argc, char* argv[]){
  //get sample size n
  int n=argc-1;
  //get each sum of x's 1-4 power
  long double x=0;
  long double x2=0;
  long double x3=0;
  long double x4=0;
  long double CV=0;

  for(int i=1;i<=n;i++){
    CV=atof(argv[i]);
    x=x+CV;
    x2=x2+CV*CV;
    x3=x3+CV*CV*CV;
    x4=x4+CV*CV*CV*CV;
  }

  //mean part
  long double mean=x/n;
  //variance part
  long double variance=(x2-n*mean*mean)/(n-1);
  cout<<setprecision(8)<<mean<<endl;
  cout<<setprecision(8)<<variance<<endl;
  //calculate skewness and kurtosis if variance is not equal to zero

  if(variance!=0){
    
    long double sd=sqrt(variance);
    long double skewness=(2*mean*mean*mean*n-3*mean*x2+x3)/(sd*sd*sd*n);
    long double m4=x4/n+6*mean*mean*x2/n-3*mean*mean*mean*mean-4*mean*x3/n;
    long double kurtosis=m4/(variance*variance)-3;
    cout<<setprecision(8)<<skewness<<endl;
    cout<<setprecision(8)<<kurtosis<<endl;
  }
 

  return 0;
  


  
}


	













	


	






	
	
	

