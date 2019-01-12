#include<iostream>
#include<vector>
#include<climits>
using namespace std;
void merge3Sort(vector<int>&a,vector<int>&b,vector<int>&c, int p, int r);
void merge3(vector<int>&a,vector<int>&b,vector<int>&c, int p,int q, int r);


int main(int argc,char** argv){
  vector<int>v;
  vector<int>v1;
  vector<int>v2;
  vector<int>index;
  int tok;
  while(cin >> tok)
    v.push_back(tok);
  for(int i=0;i<v.size()-1;i+=2)
    v1.push_back(v[i]);
  for(int i=1;i<v.size();i+=2)
    v2.push_back(v[i]);
  for(int i=1;i<=v1.size();i++)
    index.push_back(i);

  
  merge3Sort(v1,v2,index,0,v1.size()-1);
  for(int i=0;i<v1.size();i++){
    cout<<v1[i]<<" "<<v2[i];
    if(i!=v1.size()-1)cout<<" ";
  }
  
  cout<<endl;  
  for(int i=0;i<index.size();i++){
    cout<<index[i];
    if(i!=index.size())cout<<" ";
  }
  cout<<endl;  
}


void merge3Sort(vector<int>&a,vector<int>&b,vector<int>&c, int p, int r){
  if(p<r){
    int q=(p+r)/2;
    merge3Sort(a,b,c,p,q);
    merge3Sort(a,b,c,q+1,r);
    merge3(a,b,c,p,q,r);
  
  }
}

void merge3(vector<int>&a,vector<int>&b,vector<int>&c, int p,int q, int r){
  vector<int>aL,aR,bL,bR,cL,cR;
  for(int i=p;i<=q;++i){
    aL.push_back(a[i]);
    bL.push_back(b[i]);
    cL.push_back(c[i]);
  }
  for(int i=q+1;i<=r;++i){
    aR.push_back(a[i]);
    bR.push_back(b[i]);
    cR.push_back(c[i]);
  }
  aL.push_back(INT_MAX);
  aR.push_back(INT_MAX);
  bL.push_back(INT_MAX);
  bR.push_back(INT_MAX);
  cL.push_back(INT_MAX);
  cR.push_back(INT_MAX);

  for(int k=p, i=0,j=0,m=0,n=0;k<=r;++k){
    if(aL[i]<aR[j]){
      a[k]=aL[i];
      b[k]=bL[i];
      c[k]=cL[i];
      ++i;
      m=i;
    }
    else if(aL[i]==aR[j]){
      a[k]=aL[i];
      if(bL[i]<=bR[j]){
	b[k]=bL[i];
	c[k]=cL[i];
	++i;
      }
      else{
	b[k]=bR[j];
	c[k]=cR[j];
	++j;
      }
      
    }
    else{
      a[k]=aR[j];
      b[k]=bR[j];
      c[k]=cR[j];
      ++j;
      n=j;
    }
  }			   
}


