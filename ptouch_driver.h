#ifndef PTOUCHDRIVER_H
#define PTOUCHDRIVER_H

#include <libusb-1.0/libusb.h>
/* Define all Brother specific communication symbols */
#define at_symbol 0x40

char ptouch_invalid[] = {0x00}; //00 H {All zeroes binary}
char ptouch_init[] = {0x1B, 0x40}; //ESC+@
unsigned char ptouch_getstatus[] = {0x1B, 0x69, 0x53}; //ESC+i+s
const char ptouch_command_mode_switch[] = {0x1B, 0x69, 0x61}; //ESC+i+a
const char ptouch_print_information[] = {0x1B, 0x69, 0x7A}; //ESC+i+z
const char ptouch_set_mode[] = {0x1B, 0x69, 0x4D}; //ESC+i+M
const char ptouch_cut_every[] = {0x1B, 0x69, 0x41}; //ESC+i+a
const char ptouch_set_extended_mode[] = {0x1B, 0x69, 0x4B}; //ESC+i+K
const char ptouch_set_margin[] = {0x1B, 0x69, 0x64}; //ESC+i+d
const char ptouch_set_compression[] = {0x4D}; //M
const char ptouch_raster_graphics_transfer[] = {0x67}; //g
const char ptouch_zero_raster[] = {0x5A}; //Z
const char ptouch_print_command[] = {0x0C};
const char ptouch_print_feeding_command[] = {0x1A}; //Ctrl-Z
const char ptouch_baudrate_set[] = {0x1B, 0x69, 0x42}; //ESC+i+b

int ptouch_find_device(libusb_device *ptouch_device_result);

struct ptouch_info {
    uint8_t raw_data[32];
    char printer_type[32];
    uint8_t media_width;
    uint8_t media_type;
    uint8_t media_length;
    uint8_t error_byte_1;
    uint8_t error_byte_2;
    uint8_t status_type;
    uint8_t phase_type;
    uint8_t phase_high;
    uint8_t phase_low;
    uint8_t notification_number;

};


void ptouch_show_status(struct ptouch_info * current_info);
#endif // PTOUCHDRIVER_H
