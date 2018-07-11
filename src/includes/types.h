#ifndef TYPES_H
#define TYPES_H

enum intersectionType { normal, roundabout };

struct position
{
	float x;
	float y;
	float z;
};
struct intersection
{
	position pos;
	intersectionType type;
};


#endif