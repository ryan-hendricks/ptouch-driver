#include <iostream>
#include "main.h"
#include "ptouch_driver.h"
#include "ptouch_printer.h"
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    ptouch_printer * pp = new ptouch_printer();
    return 0;
}
