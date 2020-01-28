/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include "binarytree.h"
#include <iostream>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
	if (root == NULL)
		return;
	else
		mirror(this->root);
	
	
}

template <typename T>
void BinaryTree<T>::mirror(Node * subRoot)  //Helper function for mirror. Same format from height, print
{
	if (subRoot != NULL)
	{
	Node * rightNode = subRoot->right; //right node is temporarily held.
	subRoot->right = subRoot->left; //make the right node the left node.
	subRoot->left = rightNode; //Left is now the temporarily held right node.
	mirror(subRoot->left); //recursively call.
	mirror(subRoot->right); //recursively call.
	}

	return;
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
	InorderTraversal<T> iot(root); //Create iterator
	for (typename TreeTraversal<T>::Iterator it = iot.begin(); it != iot.end(); ++it) {
		if ( (iot.peek())->elem > (*it)->elem ) //If current element is less than the next one, return false.
			return false;
		//else
		//	value = true;
	}

    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{

    // your code here
	return recursiveHelper(root);
}
//Helper function that recursively calls itself.
template <typename T>
bool BinaryTree<T>::recursiveHelper(Node * subRoot) const
{
	Node * currentNode = subRoot;
	if (currentNode == NULL)
		return true;
	if (currentNode->left != NULL && currentNode->right != NULL)
	{
		///if (currentNode->left->elem > currentNode->right->elem)
		//	return false;
		//if (currentNode->right->elem < currentNode->left->elem)
		//	return false;
		if (currentNode->elem < currentNode->left->elem)
			return false;
		if (currentNode->elem > currentNode->right->elem)
			return false;
	bool leftVal = recursiveHelper(currentNode->left);
	bool rightVal = recursiveHelper(currentNode->right);
	
	return leftVal & rightVal;
	}
	return true;
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here
	vector<T> tempVector;
	pathsHelper(root, paths, tempVector); //Recursive call.
		
}


template <typename T>
void BinaryTree<T>::pathsHelper(Node * subRoot, vector<vector<T> > &paths, vector<T> tempVector) const
{
		tempVector.push_back(subRoot->elem);
		if (subRoot->left == NULL && subRoot->right == NULL)
		{
			paths.push_back(tempVector);
			return;
		}
		if (subRoot->left != NULL)
			pathsHelper(subRoot->left, paths, tempVector);
		if (subRoot->right != NULL)
			pathsHelper(subRoot->right, paths, tempVector);
}
/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
	int sum = 0;
	int distance = -1;
    return sumDistancesHelper(root, sum, distance);
}

template <typename T>
int BinaryTree<T>::sumDistancesHelper( Node * subRoot, int sum, int distance) const
{
	if (subRoot == NULL)
		return sum;
	distance++;
	sum+=distance;
	if (subRoot->left != NULL)
		sum = sumDistancesHelper(subRoot->left, sum, distance);
	if (subRoot->right != NULL)
		sum = sumDistancesHelper(subRoot->right, sum, distance);
	return sum;
}


