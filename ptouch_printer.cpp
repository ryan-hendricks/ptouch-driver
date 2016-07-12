#include "ptouch_printer.h"
#include <iostream>
#include <iterator>
using namespace std;

ptouch_printer::ptouch_printer()
{
    std::map <char, string>::iterator it;
    //Setup maps for status response
    printer_type[0x35] = "QL-700";
    it = printer_type.find(0x35);
    std::cout << it->second << endl;
}

void ptouch_printer::ptouch_find_printers() {

}

void ptouch_printer::ptouch_connect_QL700() {
    libusb_init(NULL); //Initialize libusb library

}
