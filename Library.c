/// TODO: Update your header comment


// You cannot use any libraries beyond the ones we have given below.
// You must use output streams, file streams, vectors, and strings.
// You are not allowed to use any other containers or objects.
// You may not use structs, pointers, or dynamic memory allocations.


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>


using namespace std;


// Function prototypes for all the glorious function decomposition
void printMenu();


void printBooks(vector<string> bookName,vector<string> isbnNumber, vector<int> bookStatus,  int i){

    // using this user defined function so the program isnt 2000 lines
    // saves a lot of space

    // used only within loops to print out certain library entries and
    // using .at() to prevent corrupting and data misplacement

    cout << bookName.at(i) << " --- " << isbnNumber.at(i) << " --- ";                                        
               
                    switch(bookStatus.at(i)){               // switch statement for to determine the book status
                                                            // becuase i find it more aesthetically pleasing than alot of if staments
                        case 0:
                            cout << "In Library" << endl;
                            break;


                        case 1:
                            cout << "Checked Out" << endl;
                            break;


                        case 2:
                            cout << "On Loan" << endl;
                            break;


                        case 3:
                            cout << "Unknown State" << endl;
                            break;


                        default:
                            cout << "Invalid State" << endl;
                            break;
                    }
}

void printSearchResultOfBookName(vector<string> bookName,vector<string> isbnNumber, vector<int> bookStatus, string userInput){
   
    bool nameMatch = false;

                /*
                    cant use ranged based loop becasue we're
                   trying to read the last entry.
               
                   so we just reverse the for loop to start
                   the last vector in bookname
                */

    // i cant use "size_t" for i or else the program releases an error "out_of_range"
    // as if it's not int the i value doesnt work for the .at() functions

    for(int i = (bookName.size()-1) ; i >= 0 ; --i){
               
        if(userInput == bookName.at(i)){

            nameMatch = true;
                   
            cout << "The Following Are Your Search Results" << endl;
            cout << "-------------------------------------" << endl;
            printBooks(bookName,isbnNumber, bookStatus, i);

            break; // needed to stop the entire loop if not range error
        }        
    }
    if(!nameMatch){

        cout << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;
        cout << "No matching entry found in the library." << endl;

    }
}

void printSearchResultOfIsbnNumber(vector<string> bookName,vector<string> isbnNumber, vector<int> bookStatus, string userInput){

    bool isbnMatch = false;
               
                /*
                    cant use ranged based loop becasue we're
                   trying to read the last entry.
               
                   so we just reverse the for loop to start
                   the last vector in bookname
                */
   
    // i cant use "size_t" for i or else the program releases an error "out_of_range"
    // as if it's not int the i value doesnt work for the .at() functions

    for(int i = (bookName.size()-1) ; i >= 0 ; --i){
               
        if(userInput == isbnNumber.at(i)){

            isbnMatch = true;
                   
            cout << "The Following Are Your Search Results" << endl;
            cout << "-------------------------------------" << endl;
            printBooks(bookName,isbnNumber, bookStatus, i);

            break; // needed to stop the entire loop if not range error
        }    
    }
    if(!isbnMatch){

        cout << "The Following Are Your Search Results" << endl;
        cout << "-------------------------------------" << endl;
        cout << "No matching entry found in the library." << endl;

    }
}

bool isbnValid(string isbnNumber) {

    int numberTotal;
    int remainder;
    int lastDigit;

    if (isbnNumber.size() != 17) {   // making sure that the ISBN is 13 digits accounting for '-' hyphens 
        return false;
    }

    // checking wether the ISBN is properly laid out
    if (isbnNumber[3] != '-' || isbnNumber[5] != '-' || isbnNumber[8] != '-' || isbnNumber[15] != '-') {
        return false;
    }

    // replecating the eqation on wikipedia for 13 digit ISBN
    numberTotal = ((isbnNumber[0] - '0') + (3 * (isbnNumber[1] - '0')) + (isbnNumber[2] - '0') + (3 * (isbnNumber[4] - '0')) +
                  (isbnNumber[6] - '0') + (3 * (isbnNumber[7] - '0')) + (isbnNumber[9] - '0') + (3 * (isbnNumber[10] - '0')) +
                  (isbnNumber[11] - '0') + (3 * (isbnNumber[12] - '0')) + (isbnNumber[13] - '0') + (3 * (isbnNumber[14] - '0')));

    remainder = (numberTotal % 10);
    lastDigit = 10 - remainder;

    // seeing wether the last ISBN number matches
    if ((isbnNumber[16] - '0') == lastDigit) {
        return true;
    } else {
        return false;
    }
}

