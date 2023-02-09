/*****************************************************************************
*
*  Author:           Sum'r Rocka
*  Email:            sumrrocka09@gmail.com
*  Label:            P01
*  Title:            Vector Class
*  Course:           CMPS 2143
*  Semester:         Spring 2023
*
*  Description:
*        This program creates a vector class that will allow a user to add, remove, and maintain sortedness in values.
*		 It can be initialized with different sources, and allows for the user to push and pull other vectors
*		 Onto the vector being worked with.
*
*  Usage:
*       - $ ./main filename
*       - This will read in a file containing whatever values to be read into our list/array.
*
*  Files:
*       main.cpp    : driver program
*       input.dat   : input file for reading
*       test.out    : output file for writing
*****************************************************************************/



#include <iostream>
#include <fstream>

using namespace std;

struct Node {
public:
	int data;
	Node* next;


	// default constructor
	Node() {
		data = 0;
		next = nullptr;
	}

	// overloaded constructor
	Node(int x) {
		data = x;
		next = nullptr;
	}

};


/**
 * Vector
 *
 * Description:
 *      This class implements methods to add and remove values to a list, as well as find the position of values
 *		and maintain order within the vector list. It can also read in values from different sources. 
 *
 * Public Methods:
 *
 *		void		 pushFront(int val);
 *		void		 pushFront(Vector other);
 *		void		 pushRear(int val);
 *		void		 pushRear(Vector other);
 *		void		 pushAt(int loc, int val);
 *		void		 inOrderPush(int val);
 *
 *		int			popFront();
 *		int			popRear();
 *		int			popAt(int loc);
 *		int			find(int val);
 *
 *		void		print();
 *		void		print(string fileName);
 *
 *
 * Usage:
 *
 *      Vector v1;				//create a vector object
 *		v1.pushFront(18);		//push a value on in the front
 *		v1.pushRear(20);		//push a value on to the rear
 *		v1.print;				//print to console
 *								OR
 *		v1.print(output)		//print to output file
 */
class Vector
{
private:
	Node* head;		//creates head pointer from Node struct
	Node* tail;		//creates tail pointer from Node struct

public:

	Vector();
	Vector(int *array, int size);
	Vector(string fileName);
	Vector(const Vector &other);


	/**
	 * Public : pushFront
	 *
	 * Description:
	 *      Pushes a value to the front of the vector
	 *
	 * Params:
	 *      int     :  integer value
	 *
	 * Returns:
	 *      nothing is returned
	 */
	void pushFront(int val);

	/**
	* Public :	pushFront
	 *
	* Description:
	*      overloaded function that pushes another vector the vector the user is working with
	*
	* Params:
	*      Vector  :  other value list
	*
	* Returns:
	*      nothing is returned
	*/
	void pushFront(Vector other);

	/**
	* Public : pushRear
	*
	* Description:
	*       Pushes a value to the end of the vector
	*
	* Params:
	*      int    :  integer value to be pushed
	*
	* Returns:
	*      Nothing is returned
	*/
	void pushRear(int val);

	/**
	 * Public : pushRear
	 *
	 * Description:
	 *      overloaded function that pushes another vector the vector the user is working with
	 *
	 * Params:
	 *      Vector  :  other value list
	 *
	 * Returns:
	 *      Nothing is returned
	 */
	void pushRear(Vector other);

	/**
	 * Public : pushAt
	 *
	 * Description:
	 *      pushes a value at a user specified location, if it exists.
	 *
	 * Params:
	 *      int    :    location to be pushed at
	 *		int    :    value to be pushed
	 *
	 * Returns:
	 *      Nothing is returned
	 */
	void pushAt(int loc, int val);

	/**
	 * Public : inOrderPush
	 *
	 * Description:
	 *      Pushes a value into the vector list, in order.
	 *
	 * Params:
	 *      int     :  integer value to be pushed
	 *
	 * Returns:
	 *      Nothing is returned
	 */
	void inOrderPush(int val);


	/**
	 * Public : popFront
	 *
	 * Description:
	 *      Removes a value from the front of the vector list
	 *
	 * Params:
	 *		There are no parameters
	 *
	 * Returns:
	 *      value   :  value that was popped from vector
	 */
	int popFront();

	/**
	 * Public : popRear
	 *
	 * Description:
	 *      Removes a value from the back of the vector list
	 *
	 * Params:
	 *      There are no parameters
	 *
	 * Returns:
	 *      value  :  value that was popped from vector
	 */
	int popRear();

