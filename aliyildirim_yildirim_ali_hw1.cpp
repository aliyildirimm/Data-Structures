#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

void FillStack(Stack<string> & obj, string input) //this function allows us to fillthe stack
{
	int size = input.length() - 1;
	for(int i = size; i >= 0; i--){
		obj.push(input.substr(i,1));
		}
}
void One(Stack<string> & copy ,Stack<string> & obj) // I created a copy stack. It fills myorginal stack when character is 1
{
	while(!copy.isEmpty())
		obj.push(copy.topAndPop());
}
void Two(Stack<string> & copy)// it removes the character on the left
{
	if(!copy.isEmpty())
		copy.pop();
}
void Three(Stack<string> & copy, Stack<string> & hold)//it allows us to move cursor to left
{
	if(!copy.isEmpty())
	hold.push(copy.topAndPop());
}
void Four(Stack<string> & copy, Stack<string> & hold)//it allows us to move cursor to right
{
	if(!hold.isEmpty()){
		copy.push(hold.topAndPop());
	}
}
void Five(Stack<string> & copy)//We flip the input 
{
	Stack<string> take = copy;
	copy.makeEmpty();
	while(!take.isEmpty())
		copy.push(take.topAndPop());
}
void Six(Stack<string> & copy, string del) //we search for a character first then delete them
{
	Stack<string> take = copy;
	Stack<string> temp;
	copy.makeEmpty();
	while(!take.isEmpty()){
		string search = take.top();
		if(search == del)
			take.pop();
		else
			temp.push(take.topAndPop());
	}
	while(!temp.isEmpty())
		copy.push(temp.topAndPop());
}
void FillReverse(Stack<string> & obj) //this is for the creating a copy stack
{
	Stack<string> copy, hold;
	while(!obj.isEmpty()){
		string temp = obj.topAndPop();
		if(temp != "1" && temp != "2" && temp != "3" && temp != "4" && temp != "5" && temp != "6"){
			copy.push(temp);
		}
		else
		{
			if(temp == "1"){
				One(hold, copy);
				One(copy, obj);
				break;
			}
			else if(temp == "2"){
				Two(copy);
			}
			else if(temp == "3"){
				Three(copy, hold);
			}
			else if(temp == "4"){
				Four(copy,hold);
			}
			else if(temp == "5"){
				Five(copy);
			}
			else if(temp =="6"){
				string del;
				if(!obj.isEmpty())
					del = obj.topAndPop();

				
				Six(copy,del);
			}
		}
	}
}
int main()
{
	cout << "Press ctrl + z to exit " << endl;
	cout << "Please enter input: " <<  endl;
	string input;
	cin >> input;

	do{
	if(input.find("1") == string::npos)
		cout << "Invalid Input" << endl;

	else if(input.find("7") != string::npos || input.find("8") != string::npos  ||input.find("9") != string::npos  || input.find("0") != string::npos )
		cout << "Invalid Input" << endl;

	else if(input.find("60") != string::npos  ||input.find("61") != string::npos  || input.find("62") != string::npos || 
		input.find("63") != string::npos  || input.find("64") != string::npos  ||input.find("65") != string::npos  ||
		input.find("66")  != string::npos || input.find("67") != string::npos  ||input.find("68") != string::npos  ||
		input.find("69") != string::npos ){

		cout << "Invalid Input" << endl;
	}

	else{
		int index = input.find("1");
		input = input.substr(0,index+1);
		Stack<string> myInput;
		FillStack(myInput, input);
		FillReverse(myInput);

		if(myInput.isEmpty())
			cout << "Stack is empty" << endl;
		while(!myInput.isEmpty()){
			string c= myInput.topAndPop();
			cout << c; 
		}
		cout << endl << endl;
	}
	cout << "Please enter input: " <<  endl;

	}while(cin>>input);

	return 0;
}