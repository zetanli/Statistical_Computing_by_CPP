#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]){
  int j=argc-1;
  long double powerLinear1=pow(2,-1);
  long double powerLinear2=pow(2,-2);
  long double powerLinear3=pow(2,-3);
  long double powerLinear4=pow(2,-4);
  long double powerLinear5=pow(2,-5);     
  for(int i;i<=j;i++){
    powerLinear1=powerLinear1+pow(2,abs(1-i))*atof(argv[i]);
    powerLinear2=powerLinear2+pow(2,abs(2-i))*atof(argv[i]);
    powerLinear3=powerLinear3+pow(2,abs(3-i))*atof(argv[i]);
    powerLinear4=powerLinear4+pow(2,abs(4-i))*atof(argv[i]);
    powerLinear5=powerLinear5+pow(2,abs(5-i))*atof(argv[i]);
  }
  /*Weight each probability for the total probability to be 1
    i.e. each value divided by the sum.*/
  long double sumall=exp(powerLinear1)+exp(powerLinear2)+exp(powerLinear3)+exp(powerLinear4)+exp(powerLinear5);
  cout<<setprecision(8)<<exp(powerLinear1)/sumall<<endl;
  cout<<setprecision(8)<<exp(powerLinear2)/sumall<<endl;
  cout<<setprecision(8)<<exp(powerLinear3)/sumall<<endl;
  cout<<setprecision(8)<<exp(powerLinear4)/sumall<<endl;
  cout<<setprecision(8)<<exp(powerLinear5)/sumall<<endl;
}
