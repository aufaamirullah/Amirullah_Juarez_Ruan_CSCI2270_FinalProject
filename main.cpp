    //menus
    //add info
    //Delete resturant
    //list resturants, location(city), rating, type of food, price
    //search by name
    //If resturant not in city, shorest distance to resturant in other city
    //Distance between similar resturants
    //Time to city and closing times of resturants
    //search price
    //search by location

#include <iostream>
#include "Graph.h"
#include <fstream>  //allows istream/ostream
#include <string>
#include <stdlib.h> //allows atoi
#include <json/json.h>
#include <vector>
#include <sstream>      // std::stringstream, std::stringbuf

using namespace std;

void displayMenu();
void foodtypeMenu();
void readFileIntoGraph(Graph & g, char* fileName);
void readinrestaurant(Graph & g, char* fileName);

int main(int argc, char*argv[])
{
    // Create a graph
    Graph g;

    // Read file into graph
    readFileIntoGraph(g, "Cities.txt");//argv[1]);//
//    readFileIntoGraph(g, "bestPlaces.txt");
    readinrestaurant(g, "restaurantData2.txt");

    // Flag used for exiting menu
    bool quit = false;

    // Used for input
    string inputString1;
    string inputString2;
    int input;
    int input2;
    string city;
    string food;
    int cost;

    //Input restaurant data from file



    while(quit != true)
    {
        displayMenu();
        cin >> input;

        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input)
        {
            // Print Vertices
            case 1:
                g.displayEdges();
                break;
            // Find districts
            case 2:
                //g.assignDistricts();
                cout << "Enter Restaurant name:" <<endl;
                getline(cin, inputString1);
                g.findrestaurant(inputString1);
                break;
            // Find shortest path
            case 3:
                cout << "Enter Restaurant name:" <<endl;
                getline(cin, inputString1);
                g.deleterestaurant(inputString1);
                break;
            case 4: //Dijkstra's
                cout << "Enter a starting city:" << endl;
                getline(cin,inputString1);
                //cout << "Enter Restaurant name:" << endl; //ORIGINAL
                cout << "Enter an ending city:" << endl;    //NEW, NEED 2 CITIES FOR DIJKSTRA'S
                getline(cin,inputString2);
                g.Dijkstra(inputString1,inputString2);
                break;
            case 5:
                cout << "Enter price rating between 1 & 5:" << endl;
                cin >> input2;
                cin.clear();
                cin.ignore(10000,'\n');
                g.searchbyprice(input2);
                break;
            case 6:
                cout << "Enter Restaurant name:" <<endl;
                getline(cin, inputString1);
                cout << "Enter City Restaurant is located:"<<endl;
                getline(cin, city);
                cout << "Enter Restaurant rating between 1 & 5:"<<endl;
                cin >> input2;
                cin.clear();
                cin.ignore(10000,'\n');
                cout << "Enter Restaurant food type:"<<endl;
                getline(cin, food);
                cout << "Enter Restaurant price rating between 1 & 5:"<<endl;
                cin >> cost;
                cin.clear();
                cin.ignore(10000,'\n');
                g.addrestaurtant(inputString1, city, input2, food, cost);
                break;
            case 7:
                foodtypeMenu();
                cin >> input;
                if(input == 1){  //Helps broaden the search, the user doesn't necessarily know that these are the only input options for searchbyType();
                    g.searchbytype("American Food");
                }
                else if(input == 2){
                    g.searchbytype("Mexican Food");
                }
                else if(input == 3){
                    g.searchbytype("Asian Food");
                }
                else if(input == 4){
                    g.searchbytype("Indian Food");
                }
                else if(input >= 5){
                    cout<<"Enter a food type followed by "Food" (ex. Italian Food, Egyptian Food)" << endl;
                    cin >> inputString1;
                    g.searchbytype(inputString1);
                }
                break;
            case 8:
                cout << "Enter City name:" <<endl;
                getline(cin, inputString1);
                //cout<<inputString1<<endl;
                g.searchbylocation(inputString1);
                break;
            // Quit
            case 9:
                cout << "Goodbye!" << endl;
                quit = true;
                break;
            // invalid input
            default:
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                break;
        }
    }

    return 0;
}

/*displays a menu with options to enqueue and dequeue a message and transmit the entire message and quit*/
void displayMenu()
{
    cout << "======Main Menu======" << endl;
    cout << "1. Print vertices" << endl;
    cout << "2. Find restaurant" << endl;
    cout << "3. Delete restaurant" << endl;
    cout << "4. Find shortest distance" << endl;
    cout << "5. Search by price" << endl;
    cout << "6. Add restaurant"<<endl;
    cout << "7. Search by kind of food"<<endl;
    cout << "8. List restaurants in city"<<endl;
    cout << "9. Quit" << endl;
    return;
}

// Shows the user the inputs for Food Type to select.
void foodtypeMenu(){
    cout << "Here are the food types stored in our database." << endl;
    cout << "Select the option below to search by food type:" <<endl;
    cout << "1. American Food" << endl;
    cout << "2. Mexican Food" << endl;
    cout << "3. Asian Food" << endl;
    cout << "4. Indian Food" << endl;
    cout << "5. Enter a Food Type" << endl;  //User has option of entering their own Food Type.
}

/* reads file into graph */
void readFileIntoGraph(Graph & g, char* fileName)
{
    vector<string> cities;
    ifstream in_stream;
    //cout << fileName << endl;
    in_stream.open(fileName);
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }

    string city;
    string line;
    getline(in_stream,line);
    std::stringstream ss(line);
    int y = 0;

    // Read a list of cities from the first line
    while (getline(ss,city,','))
    {
        if (city != "cities")
        {
            //g.addVertex(city);
            //cout<<city<<endl;
            cities.push_back(city);
        }
    }
    cities.pop_back();
    for(int x = 0; x < cities.size(); x++)
    {
        g.addVertex(cities[x]);
    }
   /* getline(ss,city);
    g.addVertex(city);
    cities.push_back(city);*/

    // Now read in all the vertices
    int i = 0;
    string in;
    while (!in_stream.eof())
    {
        i = -1;
        getline(in_stream,line);
        stringstream ss(line); // why does ss.str(line) not work?

        while (getline(ss,in,','))
        {
            if (i == -1)
            {
                city = in;
            }
            else
            {
                if (in != "-1" && in != "0")
                {
                    g.addEdge(cities[i], city, atoi(in.c_str()));
//                    g.addEdge(city,cities[i],atoi(in.c_str()));
                    //cout<<"city:"<<city<<" cities[i]:"<<cities[i]<<endl;
                }
            }
            i++;
        }

    }

}


void readinrestaurant(Graph & g, char* filename)
{
    //read in restaurants into each city
    int userinput;
    const int tableSize = 100;
    ifstream inFile(filename); //"restaurantData2.txt"
    string data;

    if(inFile.is_open())
    {
      while(getline(inFile,data))
        {
            //cout << data << endl;
            stringstream aufa (data);

            string restoname;
            getline(aufa, restoname,',');

            string city;
            getline(aufa,city,',');

            string foodtype;
            getline(aufa,foodtype,',');

            string prices;
            getline(aufa, prices,',');
            int price = atoi(prices.c_str());

            string rates;
            getline(aufa,rates);
            double rating = atof(rates.c_str());


            g.addrestaurtant(restoname, city, rating, foodtype, price);
        }
        inFile.close();
    }
}
