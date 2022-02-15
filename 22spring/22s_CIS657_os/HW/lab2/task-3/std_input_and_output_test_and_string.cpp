#include <iostream>


using namespace std;

int main(int argc, char *argv[]){
    cout << argc << endl;

    char *str = argv[1];

    printf("%s\n", str);

    cout << (char*)(argv[1]) << endl;

    cout << argv[1][2] << endl;

    cout << str << endl;


    int arr[] = {1,2,3,4,5};

    cout << arr << endl;

    char s1[] = "string";
    
    cout << s1 << endl;

    char s2[] = {'s', 't', 'r', 'i', 'n', 'g'};
    
    cout << s2 << endl;
    cout << (s2[6] == '\0') << endl;

    return argc;
}