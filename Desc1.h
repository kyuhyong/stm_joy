// D:\my_workspace\my_fw\stm_joy\Desc1.h


char ReportDescriptor[52] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x0b, 0x04, 0x00, 0x01, 0x00,  // USAGE (Generic Desktop:Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x0b, 0x01, 0x00, 0x01, 0x00,  //   USAGE (Generic Desktop:Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x09,                    // USAGE_PAGE (Button)
    0x19, 0x01,                    // USAGE_MINIMUM (Button 1)
    0x29, 0x08,                    // USAGE_MAXIMUM (Button 8)
    0x15, 0x00,                    // LOGICAL_MINIMUM (0)
    0x25, 0x01,                    // LOGICAL_MAXIMUM (1)
    0x95, 0x08,                    // REPORT_COUNT (8)
    0x75, 0x01,                    // REPORT_SIZE (1)
    0x81, 0x02,                    // INPUT (Data,Var,Abs)
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    // USAGE (X)
    0x09, 0x31,                    // USAGE (Y)
    0x16, 0x01, 0xf8,              // LOGICAL_MINIMUM (-2047)
    0x26, 0xff, 0x07,              // LOGICAL_MAXIMUM (2047)
    0x75, 0x10,                    // REPORT_SIZE (16)
    0x95, 0x02,                    // REPORT_COUNT (2)
    0x81, 0x06,                    // INPUT (Data,Var,Rel)
    0xc0,                          //     END_COLLECTION
    0xc0                           // END_COLLECTION
};

