//CIS554 HW6. Due: 11:59pm, Saturday, Dec. 11.

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;


class Circuit {//Truth Table
public:
int input_length;
int output_length;
int offset;
unordered_map<string, string> data;

Circuit(){
    offset = 0;
    input_length = 0;
    output_length = 0;
    data = unordered_map<string, string>();
}

void setOffset(){
    string key(input_length, '0');

    key[0] = '1';

    for(int i = 1; i < key.size(); i++){
        key[i] = '1';
        key[i-1] = '0';

        if(data[key] != null)
    }

}

bool operator==(const Circuit &M2) const;

};

bool Circuit::operator==(const Circuit &M2) const{
    if((input_length != M2.input_length) || (output_length != M2.output_length)) return false;

    //the postion of 1 is found based on 1XXXXXXX;

    unordered_map<string, string> map1 = data,  map2 = M2.data;

    for(auto i = map1.begin(); i != map1.end(); i++){
        string key = i->first;

        if(map1[key] != map2[key]) return false;
    }

	return true;

}

class myHashEqualClass
{
public:
	size_t operator()(Circuit &M1) const;
};

// size_t myHashEqualClass::operator()(const map<list<set<int *, myCompareClass> *> *, vector<int *> *, myCompareClass> &M) const
size_t myHashEqualClass::operator()(Circuit &M1) const
{
    return 0;
}

int main(){
//Declare you DB of type unordered_map< â€¦,â€¦> DB;

//Declare DB
//Read inuts from file "circuits.txt" and store them to DB by
//adding circuits one by one to DB as follows:
//DB[key] = value;

//When adding a circuit, if a duplicate is detected, your program will print a message "The circuit is already in DB."

//You should support cout <<DB << endl; You will need to overload operator<<
//You need to support find function to see if a given circuit is in the DB


return 0;
}



// //input circuits in file circuits.txt

// //
// 16//number of circuits
// 3//number of inputs; the number of rows will be 2^(number of inputs)
// 2//number of outputs
// 000 10
// 001 00
// 010 00
// 011 10
// 100 00
// 101 11
// 110 01
// 111 11
// 4
// 1
// 0000 0
// 0001 1
// 0010 0
// â€¦