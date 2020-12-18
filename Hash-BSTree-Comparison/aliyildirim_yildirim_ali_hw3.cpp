#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>
#include "BstAndHash.h"

// Ali Yýldýrým 23737 CS300 HW3
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

void FillTreeAndHashTable(ifstream & input,  BinarySearchTree<string> &tree, 
						  HashTable<string> &obj) // I read the file
												// then push the words to tree
												// after some operations
{
	string name = "dict.txt";
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
				obj.insert(word1,translate);
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
				obj.insert(word1,translate);
			}
		}
	}
}

vector<string> FillOutputForTree(ifstream & input2, ofstream & out, BinarySearchTree<string> &tree)
{// in this func. I read txt file and write them to output file and also to a vector for binary search tree
	string name = "query1.txt";
	ifstream file(name);
	out.open("outputForTree.txt");
	vector<string> a;
	if(!file.fail()){
		for(string s; getline(file,s);)
		{
			if(s!="" && s.find("ï»¿") == string::npos){
				istringstream iss(s);
				string word1, word2;
				iss >> word1;
				word1 = toLower(word1);
				word2 = tree.find(word1);
				a.push_back(word2);
				out << word1 << "	" << word2 << endl;
			}
			if(s.find("ï»¿") != string::npos){
				int index1= s.find("¿");
				int index2 = index1-2;
				s = s.substr(0,index2) + s.substr(index1+1);
				istringstream iss(s);
				string word1, word2;
				iss >> word1;
				word1 = toLower(word1);
				word2 = tree.find(word1);
				a.push_back(word2);
				out << word1 << "	" << word2 << endl;
			}
		}
	}
	return a;
}

vector<string> FillOutputForHash(ifstream & input2, ofstream & out2, HashTable<string> &obj)
{ // in this func. I read txt file and write them to output file and also to a vector for hash table
	string name = "query1.txt";
	ifstream file(name);
	out2.open("outputForHash.txt");
	vector<string> a;
	if(!file.fail()){
		for(string s; getline(file,s);)
		{
			if(s!="" && s.find("ï»¿") == string::npos){
				istringstream iss(s);
				string word1, word2;
				iss >> word1;
				word1 = toLower(word1);
				word2 = obj.find(word1);
				a.push_back(word1);
				out2 << word1 << "	" << word2 << endl;
			}
			if(s.find("ï»¿") != string::npos){
				int index1= s.find("¿");
				int index2 = index1-2;
				s = s.substr(0,index2) + s.substr(index1+1);
				istringstream iss(s);
				string word1, word2;
				iss >> word1;
				word1 = toLower(word1);
				word2 = obj.find(word1);
				a.push_back(word1);
				out2 << word1 << "	" << word2 << endl;
			}
		}
	}
	return a;
}

void FindTree(vector<string> a,BinarySearchTree<string> &tree) //this func. is made for seeing the pace of tree
{
	int len = a.size();
	for (int i = 0; i <len; i++)
		tree.find(a[i]);
}

void FindHash(vector<string> a, HashTable<string> &obj)//this func. is made for seeing the pace of hash table
{
	int len = a.size();
	for (int i = 0; i <len; i++)
		obj.find(a[i]);
}

int main()
{
	ifstream input;
	const string notFound = "";
	BinarySearchTree<string> myTree(notFound);
	HashTable<string> myHash(notFound);

	cout << "Building a binary tree for dict.txt..." << endl;
	cout << "Building a hash table for dict.txt..." << endl;

	FillTreeAndHashTable(input, myTree, myHash);	

	cout << "After preprocessing, the unique word count is " << myHash.Size() << ". Current load ratio is " << 
		(double)((double)myHash.Size()/(double)myHash.TableSize())<< "." <<endl;

	ifstream input2;
	ofstream out;
	ofstream out2;
	vector<string> query1 ,query2; // words will be put on this vectors for find processes
	
	query1 = FillOutputForTree(input2, out, myTree); // outputs are formed 
	query2 = FillOutputForHash(input2, out2, myHash);

	
	auto start = std::chrono::high_resolution_clock::now();
	for(int i= 0; i <64; i++) // to see times well I did it 64 times
		FindTree(query1, myTree);
	auto time = (std::chrono::high_resolution_clock::now() - start).count();

	auto start2 = std::chrono::high_resolution_clock::now();
	for(int i= 0; i <64; i++)
		FindHash(query2, myHash);
	auto time2 = (std::chrono::high_resolution_clock::now() - start2).count();

	cout << "Running queries in query1.txt..." << endl << endl;
	cout <<"***********************************************" << endl;
	cout <<"Benchmark results for Binary Search Tree (BST):\n***********************************************"<<endl;

	cout << "+ Elapsed time for N=64: " << (double)time << "ns." << endl;
	cout << "+ Average query time: " << (double)((double)time/((double)query1.size()*(double)64)) << "ns." << endl << endl;

	cout <<"***********************************************" << endl;
	cout <<"Benchmark results for Hash Table:\n***********************************************"<<endl;

	cout << "+ Elapsed time for N=64: " << (double)time2 << "ns." << endl;
	cout << "+ Average query time: " << (double)((double)time2/((double)query1.size()*(double)64)) << "ns." << endl << endl;
	double Ratio = double(time/query1.size()) / double (time2/query2.size());
	cout << "+ Speed up ratios for N=64: " << Ratio << endl << endl;


	cout << "Time measurements in ns (N, 4096N):\n*****************************" << endl << endl;
	cout << "BST" << endl;
	cout << "N" << "		time" << endl; 

	for(int j = 1; j<=4096; j = 2*j){
		auto start = std::chrono::high_resolution_clock::now();
		for(int i= 0; i <j; i++)
			FindTree(query1, myTree);
		auto time = (std::chrono::high_resolution_clock::now() - start).count();
		cout << j << "		" << time << endl;
	}

	cout << endl;
	cout << "HT" << endl;
	for(int j = 1; j<=4096; j = 2*j){
		auto start = std::chrono::high_resolution_clock::now();
		for(int i= 0; i <j; i++)
			FindHash(query2, myHash);
		auto time = (std::chrono::high_resolution_clock::now() - start).count();
		cout << j << "		" << time << endl;
	}
	
	return 0;
}