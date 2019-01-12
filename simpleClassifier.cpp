#ifndef _Read_Matrix_615_H_
#define _Read_Matrix_615_H_

#include<iostream> 
#include<cmath>
#include<vector>
#include<string> 

#include<boost/tokenizer.hpp>
#include<iomanip>
#include<Eigen/Core>
#include<Eigen/Dense> 
#include<Eigen/SVD>
#include<cstdlib>
#include<climits>
#include<fstream>
#include<boost/lexical_cast.hpp>


using namespace std;
using namespace boost;
using namespace Eigen;

template <class T>
Matrix<T,Dynamic, Dynamic> readFromFile(const char* fileName) {
      vector<T> temp; 
      ifstream ifs(fileName);
      if ( ! ifs.is_open() ) {
            cerr<< "Cannot open file" <<fileName<< endl;
            abort();
       }
       string line;
       char_separator<char> sep(", \t \"");
       typedef tokenizer<char_separator<char> > wsTokenizer;
       temp.clear();
       int nr=0, nc=0, nc_check = 0;
       getline(ifs, line);
       while(getline(ifs, line) ) {
            if (line[0]=='#') continue;
             wsTokenizer t(line,sep);
             nc_check = 0;
             for(wsTokenizer::iterator i=t.begin(); i !=t.end(); ++i) {
                 temp.push_back(lexical_cast<T>(i->c_str()));
                 //temp.push_back(lexical_cast<T>(*i));
                 if (nr==0) ++nc;
                 ++nc_check;
              }
             
             if (nc != nc_check ) {
              cerr<<"The input file is not rectabgle at line "<<nr<<endl;
              abort();
        }
            ++nr;
        }
        
        Map<Matrix<T, Dynamic, Dynamic,RowMajor> > mf(&temp[0],nr,nc);
        return mf;
}

#endif

void simpleClassifier(MatrixXd train,MatrixXd test){
    	int row = train.rows();
  	int col = train.cols();
  	VectorXd y = train.col(0);
  	MatrixXd x = train.block(0,1,row,col-1);
	int ct = 0; 
	vector<int> id1,id0;
        
	for(int i=0; i<row; i++){
		if(y[i] == 1){
			ct +=1;
			id1.push_back(i);	
		}
		else{
			id0.push_back(i);
		}
	}
	
	VectorXd center_1(col-1);
	for(int i=0; i<col-1 ; i++){
		double sum = 0.0;
		
		for(int c=0; c<ct; c++){
		  
			sum += x(id1[c],i);
			
		}
		
		center_1[i] = sum/double(ct); 	
	}

 	VectorXd center_0(col-1);
        for(int i=0; i<col-1 ; i++){
                double sum = 0.0;
                for(int c=0; c<row-ct; c++){
                        sum += x(id0[c],i);
                }
                center_0[i] = sum/double(row-ct);
        }

	VectorXd s_1(col-1);
	for(int i=0; i<col-1 ; i++){
                double sum = 0.0;
                for(int c=0; c<ct; c++){
                        sum += pow(x(id1[c],i)-center_1[i],2);
                }
                s_1[i] = sum/double(ct-1);
        }
		
	VectorXd s_0(col-1);
        for(int i=0; i<col-1 ; i++){
                double sum = 0.0;
                for(int c=0; c<row-ct; c++){
                        sum += pow(x(id0[c],i)-center_0[i],2);
                }
                s_0[i] = sum/double(row-ct-1);
        }

	
	
        int row2 = test.rows();
        int col2 = test.cols();
        VectorXd y2 = test.col(0);
        MatrixXd x2 = test.block(0,1,row2, col2-1);
	
	VectorXd dist_1(row2);
	for(int i=0; i<row2; i++){
		double sum = 0.0;
		for(int c=0; c<col2-1; c++){
			sum += pow(x2(i,c)-center_1[c],2)/s_1[c];
		}
		dist_1[i] = sum;
	}

	VectorXd dist_0(row2);
        for(int i=0; i<row2; i++){
                double sum = 0.0;
                for(int c=0; c<col2-1; c++){
                        sum += pow(x2(i,c)-center_0[c],2)/s_0[c];
                }
                dist_0[i] = sum;
        }

	VectorXd pred(row2);
	for(int i=0; i<row2; i++){
		if(dist_1[i] < dist_0[i]){
			pred[i] = 1;	
		}
		else{
			pred[i] = 0;
		}	
	}

	int accuracy = 0;
	for(int i=0; i<row2; i++){
		if(pred[i] == y2[i]){
			accuracy+=1;
		}
	}	
        cout << setprecision(4)  << accuracy/double(row2) << endl;
	
}

int main( int argc , char** argv) { 

	MatrixXd X1 = readFromFile<double>(argv[1]);
	MatrixXd X2 = readFromFile<double>(argv[2]);
        simpleClassifier(X1,X2);
	return 0;

}
