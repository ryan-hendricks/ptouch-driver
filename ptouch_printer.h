#ifndef PTOUCH_PRINTER_H
#define PTOUCH_PRINTER_H

#include <libusb-1.0/libusb.h>
#include <map>
#include <string>

class ptouch_printer
{
private:
    libusb_device_handle * printer_handle;
    std::map <char,std::string> printer_type;
public:
    ptouch_printer();
    void ptouch_find_printers();
    void ptouch_connect_QL700();
};

#endif // PTOUCH_PRINTER_H
