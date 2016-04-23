#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

using namespace std;

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    int ID = -1;
    vertex *parent;
    string names;
    int district;
    bool visited;
    vertex *previous;
    int distance;
    vector<adjVertex> adj;
};
struct restaurant{
    string names;
    string city;
    double rating;
    string foodtype;
    int price;
    restaurant *parent;
    restaurant *leftChild;
    restaurant *rightChild;
    restaurant *next;
    restaurant *previous;

    restaurant(){};

    restaurant(string in_names,string in_city, string in_foodtype, int in_price,double in_rating)
    {
        names = in_names;
        city = in_city;
        foodtype = in_foodtype;
        price = in_price;
        rating = in_rating;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }
};



struct queueVertex{
    int distance;
    vector<vertex *> path;
};
class Graph
{
    public:
        Graph();
        ~Graph();
        void readFileIntoGraph(Graph &g);
        void addEdge(string v1, string v2, int weight);
        void addVertex(string name);
        void addrestaurant(string name, string city, string foodtype, int price,double rating);
        void displayEdges();
        void deleterestaurant(string restoname);
        void searchbyprice(int price);
        void findrestaurant(string name);
        void searchbylocation(string location);
        void searchbytype(string type);
        void printRestaurant();
        //void ClearNetwork();
        //void assignDistricts();
        void shortestPath(string startingCity,string endingCity);

    protected:
    private:
        vector<vertex> vertices;
        vertex * findVertex(string name);
        void BFTraversal(string name, int distCount);
        void BFTraversalShortest(string starting,string destination);
        void Dijkstra(string starting, string destination);
        void printRestaurant(restaurant *nodes);
        restaurant *treeMinimum(restaurant *node);
        restaurant *root = NULL;



};


#endif // GRAPH_H
