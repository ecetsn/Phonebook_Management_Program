#ifndef AVL_H
#define AVL_H

#include <string>
#include <vector>

using namespace std;

/////////////////////////////
///		AVL Class        ////						
/////////////////////////////


template <class Comparable>
class AvlTree;

template <class Comparable>
class AvlNode
{
	Comparable 	element;
	Comparable 	element_f;
	Comparable 	fullInfo;
	AvlNode   		*left;
	AvlNode   		*right;
	int        		height;

	AvlNode( const Comparable & theElement, AvlNode *lt, AvlNode *rt, int h = 0 )
		: fullInfo( theElement ), left( lt ), right( rt ), height( h ) {
			// Extract the first two words from fullInfo
			istringstream iss(fullInfo);
			string firstWord, secondWord;
			iss >> firstWord >> secondWord;
			element = firstWord + " " + secondWord;
			element_f = to_upper(element);
	}

	friend class AvlTree<Comparable>;
};

template <class Comparable>
class AvlTree
{
public:
	explicit AvlTree( const Comparable & notFound );
	AvlTree( const AvlTree & rhs );
	~AvlTree( );

	const Comparable & findMin( ) const;
	const Comparable & findMax( ) const;
	const Comparable & find( const Comparable & x ) const;
	vector<string> findPartial(const string& searchStr, vector<string>& results) const;
	bool isEmpty( ) const;
	bool isBalanced() ;
	void inOrderPrintTree(ofstream& outFile ) const;
	void preOrderPrintTree(ofstream& outFile ) const;	
	void getHeight();
	void makeEmpty( );
	void insert( const Comparable & x , const Comparable & y );
	void remove( const Comparable & x );
	void drawTree(ofstream& outFile);
private :
	AvlNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( AvlNode<Comparable> *t ) const;
	int getHeight( AvlNode<Comparable> * root);
	bool isBalanced(AvlNode<Comparable>* root) ;
	void insert( const Comparable & x,const Comparable & y, AvlNode<Comparable> * & t ) const;
	void remove(const Comparable & x, AvlNode<Comparable> * & t ) const;
	void makeEmpty( AvlNode<Comparable> * & t ) const;
	void printTree( AvlNode<Comparable> *t ) const;
	void inOrderPrintTree( AvlNode<Comparable> *t , ofstream& outFile ) const;
	void preOrderPrintTree( AvlNode<Comparable> *t , ofstream& outFile) const;
	void drawTree(AvlNode<Comparable> * t, ofstream& outFile, bool isRight, const string& space);
	AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
	AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
	AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> *t ) const;
	void findPartial( const string & searchStr, AvlNode<Comparable> * t, vector<string> & results ) const;

	// Avl manipulations
	int height( AvlNode<Comparable> *t ) const;
	int max( int lhs, int rhs ) const;
	int getBalance(AvlNode<Comparable> *t) const;
	void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
	void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
	void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
	void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const;
};

//////////////////////////////////////////////////////////////////////////////
///		      Constructor, Destructor, Copy Constructor                   ////						
//////////////////////////////////////////////////////////////////////////////

//Construct the tree.
template <class Comparable>
AvlTree<Comparable>:: AvlTree(const Comparable & notFound ) :
	ITEM_NOT_FOUND( notFound ), root( NULL ){}

// Destructor for the tree.
template <class Comparable>
AvlTree<Comparable>::~AvlTree( )
{
	makeEmpty( );
}

// Copy constructor, shallow copy.
template <class Comparable>
AvlTree<Comparable>:: AvlTree( const AvlTree<Comparable> & rhs ) : root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{ 
	*this = rhs;
}

//////////////////////////////////////////////////////////////////////////////////////
///								Member Functions							      ////						
//////////////////////////////////////////////////////////////////////////////////////

template <class Comparable>
bool AvlTree<Comparable>:: isBalanced() {
	return isBalanced(root);
}

template <class Comparable>
bool AvlTree<Comparable>::isBalanced(AvlNode<Comparable>* root) {
	if (root == NULL) {
		return true;
	} else {
		int leftHeight = getHeight(root->left);
		int rightHeight = getHeight(root->right);
		if (abs(leftHeight - rightHeight) > 1) {
			return false;
		}
		return isBalanced(root->left) && isBalanced(root->right);
	}
}

template <class Comparable>
void AvlTree<Comparable>::getHeight( ) {
	int right, left;

	if(root)
		left = getHeight(root->left);
	else
		left = 0;

	if(root)
		right = getHeight(root->right) ;
	else
		right = 0;

	cout << "The heights of BST are for left: " << left << " and right: " << right << endl;
}

template <class Comparable>
int AvlTree<Comparable>::getHeight(AvlNode<Comparable> * root) {
	if (root == NULL) 
		return 0;
	else {
		// Find the height of left, right subtrees
		int left_height = getHeight(root->left);
		int right_height = getHeight(root->right);

		// Find max(subtree_height) + 1 to get the height of the tree
		return max(left_height, right_height) + 1;
	}
}

