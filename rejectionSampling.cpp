#include <iostream>
#include <iomanip>
#include <cmath>
#include <boost/random/uniform_real.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/beta_distribution.hpp>
#include <vector>

using namespace std;
using namespace boost;

int main(int agrc, char** argv){
  mt19937 rng;
  float alpha = atof(*(argv+1)), beta = atof(*(argv+2));
  int num = 5000000;
  vector<float> v;
  double x, u, r;
  for(int i=0; i<num ; i++){
    boost::random::beta_distribution<> beta_dist(alpha, beta);
    uniform_real<> uni(0 ,1);
    x = beta_dist(rng);
    u = uni(rng);
    r = exp(-x*x);
    if(u<r)
      v.push_back(x);
		
    }

  sort(v.begin(), v.end());  
  const float a[] = { 0.01, 0.25, 0.5, 0.75, 0.99};
  vector<float> percentile(a,a + sizeof(a)/sizeof(a[0]));
  vector<int> quantile;
  for (int i = 0; i < percentile.size(); ++i){
    quantile.push_back(v.size()*percentile[i]);
  }
  cout << setprecision(1) <<v.size()/float(num) << endl;
  for (int i = 0; i < quantile.size(); ++i)
     cout << setprecision(1) << v[quantile[i]] <<' ';
  cout << endl;
}
