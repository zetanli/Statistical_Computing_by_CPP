#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<float.h>
#include<vector>
#define ZEPS 1e-10

using namespace std;

double dnorm(double x, double mu, double sigma){
  return 1.0 / (sigma * sqrt(M_PI * 2.0)) * exp (-0.5 * (x - mu) * (x-mu) / sigma / sigma);
}
double mixLLK(vector<double> data, double p, vector<double> mean, vector<double> sigma){
  double llk = 0.0;
  for(int i=0; i<(int)data.size(); i++)
    llk += log(p * dnorm(data[i], mean[0], sigma[0]) + (1-p) / sqrt(sigma[1]*sigma[1]*12));
  return llk;
}
int check_tol(double fmax, double fmin, double ftol){
  double delta = fabs(fmax - fmin);
  double accuracy = (fabs(fmax) + fabs(fmin)) * ftol;
  return (delta < (accuracy + ZEPS));
}
void updateProbs(vector<double>& prob, vector<double> data, double p, vector<double> mean, vector<double> sigma, int n){

  for(int i=0; i<n; i++){
    
    double cum;
    prob[i*2] = p * dnorm(data[i], mean[0], sigma[0]);
    prob[i*2+1] = (1-p) / sqrt(sigma[1]*sigma[1]*12);
    cum = prob[i*2] + prob[i*2+1];
    prob[i*2] /= cum;
    prob[i*2+1] /= cum;
	
  }
  
}
void updateP(double& p, vector<double> prob, int n){

  p = 0.0;
  for (int i=0; i<n; i++)
    p += prob[2*i];
  p /= n;
    
}
void updateMeans(vector<double>& mean, vector<double> data, vector<double> prob, double p, int n){
  
  mean[0] = 0.0;
  for (int i=0; i<n; i++)
    mean[0] += data[i]*prob[i*2];
  mean[0] /= (n*p + 1e-6);
    
}
void tryIdx(vector<double>& llkList, vector<double>& meanList, vector<double> data, double meanInit, double dataMax, double dataMin){
  double p;
  vector<double> mean,sigma,prob;
  int n,k;

  double llk = 0.0,prevLLK = 0.0,eps = 1e-6;

  k = 2;
  n = data.size();
  p = 0.5;
  prob.resize(n*k);
  mean.push_back(meanInit);
  sigma.push_back(1.0);
  mean.push_back((dataMax+dataMin)/2);
  sigma.push_back(sqrt((dataMax-dataMin)*(dataMax-dataMin)/12));
  while ((llk == 0) || (check_tol(llk, prevLLK, eps) == 0)){
    updateProbs(prob, data, p, mean, sigma, n);
    updateP(p, prob, n);
    updateMeans(mean, data, prob, p, n);
    prevLLK = llk;
    llk = mixLLK(data, p, mean, sigma);
  }
  meanList.push_back(mean[0]);
  llkList.push_back(llk);
}







int main(int argc, char** argv){
  vector<double> listLLK,mList,data;
  double tmp = 0.0;
  while ( cin >> tmp )
    data.push_back(tmp);
  
  vector<double>::iterator maxH = max_element(data.begin(), data.end()),minH = min_element(data.begin(), data.end());


  double Max = (double)*maxH,Min = (double)*minH;

  double sum = 0.0, sSum = 0.0;
  int n = (int)data.size();
  for (int i=0; i<n; i++){
    sum += data[i];
    sSum += data[i]*data[i];
  }
  double tmp_mean = sum/n ;

  tryIdx(listLLK, mList, data, Max, Max, Min);
  tryIdx(listLLK, mList, data, Min, Max, Min);
  tryIdx(listLLK, mList, data, tmp_mean, Max, Min);
  tryIdx(listLLK, mList, data, (Max+Min)/2, Max, Min);
  tryIdx(listLLK, mList, data, data[rand()%n], Max, Min);
  tryIdx(listLLK, mList, data, data[rand()%n], Max, Min);

  int idx;
  double llkMax = -DBL_MAX;

  for (int i=0; i<(int)listLLK.size(); i++){
    if(listLLK[i] > llkMax){
        llkMax = listLLK[i];
        idx = (int)(i);
    }
  }
  cout << (int)(round(mList[idx]));
  cout<<endl;
  return 0;
}

