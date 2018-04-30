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

class utility
{
public:
	utility (vector<Point_3> curve1, vector<Point_3> curve2){


	c1 = curve1;
	c2 = curve2;

	n1 = c1.size() - 1;
	n2 = c2.size() - 1;
}



~utility(){};

	bool reachable (double epsilon) {
		edge left = computedge(epsilon, c2[0], c1[0], c1[1]);
		edge bottom = computedge(epsilon, c1[0], c2[0], c2[1]);

		if (left.start != 0 || bottom.start != 0)
			return false;

		edge top = computedge(epsilon, c1[n1], c2[n2-1], c2[n2]);
		edge right = computedge(epsilon, c2[n2], c1[n1-1], c1[n1]);

		if (right.end != 1 || top.end != 1)
			return false;



		stack<vector<int>> cell = stack<vector<int>>();
		set<vector<int>> seen = set<vector<int>>();
		cell.push({ 0,0 });
		seen.insert({ 0,0 });

		while (!cell.empty()){
			vector<int> ind = cell.top();

			cell.pop();

			top = computedge(epsilon, c1[ind[0]+1], c2[ind[1]], c2[ind[1] + 1]);
			right = computedge(epsilon, c2[ind[1]+1], c1[ind[0]], c1[ind[0] + 1]);
	

			if (ind[0] == n1 - 1 && ind[1] == n2 - 1)
				return true; //reached end,

			if (top.passable() && ind[0] + 1 < n1 && seen.count({ ind[0] + 1, ind[1] }) == 0){
				cell.push({ ind[0] + 1, ind[1] });
				seen.insert({ ind[0] + 1, ind[1] });
			}
			if (right.passable() && ind[1] + 1 < n2 && seen.count({ ind[0], ind[1] + 1 }) == 0){
				cell.push({ ind[0], ind[1] + 1 });
				seen.insert({ ind[0], ind[1] + 1 });
			}
		}

		return false;
	}

private:
	vector<Point_3> c1;
	vector<Point_3> c2;

	unsigned long n1;
	unsigned long n2;

	class edge 
	{
	public:
		
		edge (double s = 0, double e = 0) {
			start = s;
			end = e;
		}
		
		~edge(){};
		
		bool passable() {
			if (start >= 0 && start <= 1 && end >= 0 && end <= 1)
				return true;
			else
				return false;
		}


		double start;
		double end;

	};

	edge computedge (double epsilon, Point_3 center, Point_3 p1, Point_3 p2) {
		Sphere_3 sphere = Sphere_3(center, epsilon);
		LineArc3 line = LineArc3(p1, p2);

		vector<InterO> output;
		typedef CGAL::Dispatch_output_iterator< CGAL::cpp11::tuple<InterO>, 
						CGAL::cpp0x::tuple< back_insert_iterator<vector<InterO> > > > Dispatcher;
		Dispatcher disp = CGAL::dispatch_output<InterO>( back_inserter(output) );

		CGAL::intersection(line, sphere, disp);

		// verify part
		if(output.size() == 0) {
			if (sphere.has_on_unbounded_side(p1) && sphere.has_on_unbounded_side(p2)) {
				return edge(-1,-1);  // not pass 
			} else{

				return edge(0,1);
			}
		}

		else if(output.size() == 1) {
			if (sphere.has_on_unbounded_side(p1) && sphere.has_on_unbounded_side(p2)) {
			
				Point_3 inter1(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y()), CGAL::to_double(output[0].first.z()));
			
				double start2 = CGAL::to_double(CGAL::squared_distance(p1, inter1)/CGAL::squared_distance(p1,p2));
				double end2 = start2;
				return edge(start2, end2);
			}
			else if (sphere.has_on_unbounded_side(p1) && sphere.has_on_bounded_side(p2) ) {
	
				Point_3 inter1(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y()), CGAL::to_double(output[0].first.z()) );
				double start2 = CGAL::to_double(CGAL::squared_distance(p1, inter1)/CGAL::squared_distance(p1,p2));
				double end2 = 1.0;
				return edge(start2, end2);
			}

			else if (sphere.has_on_bounded_side(p1) && sphere.has_on_unbounded_side(p2)) {
			//return edge(Point_2(Point_2(p1), 
							//Point_2(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y()))));
				Point_3 inter1(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y()), CGAL::to_double(output[0].first.z()));
				double start2 = 0.0;
				double end2 = CGAL::to_double(CGAL::squared_distance(p1, inter1)/CGAL::squared_distance(p1,p2));
				return edge(start2, end2);
			}
	}

		else if (output.size() > 1) {
		//return edge (Point_2(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y())),
						//Point_2(CGAL::to_double(output[1].first.x()), CGAL::to_double(output[1].first.y())));
			Point_3 inter1(CGAL::to_double(output[0].first.x()), CGAL::to_double(output[0].first.y()), CGAL::to_double(output[0].first.z()));
			Point_3 inter2(CGAL::to_double(output[1].first.x()), CGAL::to_double(output[1].first.y()), CGAL::to_double(output[1].first.z()));
			double start2 = CGAL::to_double(CGAL::squared_distance(p1, inter1)/CGAL::squared_distance(p1,p2));
			double end2 = CGAL::to_double(CGAL::squared_distance(p1, inter2)/CGAL::squared_distance(p1,p2));
			return edge(start2, end2);
		}
	}



};


	
























