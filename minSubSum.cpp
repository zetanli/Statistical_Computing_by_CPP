#include<iostream>
#include<vector>

using namespace std;



int main(int argc,char** argv){
  vector<double> v;
  double tok;
  while(cin>>tok)
    v.push_back(tok);
  int minsum=0;
  int minseq=0;
  
  for(int i=0;i<v.size();i++){
    minsum=minsum+v[i];
   
    if (minseq>minsum)
      minseq=minsum;
    if(minsum>0)
      minsum=0;
    
  }
  
  cout<<minseq<<endl;
  return 0;
}


