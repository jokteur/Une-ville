#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include <vector>
#include <iostream>
#include <cstdint>

#include "types.h"

using namespace std;

#define BUS        0b00001
#define TRAM       0b00010
#define PEDESTRIAN 0b00100
#define CAR        0b01000
#define NOTHING    0b10000

struct lane
{
	int authorizedVehicles;
	int authorizedCrossingLeft;
	int authorizedCrossingRight;

	uint16_t speedLimit;
	vector<lane*> connectedLanesAt_a;
	vector<lane*> connectedLanesAt_b;
};
struct segment
{
	intersection* vertice_a; //Vertices adjacent to the segment
	intersection* vertice_b;
	vector<lane> a_to_b;
	vector<lane> b_to_a;
};

class RoadSystem
{
    public:
		RoadSystem();
        virtual ~RoadSystem();

		intersection addIntersectionInSegment(segment sgmt, float pos); //pos is in % from a to b of the segment
		segment connectIntersections(intersection *a, intersection *b);
		segment addSegment(position pos_a, position pos_b);

    private:
		vector<segment> _segments;
		vector<intersection> _intersections;
};

#endif // INTERSECTIONS_H
