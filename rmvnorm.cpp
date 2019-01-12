#include <iostream>
#include <cmath>
#include <math.h>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <Eigen/Dense>
#include <numeric>
#include <iomanip>



using namespace std;
using namespace Eigen;
using namespace boost;

int main(int argc, char** argv){

  mt19937 rng;
  int num = 1000000;
  int p = atof(*(argv+1));
  float rho = atof(*(argv+2));
  MatrixXd sigma(p,p);
  for(int i = 0; i < p; i++){
    for(int j = 0; j < p; j++){
      float l1 = float(i)/p;
      float l2 = float(j)/p;
      sigma(i,j) = exp( p * log(rho) * pow(abs(l1-l2),1.99) - abs(cos(l1)) - abs(cos(l2)) );
      }
  }

  LLT<MatrixXd> lltOfA(sigma);
  MatrixXd L = lltOfA.matrixL();
  vector<vector<float> > v(3, vector<float>(num));
  VectorXd mat(p);
  normal_distribution<> norm(0 ,1);
  for (int i = 0; i < num; ++i){
    for (int j = 0; j < p; ++j)
	mat(j)=norm(rng);	       
    mat = L*mat;
    vector<float> z(mat.data(), mat.data() + mat.rows() * mat.cols());
    bool t = mat(0)*mat(1) > 0.5*rho; 
    v[0].push_back(*max_element(z.begin(),z.end()));
    v[1].push_back(sqrt(mat.dot(mat)));
    v[2].push_back(t);
    }

    for (int i = 0; i < 3; ++i)
      cout <<  setprecision(1) << accumulate(v[i].begin(),v[i].end(),0.0)/num << endl;

}
