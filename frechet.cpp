// frechet.cpp

//#include "utility.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <map>
#include <set>

#include <math.h>
#include <iomanip>

using namespace std;


/*double maxeps (utility $obj, double start_val, double error) {

	double eps = start_val;
	double left = error;
	double right = eps;
	bool found = false;

	while (fabs(left - right) > error) {

		cout <<  << " testing reachablity for eps: " << setprecision(25) << eps << endl;

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


	return eps;

}*/



int main(int argc, char* argv[]) {

	if(argc != 3) {
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

	cout << "count 1: " << count1.size() << " count 2: " << count2.size() << endl;



	int sum1 = 0;
	for (auto& kmer : count1) {
		sum1 += kmer.second;
	}

	map<string, double> countprob1 = map<string, double>();
	for (auto& kmer : count1)
	{
		countprob1.insert(pair<string, double>(kmer.first, log((float) kmer.second / (float) sum1)));
	}

	int sum2 = 0;
	for (auto& kmer : count2)
	{
		sum2 += kmer.second;
	}

	map<std::string, double> countprob2 = map<string, double>();
	for (auto& kmer : count2)
	{
		countprob2.insert(std::pair<string, double>(kmer.first, log((float)kmer.second / (float)sum2)));
	}






























}





















