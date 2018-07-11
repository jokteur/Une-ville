#ifndef ROADSYSTEM_H
#define ROADSYSTEM_H

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

struct Lane
{
	int authorizedVehicles;
	int authorizedCrossingLeft;
	int authorizedCrossingRight;

	uint16_t speedLimit;
	vector<Lane*> connectedLanesAt_a;
	vector<Lane*> connectedLanesAt_b;
};
struct Segment
{
	Intersection* vertice_a; //Vertices adjacent to the segment
	Intersection* vertice_b;
	vector<Lane> a_to_b;
	vector<Lane> b_to_a;
};

class RoadSystem
{
    public:
		RoadSystem();
        virtual ~RoadSystem();

		Intersection addIntersectionInSegment(Segment sgmt, float pos); //pos is in % from a to b of the segment
		Segment connectIntersections(Intersection *a, Intersection *b);
		Segment addSegment(Position pos_a, Position pos_b);
		void addLaneInSegment(Segment &sgmt, Lane lane);

		//Getters
		vector<Segment> getSegments() { return _segments; }
		vector<Intersection> getIntersections() { return _intersections; }
    private:
		vector<Segment> _segments;
		vector<Intersection> _intersections;
};

#endif // INTERSECTIONS_H
