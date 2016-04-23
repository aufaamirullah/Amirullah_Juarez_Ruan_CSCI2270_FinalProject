#include "Graph.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>
#include <stdlib.h>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}
int *mycounters;
int counters = 0;

void Graph::readFileIntoGraph(Graph & g){
    vector<string> cities;
    ifstream inFile;
    //cout << fileName << endl;
    inFile.open("Cities.txt");
    if (!inFile){
        cout << "Could not open file\n";
        return;
    }

    string NewTown;
    string Entire_line;
    getline(inFile,Entire_line);
    stringstream ss(Entire_line);
    int y = 0;

    // ADDING IN EACH NEW TOWN using only first line. Skips CITIES.
    while (getline(ss,NewTown,',')){
        if (NewTown != "cities"){
            g.addVertex(NewTown);
            cities.push_back(NewTown);
        }
    }

    // Now read in all the vertices
    int i = 0;
    string in;
    while (!inFile.eof()){
        i = -1;
        getline(inFile, Entire_line);
        stringstream ss(Entire_line);

        while (getline(ss,in,',')){
            if (i == -1){
                NewTown = in;
            }else{
                if (in != "0"){
                    g.addEdge(NewTown,cities[i],atoi(in.c_str()));
                }
            }
            i++;
        }
    }
}

void Graph::addEdge(string v1, string v2, int weight){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].names == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].names == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].names == n){
            found = true;
            cout<<vertices[i].names<<" already exists."<<endl;
            break;
        }
    }
    if(found == false){
        vertex v;
        v.names = n;
        v.district = -1;
        v.visited = false;
        v.parent = NULL;
        v.ID = vertices.size();
        vertices.push_back(v);
    }
}

void Graph::displayEdges(){
    for(int i = 0; i< vertices.size();i++){
        cout<<vertices[i].district << ":" << vertices[i].names << "-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<< " "<<vertices[i].adj[j].v->names;
            if(j == vertices[i].adj.size()-1){
                cout << "***";
            }
        }
        cout<<endl;
    }
}

void Graph::BFTraversal(string name, int distCount){
    vertex *s;
    int node = vertices.size();
    for (int i=0; i<node; i++){
        vertices[i].visited = false;
        if (vertices[i].names == name){
            s = &vertices[i];
        }
    }

    if (s->ID == -1){
        s->ID = distCount;
    }

    queue <vertex*> q;
    q.push (s);
    s->visited = true;

    while (!q.empty()){
        vertex *ver;
        ver = q.front();
        q.pop();
        for (int j=0; j<(ver->adj.size()); j++){
            if (ver->adj[j].v->visited == false){
                q.push((ver->adj[j]).v);
                ver->adj[j].v->visited = true;

                if (ver->adj[j].v->ID == -1){
                    ver->adj[j].v->ID = s->ID;
                }
            }
        }
    }
}

void Graph::BFTraversalShortest(string startCity, string endCity){
    vertex *a;
    vertex *b;
    for (int i=0; i<vertices.size(); i++){
        vertices[i].visited = false;
        vertices[i].previous = NULL;

        if (vertices[i].names == startCity){
            a = &vertices[i];
        }

        if (vertices[i].names == endCity){
            b = &vertices[i];
        }
    }
    queue <vertex*> q;
    q.push (a);
    a->visited = true;
    int minEdge;

    while (!q.empty()){
        vertex *ver;
        ver = q.front();
        q.pop();

        for (int j=0; j<ver->adj.size(); j++){
            if (ver->adj[j].v->visited == false){
                q.push(ver->adj[j].v);
                ver->adj[j].v->previous = ver;
                ver->adj[j].v->visited = true;
            }
        }
    }

    vector<string> way;
    while (b != NULL){
        way.push_back(b->names);
        b = b->previous;
    }

    cout << way.size()-1 << ",";
    for (int i=way.size()-1; i>=0; i--){
        if (i == 0){
            cout << way[i] << endl;
        }
        else{
            cout << way[i] << ",";
        }
    }
}

void Graph::shortestPath(string starting, string destination){
    bool Found1 = false;
    bool Found2 = false;
    vertex *a;
    vertex *b;

    for (int i=0; i<vertices.size(); i++){
        if (vertices[i].names == starting){
            Found1 = true;
            a = &vertices[i];
        }
        if (vertices[i].names == destination){
            Found2 = true;
            b = &vertices[i];
        }
    }

    if (Found1==false || Found2==false){
        cout << "One or more cities doesn't exist" << endl;
    }else{
                BFTraversalShortest(starting, destination);
    }
}

