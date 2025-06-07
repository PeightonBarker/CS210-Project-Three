//Peighton Barker CS210 7-3 Project Three

#include <iostream>
#include <fstream> //Include input and output file stream
#include <string> //Include strings
#include <vector> //Include vectors
#include <map> //Include maps
using namespace std;

//Create class Groceries with public and private data members
class Groceries {
public:
	string name;
	int frequency;
	Groceries(string name, int frequency) : name(name), frequency(frequency) {}; //Constructor

private:
	string inputFileName;
	string outputFileName;
};

//Function to print frequency of the user entered item
void userItemPurchased(map<string, int> frequencies, string itemSearch) {
	int wordFrequency = 0;
	string numOfTimes;
	//Gets frequency of user entered item
	if (frequencies.count(itemSearch)) {
		wordFrequency = frequencies[itemSearch];
	}
	//Determine if "time" or "times" should be used
	if (wordFrequency == 1) {
	    numOfTimes = "time";
	}
	else {
	    numOfTimes = "times";
	}
	//Prints number of times item appeared
	cout << itemSearch << " appeared " << wordFrequency << " " << numOfTimes << endl;
}

//Function to print frequency of all items purchased in numeric value
int frequencyAllItems(map<string, int> frequencies) {
	ofstream outFS;
	//Prints name of all items and associated frequencies
	for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
	//Opens output file frequency.dat to write to
	outFS.open("frequency.dat");
	//Checks if frequency.dat file opened
	if (!outFS.is_open()) {
		cout << "Could not open frequency.dat" << endl;
		return 1;
	}
	else {
		cout << "OUTPUT OPEN!";
	}
	//Prints name of all items and associated frequencies to output file
	for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
		outFS << it->first << " " << it->second << endl;
	}
	//Closes output file
	outFS.close();
}

//Function to print frequency of all items purchased using histogram
void frequencyAllItemsHistogram(map<string, int> frequencies) {
	int i; //Create variable i
	//Prints name of all items and associated frequencies in "*"
	for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
		cout << it->first << " ";
		for (i = 0; i < it->second; i++) {
			cout << "*";
		}
		cout << endl;
	}
}

//Function to print menu options for user to choose and then calls appropriate function depending on input, continues until user enters 4
void mainMenu(map<string, int> frequencies) {
	int userMenuChoice = 0;
	string itemSearch;
	while (userMenuChoice != 4) {
	cout << "                    Main Menu" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "1. See frequency of user entered item purchased" << endl;
	cout << "2. See numeric frequency of all items purchased" << endl;
	cout << "3. See histogram frequency of all items purchased" << endl;
	cout << "4. Exit program" << endl;
	cout << endl;
	//Prompt user to pick and enter an option from the menu
	cout << "Pick an option from above: " << endl;
	cin >> userMenuChoice;
	switch (userMenuChoice) {
	case 1:
		//Prompt user to input word, return number of times it appears
		cout << "Enter the item you wish to see: ";
		cin >> itemSearch;
		userItemPurchased(frequencies, itemSearch); //Call userItemPurchased
	case 2:
		//Print the list with all items and number purchased using numeric value
		frequencyAllItems(frequencies); //Call frequencyAllItems
	case 3:
		//Print the list with all items and number purchased using *
		frequencyAllItemsHistogram(frequencies); //Call frequencyAllItemsHistogram
	case 4:
		cout << "Goodbye!"; //Program quits if user chooses 4
		break;
		}
	}
}

//Main function
int main() {
	ifstream inFS; //Create input file object
	ofstream outFS; //Create output file object
	string groceryItem; //Create string groceryItem
	map<string, int> frequencies; //Create map with string and int variables
	vector<Groceries> purchasedGroceryItems; //Create vector of class Groceries
	//Open input file CS210_Project_Three_Input_File.txt to read from
	inFS.open("CS210_Project_Three_Input_File.txt"); //DOES NOT WORK
	//Checks if CS210_Project_Three_Input_File.txt opened
	if (!inFS.is_open()) {
		cout << "Could not open CS210_Project_Three_Input_File.txt" << endl;
		return 1;
	}
	else {
		cout << "INPUT OPEN!";
	}
	//While input file has not reached the end, gets input and adds them to map
	while (!inFS.eof()) {
		inFS >> groceryItem;
		frequencies[groceryItem]++;
	}
	//Adds values from map to vector
	for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
		purchasedGroceryItems.push_back(Groceries(it->first, it->second));
	}
	//Closes input file
	inFS.close();
	//Calls mainMenu function
	mainMenu(frequencies);
	//Return statement
	return 0;

}