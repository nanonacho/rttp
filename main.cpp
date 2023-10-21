# include "headers.h"
# include "iostream"

using namespace std;

int main(int argc, char const *argv[]) {
    Instance selectedInstance = readTxtInstance(argv[1]);
    selectedInstance.print();
    
    /*greedy(instance4);*/
    return 0;
}