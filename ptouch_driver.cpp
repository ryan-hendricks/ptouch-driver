
#include "ptouch-driver.h"

void ptouch_driver() {
    libusb_init(NULL);
    libusb_exit(NULL);
}

/*
 * ptouch-direct.c
 *
 *  Created on: Mar 27, 2016
 *      Author: vegetables
 */

#include "ptouch-direct.h"

#include "libusb.h"
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

int ptouch_find_devices(libusb_device *ptouch_device_result) {
    /* Poll usb devices and parse for known P-touch Devices
     * Currently only QL-700 is supported because its all I own
     */
    return 0;
}

libusb_device_handle * ptouch_open_QL700() {
    return libusb_open_device_with_vid_pid(NULL, 0x04F9, 0x2042);
}

void ptouch_printanerror(char * error_description, int error_bool) {
    printf("%s: ",error_description);
    if(error_bool) printf("True"); else printf("False");
}

void ptouch_show_status(struct ptouch_info * current_info) {





    printf("P-Touch Current Status Received:\n");
    char media_type[32];
    if(current_info->media_type==0x00) strcpy(media_type,"No Media");;
    if(current_info->media_type==0x0A) strcpy(media_type,"Continuous Length Tape");
    if(current_info->media_type==0x0B) strcpy(media_type, "Die-cut labels");
    printf("Media Type: \%s\n",media_type);
    printf("Media Width: %dmm\n", current_info->media_width);

    printf("---Error Status---\n");
    uint8_t error1 = current_info->error_byte_1;
    ptouch_printanerror("No media when printing", error1 & ptouch_nomedia_mask);


}
int ptouch_get_status(libusb_device_handle *p_handle, struct ptouch_info * ptouch_info_return) {
    printf("Getting Current Status...\n");
    int err, bytes_transferred;
    err = libusb_bulk_transfer(p_handle, 0x02, ptouch_getstatus, 3,
            &bytes_transferred, LIBUSB_DEFAULT_TIMEOUT);
    if(err) printf("Send Error!\n");
    if(bytes_transferred != sizeof(ptouch_getstatus)) {
        printf("Not all bytes transferred.\n");
        return 1;
    }
    err = libusb_bulk_transfer(p_handle, 0x81, ptouch_info_return->raw_data, 32, &bytes_transferred, LIBUSB_DEFAULT_TIMEOUT);
    ptouch_info_return->media_width = ptouch_info_return->raw_data[10];
    ptouch_info_return->media_type = ptouch_info_return->raw_data[11];
    ptouch_info_return->media_length = ptouch_info_return->raw_data[17];
    ptouch_info_return->error_byte_1 = ptouch_info_return->raw_data[8];
    ptouch_info_return->error_byte_2 = ptouch_info_return->raw_data[9];
    ptouch_info_return->status_type = ptouch_info_return->raw_data[18];
    ptouch_info_return->phase_type = ptouch_info_return->raw_data[19];


    return 0;
}

