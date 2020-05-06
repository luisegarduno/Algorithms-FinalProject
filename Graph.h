//
// Created by luise on 5/3/2020.
//

#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

#include "Node.h"
#include <fstream>
#include <iostream>
#include "Edge.h"
#include "LinkedList.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

template<class T>
class Graph{

private:
    //ofstream fout;                  // Outputs to outputFile;
    //string filename;
    LinkedList< LinkedList<T> > graph;

public:
    Graph();
    void add(T);
    LinkedList<T> &checkListOfVertexNodes(const string &);
    bool checkNetworkConnections(const string&,const string&, const LinkedList<T>&);
    LinkedList<T> getAllNodes(const string&);


    //void setOutputFileName(const string&);
    //string getOutputFileName();
    void printGraph();
    void printMatrix();
};

template <class T>
Graph<T>::Graph() = default;

template<class T>
void Graph<T>::add(T newNode){

    if(newNode.getVertexNode_B() != ""){

        LinkedList<T>* vertexLinkedList = &checkListOfVertexNodes(newNode.getVertexNode_A());

        if(vertexLinkedList != nullptr){

            bool dataExists = checkNetworkConnections(newNode.getVertexNode_A(), newNode.getVertexNode_B(), *vertexLinkedList);

            if(!dataExists){
                vertexLinkedList->append(newNode);                      // adds connection to Node
            }
        }

        else{
            LinkedList<T> newLinkedLinkedList;
            newLinkedLinkedList.append(newNode);
            graph.append(newLinkedLinkedList);                      // add this LinkedLinkedList to graph
        }
    }

    else{
        //cout << newNode.getVertexNode_A();
    }
}

template<class T>
LinkedList<T> & Graph<T>::checkListOfVertexNodes(const string &vertexValue) {
    Node< LinkedList<T> >* currentLinkedList = graph.getLinkedList_head();

    while(currentLinkedList != nullptr){
        if(currentLinkedList->getData()->getLinkedList_head()->getData()->getVertexNode_A() == vertexValue){
            return *(currentLinkedList->getData());
        }
        currentLinkedList = currentLinkedList->getNextNode();
    }

    LinkedList<T> *temp_val = nullptr;
    return *temp_val;
}

template<class T>
bool Graph<T>::checkNetworkConnections(const string& vertex_A, const string& vertex_B, const LinkedList<T>& aNetworkLinkedList){
    auto tempIterator = aNetworkLinkedList;
    tempIterator.resetIterator();

    while(tempIterator.iteratorIsValid()){
        if(tempIterator.getIterator().getVertexNode_A() == vertex_B){
            return true;
        }
        tempIterator.iterateForward();
    }
    return false;
}

template<class T>
LinkedList<T> Graph<T>::getAllNodes(const string& aVertex){

    Node< LinkedList<T> >* currentLinkedList = graph.getLinkedList_head();
    LinkedList<T> graphVertex = LinkedList<T>();
    currentLinkedList->getData()->resetIterator();

    while(currentLinkedList != nullptr){
        currentLinkedList->getData()->resetIterator();
        while(currentLinkedList->getData()->iteratorIsValid()){
            if(currentLinkedList->getData()->getIterator().getVertexNode_A() == aVertex){
                graphVertex.append(currentLinkedList->getData()->getIterator());
            }

            currentLinkedList->getData()->iterateForward();
        }

        currentLinkedList = currentLinkedList->getNextNode();
    }

    return graphVertex;
}

template<class T>
void Graph<T>::printGraph(){

    Node< LinkedList<T> >* currentLinkedList = graph.getLinkedList_head();

    cout << "----------------------------- Format: Vertex (Weight) ------------------------------------" << endl << endl;
    while(currentLinkedList != nullptr){
        cout << currentLinkedList->getData()->getLinkedList_head()->getData()->getVertexNode_A() << " --> ";
        currentLinkedList->getData()->print();
        currentLinkedList = currentLinkedList->getNextNode();
        if(currentLinkedList != nullptr){
            cout << endl;
        }
    }
    cout << "------------------------------------------------------------------------------------------- " << endl;
}

template<class T>
void Graph<T>::printMatrix(){
    cout << "----------------------------- Format: Vertex(Weight) ------------------------------------" << endl << endl;
    Node< LinkedList<T> >* tempLinkedList = graph.getLinkedList_head();
    int counter = 1;
    cout << "    " << std::setw(3) << std::left << "";
    while(tempLinkedList != nullptr){
        cout << std::setw(4) << std::left << tempLinkedList->getData()->getLinkedList_head()->getData()->getVertexNode_A() ;
        tempLinkedList = tempLinkedList->getNextNode();
        if(tempLinkedList != nullptr){
            counter++;
        }
    }
    cout << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

    Node< LinkedList<T> >* currentLinkedList = graph.getLinkedList_head();

    while(currentLinkedList != nullptr){
        cout << std::setw(4) << std::left << currentLinkedList->getData()->getLinkedList_head()->getData()->getVertexNode_A() << "|  ";
        currentLinkedList->getData()->printMatrix(counter);
        currentLinkedList = currentLinkedList->getNextNode();
        if(currentLinkedList != nullptr){
            cout << endl;
        }
    }
    cout << "------------------------------------------------------------------------------------------- " << endl;

}


#endif //ALGORITHMS_GRAPH_H
