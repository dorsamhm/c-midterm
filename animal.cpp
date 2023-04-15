#include "animal.h"
#include <vector>
#include <iostream>
void animal::newAnimal() {
	int cromozomes;
	cout << "\tenter cromosome count:";
	cin >> cromozomes;
	getCromozome(cromozomes);
}
float checkSimilarity(string gene1,string gene2) {
	float same = 0;
	for (unsigned int i = 0; i <gene1.size(); ++i) 
			if (gene1[i] == gene2[i])
				++same;
	return same*100/ gene1.size();
}
float animal::SimilarityPercentage(const animal& anim) {
	float totalSimilarity = 0,result;
	for (int i = 0; i < cromozomeCount; i++)
	{
		string gene1 = gene[i].readGeneDNA();
		float similarEachGene = 0;
		for (int j = 0; j < anim.cromozomeCount; j++)
		{			
			string gene2 = anim.gene[j].readGeneDNA();
			result = checkSimilarity(gene1,gene2);
			similarEachGene += result;
			//cout << "\n\tsimilarity " << gene1 << " and " << gene2 << "= " << result;
		}
		totalSimilarity += similarEachGene/anim.cromozomeCount;
		//cout << "\n\taverage similarity:" << similarEachGene / anim.cromozomeCount;
	}
	cout << "\n\ttotal similarity:" << totalSimilarity / cromozomeCount;
	return totalSimilarity / cromozomeCount;
}
bool animal::operator == (const animal& a)
{	
	float percent=SimilarityPercentage(a);
	cout << "\n\n\ttotal similarity is: " << percent;
	if (percent>0.7 && a.cromozomeCount==cromozomeCount)
		return true;
	return false;
}
animal animal::reproduction()
{
	srand((unsigned)time(NULL));
	animal child,temp;
	
	child.cromozomeCount = cromozomeCount;
	child.gene = new genome[cromozomeCount];
	
	int n = cromozomeCount*2;
	temp.cromozomeCount = n;
	temp.gene = new genome[n];

	for (auto i = 0; i < n/2; i++)
	{
		temp.gene[i].getGene( gene[i].readGeneRNA());
		temp.gene[n - i - 1].getGene(gene[i].readGeneRNA());
	}
	//temp.print();
	float percent;
	do {
		for (int i = 0; i < n / 2; i++)
		{
			int r = (rand() % (n - 0)) + 0;
			child.gene[i].getGene(temp.gene[r].readGeneRNA());
		}
		//child.print();
		percent = SimilarityPercentage(child);
	} while (percent < 50);
	
	return child;
}
animal animal::operator+(animal const& obj)
{
	animal child;
	srand((unsigned)time(NULL));
	if (obj.cromozomeCount % 2 != 0 || cromozomeCount % 2 != 0)
	{		
		child.cromozomeCount = 0;
	}
	else {
		int percent=0;
		do {			
			int n = cromozomeCount;
			animal parent1 = obj, parent2 = *this;
			child.cromozomeCount = n;
			child.gene = new genome[cromozomeCount];
			int i = 0, r;		
			while (i < n/2)
			{				
				r = rand() % n ;
				child.gene[i].getGene(parent1.gene[r].readGeneRNA());
				i++;
			}
			while (i < n)
			{
				r = rand() % n ;
				child.gene[i].getGene(parent2.gene[r].readGeneRNA());
				i++;
			}
			percent = SimilarityPercentage(child);
			cout << "\n\n\tProduced child with similarity "<<percent<<" is:";
			child.print();
		} while (percent < 50);
	}
	return child;
}
void animal::cellDie() {
	bool* die = new bool[cromozomeCount];
	int newCromozomeCount = 0;
	for (auto c = 0; c < cromozomeCount; c++)
	{
		
		int point = 0, AT = 0, GC = 0;
		DNA[0] = gene[c].readGeneDNA0();
		DNA[1] = gene[c].readGeneDNA1();
		for (unsigned int i = 0; i < DNA[0].length(); i++)
		{
			if (
				(DNA[0][i] == 'A' && DNA[1][i] != 'T')
				||
				(DNA[0][i] == 'T' && DNA[1][i] != 'A')
				||
				(DNA[0][i] == 'G' && DNA[1][i] != 'C')
				||
				(DNA[0][i] == 'C' && DNA[1][i] != 'G')
				)
				point++;

			if ((DNA[0][i] == 'A' && DNA[1][i] == 'T')
				||
				(DNA[0][i] == 'T' && DNA[1][i] == 'A'))
				AT++;

			if ((DNA[0][i] == 'G' && DNA[1][i] == 'C')
				||
				(DNA[0][i] == 'C' && DNA[1][i] == 'G'))
				GC++;
		}
		if (point > 5 || AT > 3 * GC)//should delete this gene		
		{
			cout << "\n\tDNA " << gene[c].readGeneDNA() << " died..";
			die[c] = true;
		}
		else
		{
			cout << "\n\tDNA " << gene[c].readGeneDNA() << " not died..";
			die[c] = false;
			newCromozomeCount++;
		}
	}

	genome* newGenome = new genome[newCromozomeCount];
	int g = 0;
	for (int d = 0; d < cromozomeCount; d++)
	{
		if (die[d]==false)
			newGenome[g++] = gene[d];
	}
	cromozomeCount = newCromozomeCount;
	delete[] gene;
	gene = newGenome;
}
vector <string> animal::geneList() {
	vector <string> strings;
	for (int i = 0; i < cromozomeCount; i++)
		strings.push_back(gene[i].readGeneDNA0());
	return strings;
}
