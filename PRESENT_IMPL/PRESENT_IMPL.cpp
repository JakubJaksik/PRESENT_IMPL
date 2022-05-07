#include <iostream>
#include "present.h"

using namespace std;

int main()
{
    present *cipher = new present();
    unsigned __int64 plaintext;
    plaintext = 0x0;
    unsigned __int8 key[8]={0,0,0,0,0,0,0,0};

    string ret = cipher->encrypt(&plaintext, key);
    cout << ret;

    std::cout << "Hello World!\n";
}
