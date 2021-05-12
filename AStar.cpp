#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>

#include "Node.h"

using namespace std;

struct CompareCost {
    bool operator() (Node const *n1, Node const *n2) {
        return n1->score > n2->score;
    }
};

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Correct usage:\n" << endl << argv[0] << " [start state]" << endl;
        return 1;
    }

    int iter = 0;

    Node* start = new Node(argv[1], "NONE");
    // wwwwwwwwwbbbbbbbbbooooooooogggggggggrrrrrrrrryyyyyyyyy (in case you change the below for debugging purposes)
    Node* end = new Node("wwwwwwwwwbbbbbbbbbooooooooogggggggggrrrrrrrrryyyyyyyyy", "NONE");

    priority_queue<Node*, vector<Node*>, CompareCost> *pc = new priority_queue<Node*, vector<Node*>, CompareCost>();
    pc->push(start);

    unordered_map<string, Node*> *visited = new unordered_map<string, Node*>();
    visited->emplace(start->Hash(), start);

    Node* curr = pc->top();

    int MAX_DEPTH = 2;

    queue<Node*> *waiting = new queue<Node*>();

    while (!curr->Equals(end)) {

        pc->pop();
        iter++;

        if (iter % 10000 == 0) {
            cout << iter << " (" << curr->score << ", " << curr->depth <<") " <<": " << curr->Hash() << endl;
        }

        vector<Node*> succ = curr->Successors(end);

        for (Node* n : succ) {
            if (visited->find(n->Hash()) == visited->end()) {
                if (n->depth <= MAX_DEPTH) {
                    pc->push(n);
                } else {
                    waiting->push(n);
                }
                
                visited->emplace(n->Hash(), n);

                if (n->Equals(end)) {
                    curr = n;
                    break;
                }
            }
        }

        if (curr->Equals(end)) {
            break;
        }

        if (pc->empty()) {
            while (!waiting->empty()) {
                pc->push(waiting->front());
                waiting->pop();
            }
            MAX_DEPTH++;
        }

        curr = pc->top();
        
    }

    if (curr->Equals(end)) {
        stack<Node*> path;
        path.push(curr);
        while (curr->parent != nullptr) {
            curr = curr->parent;
            path.push(curr);
        }

        while (!path.empty()) {
            curr = path.top();
            cout << curr->action.c_str() << endl;
            path.pop();
        }
    } else {
        cout << "No solution!" << endl;
    }

    return 0;
}