void Graph::Dijkstra(string starting, string destination){
    vertex *s;
    vertex *d;

    for (int i=0; i<vertices.size(); i++){
        vertices[i].visited = false;
        vertices[i].previous = NULL;
        vertices[i].distance = INT_MAX;

        if (starting == vertices[i].names){
            s = &vertices[i];
        }

        if (destination == vertices[i].names){
            d = &vertices[i];
        }
    }

    s->visited = true;
    s->distance = 0;

    vector<vertex*> solved;
    solved.push_back(s);
    int minDistance;
    vertex *minVertex;

    while (d->visited == false){
        minDistance = INT_MAX;
        minVertex = NULL;

        for (int i=0; i<solved.size(); i++){
            for (int j=0; j<solved[i]->adj.size(); j++){
                if (solved[i]->adj[j].v->visited == false){
                    if ((solved[i]->distance+solved[i]->adj[j].weight) < minDistance){
                        minDistance = solved[i]->distance+solved[i]->adj[j].weight;
                        minVertex = solved[i]->adj[j].v;
                        minVertex->previous = solved[i];
                    }
                }
            }
        }

        solved.push_back(minVertex);
        minVertex->visited = true;
        minVertex->distance = minDistance;
    }

    vector<string> path;
    while (minVertex != NULL){
        path.push_back(minVertex->names);
        minVertex = minVertex->previous;
    }

    cout << minDistance << ",";
    for (int i=path.size()-1; i>=0; i--){
        if (i == 0){
            cout << path[i] << endl;
        }
        else{
            cout << path[i] << ",";
        }
    }
}

void Graph::addrestaurant(string name,string city, string foodtype, int price, double rating){
    restaurant *tmp2 = new restaurant(name, city, foodtype, price, rating);
    restaurant *tmp = root;
    restaurant *parent = NULL;

    tmp2->leftChild = NULL;
    tmp2->rightChild = NULL;

    if(root==NULL){
        root = tmp2;
    }
    else{
        while(tmp!= NULL){
            if(root==tmp2){
                parent = tmp2;
            }
            parent = tmp;

            if((tmp2->names).compare(parent->names) < 0){
                tmp = tmp->leftChild;
            }else{
                tmp = tmp->rightChild;
            }
        }
        if(parent==NULL){
            root = tmp2;
        }else if(tmp2->names.compare(parent->names) < 0){
            parent->leftChild = tmp2;
            tmp2->parent = parent;
        }else{
            parent->rightChild = tmp2;
            tmp2->parent = parent;
        }
    }

}

void Graph::findrestaurant(string name){
    restaurant *restofind = root;
    int finding = 0;

    while(restofind != NULL){
        int test = name.compare(restofind->names);
        if(test >0){
            restofind = restofind->rightChild;
        }else if(test<0){
            restofind = restofind->leftChild;
        }else{
            cout << "Restaurant Info:" << endl;
            cout << "===========" << endl;
            cout << "Name:" << restofind->names << endl;
            cout << "Location(city):" << restofind->city << endl;
            cout << "Food type:" << restofind->foodtype<<endl;
            cout << "Price:" << restofind->price<<endl;
            cout << "Rating:" << restofind->rating<<endl;
            finding++;
            break;
        }
    }
    if(finding==0){
        cout <<"Restaurant not found."<<endl;
    }
}

void Graph::deleterestaurant(string restoname){
   restaurant *restofind = root;
   restaurant *foundit = root; //this restaurant will be the one that must be deleted
   restaurant *restoreplace = root;

   int deleted=0;
        while(restofind != NULL){
            int test = restoname.compare(restofind->names);
            if(test >0){
                restofind = restofind->rightChild;
            }else if(test<0){
                restofind = restofind->leftChild;
            }else{ //check whether the rightchild and leftchild has children
                if(restofind->leftChild == NULL && restofind->rightChild == NULL){
                //if movie has no children
                    if(restofind->parent->rightChild == restofind){
                        foundit = restofind;
                        restofind->parent->rightChild = NULL;
                        counters--;
                        delete foundit; //delete movie
                        return;
                    }else if(restofind->parent->leftChild == restofind){
                        foundit =restofind;
                        restofind->parent->leftChild = NULL;
                        counters--;
                        delete foundit; // delete movie
                        return;
                    }

                }else if(restofind->leftChild == NULL){
                      //if movie has one child on the right
                    foundit = restofind;
                    restoreplace = restofind->rightChild;

                    if(restofind->parent->rightChild == restofind){
                        restofind->parent->rightChild = restoreplace;
                        restoreplace->parent = restofind->parent;
                        counters--;
                        delete foundit;

                    }else if(restofind->parent->leftChild == restofind){
                        restofind->parent->leftChild = restoreplace;
                        restoreplace->parent = restofind->parent;
                        counters--;
                        delete foundit;
                    }

                    return;
                }
                    else if(restofind->rightChild == NULL){
                          //if movie has one child on the left
                        foundit = restofind;
                        restoreplace = restofind->leftChild;

                        if(restofind->parent->rightChild == restofind){
                            restofind->parent->rightChild = restoreplace;
                            restoreplace->parent = restofind->parent;
                            counters--;
                            delete foundit;

                        }else if(restofind->parent->leftChild == restofind){
                            restofind->parent->leftChild = restoreplace;
                            restoreplace->parent = restofind->parent;
                            counters--;
                            delete foundit;
                        }
                        return;
                    }else{
                        //movie has 2 children
                        restoreplace = treeMinimum(restofind->rightChild); //find the minimum value
                        restofind->names = restoreplace->names;
                        restofind->city = restoreplace->city;
                        restofind->rating = restoreplace->rating;
                        restofind->foodtype = restoreplace->foodtype;
                        restofind->price= restoreplace->price;


                        if(restoreplace->rightChild != NULL){
                            restoreplace->rightChild->parent = restoreplace->rightChild;
                            if(restoreplace== restoreplace->parent->leftChild){
                                restoreplace->parent->leftChild = restoreplace->rightChild;
                            }else if(restoreplace == restoreplace->parent->leftChild){
                                restoreplace->parent->rightChild = restoreplace->rightChild;
                            }
                            counters--;
                            delete restoreplace;
                            return;
                        }

                    }

                }

        }
    //if movie is not found in the trees give the error message
    if(restofind == NULL && root == NULL && deleted==0){
        cout << "Movie not found." << endl;
    }

}


