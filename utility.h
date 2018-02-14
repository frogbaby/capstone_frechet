// utility.h

#include <vector>
#include <CGAL/Cartesian.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Quotient.h>

using namespace std;

typedef CGAL::Quotient<CGAL::MP_Float>		NT;
//typedef CGAL::Cartesian<NT>					Kernel;
typedef CGAL::Point_2						Point_2;




class utility
{
public:
	utility (vector<Point_2> curve1, vector<Point_2> curve2);
	~utility();

	bool reachable (double epsilon);

private:
	vector<Point_2> c1;
	vector<Point_2> c2;

	unsigned long n1;
	unsigned long n2;

	class edge 
	{
	public:
		edge (Point_2 s, Point_2 e);
		~edge();
		void verify();

		Point_2 start;
		Point_2 end;

	};

	edge computedge (double epsilon, Point_2 center, Point_2 p1, Point_2 p2);





};
