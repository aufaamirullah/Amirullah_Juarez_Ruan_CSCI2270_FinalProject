#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include "Graph.h"
using namespace std;

int main()
{
    int userinput;
    const int tableSize = 100;
    Graph G;
    ifstream inFile("restaurantData2.txt");
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


            G.addrestaurant(restoname, city, foodtype, price, rating);
        }
        inFile.close();
    }

    string i;
    bool yesorNo = false;

    G.readFileIntoGraph(G);


    while(yesorNo == false){
        cout << "======Main Menu======" << endl;
        cout << "1. Print vertices" << endl;
        cout << "2. Find restaurant" << endl;
        cout << "3. Delete restaurant" << endl;
        cout << "4. Find shortest distance" << endl;
        cout << "5. Search by price" << endl;
        cout << "6. Add restaurant"<<endl;
        cout << "7. Search by kind of food"<<endl;
        cout << "8. Search by location(city)"<<endl;
        cout << "9. Print the list of Restaurants"<<endl;
        cout << "10. Quit" << endl;
        cin >> userinput;
        cin.ignore();

        if(userinput == 1){
            G.displayEdges();

        }else if(userinput == 2){
            cout << "Enter Restaurant name:" <<endl;
            getline(cin, i);
            G.findrestaurant(i);

        }else if(userinput == 3){
            cout << "Enter a restaurant name: " << endl;
            getline(cin,i);
            G.deleterestaurant(i);

        }else if(userinput == 4){
            cout << "Enter a starting city:" << endl;
            getline(cin, i);

            cout << "Enter an ending city:" << endl;
            getline(cin, i);

            G.shortestPath(i, i);

        }else if(userinput == 5){
             cout << "Enter price between 1 & 5:" << endl;
             getline(cin,i);
             int a3 = atoi(i.c_str());
             G.searchbyprice(a3);

        }else if(userinput == 6){
                cout << "Enter Restaurant name:" << endl;
                getline(cin, i);
                cout << "Enter City Restaurant is located:"<< endl;
                getline(cin, i);

                cout << "Enter Restaurant food type:"<<endl;
                getline(cin, i);

                cout << "Enter Restaurant price rating between 1 & 5:"<<endl;
                string cost;
                getline(cin,cost);
                int a2 = atoi(cost.c_str());

                cout << "Enter Restaurant rating between 1 & 5:"<< endl;
                string rate;
                getline(cin,rate);
                int a1 = atoi(rate.c_str());

                G.addrestaurant(i, i, i, a2, a1);

        }else if(userinput == 7){
             cout << "Enter Food Type:" <<endl;
             getline(cin, i);
             G.searchbytype(i);

        }else if(userinput == 8){
            cout << "Enter City name:" <<endl;
            getline(cin, i);
            G.searchbylocation(i);

        }else if(userinput == 9){
            G.printRestaurant();

        }else if(userinput == 10){
            cout<<"Goodbye!"<<endl;
            yesorNo = true;
        }
    }
    return 0;
}
