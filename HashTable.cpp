#include <iostream>
#include <fstream>
#include <vector>
#include "Trabahador.h"


using namespace std;
int n;
int m;
int q;
vector<vector<Trabahador*>> roster;
int collisions;

int string2Int(string nme) {
    int total = 0;
    for (auto y : nme) {
        total += int(y);
    }
    
    return total * nme[2] + nme[1];
}



int main(int argc, char** argv)
{
    //We send a warning if they forget to input the filename
    if (argc == 1) {
        cout << "You forgot the commandline parameter\n";
        exit(0);
    }

    //This is how we read the file. By putting the filename in the commandline argument.
    //An error message is also sent, just in case the file location is incorrect.
    ifstream ifs;
    ifs.open(argv[1], ios::in);
    if (!ifs) {
        cout << "could not locate file" << argv[1] << endl;
        exit(0);
    }

    //First line is the size of the array
    string line1;
    getline(ifs, line1);
    m = stoi(line1);

    //Create an arraylist inside our roster arraylis
    for (auto x = 0; x < m; x++) {
        vector<Trabahador*> vec;
        roster.push_back(vec);
    }

    //Second line is the number of records in the file.
    string line2;
    getline(ifs, line1);
    n = stoi(line1);


    //Variables needed 
    //Variable for multiplication method
    const double A = (sqrt(5) - 1) / 2;
    //collisions = 0;
    //This will loop depending on the number of lines in each file
    for (auto i = 0; i < n; i++) {
        string word[4];
        string y;

        //Loop through all the line and save it to my array of strings.
        for (int x = 0; x < 4; x++) {
            getline(ifs, word[x], '|');
        }
        getline(ifs, y);
        


        //Get all those element from the array and create a variable
        string name = word[0];
        int id = stoi(word[1]);
        int age = stoi(word[2]);
        string job = word[3];
        int year = stoi(y);

        //Initialize the new object we will add to our vector
        Trabahador* t = new Trabahador(name, id, age, job, year);



        //Let's use NAME to hash the list
        //Convert each letter to ASCII then add them all up.
        
        int total = string2Int(t->name);
       
        //the division method
        int index = total % m;	
        //the multiplication method
        //int index = (int)(m * (fmod(total * A, 1)));
        
        
        
        cout << "Attempting to hash " + t->name + "at index " + to_string(index);
        //If there are no collissions       
        if (roster[index].size() < 1 ){
            roster[index].push_back(t);
            cout << "... SUCCESS!" << endl;

        }
        //If there are collisions
        else {
            //collision++;
            //cout << "... OUCH! Collision with " + roster[index][0]->name << endl;
            cout << "  (" + to_string(roster[index].size()) + " collisions)" << endl;
            roster[index].push_back(t);
        }
    }

    //QUERY part of our program
    //Start by saving the total number of queries
    string query;
    getline(ifs, query);
    getline(ifs, query);
    q = stoi(query);

    //Forloop to get all names that we will lookup. Use the string2Int method to convert names to our key.
    for (auto x = 0; x < q; x++) {
        string queryName;
        getline(ifs, queryName);
        int modIndex = string2Int(queryName) % m;
        //int modIndex = (int)(m * (fmod(string2Int(queryName) * A, 1)));
        //We need to declare the vector inside our vector.
        vector<Trabahador*> rosterArray = roster[modIndex];
        for (int i = 0; i < rosterArray.size(); i++) {
            Trabahador* candidate = rosterArray[i];
            if (candidate->name == queryName) {
                cout << "Found " << queryName << " after " << (i) << " collisions at index " << modIndex << " in the hashtable." << endl;
                collisions += i;
            }
        }

    }



    //Print all the number of collisions
    cout << "Total collision to resolve: " << collisions << endl;
    

}