/*****************************************************************************
*
*  Author:           Sum'r Rocka
*  Title:            Overloaded Operators for Singly Linked List
*  Course:           2143
*  Semester:         Spring 2023
*
*  Description:
*        While using a starter class created by Dr. Griffin, this program is demonstrating
*        how to overload operators, creating a more robust Vector Class. This allows for ease
*        when reading the main function for the user.
*        
*
*  Usage:
*        Simply use the "<<, [], +, -, *, / ==, =" operators as you would with constants or variables :)
*
*  Files: Source.cpp    :  Contains MyVector Class and main
*****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>

#define INF 1000000000  // infinity

using namespace std;

// Node for our linked list
struct Node {
    int data;

    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};

class MyVector {
private:
    Node* head;  // base pointer of list
    Node* tail;
    int             size;
    static ofstream fout;
    string          fileName;
    bool            sorted;

    /**
     * @brief Private version of inOrder push.
     *
     * @param x
     */
    void _inorderPush(int x) {
        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (curr->data > x) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
    }

public:
    /**
     * @brief Default constructor
     *
     */
    MyVector() {
        init();
    }

    /**
     * @brief Overloaded Constructor
     *
     * @param int   *A - pointer to array
     * @param int   aSize - size of array
     */
    MyVector(int A[], int aSize) {
        init();

        for (int i = 0; i < aSize; i++) {
            pushRear(A[i]);
        }
    }

    /**
     * @brief Overloaded Constructor
     *
     * @param string FileName - file to open and read
     *
     * Assumes infile will contain numbers only delimited by spaces or
     * new lines.
     */
    MyVector(string FileName) {
        init();

        ifstream fin;
        int      x = 0;

        fin.open(FileName);
        while (!fin.eof()) {
            fin >> x;
            pushRear(x);
        }
    }

    /**
     * @brief Copy Constructor
     *
     * @param MyVector &other
     */
    MyVector(const MyVector& other) {
        init();

        Node* temp = other.head;

        while (temp) {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

    /**
     * @brief - Initialize the data members so we don't
     *      have duplicate lines in each constructor.
     *
     */
    void init() {
        head = tail = NULL;
        fileName = "";
        size = 0;
        sorted = 0;
    }


    /**
     * @brief Public version of inOrder push.
     *
     * @param x
     */
    void inorderPush(int x) {
        if (!sorted) {
            sortList();
        }

        if (!head) {
            pushFront(x);  // call push front for empty list (or pushRear would work)
        }
        else if (x < head->data) {
            pushFront(x);  // call push front if x is less than head
        }
        else if (x > tail->data) {
            pushRear(x);  // call push rear if x > tail
        }
        else {
            _inorderPush(x);  // call private version of push in order
        }
    }

    /**
     * @brief Sort the current values in the linked list.
     *
     * @returns None
     */
    void sortList() {
        Node* newFront = head;
        while (newFront->next) {
            Node* smallest = newFront;
            Node* current = newFront;
            int   minimum = INF;
            while (current) {
                if (current->data < minimum) {
                    smallest = current;
                    minimum = current->data;
                }
                current = current->next;
            }
            smallest->data = newFront->data;
            newFront->data = minimum;
            newFront = newFront->next;
        }
        sorted = true;
    }

    /**
     * @brief Add value to front of list.
     *
     * @param x
     */
    void pushFront(int x) {
        Node* tempPtr = new Node(x);

        // empty list make head and tail
        // point to new value
        if (!head) {
            head = tail = tempPtr;
            // otherwise adjust head pointer
        }
        else {
            tempPtr->next = head;
            head = tempPtr;
        }
        size++;
    }

    /**
     * @brief This method loads values from 'other' list in 'this' list.
     *          It loads an array first so we can process the values in
     *          reverse so they end up on 'this' list in the proper order.
     *          If we didn't use the array, we would reverse the values
     *          from the 'other' list.
     *
     * @depends - Uses `pushFront(int)`
     * @param MyVector& other
     * @return None
     */
    void pushFront(const MyVector& other) {
        Node* otherPtr = other.head;           // get copy of other lists head
        int* tempData = new int[other.size];  // allocate memory to hold values

        // load other list into array
        int i = 0;
        while (otherPtr) {
            tempData[i] = otherPtr->data;
            otherPtr = otherPtr->next;
            ++i;
        }

        // process list in reverse in order to keep them
        // in their original order.
        for (int i = other.size - 1; i >= 0; i--) {
            pushFront(tempData[i]);
        }
    }

    /**
     * @brief -  Add 'other' list's values to end of 'this' list.
     * @note - Uses `pushRear(int)`
     * @param MyVector& other
     * @return None
     */
    void pushRear(const MyVector& other) {
        Node* otherPtr = other.head;  // get copy of other lists head

        while (otherPtr) {  // traverse and add
            pushRear(otherPtr->data);
            otherPtr = otherPtr->next;
        }
    }

    /**
     * @brief Push value onto list at soecified position, if it exists.
     *
     * @param int i - location index
     * @param inr x - value to add
     * @return bool - true add successful / false add failed
     */
    bool pushAt(int i, int x) {
        if (i >= size) {
            return false;
        }

        Node* tempPtr = new Node(x);  // allocate new node
        Node* prev = head;            // get previous and next pointers
        Node* curr = head;

        while (i > 0) {  // loop to find proper location
            prev = curr;
            curr = curr->next;
            i--;
        }

        tempPtr->next = prev->next;  // add new node in its proper position
        prev->next = tempPtr;

        size++;  // add to size :)
        return true;
    }

    /**
     * @brief - Add value to rear of list
     *
     * @param int x - value to be added
     * @return None
     */
    void pushRear(int x) {
        Node* tempPtr = new Node(x);

        if (!head) {
            head = tail = tempPtr;

        }
        else {
            tail->next = tempPtr;
            tail = tempPtr;
        }
        size++;  // add to size of list
    }

    friend ostream& operator<<(ostream& os, const MyVector& rhs) {
        Node* temp = rhs.head;  // temp pointer copies head

        os << "[";
        while (temp) {  // this loops until temp is NULL
                        // same as `while(temp != NULL)`

            os << temp->data;  // print data from Node
            if (temp->next) {
                os << ",";
            }
            temp = temp->next;  // move to next Node
        }
        os << "]";
        os << endl;

        return os;
    }

    /**
     * @brief Destroy the My Vector object
     *
     */
    ~MyVector() {
        Node* curr = head;
        Node* prev = head;

        while (curr) {
            prev = curr;
            curr = curr->next;
            cout << "deleting: " << prev->data << endl;
            delete prev;
        }
    }

    //Overloaded Operators


     /**
     * Public : operator-
     *
     * Description:
     *      Overloads the - operator to be able to compute the difference of two MyVector objects
     *
     * Params:
     *      const MyVector &    : Vector on the right hand side of computing
     * Returns:
     *     MyVector V           : The new vector containing the difference of two lists
     */
    MyVector operator-(const MyVector& other)
     {
        MyVector V;             //storage for new list
        Node* lhs = this->head; //points to list on the left hand side
        Node* rhs = other.head; //points to list on thr right hand side
        Node* rest;             //is a temporary storage for the side of the list that is bigger so that it can
                                //be tacked onto the new list at the end

        while (lhs && rhs) {
            V.pushRear(lhs->data - rhs->data); //pushes new values to V 
            lhs = lhs->next; //traverses lhs
            rhs = rhs->next; //traverses rhs
        }
        if (rhs) {  //if this is the bigger side, set rest to it
            rest = rhs;
        }
        else { //if this is the bigger side, set rest to it
            rest = lhs;
        }
        while (rest) { //just pushes the remaining numbers, if any, to the end of the new list
            V.pushRear(rest->data);
            rest = rest->next;
        }

        return V;
    }

    //for the rest of these, the logic is the exact same as the overloaded - operator.

    /**
    * Public : operator+
    *
    * Description:
     *      Overloads the - operator to be able to compute the difference of two MyVector objects
     *
     * Params:
     *      const MyVector &    : Vector on the right hand side of computing
     * Returns:
     *     MyVector V           : The new vector containing the difference of two lists
     */
    MyVector operator+(const MyVector& other)
    {
        MyVector V;             //storage for new list
        Node* lhs = this->head; //points to list on the left hand side
        Node* rhs = other.head; //points to list on thr right hand side
        Node* rest;             //is a temporary storage for the side of the list that is bigger so that it can
                                //be tacked onto the new list at the end


        while (lhs && rhs) {
            V.pushRear(lhs->data + rhs->data);  //pushes new value to V
            lhs = lhs->next;    //traverses lhs
            rhs = rhs->next;    //traverses rhs
        }
        if (rhs) {
            rest = rhs;
        }
        else {
            rest = lhs;
        }
        while (rest) { //just tacks on the remaining amount of list at the end, if any
            V.pushRear(rest->data);
            rest = rest->next;
        }
        
        return V;
    }

    /**
    * Public : operator*
    *
    * Description:
     *      Overloads the - operator to be able to compute the difference of two MyVector objects
     *
     * Params:
     *      const MyVector &    : Vector on the right hand side of computing
     * Returns:
     *     MyVector V           : The new vector containing the difference of two lists
     */
    MyVector operator*(const MyVector& other)
    {
        MyVector V;             //storage for new list
        Node* lhs = this->head; //points to list on the left hand side
        Node* rhs = other.head; //points to list on thr right hand side
        Node* rest;             //is a temporary storage for the side of the list that is bigger so that it can
                                //be tacked onto the new list at the end

        while (lhs && rhs) {
            V.pushRear(lhs->data * rhs->data);
            lhs = lhs->next;
            rhs = rhs->next;
        }
        if (rhs) {
            rest = rhs;
        }
        else {
            rest = lhs;
        }
        while (rest) { //just tacks on the remaining amount of list at the end, if any
            V.pushRear(rest->data); 
            rest = rest->next;
        }

        return V;
    }

    /**
    * Public : operator/
    *
    * Description:
     *      Overloads the - operator to be able to compute the difference of two MyVector objects
     *
     * Params:
     *      const MyVector &    : Vector on the right hand side of computing
     * Returns:
     *      MyVector V          : The new vector containing the difference of two lists
     */
    MyVector operator/(const MyVector& other)
    {
        MyVector V;             //storage for new list
        Node* lhs = this->head; //points to list on the left hand side
        Node* rhs = other.head; //points to list on thr right hand side
        Node* rest;             //is a temporary storage for the side of the list that is bigger so that it can
                                //be tacked onto the new list at the end

        while (lhs && rhs) {
            V.pushRear(lhs->data / rhs->data);
            lhs = lhs->next;
            rhs = rhs->next;
        }
        if (rhs) {
            rest = rhs;
        }
        else {
            rest = lhs;
        }
        while (rest) { //just tacks on the remaining amount of list at the end, if any
            V.pushRear(rest->data);
            rest = rest->next;
        }

        return V;
    }

    /**
    * Public : operator[]
    *
    * Description:
    *      This allows for the MyVector to be treated as an array
    *
    * Params:
    *      int      :   is the index the user wants to see the data in
    *
    * Returns:
    *      int&     : returns the value that was in the index
    */
    int& operator[] (int key)
    {
        Node* traverse = this->head;    //creates traversal pointer that is pointing to head 
        int counter = 0;                //counter to count how many times the loop has traversed

        if (counter == key) //if key was 0
        {
            return traverse->data;
        }
        while (traverse)
        {
            traverse = traverse->next; //traverses the list
            counter++; //counts up the key 

            if (counter == key) //if key was found
                return traverse->data;
        }

    }

    /**
    * Public : operator ==
    *
    * Description:
    *      Overloads the equality operator so that it can check for equality between two
    *      linked lists
    *
    * Params:
    *      const MyVector&        :     Vector on right hand side of computing
    *
    * Returns:
    *      bool false             :     The Vectors were not equal
    *           OR
    *      bool true              :     The Vectors were equal
    */
    bool operator == (const MyVector& other)
    {
        Node* lhs = this->head; //points to list on the left hand side
        Node* rhs = other.head; //points to list on thr right hand side

        while (lhs && rhs)
        {
            if (lhs->data != rhs->data)
            {
                return false;
            }
            lhs = lhs->next;
            rhs = rhs->next;
        }

        return (lhs == NULL && rhs == NULL); // if they are both empty by this point they must be equal

    }

    /**
    * Public: operator =
    *
    * Description:
    *      This function overloads the assignment operator so that it can assign one
    *      linked list to another
    *
    * Params:
    *      const MyVector& other    :    Vector on right hand side of computing
    *
    * Returns:
    *      MyVector *this           :    The Vector on the lhs of computing
    */
    MyVector& operator = (const MyVector& other)
    {
        //if lhs and rhs are already equal
        if (this == &other)
        {
            return *this;
        }

        Node* lhs = head;
        //this clears the linked list if it has elements in it
        while (lhs)
        {
            Node* temp = lhs->next; //temp pointer that saves the next part of this list
            delete lhs;             //deletes node
            lhs = temp;             //points lhs to where temp is pointing
        }
        head = NULL; //sets head so that its pointing to nothing again

        Node* rhs = other.head; //points to list on thr right hand side
        Node* rear = NULL;      //this pointer keeps track of the end of the list

        while (rhs)
        {
            Node* temp = new Node(rhs->data);
            if (!rear) //if list is empty
            {
                head = temp;
            }
            else
            {
                rear->next = temp; //the last node of the list points to the temp node
            }
            rear = temp;           //moves the rear pointer over to the new node @ the end
            rhs = rhs->next;       //traverses other list
        }
        return *this;
    }
 };

//ofstream MyVector::fout;

int main() {


    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 20, 30 };

    MyVector v1(a1, 5);
    MyVector v2(a2, 3);

    ofstream fout;
    fout.open("output.txt");

    fout << "Sum'r Rocka\n";
    fout << "2/21/2023\n";
    fout << "Spring 2021\n\n";

    cout << v1[2] << endl;
    // writes out 3

    v1[4] = 9;
    //// v1 now = [1,2,3,4,9]

    cout << v1 << endl;
    // //writes out [1,2,3,4,9] to console.

    fout << v1 << endl;
    // //writes out [1,2,3,4,9] to your output file.

    MyVector v3 = v1 + v2;
    cout << v3 << endl;
    fout << v3 << endl;
    //// writes out [11,22,33,4,9] to console.

    v3 = v1 - v2;
    cout << v3 << endl;
    fout << v3 << endl;
    // writes out [-9,-18,-27,4,9] to console.

    v3 = v2 - v1;
    cout << v3 << endl;
    fout << v3 << endl;
    // writes out [9,18,27,4,9] to console.

    v3 = v2 * v1;
    cout << v3 << endl;
    fout << v3 << endl;
    // writes out [10,40,90,4,9] to console.

    v3 = v1 * v2;
    cout << v3 << endl;
    fout << v3 << endl;
    // writes out [10,40,90,4,9] to console.

    v3 = v1 / v2;
    cout << v3 << endl;
    fout << v3 << endl;
    // writes out [0,0,0,4,9] to console.

    v3 = v2 / v1;
    cout << v3 << endl;
    fout << v3 << endl;
    // writes out [10,10,10,4,9] to console.

    cout << (v2 == v1) << endl;
    fout << (v2 == v1) << endl;
    // writes 0 to console (false) .
   
    MyVector v4 = v1;
    cout << (v4 == v1) << endl;
    fout << (v4 == v1) << endl;
    // writes 1 to console (true) .

    fout.close(); //closes output file

    return 0;
}
