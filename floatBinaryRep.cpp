#include <cmath>
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;
int main(int argc, char* argv[]){
  long double dect=atof(argv[1]);
  long double dec=abs(dect);
  if(dect!=0){
  //get sign
  int sign=0;
  if(dect<0)
    sign=1;
  //calculate power of 2
  long double decLog=log2(dec);
  int expon=floor(decLog);

  int exponMove=expon+127;
  //convert to binary presentation
  int binaryExpon[8]={0,0,0,0,0,0,0,0};
  for(int k=1; k<=8;k++){
    binaryExpon[8-k]=exponMove%2;
    exponMove=exponMove/2;
    
  }

  
    
  //extract fraction part
  long double frac=dec/pow(2,expon)-1;



  //get fraction presentation
  int fracAr[23];
  int macStore=0;
  int finished=0;
  for(int i=1;i<=23;i++){
    
    if(2*frac>(1-pow(2,(i-24)))){
      
      fracAr[i-1]=1;
      frac=2*frac-1;
      if(frac==0)finished=1;
    }else {fracAr[i-1]=0;
      frac=2*frac;
    }
  }

 

  cout<<sign;
  for(int m=0;m<=7;m++)
    cout<<binaryExpon[m];
  for(int d=0;d<=22;d++)
    cout<<fracAr[d];
  cout<<endl;
  cout<<finished<<endl;
  
  
  }




  
  else{
    cout<<"00000000000000000000000000000000"<<endl;
    cout<<1<<endl;
  }





  
}
