#include <iostream>
#include <list>
#include <vector>
using namespace std;



template <class T> ostream& operator<<(ostream& str, const vector<T>& V);
template <class T> ostream& operator<<(ostream& str, const vector<T *>& V);
template <class T> ostream& operator<<(ostream& str, const list<T>& L);
template <class T> ostream& operator<<(ostream& str, const list<T *>& L);
void DB1_to_DB2(vector<list<int>>& DB1, list<vector<int>*>& DB2);
void DB2_to_DB3(list<vector<int>*>& DB2, list<list<int*>*> &DB3);
int main() {

	vector<list<int>> DB1{ {1,2,3}, {4,5}, {6,7,8,9} };
	cout << DB1 << endl;

	list<vector<int>*>  DB2;
	DB1_to_DB2(DB1, DB2);
	cout << DB2 << endl;

	list<list<int*>*> DB3;
	DB2_to_DB3(DB2, DB3);
	cout << DB3 << endl;

	return 0;
}


void DB2_to_DB3(list<vector<int>*>& DB2, list<list<int*>*>& DB3) {
    for(list<int*>* i : DB3){
        for(int* j : *i){
            delete j;
        }
        delete i;
    }

    DB3.clear();

    for(vector<int>* &i : DB2){
        list<int*>* l = new list<int*>;
        for(int j : *i){
            l->push_back(new int(j));
        }        
        DB3.push_back(l);
    }

    return;
}

void DB1_to_DB2(vector<list<int>>& DB1, list<vector<int>*>& DB2) {
    for(auto& i : DB2){
        delete i;  
    }

    DB2.clear();

    for(list<int>& i : DB1){
        vector<int>* v = new vector<int>;
        for(int j : i){
            v->push_back(j);
        }
        DB2.push_back(v);
    }

    return;
}


template <class T> ostream& operator<<(ostream& str, const vector<T>& V) {
	str << "[ ";
	for (auto& i : V) { str << i << " "; }
	str << "]";
	return str;
}
template <class T> ostream& operator<<(ostream& str, const vector<T*>& V) {

	str << "[ ";
	for (auto& i : V) { str << *i << " "; }
	str << "]";
	return str;
}
template <class T> ostream& operator<<(ostream& str, const list<T>& L) {

	str << "< ";
	for (auto& i : L) { str << i << " "; }
	str << ">";
	return str;

}



template <class T> ostream& operator<<(ostream& str, const list<T*>& L) {

	str << "< ";
	for (auto& i : L) { str << *i << " "; }
	str << ">";
	return str;

}