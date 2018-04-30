// utility_3d

#include <vector>
#include <iterator>

#include <cmath>
#include <stack>
#include <set>


#include <CGAL/Exact_spherical_kernel_3.h>
#include <CGAL/intersections.h>
#include <CGAL/Circle_3.h>
#include <CGAL/Segment_3.h>
#include <CGAL/result_of.h>
#include <CGAL/iterator.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/squared_distance_3.h>

using namespace std;


typedef CGAL::Exact_spherical_kernel_3		Spherical_3;
typedef CGAL::Point_3<Spherical_3>          Point_3;
typedef CGAL::Sphere_3<Spherical_3>         Sphere_3;
typedef CGAL::Line_arc_3<Spherical_3>		LineArc3;

typedef std::pair<CGAL::Circular_arc_point_3<Spherical_3>, unsigned> InterO;


int main() {

	Point_3 a(1,0,0), b(0,1,1);
	double radius = 1;
	Sphere_3 sphere = Sphere_3(Point_3(0,0,0), radius);
	LineArc3 line = LineArc3(a,b);
	Point_3 d(2,3,4);


	std::vector<InterO> output;

	typedef CGAL::Dispatch_output_iterator< CGAL::cpp11::tuple<InterO>, 
						CGAL::cpp0x::tuple< std::back_insert_iterator<std::vector<InterO> > > > Dispatcher;
	Dispatcher disp = CGAL::dispatch_output<InterO>( std::back_inserter(output) );


	CGAL::intersection(line, sphere, disp);



	if (output.size() == 0) {
		cout << "0 intersection point" << endl;
	}

	if (output.size() > 0)
    {
    	cout << "intersection point 1: " << CGAL::to_double(output[0].first.x()) << ", " <<
    		CGAL::to_double(output[0].first.y()) << ", " << CGAL::to_double(output[0].first.z()) << endl;
    	//cout << output[0].second << endl;

    	//Pt2 x(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y()) );

    	



		}
    if (output.size() > 1)
    {
    	cout << "intersection point 2: " << CGAL::to_double(output[1].first.x()) << ", " <<
    		CGAL::to_double(output[1].first.y()) << ", " << CGAL::to_double(output[1].first.z()) << endl; 


    	Point_3 x(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y()), CGAL::to_double(output[0].first.z()));
    	Point_3 y(CGAL::to_double(output[1].first.x()), CGAL::to_double(output[1].first.y()), CGAL::to_double(output[1].first.z()));


    	Point_3 x2(0,0,0);
    	Point_3 y2(3,4,5);





    


    	cout << "squared distance: " << CGAL::to_double(CGAL::squared_distance(x, y)/CGAL::squared_distance(x2,y2)) << endl;




    }

    cout << (sphere.has_on_unbounded_side(d) ? "outside the circle\n" : "inside the circle\n");
   


    return 0;








}