	/**
	 * Public :	popAt
	 *
	 * Description:
	 *      Removes a value from the vector list at a specific location.
	 *
	 * Params:
	 *      int     :   location to be popped from
	 *
	 * Returns:
	 *		Value   :   the integer value that was popped from vector
	 */
	int popAt(int loc);

	/**
	 * Public : find
	 *
	 * Description:
	 *      finds a value in a vector list, if it exists
	 *
	 * Params:
	 *      int     :  value to be found within vector
	 *
	 * Returns:
	 *      pos     :  position in which value was found in vector
	 */
	int find(int val);


	/**
	 * Public : print
	 *
	 * Description:
	 *      prints the vector to the console
	 *
	 * Params:
	 *		There are no parameters.
	 *
	 * Returns:
	 *      Nothing is returned.
	 */
	void print();

	/**
	 * Public : print
	 *
	 * Description:
	 *      overloaded function that prints to an output file.
	 *
	 * Params:
	 *      ofstream&   :  output file to be written to that is opened in main
	 *
	 * Returns:
	 *      Nothing is returned.
	 */
	void print(ofstream& fileName);

};

Vector::Vector()
{
	head = tail = nullptr;	//initializes head & tail to NULL
}

Vector::Vector(int *array, int size)
{
	head = tail = nullptr;	//initializes head & tail to NULL

	for (int i = 0; i < size; i++)
	{
		Node* temp = new Node;	//creates temp node
		temp->data = array[i];
		temp->next = nullptr;

		if (!head)
		{
			head = tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = tail->next;
		}
	}

}

Vector::Vector(string fileName)
{
	head = tail = nullptr;	//initializes head & tail to NULL
	int data;				//storage for value to be read from input file
	ifstream infile;		//creates input file
	infile.open(fileName);	//opens input file for reading

	while (!infile.eof())
	{
		infile >> data;
		this->pushRear(data);
	}
	infile.close();
}

Vector::Vector(const Vector& other)
{
	head = tail = nullptr;		 //initializes head & tail to NULL

	Node* traverse = other.head; //creates pointer to traverse with

	while (traverse)
	{
		Node* temp = new Node(traverse->data);
		pushRear(temp->data);
		traverse = traverse->next;
	}
}

void Vector::pushFront(int val)
{
	Node* temp = new Node;	//creates temp node
	temp->data = val;
	temp->next = head;
	head = temp;

	//if tail is NULL
	if (!tail)
		tail = temp;
}

void Vector::pushFront(Vector other)
{
	//if the other list is empty
	if (!other.head)
	{
		return;
	}
	else
	{
		Node* traverse = other.head;	//initializes traverse node to the other vectors head
		while (traverse)
		{
			//creates new node with overloaded function

			//this doesn't print in the right order right now
			pushFront(traverse->data);
			traverse = traverse->next;
		}
	}
}

