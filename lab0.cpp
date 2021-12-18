#include <iostream>
#include <cstring>
using namespace std;

int main(int argc, char *argv[]) {
    int count = 1;
    if (argv[1][0] == ' ' || argv[1][0] == '\t' || argv[1][0] == '\n')
    {
        count = 0;
    }
    for (int i = 0; i < (strlen(argv[1]) - 1); ++i)
    {
        if (argv[1][i] == ' ' || argv[1][i] == '\t' || argv[1][i] == '\n')
        {
            if (!(argv[1][i + 1] == ' ' || argv[1][i + 1] == '\t' || argv[1][i + 1] == '\n'))
            {
                count++;
            }
        }
    }

    cout << "Number of words = " << count;
    return 0;
}