int ptouch_driver() {

//	libusb_device *ql700;
    libusb_device_handle *ql700_handle;
    int r,err;
    r = libusb_init(NULL);
    if (r < 0)
        return r; //Library initialization failed!

    ql700_handle = ptouch_open_QL700();

    if (ql700_handle == NULL) {
        printf("Could not find QL-700. Exiting.\n");
        return 1; //switch to an actual error?
    }
//	ql700 = libusb_get_device(ql700_handle);
    printf("Found QL-700. Requesting current status...\n");
    //	err = libusb_get_active_config_descriptor(ql700, &ql700_config);
    //	if(err) return err; //We tried
    //Is the kernel driver active?
    r = libusb_set_auto_detach_kernel_driver(ql700_handle, 1);
    err = libusb_claim_interface(ql700_handle, 0);
    if (err) {
        printf("Error Claiming Interface.\n");
        libusb_close(ql700_handle);
        libusb_exit(NULL);
        return err;
    }
    // ** Finally, we can do direct I/O
    struct ptouch_info current_info;
    ptouch_get_status(ql700_handle, &current_info);
    ptouch_show_status(&current_info);
//	int transferred_bytes;
//	uint8_t invalid = 0x00; //Used to clear bad data
//	uint8_t initialize[] = { 0x1B, 0x40 };
//	uint8_t getstatus[] = { 0x1B, 0x69, 0x53 };
//	uint8_t returned_status[32];
//	for (int i = 0; i < 200; i++)
//		libusb_bulk_transfer(ql700_handle, 0x02, &invalid, 1,
//				&transferred_bytes, 1000);
//	err = libusb_bulk_transfer(ql700_handle, 0x02, initialize,
//			sizeof(initialize), &transferred_bytes, 1000);
//	err = libusb_bulk_transfer(ql700_handle, 0x02, getstatus, sizeof(getstatus),
//			&transferred_bytes, 1000);
//	err = libusb_bulk_transfer(ql700_handle, 0x81, returned_status, 32,
//			&transferred_bytes, 1000);
//
//	uint8_t print_information[] = { 0x1B, 0x69, 0x7A, 0x40, 0x0A, 0x3E, 0x00,
//			0x77, 0x02, 0x00, 0x00, 0x00, 0x00 };
//	libusb_bulk_transfer(ql700_handle, 0x02, print_information, 13,
//			&transferred_bytes, 1000);
//	FILE *testfile = fopen("/home/vegetables/Postscript/ql700_test.bits", "r");
//	if (testfile == NULL)
//		printf("Null file.\n");
//	uint8_t currentline[90];
//	uint8_t rastertransfer[] = { 0x67, 0x00, 90 };
//	uint8_t rastertransfer_lastline[] = { 0x67, 0xFF, 90 };
//	uint8_t print_label[] = { 0x1A };
//	for (int i = 0; i < 630; i++) {
//		int j = fread(currentline, 1, 90, testfile);
//		libusb_bulk_transfer(ql700_handle, 0x02, rastertransfer, 3,
//				&transferred_bytes, 1000);
//		libusb_bulk_transfer(ql700_handle, 0x02, currentline, 90,
//				&transferred_bytes, 1000);
//		printf("Line %d: File Bytes Read: %d, Transferred Bytes: %d\n", i + 1,
//				j, transferred_bytes);
//
//	}
//	fread(currentline, 1, 90, testfile);
//	libusb_bulk_transfer(ql700_handle, 0x02, rastertransfer_lastline, 3,
//			&transferred_bytes, 1000);
//	libusb_bulk_transfer(ql700_handle, 0x02, currentline, 90,
//			&transferred_bytes, 1000);
//	libusb_bulk_transfer(ql700_handle, 0x02, print_label, 1, &transferred_bytes,
//			1000);
//	//	sleep(5);
//	err = libusb_bulk_transfer(ql700_handle, 0x02, getstatus, sizeof(getstatus),
//			&transferred_bytes, 1000);
//	err = libusb_bulk_transfer(ql700_handle, 0x81, returned_status, 32,
//			&transferred_bytes, 1000);
//	printf("Status bytes from QL-700: ");
//	for (int i = 0; i < 32; i++) {
//		printf("Status Byte %d: %X\n", i + 1, returned_status[i]);
//	}
//
//	err = libusb_bulk_transfer(ql700_handle, 0x81, returned_status, 32,
//			&transferred_bytes, 1000);
//	printf("Status bytes from QL-700: ");
//	for (int i = 0; i < 32; i++) {
//		printf("Status Byte %d: %X\n", i + 1, returned_status[i]);
//	}
//	err = libusb_bulk_transfer(ql700_handle, 0x81, returned_status, 32,
//			&transferred_bytes, 1000);
//	printf("Status bytes from QL-700: ");
//	for (int i = 0; i < 32; i++) {
//		printf("Status Byte %d: %X\n", i + 1, returned_status[i]);
//	}
//
//	fclose(testfile);
    libusb_release_interface(ql700_handle, 0);

    libusb_close(ql700_handle);

    libusb_exit(NULL);
    return 0;
}


