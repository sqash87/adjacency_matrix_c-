#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;
// location of the head & tail don't change while addinng nodes to the list.
class List
{
public:
    
    struct Node
    {
        Node* next;
        Node* prev;
        int data;
        Node (int d=0, Node* p= nullptr, Node* n= nullptr)
        {
            data= d;
            next= n;
            prev= p;
    
        }
    };
    
    Node* head;
    Node* tail;
    void createsource(int source);
    void createdest(int dest, int tail_vec_pos, Node* tail);
    void addedge(int source, int dest);
    vector<Node*>Heads; // vector contains the heads
    vector<Node*>Tails;  // vector contains the tails.
    void print();
};

void List::addedge(int source, int dest)
{
    int vec_size=0;
    while(vec_size<Heads.size())
    {
        if (source==Heads[vec_size]->next->data)
        {
            Node* tail= Tails[vec_size];
            createdest(dest,vec_size,tail);
            break;
        }
        vec_size++;
    }
    if (vec_size==Heads.size()) // if the source can't be found, creating source and destination.
    {
        createsource(source);
        int tail_vec_pos= Tails.size()-1; // tail_vec_pos is needed to pull out the right tail from the Tails vector. Since the one tail was just created, the recent tail vector position is going to be size()-1.
        Node* tail= Tails[tail_vec_pos]; // Since the one tail was just created, the recent tail vector position is going to be size()-1.
        createdest(dest, tail_vec_pos, tail);
    }
}
void List::createsource(int source)
{
    head= new Node;
    Heads.push_back(head);
    tail= new Node;
    Tails.push_back(tail);
    head->next= tail;
    tail->prev= head;
    Node* newnode = new Node (source, head, tail);
    tail->prev->next= newnode;
    tail->prev= newnode;
}

void List::createdest(int dest, int tail_vec_pos, Node *tail)
{
    Node* ptr = Tails[tail_vec_pos]->prev;
    Node* newnode = new Node (dest,ptr,tail);
    tail->prev->next= newnode;
    tail->prev= newnode;
}


void List::print()
{
    int vec_size=0;
    while (vec_size<Heads.size())
    {
        for (Node* ptr= Heads[vec_size]->next; ptr!=Tails[vec_size]; ptr= ptr->next)
        {
            cout<< ptr->data ;
            cout<< "->" ;
        }
        cout<< " " << endl;
        vec_size++;
    }
    
    
}

int main()
{
    List lst;
    lst.addedge(1, 2);
    lst.addedge(2, 3);
    lst.addedge(1, 4);
    lst.addedge(2, 5);
    lst.addedge(1, 6);
    lst.addedge(3, 7);
    lst.addedge(2, 8);
    lst.addedge(3, 9);
    lst.addedge(4, 7);
    lst.print();
}

