#ifndef PHSYICS
#define PHYSICS
#include "globals.h"
/*
eventually will be narrow phase collision detection library
another library will be broad phase(prob quadtree)
*/
struct point {
	Vector2 pos{};
};
struct colliderObject {
	std::vector<point> vertices;
};

//Testing
struct polygon : public colliderObject {

};
struct circle : public colliderObject {

};
//end

//GEOMETRY SHIT
Vector2 getVector(Vector2 vertexOne, Vector2 vertexTwo);
Vector2 getPerpindicular(Vector2 input);
float getDotProduct(Vector2 inputOne, Vector2 inputTwo);




















//Actuall Collision Stuff
struct comparator;
bool SATCollision(const colliderObject& colliderObjectA, const colliderObject& colliderObjectB);

struct collTestSets;
//IMPLEMENT LATER
//struct objectParameters;//USE AS A WAY TO QUICKLY SET UP OBJECTS LATER
//Vector2 normalizeVector();//Use for getting specific collision data later
#endif