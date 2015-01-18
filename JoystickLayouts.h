/* 
 * This is a list of the button and axis numbers for several controllers.
 */

#ifndef JOYSTICK_LAYOUTS_H
#define JOYSTICK_LAYOUTS_H

// Logitech Attack 3
#define ATK_BTN_TRGR		1
#define ATK_BTN_STCK_BTM	2
#define ATK_BTN_STCK_MDL	3
#define ATK_BTN_STCK_LFT	4
#define ATK_BTN_STCK_RGHT	5
#define ATK_BTN_BSE_LFT_FR	6
#define ATK_BTN_BSE_LFT_CLS	7
#define ATK_BTN_BSE_MDL_LFT	8
#define ATK_BTN_BSE_MDL_RGHT	9
#define ATK_BTN_BSE_RGHT_CLS	10
#define ATK_BTN_BSE_RGHT_FR	11
#define ATK_AXS_STCK_X		1
#define ATK_AXS_STCK_Y		2			//Inverted
#define ATK_AXS_THRTL		3			//Inverted

// Logitech Extreme 3D Pro
#define X3D_BTN_TRGR		1
#define X3D_BTN_STCK_SIDE	2
#define X3D_BTN_STCK_BTM_LFT	3
#define X3D_BTN_STCK_BTM_RGHT	4
#define X3D_BTN_STCK_TP_LFT	5
#define X3D_BTN_STCK_TP_RGHT	6
#define X3D_BTN_BSE_FR_LFT	7
#define X3D_BTN_BSE_FR_RGHT	8
#define X3D_BTN_BSE_MD_LFT	9
#define X3D_BTN_BSE_MD_RGHT	10
#define X3D_BTN_BSE_CLS_LFT	11
#define X3D_BTN_BSE_CLS_RGHT	12
#define X3D_AXS_STCK_X		1
#define X3D_AXS_STCK_Y		2			//Inverted
#define X3D_AXS_STCK_TWIST	3			//Untested
#define X3D_AXS_THRTL		4			//Inverted
#define X3D_AXS_HT_X		5
#define X3D_AXS_HT_Y		6			//Inverted

// Xbox Controller
#define XBX_BTN_A		1
#define XBX_BTN_B		2
#define XBX_BTN_X		3
#define XBX_BTN_Y		4
#define XBX_BTN_BMP_LFT		5
#define XBX_BTN_BMP_RGHT	6
#define XBX_BTN_BCK		7
#define XBX_BTN_STRT		8
#define XBX_BTN_STCK_LFT	9
#define XBX_BTN_STCK_RGHT	10
#define XBX_AXS_STCK_LFT_X	1
#define XBX_AXS_STCK_LFT_Y	2			//Inverted
#define XBX_AXS_TRGR		3			//Untested
#define XBX_AXS_STCK_RGHT_X	4
#define XBX_AXS_STCK_RGHT_Y	5			//Inverted
#define XBX_AXS_HT_X		6
#define XBX_AXS_HT_Y		7			//Inverted

// Playstation Controller
#define PS_BTN_SQR		1
#define PS_BTN_CRS		2
#define PS_BTN_CRCL		3
#define PS_BTN_TRNGL		4
#define PS_BTN_BMP_LFT		5
#define PS_BTN_BMP_RGHT		6
#define PS_BTN_TRGR_LFT		7
#define PS_BTN_TRGR_RGHT	8
#define PS_BTN_SLCT		9
#define PS_BTN_STRT		10
#define PS_BTN_STCK_LFT		11			//Untested
#define PS_BTN_STCK_RGHT	12			//Untested
#define PS_AXS_STCK_LFT_X	1
#define PS_AXS_STCK_LFT_Y	2			//Inverted
#define PS_AXS_STCK_RGHT_X	3
#define PS_AXS_STCK_RGHT_Y	4			//Inverted
#define PS_AXS_HT_X		5
#define PS_AXS_HT_Y		6			//Inverted


// Logitech 310

#define L310_BUTTON_A				1
#define L310_BUTTON_B				2
#define L310_BUTTON_X				3
#define L310_BUTTON_Y				4
#define L310_BUTTON_BUMPER_LEFT		5
#define L310_BUTTON_BUMPER_RIGHT	6
#define L310_BUTTON_STOP			7
#define L310_BUTTON_START			8
#define L310_BUTTON_THUMB_LEFT		9
#define L310_BUTTON_THUMB_RIGHT		10

#define L310_THUMBSTICK_LEFT_X		0
#define L310_THUMBSTICK_LEFT_Y		1
#define L310_THUMBSTICK_RIGHT_X		4
#define L310_THUMBSTICK_RIGHT_Y		5

#define L310_TRIGGER_LEFT			2	// value > 0
#define L310_TRIGGER_RIGHT			3	// value < 0

/* 
DPAD works like this (not sure which channel)

-1: No Thumbpad Button
0: North Thumbpad Button
45: North-East Thumbpad Button
90: East Thumbpad Button
135: South-East Thumbpad Button
180: South Thumbpad Button
225: South-West Thumbpad Button
270: West Thumbpad Button
315: North-West Thumbpad Button 
*/

#endif //JOYSTICK_LAYOUTS_H
