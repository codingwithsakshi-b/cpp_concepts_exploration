// main.cpp
#include "file1.cpp"
#include "file2.cpp"

int main() {
    cout << "Accessing extern variable 'score' from file2: " << score << endl;
    printScore();
    return 0;
}