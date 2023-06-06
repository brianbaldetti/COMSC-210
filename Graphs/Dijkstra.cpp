#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <queue>

using namespace std;

#define IS_QUIT(s) (s == "X" || s == "x")
#define FILENAME "/Users/messenger01/Desktop/fb_weighted.csv"

// A node in the Facebook graph
struct Person {
    int best_weight;        // The sum of the weights along the best path
    string best_parent;     // The parent node for the best path
    vector<string> friends; // String names of the friend edges
    vector<int> weights;    // Weights for each friend edge
};

struct PersonCandidate
{
    string name;
    int weight;
    string parent;
    bool operator<(const PersonCandidate & rightPersonCandidate) const
    {
        return weight > rightPersonCandidate.weight;
    }
    PersonCandidate(string inputName, int inputWeight, string inputParent)
    {
        name = inputName;
        weight = inputWeight;
        parent = inputParent;
    }
};

void parse_line(const string & str,vector<string> & line)
{
    istringstream istr(str);
    string tmp;
    
    while (getline(istr, tmp, ','))
    {
        line.push_back(tmp);
    }
}

// Output the shortest path
// - everyone:  reference variable to the graph
// - starting:  string name of the starting person
// - ending: string name of the ending person
bool dijkstra(map<string, Person> &everyone, string starting, string ending) {
    // Complete this function -- run the Dijkstra algorithm.
    // Here are the things you'll need:
    // - Some way to track tentative "candidate" nodes (priority queue?)
    // - Process each node just like you did in the MST calculation, except
    //   consider the total path length (cost to this node + cost of edge)
    // - Update the best cost/best parent in the graph when found.
    // - Stop the algorithm when the end node is reached.
    
    priority_queue<PersonCandidate> priorityQueueWeights;
    vector<PersonCandidate> candidateVec;
    
    Person & startingPerson = everyone[starting];
    
    //for loop will create a candidate for every friend that the starting person contains
    for (int i = 0; i < startingPerson.friends.size(); i++)
    {
        priorityQueueWeights.emplace(PersonCandidate(startingPerson.friends[i], startingPerson.weights[i], starting));
        candidateVec.emplace_back(PersonCandidate(startingPerson.friends[i], startingPerson.weights[i], starting));
    }
    
    startingPerson.best_weight = 0;
    startingPerson.best_parent = "";
    
    //add_to_tent(pq, p, starting)
    
    while (!priorityQueueWeights.empty())
    {
        //cout << __LINE__ << endl;
        PersonCandidate bestCandidate = priorityQueueWeights.top();     //gets best candidate from priority queue
        candidateVec.push_back(bestCandidate);
        priorityQueueWeights.pop();
        
        Person & nextPerson = everyone[bestCandidate.name];
        
        //prevents node from being added to the path multiple times since
        //when a node is added to the path its weight is altered
        if (nextPerson.best_weight != -1)
            continue;
        
        nextPerson.best_weight = bestCandidate.weight;
        nextPerson.best_parent = bestCandidate.parent;
        
        //cout << __LINE__ << endl;
        //cout << "BEST CANDIDATE: " << bestCandidate.name << endl;
        if (bestCandidate.name == ending)
        {
            vector<string> displayVec;
            string tmp = bestCandidate.name;
            string parent = bestCandidate.parent;
            displayVec.push_back(tmp);

            while (parent != starting)
            {
                //cout << __LINE__ << endl;
                for (int i = 0; i < candidateVec.size(); i++)
                {
                    if (candidateVec[i].name == parent)
                    {
                        tmp = candidateVec[i].name;
                        parent = candidateVec[i].parent;
                        displayVec.push_back(tmp);
                        //cout << __LINE__;
                        break;
                    }
                }
            }
            displayVec.push_back(parent);
            
            cout << "The best path between these two people is: \n";
            for (int i = static_cast<int>(displayVec.size() - 1); i >= 0; i--)
            {
                cout << "\t" << displayVec[i] << endl;
            }
            cout << "The weight between these two people is: " << bestCandidate.weight << endl;
            return true;
        }
        
        //cout << __LINE__ << endl;
        for (int i = 0; i < nextPerson.friends.size(); i++)
        {
            priorityQueueWeights.emplace(PersonCandidate(nextPerson.friends[i], (nextPerson.best_weight + nextPerson.weights[i]), bestCandidate.name));
        }
        
    }
    
    
    return (false);
}


int main()
{
    //defining variables
    ifstream inFile(FILENAME);
    vector<string> row;
    vector<string> names;
    map<string, Person> everyone;
    string inputLine;
    
    
    // if the file open failed then standard error sends msg and program terminates with a value of -1
    if (!inFile.good())
    {
        cerr << "Invalid file." << endl;
        return -1;
    }
    
    // Read the header line of the file (first line, contains column labels).
    // We save this line (names) so we can lookup the string names when
    // needed.
    getline(inFile, inputLine);                 //priming the read
    parse_line(inputLine, names);
    
    // Reach each subsequent entry
    while (getline(inFile, inputLine))
    {
        //terminates the while look of the EOF (end of file flag is reached)
        if (inFile.eof())
            break;
        
        vector<string> row;
        Person p;
        parse_line(inputLine, row);
        
        // Start at 1 (0th field is the string name)
        for (size_t i = 1; i < row.size(); i++)
        {
            int adj_status = atoi(row[i].c_str());
            
            // A '1' indicates an adjacency, so skip if we get a '0'
            // If there is an adjacency to this person, push the string name
            // of that person on the adjacency list.
            if (adj_status > 0) {
                p.friends.push_back(names[i]);
                p.weights.push_back(adj_status);
            }
            // Initialize the other fields
            p.best_weight = -1;
            p.best_parent = "";
        }
        // Add this (new) person to the map.
        // In this map, the key is the string name of the person, and
        // the value is their Person structure (adjacency list).
        everyone.insert(make_pair(row[0], p));

    }
    
    
    // The main loop of the program
    for (;;)
    {
        // Use this code to explore the graph and weights if needed.  It is
        // left commented out here.
        /*
        cout << endl << "Enter the name and I'll tell you their friends: ";
        getline(cin, inputLine);
        if (IS_QUIT(inputLine))
            break;
        // Look up the adjacency list of this person in the map
        if (everyone.count(inputLine) == 0) {
            cout << "That person is not in the map." << endl;
            continue;
        }
        Person this_person = everyone[inputLine];
        // Output all their friends
        cout << inputLine << " is friends with: " << endl;
        for (size_t i = 0; i < this_person.friends.size(); i++) {
            cout << "\t" << this_person.friends[i] << " (weight "
                 << this_person.weights[i] << ")" << endl;
        }
        */
        string to, from;
        cout << endl << "Enter the starting name (X to quit): ";
        getline(cin, from);
        
        if (IS_QUIT(from))
            break;
        
        cout << endl << "Enter the ending name (X to quit): ";
        getline(cin, to);
        
        if (IS_QUIT(to))
            break;
        
        if (everyone.count(from) == 0 || everyone.count(to) == 0) {
            cout << "One or more people is not in the map." << endl;
            continue;
        }
        // Run the calculation
        if (!dijkstra(everyone, from, to))
        {
            cout << "There is NOT a path between these two people." << endl;
        }
        // Clean up all the state
        for (auto i = everyone.begin(); i != everyone.end(); i++)
        {
            Person &p = i->second;
            p.best_weight = -1;
            p.best_parent = "";
        }
    }
    
    
    cout << "Exiting..." << endl;
}
