#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main(int argc,char* argv[]){
  int i=1;
  int n=argc-1;
  long double sumx=((long double)n+1)/2;
  long double sumy=0;
  long double sumx2=((long double)n+1)*(2*(long double)n+1)/(6*n);
  long double sumiy=0;
  long double CV=0;
  long double cx=0;
  for(int i;i<=n;i++){
    CV=atof(argv[i]);
    sumy=sumy+CV;
    sumiy=sumiy+i*CV;
 	}
  long double sumxy=sumiy/n;
  long double xbar=sumx/n;
  long double ybar=sumy/n;
  long double beta1=(sumxy-ybar*sumx)/(sumx2-xbar*sumx);
  long double beta0=(sumx2*sumy-sumx*sumxy)/(((long double)n+1)*(2*(long double)n+1)/6-sumx*sumx);

  if(fabs((beta0/beta1)-0.0)<1.0e-10){
    beta0=0.0;
  }
  cout<<setprecision(8)<<beta0<<" "<<beta1<<endl;
  

}

