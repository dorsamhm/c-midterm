#pragma once
#include "cell.h"
#include "virus.h"
#include <vector>
#include <iostream>
class animal:public cell
{
	friend class virus;
public:	
	void newAnimal();
	float SimilarityPercentage(const animal& a);
	bool operator == (const animal& a);
	animal reproduction();
	animal operator+(animal const& obj);
	void cellDie();
	vector <string> geneList();
};

