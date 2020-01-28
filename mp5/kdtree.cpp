/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
								const Point<Dim>& second, int dimension) const
{
	/**
	 * @todo Implement this function!
	 */
	if (first[dimension] > second[dimension]) // 1st point > 2nd point in current dimension
		return false;
	else if (first[dimension] < second[dimension]) //1st point < 2nd point in curr dimension
		return true;
	return first < second; //If 1st == 2nd in curr dimension, return the operator<.

}

template <int Dim>
double KDTree<Dim>::eucDistance(Point<Dim> first, Point<Dim> second) const
{
	double distanceSum = 0;
	int i;
	for (i = 0; i < Dim; i++) //Until we reach the highest dimension.
	{
		distanceSum = distanceSum + pow(first[i] - second[i], 2);
	}

	//distanceSum = sqrt(distanceSum);
	return distanceSum;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target, const Point<Dim>& currentBest, const Point<Dim>& potential) const
{
	/**
	 * @todo Implement this function!
	 */
	double potentialDistance = eucDistance(potential, target);
	double currentDistance = eucDistance(currentBest, target);

	if (potentialDistance < currentDistance)
		return true;
	else if (potentialDistance > currentDistance)
		return false;
	return potential < currentBest;
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
	/**
	 * @todo Implement this function!
	 */
	if (newPoints.size() - 1 == 0) //Make sure that we dont have first = last.
		return;
	pointz = newPoints;
	root = constructorHelper(0, newPoints.size() - 1, 0, pointz);
	return;
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::constructorHelper(int first, int last, int dimension, vector<Point<Dim>> points)
{
	if (first > last) //Return on edge cases.
		return NULL;
	int median = (first+last)/2; //Initial median.
	quickSelect(first, last, dimension, median, pointz); //Make sure median is gucci.
	KDTreeNode * node = new KDTreeNode(pointz[median]); //Allocates new node.
	node->left = constructorHelper(first, median - 1, (dimension + 1) % Dim, pointz); //Recursive call.
	node->right = constructorHelper(median + 1, last, (dimension + 1) % Dim, pointz); //Recursive call.

	return node;

}

template <int Dim>
void KDTree<Dim>::quickSelect(int first, int last, int dimension, int m, vector<Point<Dim>> points)
{
	if (first > last || first == last)
		return;
	int median = (first+last)/2;
	int currIndex = partition(first, last, dimension, median, pointz);
	if (m > currIndex)
		quickSelect(currIndex+1, last, dimension, m, pointz);
	else if (m < currIndex)
		quickSelect(first, currIndex-1, dimension, m, pointz);
	return;
}

template <int Dim>
int KDTree<Dim>::partition(int first, int last, int dimension, int p, vector<Point<Dim>> points)
{

	int currPart = first;
	int currMedian = (first+last)/2;
	int i = 0;

	Point<Dim> currPoint = pointz[p];
  	swap(pointz[last], pointz[p]);

  	for (i = first; i < last; i++)
	{
		if (smallerDimVal(pointz[i], currPoint, dimension) == true)
		{
		  		swap(pointz[i], pointz[currPart]);
		  		currPart++;
   		}
	}
  	swap(pointz[last], pointz[currPart]);
	return currPart;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& otherPoint) {
  /**
   * @todo Implement this function!
   */
	root = copy(otherPoint.root);
}

template <int Dim>
KDTree<Dim> KDTree<Dim>::copy(KDTreeNode* root)
{
	if (root == NULL)
		return NULL;

	// Copy this node and it's children
	KDTreeNode* node = new KDTreeNode(root->point);
	node->left = copy(root->left);
	node->right = copy(root->right);
	return node;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
	if (this != &rhs)
	{
		clear(root);
		root = copy(rhs.root);
	}

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
	clear(root);
}

template<int Dim>
void KDTree<Dim>::clear(KDTreeNode * root)
{
	if (root == NULL)
			return;

	clear(root->left);
	clear(root->right);
	delete root;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
	/**
	 * @todo Implement this function!
	 */
	int currentBest = finderHelper(query, 0, 0, pointz.size() - 1);
	return pointz[currentBest];
}

template <int Dim>
int KDTree<Dim>::finderHelper(const Point<Dim>& query, int dimension, int left, int right) const
{
	if (left > right || left == right)
		return left;

	int median = (left + right) / 2, currentBest, otherPoint;

	if (smallerDimVal(query, pointz[median], dimension) == false)  //right
		currentBest = finderHelper(query, (dimension + 1) % Dim, median + 1, right);
	else //left
		currentBest = finderHelper(query, (dimension + 1) % Dim, left, median - 1);

	if (shouldReplace(query, pointz[currentBest], pointz[median]) == true)
		currentBest = median;

   
	double distance = eucDistance(pointz[currentBest], query);
	Point<Dim> slicePoint = query;
	Point<Dim> tempPoint = query;
	tempPoint[dimension] = pointz[median][dimension];
	double slice = eucDistance(tempPoint, slicePoint);

	if (distance > slice || distance == slice) 
	{
		if (smallerDimVal(query, pointz[median], dimension) == false)
			otherPoint = finderHelper(query, (dimension + 1) % Dim, left, median - 1);
		else 
			otherPoint = finderHelper(query, (dimension + 1) % Dim, median + 1, right);

		if (shouldReplace(query, pointz[currentBest], pointz[otherPoint]) == true)
			currentBest = otherPoint;
	}

	return currentBest;
}
