#include "physics.h"

//GEOMETRY SHIT
Vector2 getVector(Vector2 vertexOne, Vector2 vertexTwo) {
	Vector2 output{};
	output.x = vertexTwo.x - vertexOne.x;
	output.y = vertexTwo.y - vertexOne.y;
	return output;
}
Vector2 getPerpindicular(Vector2 input) {
	float temp = input.x;
	input.x = input.y * -1;
	input.y = temp;
	return input;
}
float getDotProduct(Vector2 inputOne, Vector2 inputTwo) {
	Vector2 output{};
	output.x = inputOne.x * inputTwo.x;
	output.y = inputOne.y * inputTwo.y;
	return output.x + output.y;
}







//OLD SHIT WILL REWORK
//Actuall Collision Stuff
struct comparator {
	float aMin{}, aMax{}, bMin{}, bMax{};

	const bool checkProjection() {
		std::cout << aMin << " " << aMax << " " << bMin << " " << bMax << '\n';
		if ((aMin <= bMax && aMin >= bMin) || (bMin <= aMax && bMin >= aMin)) {
			return true; 
		}
		else {
			return false;
		}
	}
	void compareProjectionA(float projection) {
		if (projection > aMax) {
			aMax = projection;
			return;
		}
		if (projection < aMin) {
			aMin = projection;
			return;
		}
		return;
	}
	void compareProjectionB(float projection) {
		if (projection > bMax) {
			bMax = projection;
			return;
		}
		if (projection < bMin) {
			bMin = projection;
			return;
		}
		return;
	}
};

bool SATCollision(const colliderObject& colliderObjectA, const colliderObject& colliderObjectB) {//its so ugly:(
	comparator Data;
	Vector2 edgeVector{};
	float projection{};

	for (int i = 0; i < colliderObjectA.vertices.size() - 1; i++) {
		edgeVector = getVector(colliderObjectA.vertices[i].pos, colliderObjectA.vertices[i + 1].pos);
		edgeVector = getPerpindicular(edgeVector);

		Data.aMax = Data.aMin = getDotProduct(edgeVector, colliderObjectA.vertices[0].pos);
		for (int j = 1; j < colliderObjectA.vertices.size(); j++) {
			Data.compareProjectionA(getDotProduct(edgeVector, colliderObjectA.vertices[j].pos));
		}

		Data.bMax = Data.bMin = getDotProduct(edgeVector, colliderObjectB.vertices[0].pos);
		for (int j = 1; j < colliderObjectB.vertices.size(); j++) {
			Data.compareProjectionB(getDotProduct(edgeVector, colliderObjectB.vertices[j].pos));
		}

		if (Data.checkProjection()) {
			continue;
		}
		else { return false; };
	}
	edgeVector = getVector(colliderObjectA.vertices.back().pos, colliderObjectA.vertices[0].pos);
	Data.aMax = Data.aMin = getDotProduct(edgeVector, colliderObjectA.vertices[0].pos);
	for (int j = 1; j < colliderObjectA.vertices.size(); j++) {
		Data.compareProjectionA(getDotProduct(edgeVector, colliderObjectA.vertices[j].pos));
	}

	Data.bMax = Data.bMin = getDotProduct(edgeVector, colliderObjectB.vertices[0].pos);
	for (int j = 1; j < colliderObjectB.vertices.size(); j++) {
		Data.compareProjectionB(getDotProduct(edgeVector, colliderObjectB.vertices[j].pos));
	}

	if (Data.checkProjection()) {}
	else { return false; };

	return true;
}

struct collTestSets {
private:
	std::string formatted_str = std::format(
		"Hello, {}", 14
	);
	struct ER {//A test sets expected results
		bool isColliding{};
	};
	struct TestSet {
		colliderObject polyA{};
		colliderObject PolyB{};
		ER result{false};
	};
	TestSet Set1;//upright non-colliding squares
	TestSet Set2;//upright colliding squares
	collTestSets() {
		Set1.result.isColliding = false;
		Set1.polyA.vertices.reserve(4);
		Set1.polyA.vertices[0].pos = { .x = 1, .y = 1 };
		Set1.polyA.vertices[1].pos = { .x = 1, .y = 5 };
		Set1.polyA.vertices[2].pos = { .x = 5, .y = 5 };
		Set1.polyA.vertices[3].pos = { .x = 5, .y = 1 };
		Set1.PolyB.vertices.reserve(4);
		Set1.PolyB.vertices[0].pos = { .x = 7, .y = 3 };
		Set1.PolyB.vertices[1].pos = { .x = 7, .y = 7 };
		Set1.PolyB.vertices[2].pos = { .x = 11, .y = 7 };
		Set1.PolyB.vertices[3].pos = { .x = 11, .y = 3 };

		Set2.result.isColliding = true;
		Set2.polyA.vertices.reserve(4);
		Set2.polyA.vertices[0].pos = { .x = 1, .y = 1 };
		Set2.polyA.vertices[1].pos = { .x = 1, .y = 5 };
		Set2.polyA.vertices[2].pos = { .x = 5, .y = 5 };
		Set2.polyA.vertices[3].pos = { .x = 5, .y = 1 };
		Set2.PolyB.vertices.reserve(4);
		Set2.PolyB.vertices[0].pos = { .x = 3, .y = 3 };
		Set2.PolyB.vertices[1].pos = { .x = 3, .y = 7 };
		Set2.PolyB.vertices[2].pos = { .x = 7, .y = 7 };
		Set2.PolyB.vertices[3].pos = { .x = 7, .y = 3 };
	}
public:
	std::string runTestSet() {
		SATCollision(Set1.polyA, Set1.PolyB);
		SATCollision(Set2.polyA, Set2.PolyB);

		return "";
	}
};