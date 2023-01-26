
/*****************************************************************************
*
*  Author:           Sum'r Rocka
*  Email:            sumrrocka09@gmail.com
*  Label:            A03
*  Title:            Basic Project Organization        
*  Course:           CMPS 2143
*  Semester:         Spring 2023
*
*  Description:
*        This program implements a class that creates a circular queue array with a default max of ten,
         though the user can declare a different size.
*        If the queue is to reach the max size, it notifies the user so they know what is going on.
*        Outside of the class there is an overload of the operator '<<' in order to keep code clean for the user.
*        This allows for readable output commands.
*
*  Usage:
*        how to use the program if necessary
*
*  Files:
        main.cpp        : includes class and main
*****************************************************************************/
#include <iostream>

using namespace std;

/**
 * CircularArrayQue
 *
 * Description:
 *      This class creates an array queue that is circular, meaning the last index in the array 
 *
 * Public Methods:
 *                      CircularArrayQue()
 *      void            Push(int item)
 *      int         Pop()
 *      
 *      
 *
 * Private Methods:
 *      void            init(int size = 0)
 *      bool            full()
 *
 * Usage:
 *
 *      CircularArrayQue Q2(8);         // Create an instance of a CircularArrayQue
 *                                      // And set the your size or leave empty for default value.
 * 
 *      Q2.Push(4);                     // Push numbers onto your queue
 *      Q2.Push(7);
 *      Q2.Push(9);                     
 * 
 *      Q2.Pop();                       // Remove a number from your queue
 *  
 *      cout << Q2 << endl;             // Output your queue to the console to see the results.
 *
 */
class CircularArrayQue {
private:
    int *Container;     // Pointer that allocates memory for array
    int Front;          // Keeps track of first position in array
    int Rear;           // Keeps track of last item in array
    int QueSize;        // Items in the queue
    int CurrentSize;    // Stores the current size of array


    /**
     * Private : init
     *
     * Description:
     *      This function assigns the Front, Rear, and CurrentSize values to 0
     *      and sets the QueSize equal to the size passed in, or the default perameter.
     *
     * Params:
     *     int      : array size
     *      
     *
     * Returns:
     *      Nothing is returned.
     */
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }



    /**
     * Private : Full
     *
     * Description:
     *      Checks if the current size of the array is equal to the predetermined array size.
     *
     * Params:
     *      No parameters.
     *
     * Returns:
     *      bool    : either true or false comparing Currentsize to Quesize
     */
    bool Full() {
        return CurrentSize == QueSize;
    }

public:

    /**
     * Public : CircularArrayQue
     *
     * Description:
     *      Default constructer that creates an array of size ten.
     *
     * Params:
     *      None.
     *
     * Returns:
     *      Nothing is returned.
     */
    CircularArrayQue() {
        Container = new int[10];
        init(10);
    }


    /**
     * Public : CircularArrayQue
     *
     * Description:
     *      Constructor that allows for the user to input their own array size.
     *
     * Params:
     *      int     : size
     *
     * Returns:
     *      Nothing is returned.
     */
    CircularArrayQue(int size) {
        Container = new int[size];
        init(size);
    }


    /**
     * Private : Push
     *
     * Description:
     *      Allows for the user to put numbers into the queue while keeping track of the rear value.
     *
     * Params:
     *      int     : value to be put into the array.
     *
     * Returns:
     *      Nothing is returned.
     */
    void Push(int item) {
        //if array is not full, add item to the back, else, report to the user the array is full.
        if (!Full()) {    
            Container[Rear] = item;
            Rear = (Rear + 1) % QueSize;
            CurrentSize++;  //keeps track of the current array size
        } else {
            cout << "FULL!!!!" << endl;
        }
    }


    /**
     * Private : Pop
     *
     * Description:
     *      This function takes the value at the beginning of the list off of the queue and reasigns front to the next value.
     *
     * Params:
     *     None.
     *
     * Returns:
     *      temp       :    The value of the integer that has been popped off.
     */
    int Pop() {
        int temp = Container[Front];
        Front = (Front + 1) % QueSize;  //sets front equal to the next value in list
        CurrentSize--;                  //takes away one value from size
        return temp;
    }
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other); //alows operator to access private members
};

ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);     // Creates an instance of an array using class

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);
    C1.Push(2);
    C1.Push(3);
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;
}