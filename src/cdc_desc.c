/***********************************************************************
* $Id:: cdc_desc.c 211 2011-06-17 21:34:04Z usb06052                          $
*
* Project: USB device ROM Stack test module
*
* Description:
*     USB Communication Device Class User module.
*
***********************************************************************
*   Copyright(C) 2011, NXP Semiconductor
*   All rights reserved.
*
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/

#include <string.h>
#include "mw_usbd.h"
#include "mw_usbd_rom_api.h"
#include "app_usbd_cfg.h"


#ifdef __GNUC__
#define ALIGN4 __attribute__ ((aligned(4)))
#else // Keil
#define ALIGN4 __align(4)
#endif

/* USB Standard Device Descriptor */
ALIGN4 const uint8_t VCOM_DeviceDescriptor[] = {
  USB_DEVICE_DESC_SIZE,              /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(0x0200), /* 2.0 */           /* bcdUSB */
  0xEF,                              /* bDeviceClass Misc */
  0x02,                              /* bDeviceSubClass */
  0x01,                              /* bDeviceProtocol - Interface Association Descriptor */
  USB_MAX_PACKET0,                   /* bMaxPacketSize0 */
  WBVAL(0x257F),                     /* idVendor */
  WBVAL(0x0001),                     /* idProduct */
  WBVAL(0x0100), /* 1.00 */          /* bcdDevice */
  0x01,                              /* iManufacturer */
  0x02,                              /* iProduct */
  0x03,                              /* iSerialNumber */
  0x01                               /* bNumConfigurations: one possible configuration*/
};

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
ALIGN4 const uint8_t VCOM_ConfigDescriptor[] = {
/* Configuration 1 */
  USB_CONFIGUARTION_DESC_SIZE,       /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(                             /* wTotalLength */
    1*USB_CONFIGUARTION_DESC_SIZE +

    1*0x08 + /* IAD size */
    1*USB_INTERFACE_DESC_SIZE     +  /* communication interface */
    0x0013                        +  /* CDC functions */
    1*USB_ENDPOINT_DESC_SIZE      +  /* interrupt endpoint */

    1*USB_INTERFACE_DESC_SIZE     +  /* data0 interface */
    2*USB_ENDPOINT_DESC_SIZE      +  /* bulk endpoints */


    1*0x08 + /* IAD size */
    1*USB_INTERFACE_DESC_SIZE     +  /* communication interface */
    0x0013                        +  /* CDC functions */
    1*USB_ENDPOINT_DESC_SIZE      +  /* interrupt endpoint */

    1*USB_INTERFACE_DESC_SIZE     +  /* data1 interface */
    2*USB_ENDPOINT_DESC_SIZE         /* bulk endpoints */

  ),
  0x04,                              /* bNumInterfaces */
  0x01,                              /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                              /* iConfiguration: no string to describe this configuration */
  USB_CONFIG_BUS_POWERED /*|*/       /* bmAttributes */
/*USB_CONFIG_REMOTE_WAKEUP*/,
  USB_CONFIG_POWER_MA(50),          /* bMaxPower, device power consumption is 100 mA */

  /* IAD 1 Descriptor */
  0x08,                              /* sizeof(USB_IAD_DSC) */
  0x0B,                              /* Interface assocication descriptor type */
  0x00,                              /* The first associated interface */
  0x02,                              /* Number of contiguous associated interfaces */
  CDC_COMMUNICATION_INTERFACE_CLASS, /* bInterfaceClass: Communication Interface Class */
  CDC_ABSTRACT_CONTROL_MODEL,        /* bInterfaceSubClass: Abstract Control Model */
  0x00,                              /* bInterfaceProtocol: no protocol used */
  0x04,                              /* iInterface: */


/* Interface 0, Alternate Setting 0, Communication class interface descriptor */
  USB_INTERFACE_DESC_SIZE,           /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType */
  USB_CDC_CIF_NUM,                   /* bInterfaceNumber: Number of Interface */
  0x00,                              /* bAlternateSetting: Alternate setting */
  0x01,                              /* bNumEndpoints: One endpoint used */
  CDC_COMMUNICATION_INTERFACE_CLASS, /* bInterfaceClass: Communication Interface Class */
  CDC_ABSTRACT_CONTROL_MODEL,        /* bInterfaceSubClass: Abstract Control Model */
  0x00,                              /* bInterfaceProtocol: no protocol used */
  0x04,                              /* iInterface: */
/*Header Functional Descriptor*/
  0x05,                              /* bLength: Endpoint Descriptor size */
  CDC_CS_INTERFACE,                  /* bDescriptorType: CS_INTERFACE */
  CDC_HEADER,                        /* bDescriptorSubtype: Header Func Desc */
  WBVAL(CDC_V1_10), /* 1.10 */       /* bcdCDC */
/*Call Management Functional Descriptor*/
  0x05,                              /* bFunctionLength */
  CDC_CS_INTERFACE,                  /* bDescriptorType: CS_INTERFACE */
  CDC_CALL_MANAGEMENT,               /* bDescriptorSubtype: Call Management Func Desc */
  0x00,                              /* bmCapabilities: device handles call management */
  0x00,                              /* bDataInterface: CDC data IF ID */
/*Abstract Control Management Functional Descriptor*/
  0x04,                              /* bFunctionLength */
  CDC_CS_INTERFACE,                  /* bDescriptorType: CS_INTERFACE */
  CDC_ABSTRACT_CONTROL_MANAGEMENT,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,                              /* bmCapabilities: SET_LINE_CODING, GET_LINE_CODING, SET_CONTROL_LINE_STATE supported */
/*Union Functional Descriptor*/
  0x05,                              /* bFunctionLength */
  CDC_CS_INTERFACE,                  /* bDescriptorType: CS_INTERFACE */
  CDC_UNION,                         /* bDescriptorSubtype: Union func desc */
  USB_CDC_CIF_NUM,                   /* bMasterInterface: Communication class interface is master */
  USB_CDC_DIF_NUM,                   /* bSlaveInterface0: Data class interface is slave 0 */
/*Endpoint 1 Descriptor*/            /* event notification (optional) */
  USB_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
  USB_CDC_EP_INT_IN,                /* bEndpointAddress */
  USB_ENDPOINT_TYPE_INTERRUPT,       /* bmAttributes */
  WBVAL(0x0010),                     /* wMaxPacketSize */
  0x02,          /* 2ms */           /* bInterval */

/* Interface 1, Alternate Setting 0, Data class interface descriptor*/
  USB_INTERFACE_DESC_SIZE,           /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType */
  USB_CDC_DIF_NUM,                   /* bInterfaceNumber: Number of Interface */
  0x00,                              /* bAlternateSetting: no alternate setting */
  0x02,                              /* bNumEndpoints: two endpoints used */
  CDC_DATA_INTERFACE_CLASS,          /* bInterfaceClass: Data Interface Class */
  0x00,                              /* bInterfaceSubClass: no subclass available */
  0x00,                              /* bInterfaceProtocol: no protocol used */
  0x04,                              /* iInterface: */
/* Endpoint, EP3 Bulk Out */
  USB_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
  USB_CDC_EP_BULK_OUT,               /* bEndpointAddress */
  USB_ENDPOINT_TYPE_BULK,            /* bmAttributes */
  WBVAL(USB_HS_MAX_BULK_PACKET),     /* wMaxPacketSize */
  0x00,                              /* bInterval: ignore for Bulk transfer */
/* Endpoint, EP3 Bulk In */
  USB_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
  USB_CDC_EP_BULK_IN,                /* bEndpointAddress */
  USB_ENDPOINT_TYPE_BULK,            /* bmAttributes */
  WBVAL(USB_HS_MAX_BULK_PACKET),     /* wMaxPacketSize */
  0x00,                              /* bInterval: ignore for Bulk transfer */



  /* IAD 2 Descriptor */
  0x08,                              /* sizeof(USB_IAD_DSC) */
  0x0B,                              /* Interface assocication descriptor type */
  0x02,                              /* The first associated interface */
  0x02,                              /* Number of contiguous associated interfaces */
  CDC_COMMUNICATION_INTERFACE_CLASS, /* bInterfaceClass: Communication Interface Class */
  CDC_ABSTRACT_CONTROL_MODEL,        /* bInterfaceSubClass: Abstract Control Model */
  0x00,                              /* bInterfaceProtocol: no protocol used */
  0x05,                              /* iInterface: */

  /* Interface 2, Alternate Setting 0, Communication class interface descriptor */
    USB_INTERFACE_DESC_SIZE,           /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType */
    2,                   /* bInterfaceNumber: Number of Interface */
    0x00,                              /* bAlternateSetting: Alternate setting */
    0x01,                              /* bNumEndpoints: One endpoint used */
    CDC_COMMUNICATION_INTERFACE_CLASS, /* bInterfaceClass: Communication Interface Class */
    CDC_ABSTRACT_CONTROL_MODEL,        /* bInterfaceSubClass: Abstract Control Model */
    0x00,                              /* bInterfaceProtocol: no protocol used */
    0x05,                              /* iInterface: */
  /*Header Functional Descriptor*/
    0x05,                              /* bLength: Endpoint Descriptor size */
    CDC_CS_INTERFACE,                  /* bDescriptorType: CS_INTERFACE */
    CDC_HEADER,                        /* bDescriptorSubtype: Header Func Desc */
    WBVAL(CDC_V1_10), /* 1.10 */       /* bcdCDC */
  /*Call Management Functional Descriptor*/
    0x05,                              /* bFunctionLength */
    CDC_CS_INTERFACE,                  /* bDescriptorType: CS_INTERFACE */
    CDC_CALL_MANAGEMENT,               /* bDescriptorSubtype: Call Management Func Desc */
    0x00,                              /* bmCapabilities: device handles call management */
    0x00,                              /* bDataInterface: CDC data IF ID */
  /*Abstract Control Management Functional Descriptor*/
    0x04,                              /* bFunctionLength */
    CDC_CS_INTERFACE,                  /* bDescriptorType: CS_INTERFACE */
    CDC_ABSTRACT_CONTROL_MANAGEMENT,   /* bDescriptorSubtype: Abstract Control Management desc */
    0x02,                              /* bmCapabilities: SET_LINE_CODING, GET_LINE_CODING, SET_CONTROL_LINE_STATE supported */
  /*Union Functional Descriptor*/
    0x05,                              /* bFunctionLength */
    CDC_CS_INTERFACE,                  /* bDescriptorType: CS_INTERFACE */
    CDC_UNION,                         /* bDescriptorSubtype: Union func desc */
    2,                                 /* bMasterInterface: Communication class interface is master */
    3,                                 /* bSlaveInterface0: Data class interface is slave 0 */
  /*Endpoint 1 Descriptor*/            /* event notification (optional) */
    USB_ENDPOINT_DESC_SIZE,            /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
    USB_ENDPOINT_IN(3),                /* bEndpointAddress */
    USB_ENDPOINT_TYPE_INTERRUPT,       /* bmAttributes */
    WBVAL(0x0010),                     /* wMaxPacketSize */
    0x02,          /* 2ms */           /* bInterval */

  /* Interface 3, Alternate Setting 0, Data class interface descriptor*/
    USB_INTERFACE_DESC_SIZE,           /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType */
    3, 				                  /* bInterfaceNumber: Number of Interface */
    0x00,                              /* bAlternateSetting: no alternate setting */
    0x02,                              /* bNumEndpoints: two endpoints used */
    CDC_DATA_INTERFACE_CLASS,          /* bInterfaceClass: Data Interface Class */
    0x00,                              /* bInterfaceSubClass: no subclass available */
    0x00,                              /* bInterfaceProtocol: no protocol used */
    0x05,                              /* iInterface: */
  /* Endpoint, EP3 Bulk Out */
    USB_ENDPOINT_DESC_SIZE,            /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
    USB_ENDPOINT_OUT(4),               /* bEndpointAddress */
    USB_ENDPOINT_TYPE_BULK,            /* bmAttributes */
    WBVAL(USB_HS_MAX_BULK_PACKET),     /* wMaxPacketSize */
    0x00,                              /* bInterval: ignore for Bulk transfer */
  /* Endpoint, EP3 Bulk In */
    USB_ENDPOINT_DESC_SIZE,            /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
    USB_ENDPOINT_IN(4),                /* bEndpointAddress */
    USB_ENDPOINT_TYPE_BULK,            /* bmAttributes */
    WBVAL(USB_HS_MAX_BULK_PACKET),     /* wMaxPacketSize */
    0x00,                              /* bInterval: ignore for Bulk transfer */

/* Terminator */
  0                                  /* bLength */
};

