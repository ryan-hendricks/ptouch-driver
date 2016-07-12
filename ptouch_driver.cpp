
#include "ptouch_driver.h"


/*
 * ptouch_driver.cpp
 *
 *  Created on: Mar 27, 2016
 *      Author: vegetables
 */


#include <libusb-1.0/libusb.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define LIBUSB_DEFAULT_TIMEOUT 1000

#define ptouch_nomedia_mask 			0x01
#define ptouch_enofmedia_mask_mask 		0x02
#define ptouch_tapecutterjam_mask 		0x04
#define ptouch_mainunitinuse_mask 		0x10
#define ptouch_fandoesntwork_mask 		0x80
#define ptouch_transmissionerror_mask 	0x04
#define ptouch_coveropenedwhileprinting 0x10
#define ptouch_cannotfeed_mask 			0x40
#define ptouch_systemerror_mask 		0x80



