// frechet.cpp

#include "utility.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <map>
#include <set>

#include <math.h>
#include <iomanip>

#include <vector>
#include <iterator>

#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/Circle_2.h>
#include <CGAL/intersections.h>
#include <CGAL/Segment_2.h>
#include <CGAL/result_of.h>
#include <CGAL/iterator.h>
#include <CGAL/point_generators_2.h>

using namespace std;

typedef CGAL::Exact_circular_kernel_2		Circ2;
typedef CGAL::Point_2<Circ2>				Point_2;

// lala
double maxeps (utility &obj, double start_val, double error) {

	double eps = start_val;
	double left = error;
	double right = eps;
	bool found = false;

	while (fabs(left - right) > error) {



		double eps3 = sqrt(eps);
		cout <<  " testing reachablity for eps: " << setprecision(25) << eps3 << endl;


		if (obj.reachable(eps)) {
			found = true;
			right = eps;
			eps = (right + left) / 2.0;
		} else {
			if(!found) {
				eps *= 2;
				right = eps;
			} else {
				left = eps;
				eps = (right + left) / 2.0;
			}
		}

		if (left > right) {
			double temp = left;
			left = right;
			right = temp;
		}





	}

	double eps2 = sqrt(eps);


	return eps2;

}



int main(int argc, char* argv[]) {

	/*if(argc != 3) {
		return -1;
	}

	string f1 = argv[1];
	string f2 = argv[2];

	cout << "fileshort: " << f1 << endl;

	ifstream curve1;
	curve1.open(f1);

	ifstream curve2;
	curve2.open(f2);

	map<string, int> count1 = map<string, int>();
	map<string, int> count2 = map<string, int>();

	string line;

	while (getline(curve1, line)) {

		int ind = line.find(':');
		string kmer = line.substr(0, ind); // get string from index 0 to index ind
		string count = line.substr(ind+1, line.size());

		count1.insert(pair<string, int> (kmer, stoi(count)));   //stoi: string to int

	}

	line.clear();

	while (getline(curve2, line))
	{
		int ind = line.find(':');
		string kmer = line.substr(0, ind);
		string count = line.substr(ind + 1, line.size());

		count2.insert(pair<std::string, int>(kmer, stoi(count)));
	}

	curve1.close();
	curve2.close();

	cout << "count 1: " << count1.size() << " count 2: " << count2.size() << endl;*/



	/*vector<Point_2> c1 = vector<Point_2>();
	vector<Point_2> c2 = vector<Point_2>();

	//construct 2 curves here

	Point_2 x1(1,3);
	c1.push_back(x1);

	Point_2 x2(2,4);
	c1.push_back(x2);

	Point_2 x3(3,5);
	c1.push_back(x3);

	Point_2 x4(7,7);
	c1.push_back(x4);


	Point_2 y1(-2,1);
	c2.push_back(y1);

	Point_2 y2(1,3);
	c2.push_back(y2);

	Point_2 y3(3,4);
	c2.push_back(y3);*/



	ifstream c1file("c1.txt");
	ifstream c2file("c2.txt");
	vector<Point_2> c1 = vector<Point_2>();
	vector<Point_2> c2 = vector<Point_2>();
	string line;
	string line2;

	cout<<"1"<< endl;

	if(!c1file) //Always test the file open.
    {
        cout<<"Error opening output file"<< endl;
        system("pause");
        return -1;
    }
    if(!c2file) //Always test the file open.
    {
        cout<<"Error opening output file"<< endl;
        system("pause");
        return -1;
    }

    while(getline(c1file, line)){
    	cout<<"2"<< endl;
    	int n = line.length(); 
    	char l[n+1];
    	strcpy(l, line.c_str()); 
    	vector<string> pts;
    	char* token = strtok(l,",");
    	while(token){
        	pts.push_back(token);
        	cout<<"3"<< endl;
        	token = strtok(NULL, ",");
    	}
    	double x = stod(pts[0]);
    	double y = stod(pts[1]);

    	//Point_2 pt(x,y);
        c1.push_back(Point_2 (x,y));
    }

  	while(getline(c2file, line2)){
  		int n = line2.length(); 
    	char l2[n+1];
    	strcpy(l2, line2.c_str()); 
    	vector<string> pts;
    	char* token = strtok(l2,",");
    	while(token){
        	pts.push_back(token);
        	token = strtok(NULL, ",");
    	}
    	double x = stod(pts[0]);
    	double y = stod(pts[1]);
    	//Point_2 pt(x,y);
        c2.push_back(Point_2 (x,y));

    }
    for(vector<Point_2>::iterator it = c1.begin(); it != c1.end(); ++it){
    	cout << ' ' << *it;
    }
    cout << '\n';

    /*if (c1 == c3) {
    	cout << "success" << endl;
    }*/


	


	utility frechet = utility::utility(c1,c2);
	double eps = maxeps(frechet,10,0.25);

	cout << "Frechet Distance is: " << eps << endl;






























}





















