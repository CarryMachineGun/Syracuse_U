#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;


template<class T> ostream &operator<<(ostream& str, list<T> l){
    for(T i : l){
        str << i << ", ";
    }

    return str;
} 


int main(){
    string in[]{"god", "cat", "act", "foo", "dog", "tac"};

    //shouldn't work as list<string> will be depicated and not the saem one
    unordered_map<string, list<string>> ret;

    for(string i : in){
        string key = i;
        sort(key.begin(), key.end());
        ret[key].push_back(i);
    }

    for(auto i = ret.begin(); i != ret.end(); i++){
        cout << i->second << endl;
    }

    return 0;
}

