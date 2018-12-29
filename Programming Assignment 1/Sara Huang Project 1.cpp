//Sara Huang
//ECE264: Programming Assignment 1
//This program manipulates stacks and queues.

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

template <class S>
class SimpleList
{
public:
	virtual void push (S &) = 0;
	virtual S * pop () = 0;
	string name;
	SimpleList(string &inname) {
		name = inname;
	}

private:
	struct Node //Creating Node Structure
	{
		S data;
		Node *link;
	};

protected:
	Node *head = NULL; //creating head pointer and equating it to NULL
	void insertStart(S &d); //function to insert a node at the start of the list
	void insertEnd(S &d); //function to insert at node at the end of the list
	S *deleteStart(); //function to remove a node from the start of the list
};

template <class S>
void SimpleList<S>::insertStart(S &d) //function to insert a node at the start of the list
	{
		Node *ptr = new Node();
		ptr->data = d;
		ptr->link = head;
		head = ptr;
	}

template <class S>
void SimpleList<S>::insertEnd(S &d) //function to insert at node at the end of the list
	{
		Node *ptr = new Node(); //creating new node
		ptr->data = d;
		ptr->link = NULL;
		if(head == NULL) //if list is empty
		{
			head = ptr;
		}
		else //if list is not empty
		{
			Node *temp = head;
			while (temp->link != NULL)
			{
				temp = temp->link; //traversing the list
			}
			temp->link = ptr;
		}
	}

template <class S>
S *SimpleList<S>::deleteStart() //function to remove a node from the start of the list
	{
		if (head == NULL) //if list is empty
			return NULL;
		else
		{
			Node *ptr = head;
			S *y = new S;
			*y = head->data;
			head = head->link;
			free(ptr);
			return y;
		}
	}

template <class S>
class Stack : public SimpleList<S>
{
public:
	Stack(string &stackname) : SimpleList<S>(stackname) {};
	void push(S &x) {
		SimpleList<S>::insertStart(x);
	}
	S *pop() {
		return SimpleList<S>::deleteStart();
	}
};

template <class S>
class Queue : public SimpleList<S>
{
public:
	Queue(string &queuename) : SimpleList<S>(queuename) {};
	void push(S &x) {
		SimpleList<S>::insertEnd(x);
	}
	S *pop() {
		return SimpleList<S>::deleteStart();
	}
};

template <class S>
SimpleList<S> * search(string &C, list<SimpleList<S> *> D, ofstream &out){ //function to search through lists
	for (class list<SimpleList<S> *>::iterator l = D.begin(); l != D.end() ; l++) {
		if ((*l)->name == C) {
			return *l;
		}
	}
	return NULL;
}

int main()
{
	ifstream input;
	string infile;
	cout<<"Enter name of input file: ";
	cin>>infile;
	input.open(infile);

	list<SimpleList<int> *> listSLi;
	list<SimpleList<double> *> listSLd;
	list<SimpleList<string> *> listSLs;

	ofstream output;
	string outfile;
	cout<<"Enter name of output file: ";
	cin>>outfile;
	output.open(outfile);

	string a, b, c;
	while (input >> a >> b){
		if (a == "create") {
			input >> c;
			output<<"PROCESSING COMMAND: "<< a << " " << b << " " << c << "\n";
			if (c == "stack"){
				if (b[0] == 'i')  {
					SimpleList<int> *pSLi = search(b,listSLi,output);
					if (pSLi != NULL) {
						output << "ERROR: This name already exists!\n";
					} else {
						pSLi = new Stack<int>(b);
						listSLi.push_front(pSLi);
					}
				}
				else if (b[0] == 'd') {
					SimpleList<double> *pSLd = search(b,listSLd,output);
					if (pSLd != NULL) {
						output << "ERROR: This name already exists!\n";
					} else {
						pSLd = new Stack<double>(b);
						listSLd.push_front(pSLd);
					}
				}
				else if (b[0] == 's') {
					SimpleList<string> *pSLs = search(b,listSLs,output);
					if (pSLs != NULL) {
						output << "ERROR: This name already exists!\n";
					} else {
						pSLs = new Stack<string>(b);
						listSLs.push_front(pSLs);
					}
				}
			}
			else if (c == "queue") {
				if (b[0] == 'i') {
					SimpleList<int> *pSLi = search(b,listSLi,output);
					if (pSLi != NULL) {
						output << "ERROR: This name already exists!\n";
					} else {
						pSLi = new Queue<int>(b);
						listSLi.push_front(pSLi);
					}
				}
				else if (b[0] == 'd') {
					SimpleList<double> *pSLd = search(b,listSLd,output);
					if (pSLd != NULL) {
						output << "ERROR: This name already exists!\n";
					}
					else {
						pSLd = new Queue<double>(b);
						listSLd.push_front(pSLd);
					}
				}
				else if (b[0] == 's') {
					SimpleList<string> *pSLs = search(b,listSLs,output);
					if (pSLs != NULL) {
						output << "ERROR: This name already exists!\n";
					} else {
						pSLs = new Queue<string>(b);
						listSLs.push_front(pSLs);
					}
				}
			}
		}	
		else if (a == "push"){
			input >> c;
			output<<"PROCESSING COMMAND: "<< a << " " << b << " " << c << "\n";
			if (b[0] == 'i') {
				int p = stoi(c,NULL,10);
				SimpleList<int> *pSLi;
				pSLi = search(b,listSLi,output);
				if (pSLi != NULL)
					pSLi->push(p);
				else 
					output << "ERROR: This name does not exist!\n";
			}
			else if (b[0] == 'd') {
				double p = stod(c,NULL);
				SimpleList<double> *pSLd;
				pSLd = search(b,listSLd,output);
				if (pSLd != NULL)
					pSLd->push(p);
				else
					output << "ERROR: This name does not exist!\n";	
			}
			else if (b[0] == 's') {
				SimpleList<string> *pSLs;
				pSLs = search(b,listSLs,output);
				if (pSLs != NULL)
					pSLs->push(c);
				else
				output << "ERROR: This name does not exist!\n";	
			}
		}
		else if (a == "pop"){
			output<<"PROCESSING COMMAND: "<< a << " " << b << "\n";
			if (b[0] == 'i') {
				SimpleList<int> *pSLi;
				pSLi = search(b,listSLi,output);
				if (pSLi != NULL) {
					int *p = pSLi->pop();
					if (p != NULL)
						output << "Value popped: " << *p << "\n";
					else
						output<<"ERROR: This list is empty!\n";
				}
				else 
					output << "ERROR: This name does not exist!\n";
			}
			else if (b[0] == 'd') {
				SimpleList<double> *pSLd;
				pSLd = search(b,listSLd,output);
				if (pSLd != NULL) {
					double *p = pSLd->pop();
					if (p != NULL)
						output << "Value popped: " << *p << "\n";
					else
						output<<"ERROR: This list is empty!\n";
				}
				else 
					output << "ERROR: This name does not exist!\n";
			}
			else if (b[0] == 's') {
				SimpleList<string> *pSLs;
				pSLs = search(b,listSLs,output);
				if (pSLs != NULL) {
					string *p = pSLs->pop();
					if (p != NULL)
						output << "Value popped: " << *p << "\n";
					else
						output<<"ERROR: This list is empty!\n";
				}
				else 
					output << "ERROR: This name does not exist!\n";
			}
		
	}
}
	output.close();
	return 0;
}
