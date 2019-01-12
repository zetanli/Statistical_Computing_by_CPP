#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <climits>
using namespace std;


void mergeSort(vector<double> &A,int p, int r);
void merge(vector<double> &A,int p,int q,int r);

void Quantiles(vector<double> &A,long double c);
int main(int argc, char* argv[]){
  vector<double> v;
  double tok;
  while(cin>>tok)
    v.push_back(tok);
  mergeSort(v,0,v.size()-1);
  double quant=0;
  for(int i=1;i<argc;i++){
    quant=atof(argv[i])*v.size();
    if(quant==floor(quant)&&quant !=0)
      quant=quant-1;
    cout<<v[quant]<<" ";
  }
  cout<<endl;
  
  
  return 0;
}

void mergeSort(vector<double> &A,int p, int r){
  if(p<r){
    int q=(p+r)/2;
    mergeSort(A,p,q);
    mergeSort(A,q+1,r);
    merge(A,p,q,r);
  }
}
void merge(vector<double> &A,int p,int q,int r){
  vector<double>aL,aR;
  for(int i=p;i<=q;++i)aL.push_back(A[i]);
  for(int i=q+1;i<=r;++i)aR.push_back(A[i]);
  aL.push_back(INT_MAX);
  aR.push_back(INT_MAX);

  for(int k=p, i=0,j=0;k<=r;++k){
    if(aL[i]<=aR[j]){
      A[k]=aL[i];
      ++i;
    }
    else{
      A[k]=aR[j];
      ++j;
    }
  }			   
}


