#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include <vector>
#include "BST.h"
#include "AVL.h"

using namespace std;

template <typename Tree>
void SearchAContact(Tree & tree,const string& partial, vector<string>& results) {
	tree.findPartial(partial,results);
	for (int i = 0; i < results.size(); i++)
	{
		cout << results[i] << endl;
	}
	cout << endl;
	results.clear();
}


template <typename Tree>
void PreOrderPrintToFile(Tree & tree,const string& info) {
	string filename = info ;
	ofstream out(filename);
	tree.preOrderPrintTree(out);
	out.close();
}

template <typename Tree>
void InOrderPrintToFile(Tree & tree,const string& info) {
	string filename = info ;
	ofstream out(filename);
	tree.inOrderPrintTree(out);
	out.close();
}

template <typename Tree>
void DrawTreeToFile(Tree& tree, const string& info) {
	// drawing tree to file
	string filename = info;
	ofstream out(filename);
	tree.drawTree(out); 
	out.close();
}

template <typename Tree>
void loadfromfile(const string& filename, Tree& tree) {
	ifstream inputfile(filename);
	if (!inputfile) {
		throw runtime_error("failed to open input file"); 
	}

	string line;
	while (getline(inputfile, line)) {
		if (!line.empty()) {
			istringstream iss(line);
			string word1, word2;
			iss >> word1 >> word2;
			const string x = word1 + " " + word2;
			tree.insert(x,line);
		}
	}
	inputfile.close();
}

template <typename Tree>
void AddContact(Tree & tree, const string& newName ,const string& info) {
	tree.insert(newName,info);
}
template <typename Tree>
void DeleteContact(Tree & tree, const string& info) {
	tree.remove(info);
}

// free function to lower the string for partial searching
string to_upper(string str)
{
	for(int i=0;str[i]!='\0';i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')   //checking for lowercase characters
			str[i] = str[i] - 32;        //converting lowercase to uppercase
	}
	return str;
}