//Return the height of node t, or -1, if NULL.
template <class Comparable>
int AvlTree<Comparable>::height( AvlNode<Comparable> *t ) const
{
	if (t == NULL)
		return -1;

	return t->height;
}

//Return maximum of lhs and rhs.
template <class Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs ) const
{
	if (lhs > rhs)
		return lhs;

	return rhs;            
}

/*
Insert x into the tree; duplicates are ignored.
*/
template <class Comparable>
void AvlTree<Comparable>::insert( const Comparable & x , const Comparable & y )
{
	insert( x, y ,root );
}

// inserting into AVL Tree considering tree balance
template <class Comparable>
void AvlTree<Comparable>::insert ( const Comparable & x, const Comparable & y, AvlNode<Comparable> * & t ) const{


	if ( t == NULL ){
		t = new AvlNode<Comparable>( y, NULL, NULL );
	}
	else if (x.compare(t->element) < 0 ) {
		// X should be inserted to the left tree!
		insert( x, y,t->left );

		// Check if the left tree is out of balance (left subtree grew in height!)
		if ( height( t->left ) - height( t->right ) == 2 )
			if ( x.compare(t->left->element) < 0 )  // X was inserted to the left-left subtree!
				rotateWithLeftChild( t );
			else			     // X was inserted to the left-right subtree!
				doubleWithLeftChild( t );
	}
	else if( x.compare(t->element) > 0)
	{    // Otherwise X is inserted to the right subtree
		insert( x, y,t->right );
		if ( height( t->right ) - height( t->left ) == 2 )
			// height of the right subtree increased
				if ( x.compare(t->right->element) > 0 )
					// X was inserted to right-right subtree
						rotateWithRightChild( t );
				else // X was inserted to right-left subtree
					doubleWithRightChild( t );
	}
	else{
		cout << "The given " << t->element << " already exists in the database." << endl; // Duplicate; do nothing
		return;
	}

	// update the height the node
	t->height = max( height( t->left ), height( t->right ) ) + 1;
}

template <class Comparable>
int AvlTree<Comparable>::getBalance(AvlNode<Comparable> *t) const
{
	if (t == nullptr)
		return 0;
	return height(t->left) - height(t->right);
}

template <class Comparable>
void AvlTree<Comparable>::remove( const Comparable & x )
{
	remove( x, root );
}

// deletion from AVL Tree considering the height balance
template <class Comparable>
void AvlTree<Comparable>::remove(const Comparable & x, AvlNode<Comparable> * & t) const
{
	if (t == nullptr)
		return;  // Item not found; do nothing

	if (x.compare(t->element_f) < 0)
		remove(x, t->left);
	else if (x.compare(t->element_f) > 0)
		remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr) // Two children
	{
		t->fullInfo = findMin(t->right)->fullInfo;
		t->element = findMin( t->right )->element;
		t->element_f = findMin( t->right )->element_f;
		t->height = findMin( t->right )->height;

		remove(t->element_f, t->right);
	}
	else // one or no children
	{
		AvlNode<Comparable> *oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}

	if (t == nullptr)
		return;

	// update the height of the node
	t->height = 1 + max(height(t->left), height(t->right));

	// check if the node is unbalanced
	int balance = getBalance(t);

	if (balance > 1 && getBalance(t->left) >= 0) // left-left case
		rotateWithRightChild(t);
	else if (balance > 1 && getBalance(t->left) < 0) // left-right case
	{
		rotateWithLeftChild(t->left);
		rotateWithRightChild(t);
	}
	else if (balance < -1 && getBalance(t->right) <= 0) // right-right case
		rotateWithLeftChild(t);
	else if (balance < -1 && getBalance(t->right) > 0) // right-left case
	{
		rotateWithRightChild(t->right);
		rotateWithLeftChild(t);
	}
}

/*
Internal method to get element field in node t.
Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
const Comparable & AvlTree<Comparable>:: elementAt( AvlNode<Comparable> *t ) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->fullInfo;
}


//Find Helper
template <class Comparable>
const Comparable & AvlTree<Comparable>::find( const Comparable & x ) const
{
	if(find( x, root )!= NULL){
		return x;
	}
	else
		return ITEM_NOT_FOUND ;
}

/*
Internal method to find an item in a subtree.
x is item to search for.
t is the node that roots the tree.
Return node containing the matched item.
*/
template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::find( const Comparable & x, AvlNode<Comparable> * t ) const
{
	if ( t == NULL )
		return NULL;
	else if( x.compare(t->element_f) < 0 )
		return find( x, t->left );
	else if(x.compare(t->element_f) > 0 )
		return find( x, t->right );
	else
		return t;    // Match
}

template <class Comparable>
vector<string> AvlTree<Comparable>::findPartial(const string& searchStr, vector<string>& results) const
{
	findPartial(searchStr, root, results);
	return results;
}

