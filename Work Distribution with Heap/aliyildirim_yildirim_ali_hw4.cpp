#include <iostream>
#include <fstream>
#include <sstream>
#include "Heap.h"
//Ali Yýldýrým - 23737 - CS300 HW#4 - HEAP
using namespace std;

struct Job
{
	int JobId;
	int days;

	bool Job::Less (const Job & j){
		return ((this->JobId) < j.JobId);
	}

	bool Job::operator< (const Job & j)  { 
		return (Less(j));
	} 
	bool Job::operator< (int  j)  { 
		return (this->JobId < j);
	} 

	bool Job::operator> (const Job & j)  { 
		return !(Less(j));
	}
	bool Job::operator> (int j) {
		return (this->JobId > j);
	} 
	bool Job::operator==(int d)
	{
		return (JobId ==d);
	}
	const Job & Job::operator=(const Job & j)
	{
		this->days = j.days;
		this->JobId = j.JobId;
		return *this;
	}
	const Job & Job::operator-(int d)
	{
		this->days = this->days - d;
		return *this;
	}
};

struct Worker
{
	int WorkerId;
	Job job;
	bool Worker::Less (const Worker & j){
		return ((this-> job.days) < j.job.days);
	}

	bool Worker::operator< (const Worker & j)  { 
		return (Less(j));
	} 
	bool Worker::operator< (int  j)  { 
		return (this->job.days < j);
	} 

	bool Worker::operator> (const Worker & j)  { 
		return !(Less(j));
	}
	bool Worker::operator> (int j) {
		return (this->job.days > j);
	}
	const Worker & Worker::operator= (const Worker & j)
	{
		this->job = j.job;
		this->WorkerId = j.WorkerId;
		return *this;
	}
	bool Worker::operator==(int d)
	{
		return (job.days == d );
	}
    const Worker & Worker::operator-( int  d)
	{
		this->job.days = this->job.days - d;
		return *this;
	}
};

void FillQueue(string name, ifstream & input, BinaryHeap<Job> & heap, int &workerNum, int &JobNum)
	// to read input file
{
	ifstream file(name);
	if(!file.fail()){
		int i = 0;
		string s;
		while( getline(file,s))
		{
			if(i >= 2){
				if(s!="" && s.find("ï»¿") == string::npos){
					istringstream iss(s);
					int jobId, days;
					iss >> jobId >> days;
					Job x;
					x.JobId = jobId;
					x.days = days;
					heap.insert(x);
				}
				if(s.find("ï»¿") != string::npos){
					int index1= s.find("¿");
					int index2 = index1-2;
					s = s.substr(0,index2) + s.substr(index1+1);
					istringstream iss(s);
					int jobId, days;
					iss >> jobId >> days;
					Job x;
					x.JobId = jobId;
					x.days = days;
					heap.insert(x);
				}
			}
			if(i == 0)
			{
				istringstream iss(s);
				int num;
				iss >> num;
				workerNum = num;
			}
			if(i == 1)
			{
				istringstream iss(s);
				int num;
				iss >> num;
				JobNum = num;
			}
			i++;
		}
	}
}

void FinishWork(int&a, BinaryHeap<Worker> & heap, BinaryHeap<Worker> & hold)
	// is used for deleting the worker who finishes his work and worker is added to heap for free workers
{
	Job temp;
	temp.days = heap.value(1).job.days;
	a= temp.days;
	int n = heap.findNum(temp.days);
	Worker x;
	for(int k = 0; k <n; k++){
		x.WorkerId = heap.value(1).WorkerId;
		x.job.days = heap.value(1).WorkerId;
		hold.insert(x);
		heap.deleteMin();
	}
}

void giveIds(int workerNum, BinaryHeap<Worker> & hold)//gives an Id to worker
{
	for(int i = 1; i <=workerNum; i++)
	{
		Worker x;
		x.WorkerId = i;
		x.job.days= i;
		hold.insert(x);
	}
}

void fortemp(int day, int iteration, BinaryHeap<Worker> & temp, BinaryHeap<Worker> & hold, BinaryHeap<Job> & heap, ofstream & output)
	//this function is used for assigning jobs to workers who are free at that moment(according to Id's)
{
	int n = temp.Size();
	for(int i = 0; i <(iteration-n); i++)
	{
		Worker x;
		if(!heap.empty() && !hold.empty()){
			x.job.days = heap.value(1).days;
			x.job.JobId = heap.value(1).JobId;
			x.WorkerId = hold.value(1).WorkerId;
			heap.deleteMin();
			hold.deleteMin();
			temp.insert(x);
			output << "Job-"<<  x.job.JobId << "->Worker-" << x.WorkerId << " " << "(Day: " << day << ")" << endl;
		}
	}
}

int main()
{
	ifstream input;
	ofstream output;
	string FileName;
	cout << "Please enter a file name(in filename.txt format): ";
	cin >> FileName;
	BinaryHeap<Job> heap;
	
	int workerNum = 0;
	int JobNum = 0;
	string file = FileName + ".out" ;
	output.open(file);
	FillQueue(FileName, input, heap, workerNum, JobNum);

	BinaryHeap<Worker> temp;
	BinaryHeap<Worker> hold;

	int iteration;
	if(heap.Size() < workerNum){
		iteration = JobNum;
			giveIds(JobNum, hold);
	}
	else{
		iteration = workerNum;
			giveIds(workerNum,hold);
	}

	int day = 0;
	for(int j = 0; j < (iteration); j++){
		Job X;
		X = heap.deleteMin();
		Worker Y;
		Y.job = X;
		Y.WorkerId = hold.value(1).WorkerId;
		hold.deleteMin();
		temp.insert(Y);
		output << "Job-"<<  X.JobId << "->Worker-" << Y.WorkerId << " " << "(Day: " << day << ")" << endl;
	}

	int n;
	do 
	{
		n = 0;
		FinishWork(n, temp, hold);
		if(!temp.empty())
		{
			temp.decrease(n);
		}
		day += n;
		fortemp(day, iteration, temp, hold, heap, output);
	}while(!heap.empty());

	while(!temp.empty())
	{
		FinishWork(n, temp, hold);
		if(!temp.empty())
		{
			temp.decrease(n);
		}
		day += n;
	}

	output << "All jobs are completed in " << day << " days." << endl;
	return 0;
}