// file2.cpp
#include <iostream>
using namespace std;

// 👇 extern variable declaration (memory already allocated in file1.cpp)
extern int score;

// 👇 extern function declaration (function body in file1.cpp)
extern void printScore();

