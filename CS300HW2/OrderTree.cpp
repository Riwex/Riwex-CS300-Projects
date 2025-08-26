//
// Created by lorda on 8/5/2025.
//
#include "OrderTree.h"
#include <iostream>
#include <ios>
using namespace std;
#include <vector>
#include <string>
#include <algorithm>

OrderTree::OrderTree() {

}
static void clearTree(OrderTree::Node* n){
    if(!n) return;
    clearTree(n->left);
    clearTree(n->right);
    delete n;
}
OrderTree::~OrderTree(){ clearTree(root); }

bool playerExists(OrderTree::Node* node, const std::string& name) {
    if (!node) return false;


    return std::find(node->players.begin(), node->players.end(), name) != node->players.end();
}
bool OrderTree::insert(int score, const string& player) {

return insertHelper(root, score, player);
}

bool OrderTree::insertHelper(Node*& node, int score, const string& player) {
    if (node == nullptr) {
        node = new Node(score, player);

        return true;
    }

    if (score == node->score) {
        auto it = std::lower_bound(node->players.begin(), node->players.end(), player);
        if (it != node->players.end() && *it == player) {
            std::cout << "Duplicate entry.\n";

            return false;
        }
        node->players.insert(it, player);
        return true;
    }

    bool changed;
    if (score < node->score) changed = insertHelper(node->left, score, player);
    else                     changed = insertHelper(node->right, score, player);

    update(node);
    node = rebalance(node);
    return changed;

}
OrderTree::Node* OrderTree::removeHelper(Node* node, int score, const std::string& player, bool& removed){
    if(!node) return nullptr;

    if(score < node->score){
        node->left = removeHelper(node->left, score, player, removed);
    } else if(score > node->score){

        node->right = removeHelper(node->right, score, player, removed);
    } else {


        auto it = std::lower_bound(node->players.begin(), node->players.end(), player);
        if(it == node->players.end() || *it != player){
            return node;
        }
        node->players.erase(it);
        removed = true;

        if(node->players.empty()){
            // delete this score node
            if(!node->left || !node->right){
                Node* child = node->left ? node->left : node->right;
                delete node;
                return child;
            } else {
                Node* pred = node->left;
                while(pred->right) pred = pred->right;
                node->score   = pred->score;
                node->players = pred->players;
                bool dummy=false;
                node->left = removeNodeByScore(node->left, pred->score, dummy);
            }
        }
    }
    update(node);
    return rebalance(node);
}

OrderTree::Node* OrderTree::removeNodeByScore(Node* node, int score, bool& removed){
    if(!node) return nullptr;
    if(score < node->score){
        node->left = removeNodeByScore(node->left, score, removed);
    } else if(score > node->score){
        node->right = removeNodeByScore(node->right, score, removed);
    } else {
        removed = true;
        if(!node->left || !node->right){
            Node* child = node->left ? node->left : node->right;
            delete node;
            return child;
        } else {
            Node* pred = node->left;
            while(pred->right) pred = pred->right;
            node->score   = pred->score;
            node->players = pred->players;
            bool dummy=false;
            node->left = removeNodeByScore(node->left, pred->score, dummy);
        }
    }
    update(node);
    return rebalance(node);
}


bool OrderTree::remove(int score, const std::string& player) {
    bool removed = false;
    root = removeHelper(root, score, player, removed);
    if(!removed) std::cout << "Not found.\n";
    return removed;
}


static void printScoreWithPlayers(const OrderTree::Node* n) {
    cout << n->score << " : ";
    for (size_t i = 0; i < n->players.size(); ++i) {
        if (i) cout << ", ";
        cout << n->players[i];
    }
    cout << "\n";
}

std::vector<std::string> OrderTree::find(int score) const {
    Node* curr = root;
    while (curr) {
        if (score == curr->score) return curr->players;
        curr = (score < curr->score) ? curr->left : curr->right;
    }
    return {};


}

int OrderTree::findMin() const {
    if(!root) return -1;
    Node* curr = root;
    while(curr->left) curr = curr->left;


    return curr->score;
}
int OrderTree::findMax() const {
    if(!root) return -1;
    Node* curr = root;
    while(curr->right) curr = curr->right;
    return curr->score;
}


const OrderTree::Node* OrderTree::kthLargestDFS(const Node* n, int k, int& seen) const {
    if (!n) return nullptr;

    if (auto r = kthLargestDFS(n->right, k, seen)) return r;

    if (++seen == k) return n;


    return kthLargestDFS(n->left, k, seen);
}

int OrderTree::findKthLargest(int k) const {

    int total = nodeCount();                 // count of distinct score nodes
    if (k < 1 || k > total) return -1;       // your command layer should print the error

    int seen = 0;
    const Node* ans = kthLargestDFS(root, k, seen);

    return ans ? ans->score : -1;

}

int OrderTree::countNodes(Node* node) const {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}
int OrderTree::nodeCount() const {
    return countNodes(root);
}

bool OrderTree::rankDFS(Node* node, int score, int& rank) const {
     if(!node) return false;
     if(rankDFS(node->right, score, rank)) return true;
     ++rank;
     if(node->score == score) return true;


     return rankDFS(node->left, score, rank);
}
int OrderTree::rankOf(int score) const {
        int rank = 0;
    if(!rankDFS(root, score, rank)) return -1; // caller prints "Not found."
    return rank;
}

int OrderTree::countPlayers(Node* node) const {
    if(!node) return 0;
    return (int)node->players.size() + countPlayers(node->left) + countPlayers(node->right);
}
int OrderTree::size() const { return countPlayers(root); }

int OrderTree::height() const { return H(root); }

void OrderTree::printDesc(Node* n) const {
    if(!n) return;
    printDesc(n->right);
     printScoreWithPlayers(n);
     printDesc(n->left);
}
void OrderTree::printInOrder() const { printDesc(root); }

void OrderTree::update(Node* n){
      if(!n) return;
     n->height = 1 + std::max(H(n->left), H(n->right));
}


int OrderTree::balanceFactor(Node* n) const {
    return H(n->left) - H(n->right);
}

OrderTree::Node* OrderTree::rotateRight(Node* y){
    Node* x  = y->left;
    Node* T2 = x->right;
      x->right = y;
      y->left  = T2;
      update(y);
    update(x);
    return x;
}
OrderTree::Node* OrderTree::rotateLeft(Node* x){
    Node* y  = x->right;
    Node* T2 = y->left;
    y->left  = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}
OrderTree::Node* OrderTree::rebalance(Node* n){
    if(!n) return n;
    int bf = balanceFactor(n);                  // <-- member call
    if(bf > 1){
        if(balanceFactor(n->left) < 0)          // <-- member call
            n->left = rotateLeft(n->left);
        return rotateRight(n);
    } else if(bf < -1){
        if(balanceFactor(n->right) > 0)         // <-- member call
            n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}


