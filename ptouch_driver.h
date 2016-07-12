#ifndef PTOUCHDRIVER_H
#define PTOUCHDRIVER_H

#include <libusb-1.0/libusb.h>
/* Define all Brother specific communication symbols */
#define at_symbol 0x40

const char ptouch_invalid[1] = {0x00}; //00 H {All zeroes binary}
const char ptouch_init[2] = {0x1B, 0x40}; //ESC+@
const char ptouch_getstatus[] = {0x1B, 0x69, 0x53}; //ESC+i+s
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


#endif // PTOUCHDRIVER_H
