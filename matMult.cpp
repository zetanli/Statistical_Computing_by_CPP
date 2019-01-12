#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main(int argc, char** argv){
  vector<int>v;
  int tok;
  int length=0;
  while(cin>>tok){
    v.push_back(tok);
    length++;
  }
 
  int kPower=v[0];
  int i=v[1];
  int j=v[2];
  

  //create a matrix representing what we want to put in
  MatrixXd mat(length-3,length-3);
  for(int i1=0;i1<length-3;i1++){
    for(int j1=0;j1<length-3;j1++){
      if(i1>=j1){
	if(v[i1-j1+3]<10000)
	  mat(i1,j1)=v[i1-j1+3];
        else mat(i1,j1)=v[i1-j1+3]%10000;
	       }
      else {
	if(v[j1-i1+3]<10000)
	  mat(i1,j1)=v[j1-i1+3];
	else
	  mat(i1,j1)=v[j1-i1+3]%10000;
      }
    }
  }
  //vector
  VectorXd newj(length-3);
  newj=mat.col(j-1);
  
  //acquire the results of Kth power
  for(int n=1; n<kPower;n++){
    newj=mat*newj;
    for(int p=0;p<(length-3);p++){
      if(newj[p]>=10000){
	int tmp=newj[p];
	newj[p]=tmp%10000;}
    }
  
  }

  int aij=newj[i-1];
    
  if(aij<10000)
    cout<<aij<<endl;
  else cout<<aij%10000<<endl;
  return 0;

  
}
