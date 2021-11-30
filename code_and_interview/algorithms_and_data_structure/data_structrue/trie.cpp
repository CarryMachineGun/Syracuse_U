#include <iostream>
#include <vector>

using namespace std;


class TrieNode{
private:
    bool is_end;
    vector<TrieNode*> next;
public:
    TrieNode(){
        next = vector<TrieNode*>(26);
        is_end = false;
        return;
    }
    
    bool containNext(char c){
        return next[(int)(c-'a')] != nullptr;
    }
    
    TrieNode* getNext(char c){
        return next[(int)(c-'a')];
    }
    
    void setNext(char c, TrieNode* next_node){
        delete next[(int)(c-'a')];
        next[(int)(c-'a')] = next_node;
        return;
    }
    
    bool isEnd(){
        return is_end;
    }
    
    void setEnd(){
        is_end = true;
        return;
    }
};


class Trie {


private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
        return;
    }
    
    ~Trie(){
        delete root;
        return;
    }
    
    void insert(string word) {
        TrieNode* curr = root;
        
        for(char c : word){
            if(!curr->containNext(c)) curr->setNext(c, new TrieNode());
            
            curr = curr->getNext(c);
        }
        
        curr->setEnd();
        
        return;
    }
    
    TrieNode* searchPrefix(string prefix){
        TrieNode* curr = root;
        
        for(char c : prefix){
            if(!curr->containNext(c)) return nullptr;
            
            curr = curr->getNext(c);
        }

        return curr;
    }
    
    bool search(string word) {
        TrieNode* end = searchPrefix(word);
        if(!end) return false;
        
        return end->isEnd();
    }
    
    bool startsWith(string prefix) {
        return searchPrefix(prefix) != nullptr;
    }
};


int main(){


    return 0;
}