 /*****************************************************************************
 *	Name:     Ana Balteanu                                                    *
 *	Date:     9/19/2020                                                       *
 *                                                                            *
 *	Description: Merges two lists of numbers from two different text files    *
 *                                                                            *
 *****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//prototyping
int checkFiles (ifstream& File1);
void readData (ifstream& File1, int data[], int& dataCounter);

int main() {

    int dataCounter1 = 0;
    int dataCounter2 = 0;
    int data1[100];
    int data2[100];
    int datafinal[200];


    //input data from file
    ifstream dataFile1("data1.txt");
    ifstream dataFile2("data2.txt");
    ofstream outputFile;
    outputFile.open("outputFile.txt");
    checkFiles(dataFile1);
    checkFiles(dataFile2);

    if (!outputFile.is_open() ) {
        cout << "Unable to open file" << endl;
        return 1;
    }

    readData (dataFile1, data1, dataCounter1);
    readData (dataFile2, data2, dataCounter2);

    int i = 0;  //counter for data1
    int j = 0;  //counter for data2
    int k = 0;  //counter for final list

    ///MERGING ARRAYS
    //if either reach the end of the file, go out of while loop
    while (i < dataCounter1 && j < dataCounter2) {
        //compares two numbers from list
        if(data1[i] > data2[j]) {
            //if data1 entry is larger, insert data2's number in datafinal[]
            datafinal[k] = data2[j];    //inserts number as next number in final array
            k++;                        //increase final array counter to add next number to next location in the list
            j++;                        //increase counter for list two(j) to read next number in that list
        }
        else {
            //same thing but if data1 is SMALLER, it inserts data1's number
            datafinal[k] = data1[i];
            k++;
            i++;
        }
    }

    ///INSERTING FINAL DATA
    //once one of the files has run out of numbers, print the rest of the larger file into datafinal[]
    if (dataCounter1 > dataCounter2) {
        while (i < dataCounter1){
            datafinal[k] = data1[i];
            k++;
            i++;
        }
    }
    else {
        while (j < dataCounter1){
            datafinal[k] = data2[j];
            k++;
            j++;
        }
    }

    //putting final array into output file
    for (int i = 0; i < k; i++){
        outputFile << datafinal[i] << endl;
    }

    ///CLOSING FILES
    dataFile1.close();
    dataFile2.close();
    outputFile.close();
    return 0;
}

int checkFiles (ifstream& File1){
    //check if input files can open
    if (!File1.is_open() ) {
        cout << "Unable to open file" << endl;
        return 1;
    }else {
        return 0;
    }
}

void readData (ifstream& File1, int data[], int& dataCounter) {
    //reads data from file
    while(!File1.eof()) {
        if (dataCounter < 100){
            File1 >> data[dataCounter++];
        }
        else {
            cout << "File is longer than 100. cannot continue reading." << endl;    //max amount of data is 100
        }
    }
    if (dataCounter < 100) {
        data[dataCounter] = 0;
    }

}

