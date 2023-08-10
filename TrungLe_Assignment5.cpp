// This program illustrates recursion on linked lists.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

struct CensusData {
    string state, totalPop, adultPop, percent;
};

struct ListNode // ListNode is a struct, but remember, in C++ a struct, by convention, has no more than a single constructor function.
                // The C language has struct data types, but not classes. C++ has classes usually with additional member functions.
  {
     CensusData value;
     ListNode *next;
     // Constructor
     ListNode(CensusData value1, ListNode *next1 = nullptr) // Constructor function inside (inline in) the struct definition
     {
       value = value1;
       next = next1;
     }
  };

// Function prototypes
int size(ListNode *);
void displayList(ListNode *);
void readStateData();
void writeDataToFile(ListNode *stateList);
void stateAddfront(CensusData stateData);
void writeMemoryAddress();
void writeMemoryAddress2();
bool validLetterCheck(char c);
void printLetterStates (string stateLetter);
void removeStates (char c) ;
ListNode *stateList = nullptr;
string validLetter = "";
vector<char> validLetters;
int main()
{
    bool validLetter = false;
    string stateLetter;
    readStateData();
    cout << endl << "The contentI of the list are: ";
    displayList (stateList) ;

    writeMemoryAddress();
    cout<<"\n Enter letter";
    while (!validLetter)
    {
       getline(cin, stateLetter);
       validLetter = validLetterCheck(stateLetter[0]);
       if (!validLetter)
       {
           cout<<"\n"<<stateLetter<<"Not valid"<<endl;
       }
       else
       {
           printLetterStates(stateLetter);
       }
    }
    cout<<"\n Delete these states? Y or N? ";
    string input = " ";
    cin >> input;
    while (input != "Y" && input != "N")
    {
        cout<<"Please enter Y or N only: ";
        getline (cin, input);
    }
    if (input == "Y")
    {
        removeStates(stateLetter[0]);
    }
    displayList(stateList);
    writeMemoryAddress2();
    return 0;

   // Open the file
   ifstream stateFile("CensusData.csv");
   if (!stateFile)
   {
        cout << "Error in opening the file of numbers.";
        exit(1);
   }
}
//*****************************************
// length computes the number of nodes in *
// a linked list                          *
//*****************************************
   int size(ListNode *ptr)
    {
        if (ptr == nullptr)
        {
        return 0;
        }
        else
        {
        return 1 + size(ptr->next);
        }
    }
//*******************************************
// displayList prints all the values stored *
// in the list                              *
//*******************************************
void displayList(ListNode *ptr)
{
  if (ptr != nullptr)
    {
      cout << "State: " << ptr-> value.state << endl;
      cout << "TotalPop: " << ptr->value.totalPop << endl;
      cout << "AdultPop: " << ptr->value.adultPop << endl;
      cout << "Percent: " << ptr->value.percent << endl;
      cout << endl;
      displayList(ptr->next);
    }
}

// Read the file into a linked list
void readStateData()
{
    CensusData stateData;
    string data;
    ifstream stateFile("CensusData.CSV");
    if (!stateFile)
    {
        cout<<"Error in opening the file of numbers.";
        exit(1);
    }
    while (!stateFile.eof()) {
     std::getline(stateFile, stateData.state, ',');
     std::getline(stateFile, stateData.totalPop, ',');
     std::getline(stateFile, stateData.adultPop, ',');
     std::getline(stateFile, stateData.percent);
     stateList = new ListNode(stateData, stateList);
     if (!validLetterCheck(stateData.state.front()))
    {

    }
    else
    {
       validLetters.push_back(stateData.state.front());
    }
   }
   displayList(stateList);
   writeDataToFile(stateList);
   stateFile.close();
}

//Check if letter of state exists
bool validLetterCheck(char c)
{
    for (char letter : validLetter) {
        if (letter == c) {
            return false;
        }
    }
    return true;
}

void writeDataToFile(ListNode *stateList) {
    return;
}
// Add state note to front of list
void stateaddfront(CensusData stateData)
{
    ListNode *newState = new ListNode(stateData, stateList);
    stateList = newState;
}

//Writes memory address of each node to txt file
void writeMemoryAddress()
{
    ListNode *ptr = stateList;
    ofstream writeFile;
    writeFile.open("CensusNodes.text");
    if (!writeFile)
    {
        cout<<"Error, Fike couldn't be opened";
    }
    else
    {
        writeFile<<"State, Current  Node Address, Next Node Address \n";
        while(ptr != nullptr)
        {
            writeFile<<ptr->value.state
            <<" "<<ptr
            <<" "<<ptr->next
            <<"\n";
            ptr = ptr->next;
        }
    }
    writeFile<<"End of Original Node List \n";
    writeFile.close();
}

void writeMemoryAddress2() {
    return;
}
//Print all states in List
void printLetterStates(string stateLetter)
{
    string prompt;
    ListNode *ptr=stateList;
    while(ptr != nullptr)
    {
        char s = ptr->value.state.front();
        if (s == stateLetter[0])
        {
            cout<<ptr->value.state<<"\n";
        }
        ptr = ptr->next;
    }
    return;
}

//Removes states determines my user input

void removeStates(char c)
{
    ListNode *ptr = stateList;
    ListNode *ptrPrev = ptr;
    while (ptr != nullptr)
    {
        if(ptr->value.state[0] == c)
        {
            if(ptr==stateList)
            {
            stateList = stateList->next;
            delete ptr;
            ptr = stateList;
            ptrPrev = ptr;
            }
        else
        {
            ptrPrev->next = ptr->next;
            delete ptr;
            ptr = ptrPrev->next;
        }
    }
        else
        {
        ptrPrev = ptr;
        }
    }
    return;
}

// Write memory addresses after list has been modified

