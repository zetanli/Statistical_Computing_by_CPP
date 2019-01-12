#include<cmath>
#include<cstdlib>
#include<iostream>

using namespace std;
double lHypergeometricProb(double*lF, int a, int b, int c, int d);
void lgF(double* lF, int n);

int main(int argc, char** argv){
   int a = atoi(argv[1]), b = atoi(argv[2]), c = atoi(argv[3]), d = atoi(argv[4]);
   int n = a + b + c + d;
   double* lF = new double[n+1];
   lgF(lF, n);
   double pFrac = 0;
   for(int x=0; x <= a; ++x){
     if(d-a+x >=0 ){
      double l = lHypergeometricProb(lF,x,a+b-x,a+c-x,d-a+x);
      pFrac += exp(l);
     }
   }
  double p_v = pFrac;
  if(p_v < 0.05)
    cout << "significant" << endl;
  else
    cout << "not significant" << endl;
  delete [] lF;
  return 0;
}

void lgF(double* lF, int n) {
  lF[0] = 0;
  for(int i=1; i < n+1; ++i) {
    lF[i] = lF[i-1] + log((double)i); // only n times of log() calls
  }
}

double lHypergeometricProb(double* lF, int a, int b, int c, int d) {
  return lF[a+b] + lF[c+d] + lF[a+c] + lF[b+d]
  - lF[a] - lF[b] - lF[c] - lF[d] - lF[a+b+c+d];
}
