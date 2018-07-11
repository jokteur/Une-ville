#ifndef TYPES_H
#define TYPES_H

enum intersectionType { normal, roundabout };

struct Position {
    float x;
    float y;
    float z;
    Position operator+(const Position& p){
        Position pos;
        pos.x = this -> x + p.x;
        pos.y = this -> y + p.y;
        pos.y = this -> y + p.y;
        return pos;
    }
    
    Position operator*(const float& f){
        Position pos;
        pos.x = this -> x * f;
        pos.y = this -> y * f;
        pos.z = this -> z * f;
        return pos;
    }
    
    Position operator-(const Position& p){
        Position pos;
        pos.x = this -> x - p.x;
        pos.y = this -> y - p.y;
        pos.y = this -> y - p.y;
        return pos;
    }
};

struct intersection
{
	position pos;
	intersectionType type;
};


#endif
