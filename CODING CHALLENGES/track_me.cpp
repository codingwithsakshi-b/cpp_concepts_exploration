#include <iostream>
using namespace std;

// complete this function
void track()
{
    static int x = 0;
    x++;

    cout << "Called " << x << " times" << endl;
}

int main()
{
    track();
    track();
    track();
    return 0;
}