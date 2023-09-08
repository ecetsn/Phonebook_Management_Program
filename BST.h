#ifndef BST_H
#define BST_H

#include <fstream>
#include <sstream>

using namespace std;

/////////////////////////////
///	BST Class        ////						
/////////////////////////////

template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
	Comparable element;
	Comparable 	element_f;
	Comparable 	fullInfo;
	BinaryNode  *left;
	BinaryNode  *right;
	int height;

	BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt ,  int h = 0)
		: fullInfo( theElement ), left( lt ), right( rt ),height( h ) {
			istringstream iss(fullInfo);
			string firstWord, secondWord;
			iss >> firstWord >> secondWord;
			element = firstWord + " " + secondWord;
			element_f = to_upper(element);
	}	

	friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree
{
public:
	explicit BinarySearchTree( const Comparable & notFound );
	~BinarySearchTree( );
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
	void insert( const Comparable & x ,const Comparable& y );
	void remove( const Comparable & x );
	void drawTree(ofstream& outFile);

private:
	BinaryNode<Comparable> *root;
	const Comparable ITEM_NOT_FOUND;
	const Comparable & elementAt( BinaryNode<Comparable> *t ) const;
	bool isBalanced(BinaryNode<Comparable>* root) ;
	int  getHeight( BinaryNode<Comparable> * root);
	int  height( BinaryNode<Comparable> *t ) const ;
	void drawTree(BinaryNode<Comparable> * t, ofstream& outFile, bool isRight, const string& space);
	void insert( const Comparable & x, const Comparable& y ,BinaryNode<Comparable> * & t ) const;
	void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
	void makeEmpty( BinaryNode<Comparable> * & t ) const;
	void inOrderPrintTree( BinaryNode<Comparable> *t , ofstream& outFile) const;
	void preOrderPrintTree( BinaryNode<Comparable> *t , ofstream& outFile) const;	
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
	BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t ) const;
	void findPartial( const string & searchStr, BinaryNode<Comparable> * t, vector<string> & results ) const;

};

/////////////////////////////////////////////////////////////////////////////
///	         Constructor, Destructor, Copy Constructor               ////						
/////////////////////////////////////////////////////////////////////////////

//Construct the tree.
template <class Comparable>
BinarySearchTree<Comparable>:: BinarySearchTree(const Comparable & notFound ) :
	ITEM_NOT_FOUND( notFound ), root( NULL ){}


// Destructor for the tree.
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
	makeEmpty( );
}

//////////////////////////////////////////////////
///		Member Function		      ////						
//////////////////////////////////////////////////