int main()
{
    string command;

    // used in nearly all getline user inputs
    string userInput;

    // using to store a temperally string value
    // mainly used within the load library command
    string tempString1; 
    string tempString2;
    string tempString3;
    string tempString4;

    // used in the load library commmand aswell to compase last digit of ISBN
    int lastISBN;

    // used during the output and input file streams to count the number of files inputted
    // and had to be seperate becasue if not that values can represent an incorrect value.
    int countINFS = 0;
    int countOUTFS = 0;
    
    // used during the checkout status print and used to store the number of status of books
    int statusBookTotal;
    int statusLibraryCount;
    int statusCheckedOutCount;
    int statusOnLoanCount;
    int statusUnkownCount;
    int statusInvalidCount;

    // used for for loops
    int i;

    // input/output file streams
    ifstream inFS;
    ofstream outFS;

    // used during invalid print out to detect wether
    // or not the book or library entry is valid
    bool bookValid;

    //used during the remove command to detecet wether
    // or not the inputted book or ISBN is a match
    bool nameMatch;
    bool isbnMatch;

    // used in add entry to detect a comma
    bool containsComma = false;

    // used in load library command to mainpulate and detect commas
    size_t commaPlacement1;  
    size_t commaPlacement2;

    // data structures to store each of the data pieces for every library entry
    vector<string> bookName;
    vector<string> isbnNumber;
    vector<int> bookStatus;

    // TODO: define your variables

    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do
    {
        // Output the menu and acquire a user selection
       
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";

        // We use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline

        getline(cin, command);
        cout << endl;

        // TODO: Execute non-exit commands

        if (command == "a" || command == "A"){

            cout << "What is the book title? ";
            getline(cin, userInput);
            cout << endl;

            // have to use a for loop to find comma because enough it may 
            // be more longer, its easier to format the code after 
            for( i = 0 ; i <= userInput.size(); ++i ){

                if(userInput[i] == ','){

                    cout << "The book title cannot contain commas." << endl;
                    containsComma = true;
                    break;

                }
            }
            if(!containsComma){

		        // inputing bookk name into the vector of book names
                // and using tempstr to later use in print out
                bookName.push_back(userInput);
                tempString1 = userInput;

                cout << "What is the 13-digit ISBN (with hyphens)? ";
                getline(cin, userInput);
                cout << endl;
                isbnNumber.push_back(userInput);
                tempString2 = userInput;

                bookStatus.push_back(0);          
                tempString3 = "In Library";

                cout << "The Following Entry Was Added" << endl;
                cout << "-----------------------------" << endl;
                cout << tempString1 << " --- " << tempString2 << " --- " << tempString3 << endl;;
               
            }
        }

        if (command == "c" || command == "C"){

            bookName.clear();
            isbnNumber.clear();
            bookStatus.clear();
            cout << "Your library is now empty." << endl;

        }

        if (command == "d" || command == "D"){
           
            cout << "Your Current Library" << endl;
            cout << "--------------------" << endl;

            if(bookName.empty() && isbnNumber.empty() && bookStatus.empty()){  // checking for empty library

                cout << "The library has no books." << endl;
               
            }
            else {  // had to use an else statement because if not the whole program stops and you have to restart it manually

                for ( i = 0; i < bookName.size(); ++i){

                    printBooks(bookName, isbnNumber, bookStatus, i);

                }
            }
        }

        if (command == "i" || command == "I"){

            cout << "The Following Library Entries Have Invalid Data" << endl;
            cout << "-----------------------------------------------" << endl;
            bookValid = true;

            for( i = 0 ; i < bookName.size() ; ++i){
                
                // using the if statment to see wether the isbn is valid and need to use 
                // all the && statmenst becasue Invalid status doesnt have a state

                if(isbnValid(isbnNumber.at(i)) == false || ((bookStatus.at(i) != 0 && bookStatus.at(i) != 1 && bookStatus.at(i) != 2 && bookStatus.at(i) != 3))){

                    printBooks(bookName, isbnNumber, bookStatus, i);
                    bookValid = false;

                }
            }
            if(bookName.empty()){

                cout << "The library has no books." << endl;

            } 
            else if(bookValid){

                cout << "The library has no invalid entries." << endl;

            }
        }

        if (command == "l" || command == "L"){
           
            // reseting the read in count
            countINFS = 0;    

            cout << "What database to read from? " << endl;
            getline(cin, userInput);
            inFS.open(userInput);

            if (!inFS.is_open()) {

                cout << "Could not find the database file." << endl;

            }
            else{
           
                while(!(inFS.eof())){

                    getline(inFS, tempString1);

                    // cutting the string into 3 differnt ones for easier storage
                    commaPlacement1 = tempString1.find(", ", 0);
                    tempString2 = (tempString1.substr(0, ((commaPlacement1 ))));
                    commaPlacement2 = tempString1.find(", ", ((commaPlacement1 + 2)));
                    tempString3 = (tempString1.substr((commaPlacement1 + 2),((commaPlacement2)-(commaPlacement1+2))));

                    if(commaPlacement1 == string::npos){
                        
                        // makes the libhrary entry based on defaults
                        // if only the name was loaded
                        bookName.push_back(tempString1);
                        isbnNumber.push_back("000-0-00-000000-0");  
                        bookStatus.push_back(0);

                    }
                    else if(commaPlacement2 == string::npos){

                        // makes the libhrary entry based on defaults
                        // if only the name and isbn was loaded
                        bookName.push_back(tempString2);
                        isbnNumber.push_back(tempString3);     
                        bookStatus.push_back(0);

                    }
                    else{

                        // proper library entry if all data is entered correctly
                        bookName.push_back(tempString2);
                        isbnNumber.push_back(tempString3);
                        lastISBN = (tempString1[tempString1.size() - 1] - '0');
                        bookStatus.push_back(lastISBN);

                    }
                    countINFS++;
                }
                cout << "Read in " << countINFS << " lines from the file." << endl;
            }
            inFS.close();

        }

        if (command == "o" || command == "O"){
           
            cout << "where should the database output to? " << endl;
            getline(cin, userInput);

            // reseting the read in count
            countOUTFS = 0; 
           
            outFS.open(userInput);

            for ( i = 0; i < bookName.size(); ++i){
               
                if(bookName.empty()){
                    cout << "nothing in library";
                    break;
                }

                outFS << bookName.at(i) << ", " << isbnNumber.at(i) << ", " << bookStatus.at(i) << endl;

                countOUTFS++;
            }
    
            outFS.close();
            cout << "Read in " << countOUTFS << " lines from the file." << endl;
           
        }

        if (command == "p" || command == "P"){

            // resetting count
            statusBookTotal = 0;
            statusLibraryCount = 0;
            statusCheckedOutCount = 0;
            statusOnLoanCount = 0;
            statusUnkownCount = 0;
            statusInvalidCount = 0;

            for(auto statusNumber : bookStatus){

                switch(statusNumber){  // switch statement for to determine the book status

                            // counting the Statuses
                            case 0:
                                statusLibraryCount++;
                                statusBookTotal++;
                                continue;

                            case 1:
                                statusCheckedOutCount++;
                                statusBookTotal++;
                                continue;

                            case 2:
                                statusOnLoanCount++;
                                statusBookTotal++;
                                continue;

                            case 3:
                                statusUnkownCount++;
                                statusBookTotal++;
                                continue;

                            default:
                                statusInvalidCount++;
                                statusBookTotal++;
                                continue;
                }
            }

            cout << "Your Current Library's Stats" << endl;
            cout << "----------------------------" << endl;
            cout << "Total Books: " << statusBookTotal << endl;
            cout << "   In Library: " << statusLibraryCount << endl;
            cout << "   Checked Out: " << statusCheckedOutCount << endl;
            cout << "   On Loan: " << statusOnLoanCount << endl;
            cout << "   Unknown: " << statusUnkownCount << endl;
            cout << "   Other: " << statusInvalidCount << endl;

        }

        if (command == "r" || command == "R"){

            cout << "Would you like remove by (1) name or (2) ISBN." << endl;
            cout << "Enter the numeric choice: ";
            getline(cin, userInput);
            cout << endl;

            if(userInput == "1"){

                cout << "Enter the book name: ";
                getline(cin, userInput);
                cout << endl;

                nameMatch = false;

                            /*
                                cant use ranged based loop becasue we're
                            trying to read the last entry.
                           
                            so we just reverse the for loop to start
                            the last vector in bookname
                            */

                // i cant use "size_t" for i or else the program releases an error "out_of_range"
                // as if it's not int the i value doesnt work for the .at() functions

                for( i = (bookName.size()-1) ; i >= 0 ; --i){
                           
                    if(userInput == bookName.at(i)){

                        nameMatch = true;
                               
                        cout << "The Following Entry Was Removed From The Library" << endl;
                        cout << "------------------------------------------------" << endl;
                        printBooks(bookName, isbnNumber, bookStatus, i );

                        // need to use bookName.begin() becuase i doesn't 
                        // give a proper position for erase to start from
                        bookName.erase(bookName.begin() + i);
                        isbnNumber.erase(isbnNumber.begin() + i);
                        bookStatus.erase(bookStatus.begin() + i);

                        break; // needed to stop the entire loop if not range error
                    }        
                }
                if(!nameMatch){

                    cout << "The Following Entry Was Removed From The Library" << endl;
                    cout << "------------------------------------------------" << endl;
                    cout << "No matching entry found in the library." << endl;

                }
            }
            else if(userInput == "2"){

                cout << "Enter the book 13-digit ISBN (with dashes): ";
                getline(cin, userInput);
                cout << endl;

                isbnMatch = false;

                    /*
                        cant use ranged based loop becasue we're
                        trying to read the last entry.
                               
                        so we just reverse the for loop to start
                        the last vector in bookname
                    */

                // i cant use "size_t" for i or else the program releases an error "out_of_range"
                // as if it's not int the i value doesnt work for the .at() functions

                for( i = (bookName.size()-1) ; i >= 0 ; --i){
                               
                    if(userInput == isbnNumber.at(i)){

                        isbnMatch = true;
                                   
                        cout << "The Following Entry Was Removed From The Library" << endl;
                        cout << "------------------------------------------------" << endl;
                        printBooks(bookName, isbnNumber, bookStatus, i);

                        // need to use bookName.begin() becuase i doesn't 
                        // give a proper position for erase to start from
                        bookName.erase(bookName.begin() + i);
                        isbnNumber.erase(isbnNumber.begin() + i);
                        bookStatus.erase(bookStatus.begin() + i);

                        break; // needed to stop the entire loop if not range error

                        }        
                    }
                    if(!isbnMatch){

                        cout << "The Following Entry Was Removed From The Library" << endl;
                        cout << "------------------------------------------------" << endl;
                        cout << "No matching entry found in the library." << endl;

                    }
            }
            else {

                cout << "Invalid remove by choice option." << endl;

            }
        }

        if (command == "s" || command == "S"){

            cout << "Would you like to search by (1) name or (2) ISBN." << endl;
            cout << "Enter the numeric choice: ";
            getline(cin, userInput);
            cout << endl;

            if(userInput == "1"){

                cout << "Enter the book name: ";
                getline(cin, userInput);
                cout << endl;

                // see the code in the user defined function named "printSearchResultOfBookName"
                printSearchResultOfBookName(bookName, isbnNumber,  bookStatus, userInput);

            }
            else if(userInput == "2"){

                cout << "Enter the book 13-digit ISBN (with dashes): ";
                getline(cin, userInput);
                cout << endl;
               
                // see the code in the user defined function named "printSearchResultOfIsbnNumber"
                printSearchResultOfIsbnNumber(bookName, isbnNumber,  bookStatus, userInput);

            }
            else {

                cout << "Invalid search by choice option." << endl;

            }
        }
        cout << endl;

    } while (!(command == "x" || command == "X"));
    
    return 0;
}

// Function definitions for all the glorious function decomposition
// Tip: alphabetical order makes it easy to find things if you have
//      a lot of function decomposition.


/// @brief print out the main menu of the management system
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}