void Graph::printRestaurant(){
    printRestaurant(root);
}


void Graph::printRestaurant(restaurant *nodes){
    //int counter = 0;
    if(root!=NULL){
        //cout << "Restaurant: "<< nodes->names<< " " << nodes->city  << " " << nodes->foodtype << " " << nodes->price<< " " << nodes->rating <<endl;
        if(nodes->leftChild != NULL){
            printRestaurant(nodes->leftChild);
            //cout << "Restaurant: "<< nodes->names<< " " << nodes->city << " " << nodes->rating << " " << nodes->foodtype << " " << nodes->price << endl;
        }
        cout << "Restaurant: "<< nodes->names<< " " << nodes->city  << " " << nodes->foodtype << " " << nodes->price<< " " << nodes->rating <<endl;
        if(nodes->rightChild != NULL){
            printRestaurant(nodes->rightChild);
           // cout << "Restaurant: "<< nodes->names<< " " << nodes->city << " " << nodes->rating << " " << nodes->foodtype << " " << nodes->price << endl;
        }

    }
    else{
        cout << "Empty tree" << endl;
    }

}

void Graph::searchbyprice(int price){
    restaurant *restofind = root;
    int finding = 0;

    while(restofind != NULL){
        int test = price;
        if(test >0){
            restofind = restofind->rightChild;
        }else if(test<0){
            restofind = restofind->leftChild;
        }else{

            finding++;
            break;
        }
    }
    if(finding==0){
        cout <<"Restaurant not found."<<endl;
    }

}

void Graph::searchbylocation(string location){
    restaurant *restofind = root;
    int finding = 0;

    while(restofind != NULL){
        int test = location.compare(restofind->city);;
        if(test >0){
            restofind = restofind->rightChild;
        }else if(test<0){
            restofind = restofind->leftChild;
        }else{
            cout << "Restaurant Info:" << endl;
            cout << "===========" << endl;
            cout << "Name:" << restofind->names << endl;
            cout << "Location(city):" << restofind->city << endl;
            cout << "Food type:" << restofind->foodtype<<endl;
            cout << "Price:" << restofind->price<<endl;
            cout << "Rating:" << restofind->rating<<endl;
            finding++;
            break;
        }
    }
    if(finding==0){
        cout <<"Restaurant not found."<<endl;
    }
}

void Graph::searchbytype(string type){
    restaurant *restofind = root;
    int finding = 0;
    int test = type.compare(restofind->foodtype);

    while(restofind!= NULL ){
        if(test > 0){
            restofind = restofind->rightChild;
             /*if(type == "American Food"){
                cout << "Restaurant: "<< restofind->names<< " " << restofind->city  << " " << restofind->foodtype << " " << restofind->price<< " " << restofind->rating <<endl;

            }else if(type == "Asian Food"){
                cout << "Restaurant: "<< restofind->names<< " " << restofind->city  << " " << restofind->foodtype << " " << restofind->price<< " " << restofind->rating <<endl;
            }
            finding++;
            break;*/
        }else if(test < 0){
            restofind = restofind->leftChild;
            /*if(type == "American Food"){
            cout << "Restaurant: "<< restofind->names<< " " << restofind->city  << " " << restofind->foodtype << " " << restofind->price<< " " << restofind->rating <<endl;

            }else if(type == "Asian Food"){
            cout << "Restaurant: "<< restofind->names<< " " << restofind->city  << " " << restofind->foodtype << " " << restofind->price<< " " << restofind->rating <<endl;
            }*/
        }else{
            if(type == "American Food"){
                cout << "fadhil" << endl;
            }else if(type == "Asian Food"){
                cout << "fadil2" << endl;
            }
            /*if(type == "American Food"){
            cout << "Restaurant: "<< restofind->names<< " " << restofind->city  << " " << restofind->foodtype << " " << restofind->price<< " " << restofind->rating <<endl;

            }else if(type == "Asian Food"){
            cout << "Restaurant: "<< restofind->names<< " " << restofind->city  << " " << restofind->foodtype << " " << restofind->price<< " " << restofind->rating <<endl;
            }
            finding++;*/
        }
    }
    if(finding==0){
        cout <<"restaurant not found."<<endl;
    }
}


restaurant *Graph:: treeMinimum(restaurant *node){
    while(node->leftChild != NULL){
        node = node->leftChild;
    }
    return node;
}

