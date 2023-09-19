# Phonebook_Management_Program

## Main aim of program is to compare the time performance of template-based AVL and BST trees.

This program implements a phonebook management system using Binary Search Tree (BST) and AVL Tree data structures. It provides various functionalities for searching, adding, and deleting contacts, as well as printing and visualizing the phonebook. The program is template-based to allow flexibility in contact information storage.

## Functionality
The program offers the following functionalities:

**Search Contact:** Search for a contact by entering a full name (e.g., "John Doe"). The program displays contacts matching the full name or starting with the entered partial word.

**Add Contact:** Add a new contact to both the BST and AVL trees. Contacts are compared alphabetically by full name (first name + last name). If the contact already exists, a warning message is displayed.

**Delete Contact:** Remove a contact from the phonebook by providing the full contact name (e.g., "Alice Smith").

**InOrder Print to File:** Print the phonebook in InOrder sorted order to a file named "phonebookInOrder.txt". The output contains full names, phone numbers, and cities.

**PreOrder Print to File:** Print the phonebook in PreOrder sorted order to a file named "phonebookPreOrder.txt". The output contains full names, phone numbers, and cities.

**Draw Tree to File:** Visualize both the BST and AVL trees and save them to separate files named "phonebookTreeBST.txt" and "phonebookTreeAVL.txt".

## Input Data
The program reads contact information from an input file (e.g., "PhoneBook-sample2.txt"). Each line of the input file represents a contact and includes first name, last name, phone number, and city information.

## Execution Flow
Here's how the program works:

**Load Input File:** The program reads contact information from the specified input file and creates BST and AVL trees with the data. It measures and displays the time taken for tree creation.

**Menu:** After loading the phonebook, the program displays a menu of functionalities for the user to choose from.

**Function Execution:** When a user selects a function (1 to 5), the program executes that function for both the BST and AVL trees. It measures and displays the execution time for each operation.

**Printing and Visualization:** When requested, the program prints the phonebook in InOrder and PreOrder sorted order to text files. It also visualizes both trees and saves them to separate files.

**Repeat or Exit:** After executing a function, the program allows the user to perform another operation or exit the program.

:warning:
This project was developed as a programming assignment and serves as an educational resource for working.