template <class Comparable>
void AvlTree<Comparable>::findPartial( const string & searchStr, AvlNode<Comparable> * t, vector<string> & results ) const
{
	if ( t == NULL )
		return;
	else if( searchStr.length() <= t->element_f.length() && t->element_f.substr(0, searchStr.length()) == searchStr )
		results.push_back(t->fullInfo);

	findPartial(searchStr, t->left, results);
	findPartial(searchStr, t->right, results);
}

//FindMin Helper
template <class Comparable>
const Comparable & AvlTree<Comparable>::findMin( ) const
{
	return elementAt( findMin( root ) );
}

/*
Internal method to find the smallest item in a subtree t.
Return node containing the smallest item.
*/
template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::findMin( AvlNode<Comparable> *t ) const
{
	if( t == NULL )
		return NULL;
	if( t->left == NULL )
		return t;
	return findMin( t->left );
}

//FindMax Helper
template <class Comparable>
const Comparable & AvlTree<Comparable>::findMax( ) const
{
	return elementAt( findMax( root ) );
}

/*
Internal method to find the largest item in a subtree t.
Return node containing the largest item.
*/
template <class Comparable>
AvlNode<Comparable> *AvlTree<Comparable>::findMax( AvlNode<Comparable> *t ) const
{
	if( t != NULL )
		while( t->right != NULL )
			t = t->right;
	return t;
}     


//Make the tree logically empty.
template <class Comparable>
void AvlTree<Comparable>::makeEmpty( )
{
	makeEmpty( root );
}

// logical control
template <class Comparable>
bool AvlTree<Comparable>:: isEmpty( ) const
{
	return root == nullptr;
}

//Internal method to make subtree empty.
template <class Comparable>
void AvlTree<Comparable>:: makeEmpty( AvlNode<Comparable> * & t ) const
{
	if( t != NULL )
	{
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	t = NULL;
}

//Print the tree contents in sorted order.
template <class Comparable>
void AvlTree<Comparable>::inOrderPrintTree(ofstream& outFile ) const
{
	if( isEmpty( ) )
		return;
	else
		inOrderPrintTree( root , outFile );
}

//Internal method to print a subtree rooted at t in sorted order.
template <class Comparable>
void AvlTree<Comparable>::inOrderPrintTree( AvlNode<Comparable> * t , ofstream& outFile) const
{
	if ( t != NULL )
	{
		inOrderPrintTree( t->left , outFile);
		outFile << t->fullInfo << endl;
		inOrderPrintTree( t->right , outFile);
	}
}

//Print the tree contents in preOrder
template <class Comparable>
void AvlTree<Comparable>::preOrderPrintTree( ofstream& outFile) const
{
	if( isEmpty( ) )
		return;
	else
		preOrderPrintTree( root , outFile );
}

//Internal method to print a subtree rooted at t in sorted order.
template <class Comparable>
void AvlTree<Comparable>::preOrderPrintTree( AvlNode<Comparable> * t , ofstream& outFile) const
{
	if ( t != NULL )
	{
		outFile << t->fullInfo << endl;
		preOrderPrintTree( t->left , outFile);
		preOrderPrintTree( t->right, outFile );
	}
}

template <class Comparable>
void AvlTree<Comparable>::drawTree(ofstream& outFile) {
	drawTree(root,outFile,true,"");
}

template <class Comparable>
void AvlTree<Comparable>::drawTree(AvlNode<Comparable> * t, ofstream& outFile, bool isRight, const string& space) {
	if (t == nullptr)
		return;

	string n_space = space;

	if (isRight) {
		outFile << n_space <<"|__ " << t->element << endl;
		n_space += "    ";
	} else {
		outFile << n_space <<"|-- " << t->element << endl;	
		n_space += "|   ";
	}

	drawTree(t->left, outFile, false,n_space);
	drawTree(t->right, outFile,true,n_space);
}
//////////////////////////////////////////////////////////////////////////////////////
///								AVL Manipulation							      ////						
//////////////////////////////////////////////////////////////////////////////////////

/*
Rotate binary tree node with left child.
For AVL trees, this is a single rotation for case 1.
Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const
{
	AvlNode<Comparable> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}

/*
Rotate binary tree node with right child.
For AVL trees, this is a single rotation for case 4.
Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::rotateWithRightChild( AvlNode<Comparable> * & k1 ) const
{
	AvlNode<Comparable> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
	k2->height = max( height( k2->right ), k1->height ) + 1;
	k1 = k2;
}

/*
Double rotate binary tree node: first left child.
with its right child; then node k3 with new left child.
For AVL trees, this is a double rotation for case 2.
Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const
{
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}

/*
Double rotate binary tree node: first right child.
with its left child; then node k1 with new right child.
For AVL trees, this is a double rotation for case 3.
Update heights, then set new root.
*/
template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild( AvlNode<Comparable> * & k1 ) const
{
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );
}

#endif