// Parallel Turing Machine Simulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream> // to read from file
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <sstream> // for stringstream object - for concatenation of multiple strings
#include <thread>
using namespace std;


class TuringMachine {

	public:
		vector< vector<string> >code;
		vector<string> tape;
		vector<string> headSymbol;
		int startPosition;
		int rows;
		string *head;
		string *currentCommand;

		bool finished = false;

	void startTuring(string name) {

		//char filename[20];
		string filename = name;
		ifstream file;
		cout << "Enter filename:\n";
		//cin.getline(filename, 20);
		file.open(filename);

		if (!file.is_open()) { // exits if file doesn't open (basically if file doesn't exist)
			exit(EXIT_FAILURE);
		}


		string tempTape;
		file >> startPosition;
		//cout << "\nStarting position: " << startPosition << "\n";
		file >> tempTape;

		cout << "\nTape: ";
		for (int i = 0; i < tempTape.size(); ++i) {
			tape.push_back(" 0"); // what is passed in here doesn't matter
			headSymbol.push_back(" ");
			tape[i] = tempTape[i];
			cout << tape[i];
		}
		headSymbol[startPosition] = "^";
		cout << "\n";


		// determines number of rows necessary according to number of characters
		int characterNum = 0;
		char character;
		while (file >> character) {
			++characterNum;
		}
		rows = characterNum / 5;

		//cout << "\nNum of characters in code: " << characterNum << endl;
		//cout << "\nNum of rows: " << rows << endl;


		// necessary because ifstream file has already gone through all the characters in the .txt file; need to do it all over to transfer characters into vector
		file.close();
		file.open(filename);

		file >> startPosition;
		file >> tempTape;


		// transfering code from .txt file to vector code[rows][5];
		while (!file.eof()) {
			for (int i = 0; i < rows; ++i) {
				vector<string>temp;
				string tempArr[5];
				for (int j = 0; j < 5; ++j) {
					file >> tempArr[j];
					temp.push_back(tempArr[j]);
				}
				code.push_back(temp);
			}

		}

		// printing code
		/*
		cout << "\nCode from file:\n";
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < 5; ++j) {
				cout << code[i][j] << " ";
			}
			cout << "\n";
		}
		*/
		cout << "\n";

		
		head = &tape[startPosition];
		currentCommand = &code[0][0];
	}

	void turing() {

		// TURING PART
		if (finished) {
			cout << "\n\nTAPE ENDED" << endl;
			return;
		}
			// current symbol
		++currentCommand;
		if (*currentCommand != *head) {
			cout << "\nError! Current symbol in tape & current symbol in code do not match!" << endl;
			finished = true;
			return;
		}

		// new symbol
		++currentCommand;
		*head = *currentCommand; // symbol which head points to in tape changes to symbol which currentCommand points to ("new symbol")

		// printing tape

		stringstream SS;
		string concatTape;
		for (int i = 0; i < tape.size(); ++i) {
			SS << tape[i]; // concatenates separate strings of tape into one
			concatTape = SS.str(); // puts concatenated string into concatTape
		}
		stringstream SS2;
		string concatHeadSymbol;
		for (int i = 0; i < tape.size(); ++i) {
			SS2 << headSymbol[i]; // concatenates separate strings of tape into one
			concatHeadSymbol = SS2.str(); // puts concatenated string into concatHeadSymbol
		}


		//system("CLS");
		cout << concatTape << endl;
		cout << concatHeadSymbol << endl;


		// direction
		++currentCommand;
		if (*currentCommand == "R") {
			++head;
			headSymbol[startPosition] = " ";
			++startPosition;
			headSymbol[startPosition] = "^";
		}
		else if (*currentCommand == "L") {
			--head;
			headSymbol[startPosition] = " ";
			--startPosition;
			headSymbol[startPosition] = "^";

		}
		else if (*currentCommand == "*" || *currentCommand == "x" || *currentCommand == "X") {
		}


		// changing state 
		++currentCommand;
		for (int k = 0; k < rows; ++k) {
			if (code[k][0] == *currentCommand) { // *currentCommand currently points to the "next state" instruction; code[k][0] is the "current symbol" column
				string *temp;
				temp = &code[k][0];

				++temp; // checks if symbol in "current symbol" instruction matches the current symbol in the tempTape (because there may be several states by the same name)
				if (*head == *temp) {
					currentCommand = &code[k][0];
					break;
				}
			}
		}


	}
};




int main()
{
	TuringMachine instance1;
	instance1.startTuring("1.txt");
	TuringMachine instance2;
	instance2.startTuring("2.txt");
	TuringMachine instance3;
	instance3.startTuring("3.txt");
	TuringMachine instance4;
	instance4.startTuring("4.txt");

	while (!instance1.finished || !instance2.finished || !instance3.finished) {
		instance1.turing();
		cout << "\n\n";
		instance2.turing();
		cout << "\n\n";
		instance3.turing();
		cout << "\n\n";
		instance4.turing();
		cout << "\n\n";

		system("CLS");
	}

	return 0;
}




// Attempt with threads
/*
	thread t1(turing, "2.txt");
	cout << "\n\n\n";
	thread t2(turing, "3.txt");
	cout << "\n\n\n";
	t1.join();
	t2.join();
	*/
