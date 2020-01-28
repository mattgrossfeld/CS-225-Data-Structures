/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num)
{
	int oldSize;
	oldSize = upTree.size();

	upTree.resize(oldSize + num);
	size_t x = (size_t) oldSize;
	while (x < upTree.size())
	{
		upTree[x] = -1;
		x++;
	}
}

int DisjointSets::find(int elem)
{
	if (upTree[elem] >= 0)
	{
		upTree[elem] = find(upTree[elem]);
		return find(upTree[elem]);
	}		

	return elem;
	
}

void DisjointSets::setunion(int a, int b)
{
	int elem1 = find(a), elem2 = find(b);
	int newSize = upTree[elem1] + upTree[elem2];
	if (upTree[elem1] > upTree[elem2])
	{
		upTree[elem1] = elem2;
		upTree[elem2] = newSize;
	}
	else
	{
		upTree[elem2] = elem1;
		upTree[elem1] = newSize;
	}
}

int DisjointSets::size(int elem)
{
	return upTree[elem];
}
