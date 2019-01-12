#ifndef _Matrix_615_H_
#define _Matrix_615_H_

#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<climits>
#include<cmath>
#include<boost/tokenizer.hpp>
#include<fstream>
#include<boost/lexical_cast.hpp>
#include<Eigen/Core> 
#include<Eigen/SVD>
#include<typeinfo>

//from matrix615.h

using namespace std;
using namespace boost;
using namespace Eigen;

template <class T>
class Matrix615 {
    public:
    vector<vector<T> > data;
    Matrix615(){
    }
    Matrix615(int nrow, int ncol, T val = 0) {
        data.resize(nrow); // make n rows
        for(int i=0; i < nrow; ++i) {
            data[i].resize(ncol,val); // make n cols with default value val
        }
    }
    
    int rowNums() {return (int)data.size();}
    int colNums() {return (data.size()==0) ? 0: (int)data[0].size();}
    void readFromFile(const char* fileName);
    void print();
    void cloneToEigen(Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& m);
};

template <class T>
void Matrix615<T>::print(){
    for(int i=0; i < rowNums();i++){
        for(int j=0;j < colNums(); j++){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

template <class T>
void Matrix615<T>::readFromFile(const char* fileName) {
    ifstream ifs(fileName);
    if ( ! ifs.is_open() ) {
        cerr<< "Cannot open file" <<fileName<< endl;
        abort();
    }
    string line;
    char_separator<char> sep(", \t \"");
    typedef tokenizer<char_separator<char> > wsTokenizer;
    data.clear();
    int nr=0, nc=0;
    while(getline(ifs, line) ) {
        if (line[0]=='#') continue;
        wsTokenizer t(line,sep);
        data.resize(nr+1);
        for(wsTokenizer::iterator i=t.begin(); i !=t.end(); ++i) {
            data[nr].push_back(lexical_cast<T>(i->c_str()));
            if (nr==0) ++nc;
        }
        if (nc != (int)data[nr].size() ) {
            cerr<<"The input file is not rectabgle at line "<<nr<<endl;
            abort();
        }
        ++nr;
    }
}

template <class T>
void Matrix615<T>::cloneToEigen(Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic>& m) {
	int nr = rowNums(); 
	int nc = colNums();
	m.resize (nr, nc);
	for(int i=0; i < nr; ++i) {
		for(int j=0; j < nc; ++j) { m(i,j) = data[i][j];
		} 
	}
}

#endif


//fastRidgeRegression
int main(int argc, char** argv){
  //import files and lambda
    Matrix615<double> tmpX;
    tmpX.readFromFile(argv[1]);

    Matrix615<double> tmpy;
    tmpy.readFromFile(argv[2]);

    double lambda = atof(argv[3]);
    int n = tmpX.rowNums(); 
    int p = tmpX.colNums();
    MatrixXd y , X;
    tmpy.cloneToEigen(y);
    tmpX.cloneToEigen(X);
    JacobiSVD<MatrixXd> svd(X, ComputeThinU | ComputeThinV);
    VectorXd mat = svd.singularValues();
    vector<double> d(mat.data(), mat.data() + mat.rows() * mat.cols());

    int ds;
    if ( n >= p )
        ds = p;
    else
        ds = n;
    for (int i=0; i<ds; i++)
      d[i] = d[i]/(pow(d[i],2)+lambda);
    VectorXd mapd = Map<VectorXd, Unaligned>(d.data(), d.size());
    MatrixXd dia = mapd.asDiagonal();
    MatrixXd bEs = svd.matrixV() * dia * svd.matrixU().transpose() * y;

    for (int k=0; k<p; k++){
    	if (round(bEs(k,0)) != 0)
    	   cout << (k+1) <<' '<< round(bEs(k,0)) << endl;
    	
    }

}