int main() {

	const string ITEM_NOT_FOUND = "Item not found";

	string filename;
	cout << "Please enter the contact file name: ";
	cin >> filename;

	// Load the phonebook into a BST
	BinarySearchTree<string> bst(ITEM_NOT_FOUND);
	cout << "Loading the phonebook into a BST." <<endl;
	auto start = chrono::high_resolution_clock::now();
	loadfromfile(filename, bst);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << "Phonebook creation in BST took " << duration.count() << " milliseconds. . ." << endl;

	// Check if the BST is balanced
	cout << "The tree is " << (bst.isBalanced() ? "balanced" : "not balanced") << endl;
	bst.getHeight();

	// Load the phonebook into an AVL tree
	AvlTree<string> avl(ITEM_NOT_FOUND);
	cout << "loading the phonebook into an AVL" << endl;
	start = chrono::high_resolution_clock::now();
	loadfromfile(filename, avl);
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << "Phonebook creation in AVL took " << duration.count() << " milliseconds. . ." << endl;

	// Check if the AVL tree is balanced
	cout << "The tree is " << (avl.isBalanced() ? "balanced" : "not balanced") << endl;
	avl.getHeight();
	int choice;

	do {
		cout << "\nChoose which action to perform from 1 to 6:\n"
			<< "1 - Search a phonebook contact\n"
			<< "2 - Adding a phonebook contact\n"
			<< "3 - Deleting a phonebook contact\n"
			<< "4 - Print the phonebook to a file(inorder)\n"
			<< "    Print the phonebook to a file(preorder)\n"
			<< "5 - Draw the phonebook as a Tree to a file\n"
			<< "6 - Press 6 to exit\n";
		cin >> choice;
		cout << endl;

		string partial = "";
		string info ="";
		string newName="", newNumber="",newCity="";
		string delName = "";
		vector<string>  results;

		if(choice == 1){ // Search a contact
			cout << "Search for a contact: ";
			cin.ignore(); // clear input buffer
			getline(cin, partial); 
			cout << endl;
			cout << "Searching an item in the phonebook (BST) . . ."<< endl;
			cout << endl;
			cout << "Phonebook: Searching for: ("<<to_upper(partial)<<")\n"
				<< "====================================" << endl;
			auto start_C = chrono::high_resolution_clock::now();
			SearchAContact(bst,to_upper(partial), results);
			auto stop_C = chrono::high_resolution_clock::now();
			auto duration_B = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);

			cout << "Searching an item in the phonebook (AVL) . . ."<< endl;
			cout << endl;
			cout << "Phonebook: Searching for: ("<<to_upper(partial)<<")\n"
				<< "====================================" << endl;
			start_C = chrono::high_resolution_clock::now();
			SearchAContact(avl,to_upper(partial), results);
			stop_C = chrono::high_resolution_clock::now();
			auto duration_A = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);

			cout <<"The search in BST took "<< duration_B.count() <<" nanoseconds. . .\n"	
				"The search in AVL took "<< duration_A.count() <<" nanoseconds. . .\n"<< endl;
		}
		else if(choice == 2){ // Add a contact
			cout << "Enter the information of the contact to be added:\n";
			cout << "Name: ";
			cin.ignore(); // clear input buffer
			getline(cin, newName); 
			cout << endl;
			cout << "Tel: ";
			cin >> newNumber; 
			cout << endl; 
			cout << "City: ";
			cin >> newCity; cout << endl; 
			info = newName + " " +  newNumber + " " +  newCity;
			if(avl.find(to_upper(newName))==ITEM_NOT_FOUND){
				cout << "Adding an item to the phonebook BST . . .\n"
					<< "====================================" << endl;
				auto start_C = chrono::high_resolution_clock::now();
				AddContact(bst,newName,info);
				auto stop_C = chrono::high_resolution_clock::now();
				auto duration_B = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);
				cout <<"Contact has been added successfully to the BST\n"<< endl;

				cout << "Adding an item to the phonebook AVL . . .\n"
					<< "====================================" << endl;
				start_C = chrono::high_resolution_clock::now();
				AddContact(avl,newName,info);
				stop_C = chrono::high_resolution_clock::now();
				auto duration_A = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);
				cout <<"Contact has been added successfully to the AVL\n"<< endl;

				cout <<"Adding a contact to the Binary Tree took "<< duration_B.count() <<" nanoseconds. . .\n"	
					"Adding a contact to the AVL Tree took "<< duration_A.count() <<" nanoseconds. . .\n"<< endl;
			}
			else 
				cout <<"The given contact "<< newName <<" already exists in the database."<< endl;
		}


		else if(choice == 3){ // Delete a contact
			cout <<"Deleting an item from the phonebook . . ." << endl;
			cout << "Enter the fullname of the contact to be deleted: ";
			cin.ignore(); // clear input buffer
			getline(cin, delName); 
			cout << endl;
			if(avl.find(to_upper(delName))!=ITEM_NOT_FOUND){
				auto start_C = chrono::high_resolution_clock::now();
				DeleteContact(bst,to_upper(delName));
				auto stop_C = chrono::high_resolution_clock::now();
				auto duration_B = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);
				start_C = chrono::high_resolution_clock::now();
				DeleteContact(avl,to_upper(delName));
				stop_C = chrono::high_resolution_clock::now();
				auto duration_A = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);
				cout << "Deleted succcessfully. . ." << endl;
				cout << endl;
				cout << "Deletion from the Binary Tree took " << duration_B.count() << " nanoseconds. . ." << endl;
				cout << "Deletion from the AVL Tree took " << duration_A.count() << " nanoseconds. . ." << endl;
			}
			else
				cout <<"The given contact "<< delName <<" does not exists in the database."<< endl;
		}
		else if(choice == 4){ // Print the phonebook to a file (inorder and preorder)
			auto start_C = chrono::high_resolution_clock::now();
			InOrderPrintToFile( bst, "phonebookInOrderBST.txt");
			auto stop_C = chrono::high_resolution_clock::now();
			auto duration_I_BST = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);

			start_C = chrono::high_resolution_clock::now();
			InOrderPrintToFile( avl, "phonebookInOrderAVL.txt");
			stop_C = chrono::high_resolution_clock::now();
			auto duration_I_AVL = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);

			start_C = chrono::high_resolution_clock::now();
			PreOrderPrintToFile( bst, "phonebookPreOrderBST.txt");
			stop_C = chrono::high_resolution_clock::now();
			auto duration_P_BST = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);

			start_C = chrono::high_resolution_clock::now();
			PreOrderPrintToFile( avl, "phonebookPreOrderAVL.txt");
			stop_C = chrono::high_resolution_clock::now();
			auto duration_P_AVL = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);

			cout << "Printing in order to file from the Binary Tree took "<< duration_I_BST.count() <<" nanoseconds. . ." << endl;
			cout << "Printing in order to file from AVL Tree took "<< duration_I_AVL.count() <<" nanoseconds. . ." << endl;
			cout << "Printing pre order to file from the Binary Tree took "<< duration_P_BST.count() <<" nanoseconds. . ." << endl;			
			cout << "Printing pre order to file from AVL Tree took "<< duration_P_AVL.count() <<" nanoseconds. . ." << endl;
		}
		else if(choice == 5){ // Print the phonebook to a file (preorder)
			auto start_C = chrono::high_resolution_clock::now();
			DrawTreeToFile(bst,"phonebookTreeBST.txt");
			auto stop_C = chrono::high_resolution_clock::now();
			auto duration_BST = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);

			start_C = chrono::high_resolution_clock::now();
			DrawTreeToFile(avl,"phonebookTreeAVL.txt");
			stop_C = chrono::high_resolution_clock::now();
			auto duration_AVL = chrono::duration_cast<chrono::nanoseconds>(stop_C - start_C);

			cout << "Drawing tree to file from the Binary Tree took "<< duration_BST.count() <<" nanoseconds. . ."<<endl;
			cout << "Drawing tree to file from the AVL Tree took "<< duration_AVL.count() <<" nanoseconds. . ."<<endl;
		}
		else if(choice == 6)
			break;
		else{
			// Invalid choice
			cout << "Invalid choice. Please try again.\n";
		}

	} while(choice!=6);

	cout << "Exiting..." << endl;

	return 0;
}