/* USB String Descriptor (optional) */
ALIGN4 const uint8_t VCOM_StringDescriptor[] = {
/* Index 0x00: LANGID Codes */
  0x04,                              /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(0x0409), /* US English */    /* wLANGID */
  /* Index 0x01: Manufacturer */
  (8*2 + 2),                        /* bLength (8 Char + Type + length) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  '8', 0,
  'd', 0,
  'e', 0,
  'v', 0,
  'i', 0,
  'c', 0,
  'e', 0,
  's', 0,
  /* Index 0x02: Product */
  (21*2 + 2),                        /* bLength (21 Char + Type + length) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'C', 0,
  'a', 0,
  'r', 0,
  'a', 0,
  'm', 0,
  'b', 0,
  'o', 0,
  'l', 0,
  'a', 0,
  '2', 0,
  ' ', 0,
  'U', 0,
  'P', 0,
  'E', 0,
  'R', 0,
  ' ', 0,
  'b', 0,
  'o', 0,
  'a', 0,
  'r', 0,
  'd', 0,
  /* Index 0x03: Serial Number */
  (8*2 + 2),                        /* bLength (8 Char + Type + length) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'R', 0,
  'e', 0,
  'v', 0,
  ' ', 0,
  '0', 0,
  '.', 0,
  '9', 0,
  'b', 0,
/* Index 0x04: Interface 0, Alternate Setting 0 */
  ( 11*2 + 2),                        /* bLength (11 Char + Type + length) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'U',0,
  'A',0,
  'R',0,
  'T',0,
  ' ', 0,
  'B', 0,
  'r', 0,
  'i', 0,
  'd', 0,
  'g', 0,
  'e', 0,
  /* Index 0x05: Interface 2, Alternate Setting 0 */
  ( 8*2 + 2),                        /* bLength (8 Char + Type + length) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'O',0,
  'S',0,
  'C',0,
  ' ',0,
  'V', 0,
  'C', 0,
  'O', 0,
  'M', 0,
};