void Vector::pushRear(int val)
{
	Node* temp = new Node;	//creates temp node
	temp->data = val;		//sets it to value to be pushed

	if (!head)
	{
		head = tail = temp;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

void Vector::pushRear(Vector other)
{
	//if the other list is empty
	if (!other.head)
	{
		return;
	}
	else
	{
		Node* traverse = other.head;	//creates node for traversal
		while (traverse)
		{
			//creates new node with overloaded function
			pushRear(traverse->data);
			traverse = traverse->next;
		}
	}
}

void Vector::pushAt(int loc, int val)
{
	Node* temp = new Node;	//creates temp node
	temp->data = val;		//sets it to value to be pushed

	//if list is empty
	if (!head)
	{
		head = tail = temp;
	}
	//if push is at beginning of list
	else if (loc == 0)
	{
		temp->next = head;
		head = temp;
	}
	//push is somewhere within the list
	else
	{
		Node* traverse = head;	//creates node for traversal
		
		int counter = 0;

		while (traverse && counter < loc - 1)
		{
			traverse = traverse->next;
			counter++;
		}
		temp->next = traverse->next;
		traverse->next = temp;
	}
}

void Vector::inOrderPush(int val)
{
	Node* temp = new Node(val); //creates temp node

	//if head is empty
	if (!head)
	{
		head = tail = temp;
	}
	//if the value is smaller than the first item
	else if (temp->data < head->data)
	{
		pushFront(temp->data);
	}
	//if the value is larger than the last item
	else if (temp->data > tail->data)
	{
		pushRear(temp->data);
	}
	//the value had to be somewhere in the middle
	else
	{
		Node* traverse = head;

		while (traverse->next->data < temp->data)
		{
			traverse = traverse->next;
		}
	}
}

int Vector::popFront()
{
	Node* temp = new Node;	//creates temp node
	int value;				//storage for value to be returned

	temp = head;
	head = head->next;
	value = temp->data;

	//deletes the temp node
	temp->data = NULL;
	delete temp;

	return value;
}

int Vector::popRear()
{
	int value = tail -> data;

	//if only one item in list
	if (head == tail)
	{
		head = tail = nullptr;

		return value;
	}
	//
	else
	{
		Node* traverse = head; //creates node for traversal

		//traverses until one before the tail pointer because this is singly linked
		while (traverse->next != tail)
			traverse = traverse->next;

		//deletes old node
		tail = nullptr;
		delete tail;

		tail = traverse;
		tail->next = nullptr;

		return value;
	}
}

int Vector::popAt(int loc)
{
	int value;		//value to be returned

	//if list is empty
	if (!head)
		return -1;
	//if pop is at the head of list
	else if (loc == 0)
	{
		return popFront();
	}
	//if pop is somewhere within the list
	else
	{
		Node* traverse = head;
		int counter = 0;

		while (traverse && counter < loc - 1)
		{
			traverse = traverse->next;
			counter++;
		}

		//this only happens if the location exists
		if (traverse && counter == loc - 1)
		{
			Node* temp = traverse->next;
			value = temp->data;

			temp = nullptr;
			delete temp;

			return value;
		}
		else
			//position not found
			return -1;
	}
}

int Vector::find(int val)
{
	Node* traverse = head;	//node for traversal
	int pos = 0;			//position that value was found at

	while (traverse)
	{
		if (traverse->data == val)
			return pos;

		traverse = traverse->next;
		pos++;
	}
	//position was not found
	return -1;
}

void Vector::print()
{

	Node* traverse = head; //node for traversal
	
	cout << "[";

	while (traverse)
	{
		cout << traverse->data;
		
		if (traverse->next != nullptr)
			cout << ',';

		traverse = traverse->next;
	}
	cout << "]\n";
}


void Vector::print(ofstream& outfile)
{
	outfile << "[";
	Node* traverse = head; //node for traversal
	while (traverse)
	{
		outfile << traverse->data;
		traverse = traverse->next;
		if (traverse)
		{
			outfile << ", ";
		}
	}
	outfile << "]" << endl;
}




int main()
{
	ofstream fout;
	fout.open("test.out");

	fout << "Sum'r Rocka" << endl;
	fout << "2/9/2023" << endl;
	fout << "Spring 2143" << endl << endl;

	int x = 0;

	Vector v1;
	v1.pushFront(18);
	v1.pushFront(20);
	v1.pushFront(25);
	v1.pushRear(18);
	v1.pushRear(20);
	v1.pushRear(25);
	v1.print();
	v1.print(fout);

	//[25, 20, 18, 18, 20, 25]

	int A[] = { 11,25,33,47,51 };
	Vector v2(A, 5);
	v2.print();
	v2.print(fout);
	// [11, 25, 33, 47, 51]

	v2.pushFront(9);
	//v2.inOrderPush(27);
	v2.pushRear(63);
	v2.print();
	v2.print(fout);
	// [9, 11, 25, 33, 47, 51, 63]

	v1.pushRear(v2);
	v1.print();
	v1.print(fout);
	// [25, 20, 18, 18, 20, 25, 9, 11, 25, 33, 47, 51, 63]

	x = v1.popFront();
	x = v1.popFront();
	x = v1.popFront();
	v1.print();
	v1.print(fout);
	// [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
	cout << x << endl;
	// 18

	x = v1.popRear();
	x = v1.popRear();
	x = v1.popRear();
	v1.print();
	v1.print(fout);
	// [18, 20, 25, 9, 11, 25, 27, 33]
	cout << x << endl;
	// 47

	x = v2.popAt(3);
	v2.print();
	// [9, 11, 25, 33, 47, 51, 63]
	cout << x << endl;
	fout << x << endl;
	// 27

	x = v2.find(51);
	cout << x << endl;
	fout << x << endl;
	// 5

	x = v2.find(99);
	cout << x << endl;
	fout << x << endl;
	// -1

	Vector v3(v1);
	v3.print();
	v3.print(fout);
	// [18, 20, 25, 9, 11, 25, 27, 33]

	v3.pushFront(v2);
	v3.print();
	v3.print(fout);
	//[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

	Vector v4("input.dat");
	v4.pushRear(v3);
	v4.print();
	v4.print(fout);
	// [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

	fout.close();
	return 0;
}
