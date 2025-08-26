//
// Created by lorda on 8/5/2025.
//

#ifndef ORDERTREE_H
#define ORDERTREE_H



#include <vector>
#include <string>
using namespace std;


class OrderTree {



public:
    struct Node {

        int score;
        vector<string> players;
        Node *left, *right;
        int height;

        Node(int s, const std::string& n)
    : score(s), left(nullptr), right(nullptr), height(1) {
            players.push_back(n);
        }


    };
    Node *root = nullptr;
    OrderTree();
    ~OrderTree();

    bool insert(int score, const string& player);
    bool insertHelper(Node*& node, int score, const std::string& name);

    bool remove(int score, const string& player); //remove the player from the score k
    vector<string> find(int score) const;
    int findMin() const;// finds the lowest score
    int findMax() const; //find the maximum score
    int findKthLargest(int k) const; //finds 1-indexed (i.e. k = 1 is the largest) maximum
    const Node* kthLargestDFS(const Node* n, int k, int& seen) const;
    int countNodes(Node* node) const;

    int rankOf(int score) const;// 1-indexed
    int nodeCount() const; //Number of distinct score nodes
    int size() const; //total number of players
    int height() const; //tree height
    void printInOrder()const; // const; prints the values in order



private:
    Node* removeHelper(Node* node, int score, const std::string& player, bool& removed);
    Node* removeNodeByScore(Node* node, int score, bool& removed);
    int balanceFactor(Node* n) const;

    void printDesc(Node* n) const;
    int countPlayers(Node* node) const;

    bool rankDFS(Node* node, int score, int& rank) const;

    static int H(Node* x) { return x ? x->height : 0; }

    Node* rotateLeft(Node* x) ;
    Node* rotateRight(Node* y);
    Node* rebalance(Node* n) ;
    void update(Node* n);

};
#endif //ORDERTREE_H