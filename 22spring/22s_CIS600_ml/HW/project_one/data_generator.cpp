#include <iostream>
#include <string>
#include <fstream>

using namespace std;


ofstream fout;

void generateData(int size, int max){

    for(int i = 0; i < size; i++){
        int x = rand() % max;
        int y = rand() % max;
        fout << x << " " << y << endl;
    }

    return;
}

int main(){
    srand(time(NULL));
    fout = ofstream("data.txt");

    generateData(100, 5000);

    fout.close();

    return 0;
}