template <class Comparable>
bool BinarySearchTree<Comparable>::isBalanced() {
	return isBalanced(root);
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isBalanced(BinaryNode<Comparable>* root) {
	if (root == NULL) {
		return true;
	} 
	else {
		int leftHeight = getHeight(root->left);
		int rightHeight = getHeight(root->right);
		if (abs(leftHeight - rightHeight) > 1) {
			return false;
		}
		return isBalanced(root->left) && isBalanced(root->right);
	}
}

template <class Comparable>
void BinarySearchTree<Comparable>::getHeight( ) {
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
int BinarySearchTree<Comparable>::getHeight(BinaryNode<Comparable> * root) {
	if (root == NULL) 
		return 0;
	else {
		// Find the height of left, right subtrees
		int left_height = getHeight(root->left);
		int right_height= getHeight(root->right);

		// Find max(subtree_height) + 1 to get the height of the tree
		return max(left_height, right_height) + 1;
	}
}

//Return the height of node t, or -1, if NULL.
template <class Comparable>
int BinarySearchTree<Comparable>::height( BinaryNode<Comparable> *t ) const
{
	if (t == NULL)
		return 0;

	return t->height;
}

/*
Internal method to get element field in node t.
Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>:: elementAt( BinaryNode<Comparable> *t ) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->fullInfo;
}


//Find Helper
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::find( const Comparable & x ) const
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
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> * t ) const
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
vector<string> BinarySearchTree<Comparable>::findPartial(const string& searchStr, vector<string>& results) const
{
	findPartial(searchStr, root, results);
	return results;
}

template <class Comparable>
void BinarySearchTree<Comparable>::findPartial( const string & searchStr, BinaryNode<Comparable> * t, vector<string> & results ) const
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
const Comparable & BinarySearchTree<Comparable>::findMin( ) const
{
	return elementAt( findMin( root ) );
}

/*
Internal method to find the smallest item in a subtree t.
Return node containing the smallest item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const
{
	if( t == NULL )
		return NULL;
	if( t->left == NULL )
		return t;
	return findMin( t->left );
}


//FindMax Helper
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
	return elementAt( findMax( root ) );
}

/*
Internal method to find the largest item in a subtree t.
Return node containing the largest item.
*/
template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t ) const
{
	if( t != NULL )
		while( t->right != NULL )
			t = t->right;
	return t;
}

/*
Insert x into the tree; duplicates are ignored.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x ,const Comparable& y )
{
	insert( x, y ,root );
}

/*
Internal method to insert into a subtree.
x is the item to insert.
t is the node that roots the tree.
Set the new root. void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable& x, const Comparable& y ,BinaryNode<Comparable>*& t) const {

	if (t == NULL) {
		t = new BinaryNode<Comparable>(y, NULL, NULL);
	}
	else if (x.compare(t->element) < 0) {
		insert(x,y ,t->left);
	}
	else if (x.compare(t->element) > 0) {
		insert(x,y ,t->right);
	}
	else {
		cout << "The given " << t->element << " already exists in the database." << endl; // Duplicate
		return;
	}
	t->height = max( height( t->left ), height( t->right ) ) + 1;
}


/*
Remove x from the tree. Nothing is done if x is not found.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x )
{
	remove( x, root );
}

/*
Internal method to remove from a subtree.
x is the item to remove.
t is the node that roots the tree.
Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>:: remove( const Comparable & x, BinaryNode<Comparable> * & t ) const
{
	if( t == NULL )
		return;   // Item not found; do nothing
	if( x.compare(t->element_f) < 0 )
		remove( x, t->left );
	else if( x.compare(t->element_f) > 0 )
		remove( x, t->right );

	else if( t->left != NULL && t->right != NULL ) // Two children
	{
		t->fullInfo = findMin( t->right )->fullInfo;
		t->element = findMin( t->right )->element;
		t->element_f = findMin( t->right )->element_f;

		remove( t->element_f, t->right );
	}
	else // one or no children
	{
		BinaryNode<Comparable> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}
}           

//Make the tree logically empty.
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
	makeEmpty( root );
}

// logical control
template <class Comparable>
bool BinarySearchTree<Comparable>:: isEmpty( ) const
{
	return root == nullptr;
}

//Internal method to make subtree empty.
template <class Comparable>
void BinarySearchTree<Comparable>:: makeEmpty( BinaryNode<Comparable> * & t ) const
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
void BinarySearchTree<Comparable>::inOrderPrintTree(ofstream& outFile ) const
{
	if( isEmpty( ) )
		return;
	else
		inOrderPrintTree( root , outFile);
}

//Internal method to inOrder
template <class Comparable>
void BinarySearchTree<Comparable>::inOrderPrintTree( BinaryNode<Comparable> * t, ofstream& outFile ) const
{
	if ( t != NULL )
	{
		inOrderPrintTree( t->left , outFile);
		outFile << t->fullInfo << endl;
		inOrderPrintTree( t->right , outFile );
	}
}

template <class Comparable>
void BinarySearchTree<Comparable>::drawTree(ofstream& outFile) {
	drawTree(root,outFile,true,"");
}

template <class Comparable>
void BinarySearchTree<Comparable>::drawTree(BinaryNode<Comparable> * t, ofstream& outFile, bool isRight, const string& space) {
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

//Print the tree contents in sorted order.
template <class Comparable>
void BinarySearchTree<Comparable>::preOrderPrintTree( ofstream& outFile ) const
{
	if( isEmpty( ) )
		return;
	else
		preOrderPrintTree( root , outFile );
}

//Internal method to print preOrder
template <class Comparable>
void BinarySearchTree<Comparable>::preOrderPrintTree( BinaryNode<Comparable> * t , ofstream& outFile ) const
{
	if ( t != NULL )
	{
		outFile << t->fullInfo << endl;
		preOrderPrintTree( t->left , outFile);
		preOrderPrintTree( t->right , outFile );
	}
}

#endif
