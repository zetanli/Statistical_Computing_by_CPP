#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;
int main(int argc, char* argv[]){
  //load alpha
  double alpha = atof(argv[1]);
  
  vector< pair<double,int> >v;
  double tok;
  int index = 1;
  while(cin >> tok){
     v.push_back(make_pair(tok, index));
     index++;
    }
  int len= v.size();

  sort(v.begin(),v.end());

  double sum = 0.0;
  for(double j=1; j<=len ; ++j){
    sum += (1/j);
    }
  double q = alpha / sum;

  int k = 0;
  for(double i=1; i<=len; ++i){
    if(v[i-1].first <= q * (i/len))
      k = i;
    }

  if(k==0)
    cout << k;
  else {
	for(double l=0; l<k; ++l){
	   cout << v[l].second << " ";
       }
    }
    cout << endl;

}
