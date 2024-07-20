const unsigned char frisk_down_0_data[]={

	  0,  0,0x01,0,
	  8,  0,0x02,0,
	  0,  8,0x03,0,
	  8,  8,0x04,0,
	  0, 16,0x05,0,
	  8, 16,0x06,0,
	  0, 24,0x07,0,
	  8, 24,0x08,0,
	128

};

const unsigned char frisk_down_1_data[]={

	  0,  1,0x01,0,
	  8,  1,0x02,0,
	  0,  9,0x03,0,
	  8,  9,0x04,0,
	  0, 17,0x09,0,
	  8, 17,0x06,0,
	  0, 25,0x0a,0,
	  8, 25,0x0b,0,
	128

};

const unsigned char frisk_down_2_data[]={

	  0,  1,0x01,0,
	  8,  1,0x02,0,
	  0,  9,0x03,0,
	  8,  9,0x04,0,
	  0, 17,0x05,0,
	  8, 17,0x0c,0,
	  0, 25,0x0d,0,
	  8, 25,0x0e,0,
	128

};

const unsigned char frisk_left_0_data[]={

	  0,  0,0x0f,0,
	  8,  0,0x10,0,
	  0,  8,0x11,0,
	  8,  8,0x12,0,
	  0, 16,0x13,0,
	  8, 16,0x14,0,
	  0, 24,0x15,0,
	  8, 24,0x16,0,
	128

};

const unsigned char frisk_left_1_data[]={

	  0,  1,0x0f,0,
	  8,  1,0x10,0,
	  0,  9,0x11,0,
	  8,  9,0x12,0,
	  0, 17,0x17,0,
	  8, 17,0x18,0,
	  0, 25,0x19,0,
	  8, 25,0x1a,0,
	128

};

const unsigned char frisk_right_0_data[]={

	  8,  0,0x0f,0|OAM_FLIP_H,
	  0,  0,0x10,0|OAM_FLIP_H,
	  8,  8,0x11,0|OAM_FLIP_H,
	  0,  8,0x12,0|OAM_FLIP_H,
	  8, 16,0x13,0|OAM_FLIP_H,
	  0, 16,0x14,0|OAM_FLIP_H,
	  8, 24,0x15,0|OAM_FLIP_H,
	  0, 24,0x16,0|OAM_FLIP_H,
	128

};

const unsigned char frisk_right_1_data[]={

	  8,  1,0x0f,0|OAM_FLIP_H,
	  0,  1,0x10,0|OAM_FLIP_H,
	  8,  9,0x11,0|OAM_FLIP_H,
	  0,  9,0x12,0|OAM_FLIP_H,
	  8, 17,0x17,0|OAM_FLIP_H,
	  0, 17,0x18,0|OAM_FLIP_H,
	  8, 25,0x19,0|OAM_FLIP_H,
	  0, 25,0x1a,0|OAM_FLIP_H,
	128

};


const unsigned char frisk_up_0_data[]={

	  0,  0,0x1d,0,
	  8,  0,0x1e,0,
	  0,  8,0x1f,0,
	  8,  8,0x20,0,
	  8, 16,0x1c,0,
	  0, 16,0x1b,0,
	  9, 24,0x07,0|OAM_FLIP_H,
	  1, 24,0x08,0|OAM_FLIP_H,
	128

};

const unsigned char frisk_up_1_data[]={

	  0,  1,0x1d,0,
	  8,  1,0x1e,0,
	  0,  9,0x1f,0,
	  8,  9,0x20,0,
	  8, 17,0x21,0,
	  0, 17,0x1b,0,
	  9, 25,0x22,0|OAM_FLIP_H,
	  1, 25,0x23,0|OAM_FLIP_H,
	128

};


const unsigned char frisk_up_2_data[]={

	  0,  1,0x1d,0,
	  8,  1,0x1e,0,
	  0,  9,0x1f,0,
	  8,  9,0x20,0,
	  0, 17,0x24,0,
	  8, 17,0x1c,0,
	  0, 25,0x22,0,
	  8, 25,0x23,0,
	128

};

const unsigned char* const frisk[][]={
{
	frisk_down_0_data,
	frisk_down_1_data,
	frisk_down_0_data,
	frisk_down_2_data
},
{
	frisk_up_0_data,
	frisk_up_1_data,
	frisk_up_0_data,
	frisk_up_2_data
},
{
	frisk_left_0_data,
	frisk_left_1_data,
    frisk_left_0_data,
	frisk_left_1_data

},
{

	frisk_right_0_data,
	frisk_right_1_data,
    frisk_right_0_data,
	frisk_right_1_data

}
};
