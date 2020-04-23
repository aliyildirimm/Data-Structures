#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "binaryst.h"
//Ali Yýldýrým 23737 CS 300 HW2
using namespace std;

string toLower(string s) //this function is done to convert the characters in lower case eg. From A to a.
{
	int size = s.length() - 1;
	for(int i = 0; i <= size; i++){
		if(s.at(i) >= 'A' && s.at(i) <= 'Z'){
			s.at(i) = s.at(i) + 32;
		}
	}
	return s;
}

void FillTree(ifstream & input,  BinarySearchTree<string> &tree) // I read the file
																// then push the words to tree
																// after some operations
{
	string name = "ali.txt";
	ifstream file(name);
	if(!file.fail()){
		for(string s; getline(file,s);)
		{
			if(s!="" && s.find("ï»¿") == string::npos){
				istringstream iss(s);
				string word1, word2, translate;
				iss >> word1 >> word2;
				translate = word2;
				while(iss >> word2){
					translate = translate + " "+ word2;
				}
				word1 = toLower(word1);
				translate = toLower(translate);
				tree.insert(word1, translate);
			}
			if(s.find("ï»¿") != string::npos){
				int index1= s.find("¿");
				int index2 = index1-2;
				s = s.substr(0,index2) + s.substr(index1+1);
				istringstream iss(s);
				string word1, word2, translate;
				iss >> word1 >> word2;
				translate = word2;
				while(iss >> word2){
					translate = translate + " "+ word2;
				}
				word1 = toLower(word1);
				translate = toLower(translate);
				tree.insert(word1, translate);
			}
		}
	}
}

void FuncFor1(const BinarySearchTree<string> &tree) //this function helps to find the Eng word and its translation
{
	string word;
	cout << "Enter queried word: ";
	cin >> word;
	word = toLower(word);
	if(tree.find(word) == ""){
		cout << "The word does not exist." << endl;
	}
	else{
		cout << word << " ---> ";
		cout << tree.Translate(word) << endl;
	}
}

bool Exist(string edit, string translate, const BinarySearchTree<string> &tree)
	// the aim of this function is that when I am adding new translations
	// I need to check if the translation that I am trying to enter is exist or not
	// so this is the aim of this function which is used in adding new translation of a word
{

	string str = tree.Translate(edit);
	vector<string> vec;
	while(str.find(",") != string::npos){
		int index = str.find(",");
		string hold = str.substr(0,index);
		vec.push_back(hold);
		str = str.substr(index+2);
	}
	vec.push_back(str);
	int size = vec.size();

	for(int i = 0; i < size ; i++)
	{
		if(vec[i] == translate){
			return false;
		}
	}

	return true;
}

void FuncFor2(BinarySearchTree<string> &tree)//editing translations
{
	string edit;
	cout << "Which word do you want to edit: " ;
	cin >> edit;
	edit = toLower(edit);
	if(tree.find(edit) == ""){
		cout << "The word does not exist." << endl;
	}
	else{
		string word;
		cout << "Enter the new translation: ";
		cin >> word;
		word = toLower(word);
		if(Exist(edit,word,tree) == false)
			cout << word << " is already in the translation list of " << edit << endl;
		else
			tree.Update(edit, word);
	}
}

void FuncFor3(BinarySearchTree<string> &tree)// adding new word
{
	string newWord;
	cout << "Enter New Word: " ;
	cin >> newWord;
	newWord = toLower(newWord);
	if(tree.find(newWord) != ""){
		cout << "Word already exists, if you want to add new translation please use command 2." << endl;
	}
	else{
		string translate;
		cout << "Enter Translations: " ;
		cin >> translate;
		translate = toLower(translate);
		tree.insert(newWord,translate);
	}
}

int main()
{ 
	ifstream input;
	const string notFound = "";
	BinarySearchTree<string> myTree(notFound);
	FillTree(input, myTree);
	myTree.printTree();
	cout <<"***Help*** \nQuery: 1 \nAdd new translation: 2 \nAdd new word: 3 \nExit: 0" << endl;
	
	string command;

	do{
		cout << "Enter a command: ";
		cin >> command;

		if(command == "1"){
			FuncFor1(myTree);
		}
		else if(command == "2"){
			FuncFor2(myTree);
		}
		else if(command == "3"){
			FuncFor3(myTree);
		}
	}while(command != "0");

	cout << "Bye..." << endl;
	return 0;
}