/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */


//Testing to fix git.
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
	Node * y = t->right;
	t->right = y->left;
	y->left = t;
	t->height = 1+max(heightOrNeg1(t->left), heightOrNeg1(t->right));
	t = y;
	t->height = 1+max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
	Node * y = t->left;
	t->left = y->right;
	y->right = t;
	t->height = 1+max(heightOrNeg1(t->left), heightOrNeg1(t->right));
	t = y;
	t->height = 1+max(heightOrNeg1(t->left), heightOrNeg1(t->right));

}


template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
	rotateRight(t->right);
	rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
	int balanceFactor = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
	if (balanceFactor == 2) //Right heavy.
	{
		int rightBF = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
		if (rightBF == -1) //Right's left subtree is heavier.
			rotateRightLeft(subtree);
		else
			rotateLeft(subtree);
	}
	if (balanceFactor == -2) //Left heavy
	{
		int leftBF = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
		if (leftBF == 1) //Left's right subtree is heavier.
			rotateLeftRight(subtree);
		else
			rotateRight(subtree);
	}

	subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
	if (subtree == NULL) //Must insert at leaf node.
		subtree = new Node(key, value);
	else if (key < subtree->key) //Key smaller than the current node.
		insert(subtree->left, key, value);
	else if (key > subtree->key) //Key larger than the current node.
		insert(subtree->right, key, value);
	rebalance(subtree); //Make sure it is balanced.
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
		delete subtree;
		subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
		Node* iop =subtree->left;
		while (iop->right != NULL)
			iop = iop->right;
		swap(subtree, iop);
		remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
		Node* leftNode = subtree->left; //Hold the subtree's left node.
		Node* rightNode = subtree->right; //Hold the subtree's right node.
		
		delete subtree; //Delete it.
		if (leftNode != NULL) //Left not null, but right is.
			subtree = leftNode;
		else //Right not null, but left is.
			subtree = rightNode;		
        }
        // your code here
	
    }
	if (subtree != NULL) //Keep the tree balanced.
		rebalance(subtree);
}
