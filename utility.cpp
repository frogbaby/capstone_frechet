// utility.cpp

#include "utility.h"
#include <iostream>

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
typedef CGAL::Circle_2<Circ2>				Circle;
typedef CGAL::Line_arc_2<Circ2>				LineArc2;
typedef Kernel::FT							Number_type;


typedef std::pair<CGAL::Circular_arc_point_2<Circ2>, unsigned> InterO;
//unsigned integer is the multiplicity of the corresponding intersection point 
//between circle and line segment 


utility::utility(vector<Point_2> curve1, vector<Point_2> curve2)
{
	c1 = curve1;
	c2 = curve2;

	n1 = c1.size() - 1;
	n2 = c2.size() - 1;
}


bool utility::reachable(double epsilon)
{
	edge left = computedge(epsilon, c2[1], c1[0], c1[1]);
	edge bottom = computedge(epsilon, c1[1], c2[0], c2[1]);

	edge top = computedge(epsilon, c1[n1], c2[n2-1], c2[n2]);
	edge right = computedge(epsilon, c2[n2], c1[n1-1], c1[n1]);




	stack<vector<int>> cell = stack<vector<int>>();
	set<vector<int>> seen = set<vector<int>>();
	cell.push({ 0,0 });
	seen.insert({ 0,0 });

	while (!cell.empty())
	{
		vector<int> ind = cell.top();

		cell.pop();

		top = calcedge(epsilon, c1[ind[0]+1], c2[ind[1]], c2[ind[1] + 1]);
		right = calcedge(epsilon, c2[ind[1]+1], c1[ind[0]], c1[ind[0] + 1]);
		top.verify();
		right.verify();

		if (ind[0] == n1 - 1 && ind[1] == n2 - 1)
			return true; //reached end,

		if (top.passable() && ind[0] + 1 < n1 && seen.count({ ind[0] + 1, ind[1] }) == 0)
		{
			cell.push({ ind[0] + 1, ind[1] });
			seen.insert({ ind[0] + 1, ind[1] });
		}
		if (right.passable() && ind[1] + 1 < n2 && seen.count({ ind[0], ind[1] + 1 }) == 0)
		{
			cell.push({ ind[0], ind[1] + 1 });
			seen.insert({ ind[0], ind[1] + 1 });
		}
	}

	
}






utility::edge utility::computedge (double epsilon, Point_2 center, Point_2 p1, Point_2 p2)
{
	Circle c = Circle(Point_2(center), Number_type(epsilon));
	LineArc2 l = LineArc2(Point_2(p1), Point_2(p2));

	vector<InterO> output;
	typedef CGAL::Dispatch_output_iterator< CGAL::cpp11::tuple<InterO>, 
						CGAL::cpp0x::tuple< back_insert_iterator<vector<InterO> > > > Dispatcher;
	Dispatcher disp = CGAL::dispatch_output<InterO>( back_inserter(output) );

	CGAL::intersection(l, c, disp);
	




	/*if (output.size() > 0){

		return edge (CGAL::to_double(output(0).first.x()), CGAL::to_double(output[0].first.y()));


		//cout<<CGAL::to_double(output[0].first.x())<<","<<CGAL::to_double(output[0].first.y())<<endl;

		if (output.size() > 1){

			return edge (CGAL::to_double(output(1).first.x()), CGAL::to_double(output[1].first.y()));

			//cout<<CGAL::to_double(output[1].first.x())<<","<<CGAL::to_double(output[1].first.y())<<endl;
		}
	}*/

	// verify part
	if(output.size() = 0) {
		if (c.has_on_unbounded_side(p1) && c.has_on_unbounded_side(p2)) {
			return edge();  // not pass 
		} else{
			return edge(Point_2(p1),Point_2(p2));  // entire range of the line segment
		}
	}

	else if(output.size() = 1) {
		if (c.has_on_unbounded_side(p1) && c.has_on_unbounded_side(p2)) {
			return edge(Point_2(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y())),
							Point_2(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y()))); 
									
		}
		else if (c.has_on_unbounded_side(p1) && c.has_on_bounded_side(p2) ) {
			return edge(Point_2(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y())), 
									Point_2(p2));
		}

		else if (c.has_on_bounded_side(p1) && c.has_on_unbounded_side(p2)) {
			return edge(Point_2(Point_2(p1), 
							Point_2(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y()))));

		}
	}

	else if (output.size() > 1) {
		return edge (Point_2(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y())),
						Point_2(CGAL::to_double(output[1].first.x()), CGAL::to_double(output[1].first.y())));
	}


}


utility::~utility() {

}


bool utility::edge::passable() {

}








