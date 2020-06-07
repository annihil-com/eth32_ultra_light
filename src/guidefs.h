// ETH32 - an Enemy Territory cheat for windows
// Copyright (c) 2007 eth32 team
// www.cheatersutopia.com & www.nixcoders.org

#pragma once

#include "CAimbot.h"

#define SETFLOAT(x)			((int)(x * 1000))		// only keeping up to 0.001
#define GETFLOAT(x)			(x / 1000.f)

// Control definition reference: (update this if you add new control types)

// Type					Arg0			Arg1			Arg2			Arg3			Arg4
// CTRL_CHECKBOX		bool *target	N/A				N/A				N/A				N/A
// CTRL_INTDISPLAY		int *target		N/A				N/A				N/A				N/A
// CTRL_INTSLIDER		int	min			int	max			int *target		N/A				N/A
// CTRL_FLOATSLIDER		float min		float max		float *target	N/A				N/A
// CTRL_COLORPICKER		BYTE *color		N/A				N/A				N/A				N/A

// NOTE: cast arg0-arg4 to int if used, use SETFLOAT/GETFLOAT for floats

static const windef_t windows[] = 
{
	// MAINVIEW
	{ 
		"Status",				// title
		WIN_STATUS,				// type
		GUI_MAINVIEW,			// view
		5, 422, 150, 53,		// x, y, w, h
		0,						// num controls
	},
	{
		"Weapon",				// title
		WIN_WEAPON,				// type
		GUI_MAINVIEW,			// view
		6, 365, 150, 53,		// x, y, w, h
		0,						// num controls
	},
	/*{ // sol: a window I use for setting weapon rendering parms *** DO NOT REMOVE ***
		"Weap Rendering",		// title
		WIN_STANDARD,			// type
		GUI_MAINVIEW,			// view
		160, 200, 150, 200,		// x, y, w, h
		7,						// num controls
		{
			// Type				Label				X		Y		W		H		Arg0 ... Arg4
			{ CTRL_FLOATSLIDER,	"X",				5,		5,		140,	20,		SETFLOAT(-10), SETFLOAT(10), (int)&eth32.settings.weapOrigin[0] },
			{ CTRL_FLOATSLIDER,	"Y",				5,		30,		140,	20,		SETFLOAT(-10), SETFLOAT(10), (int)&eth32.settings.weapOrigin[1] },
			{ CTRL_FLOATSLIDER,	"Z",				5,		55,		140,	20,		SETFLOAT(-10), SETFLOAT(10), (int)&eth32.settings.weapOrigin[2] },
			{ CTRL_FLOATSLIDER,	"Pitch",			5,		80,		140,	20,		SETFLOAT(0), SETFLOAT(360), (int)&eth32.settings.weapAngle[0] },
			{ CTRL_FLOATSLIDER,	"Yaw",				5,		105,	140,	20,		SETFLOAT(0), SETFLOAT(360), (int)&eth32.settings.weapAngle[1] },
			{ CTRL_FLOATSLIDER,	"Roll",				5,		130,	140,	20,		SETFLOAT(0), SETFLOAT(360), (int)&eth32.settings.weapAngle[2] },
			{ CTRL_FLOATSLIDER,	"Dist",				5,		155,	140,	20,		SETFLOAT(0), SETFLOAT(120), (int)&eth32.settings.weapDist },
		},
	},*/
	{
		"mainchat",				// title
		WIN_CHAT,				// type
		GUI_MAINVIEW,			// view
		289, 379, 350, 100,		// x, y, w, h
		0,						// num controls
	},
	{
		"Respawn",				// title
		WIN_RESPAWN,			// type
		GUI_MAINVIEW,			// view
		280, 5, 80, 20,			// x, y, w, h
		0,						// num controls
	},
	// MENUVIEW
	{
		"Aimbot",				// title
		WIN_STANDARD,			// type
		GUI_MENUVIEW,			// view
		7, 58, 150, 377,		// x, y, w, h
		16,						// num controls
		{
			// Type				Label				X		Y		W		H		Arg0 ... Arg4
			{ CTRL_DROPBOX,		"Aim",				5,		5,		140,	23,		AIM_OFF, AIM_MAX-1, (int)&eth32.settings.aimType, (int)aimTypeText },
			{ CTRL_CHECKBOX,	"Autofire",			5,		33,		140,	8,		(int)&eth32.settings.autofire },
			{ CTRL_CHECKBOX,	"Validate Attack",	5,		46,		140,	8,		(int)&eth32.settings.atkValidate },
			{ CTRL_FLOATSLIDER, "Fov",				5,		59,		140,	20,		SETFLOAT(0.0), SETFLOAT(360.0), (int)&eth32.settings.fov },
			{ CTRL_DROPBOX,		"Target Sort",		5,		84,		140,	23,		SORT_OFF, SORT_MAX-1, (int)&eth32.settings.aimSort, (int)sortTypeText },
			{ CTRL_DROPBOX,		"Aim Priority",		5,		112,	140,	23,		0, AP_MAX-1, (int)&eth32.settings.headbody, (int)priorityTypeText },
			{ CTRL_CHECKBOX,	"Target Lock",		5,		140,	140,	8,		(int)&eth32.settings.lockTarget },
			{ CTRL_DROPBOX,		"Hitbox Style",		5,		153,	140,	23,		HITBOX_OFF, HITBOX_MAX-1, (int)&eth32.settings.hitboxType, (int)hitboxText },
			{ CTRL_DROPBOX,		"Trace Style",		5,		181,	140,	23,		TRACE_CENTER, TRACE_MAX-1, (int)&eth32.settings.traceType, (int)traceTypeText },
			{ CTRL_DROPBOX,		"Self Predict",		5,		209,	140,	23,		SPR_OFF, SPR_MAX-1, (int)&eth32.settings.predSelfType, (int)selfPredictText },
			{ CTRL_FLOATSLIDER,	"Self Predict",		5,		237,	140,	20,		SETFLOAT(-0.10), SETFLOAT(0.10), (int)&eth32.settings.predSelf },
			{ CTRL_FLOATSLIDER,	"Target Predict",	5,		262,	140,	20,		SETFLOAT(-0.10), SETFLOAT(0.10), (int)&eth32.settings.pred },
			{ CTRL_FLOATSLIDER, "Bot Predict",		5,		287,	140,	20,		SETFLOAT(-0.10), SETFLOAT(0.10), (int)&eth32.settings.predbot },
			{ CTRL_FLOATSLIDER, "Anim Cor",			5,      312,    140,    20,     SETFLOAT(-10.0), SETFLOAT(10.0), (int)&eth32.settings.animCorrection },
			{ CTRL_CHECKBOX,	"Auto Pred Bots",	5,		337,	140,	8,		(int)&eth32.settings.autoPredBots },
			{ CTRL_CHECKBOX,	"Auto Crouch",		5,		349,	140,	8,		(int)&eth32.settings.autoCrouch },
		},
	},
	{
		"Chams",				// title
		WIN_STANDARD,			// type
		GUI_MENUVIEW,			// view
		376, 49, 150, 89,		// x, y, w, h
		3,						// num controls
		{
			// Type				Label			X		Y		W		H		Arg0 ... Arg4
			{ CTRL_DROPBOX,		"Players",		5,		5,		140,	23,		0, MAX_CHAMS-1, (int)&eth32.settings.chamsPlayer, (int)chamsText },
			{ CTRL_DROPBOX,		"Weapons",		5,		33,		140,	23,		0, MAX_CHAMS-1, (int)&eth32.settings.chamsWeapon, (int)chamsText },
			{ CTRL_CHECKBOX,	"My Weapon",	5,		61,		140,	8,		(int)&eth32.settings.chamsOurWeapon },
		}
	},
	{
		"Colors",				// title
		WIN_STANDARD,			// type
		GUI_MENUVIEW,			// view
		109, 208, 260, 90,		// x, y, w, h
		1,						// num controls
		{
			// Type				Label				X		Y		W		H		Arg0 ... Arg4
			{ CTRL_COLORPICKER, "Picker",			5,		5,		250,	65 },
		},
	},
	{
		"Weapon Config",		// title
		WIN_WEAPCONFIG,				// type
		GUI_MENUVIEW,			// view
		201, 58, 150, 225,		// x, y, w, h
		0,						// num controls
	},
	{
		"Custom Hitbox",		// title
		WIN_HITBOX,				// type
		GUI_MENUVIEW,			// view
		395, 59, 200, 195,		// x, y, w, h
		0,						// num controls
	},
	// CLIENTVIEW
	{ 
		"Clients",				// title
		WIN_CLIENTS,			// type
		GUI_CLIENTVIEW,			// view
		5, 5, 630, 470,			// x, y, w, h
		0,						// num controls
	},

};

static const assetdef_t assetDefs[] =
{
//	  Key				Type					Target
	{ "titlecolor",		ASSET_VEC4,				(void*)eth32.guiAssets.titleColor },
	{ "textcolor1",		ASSET_VEC4,				(void*)eth32.guiAssets.textColor1 },
	{ "textcolor2",		ASSET_VEC4,				(void*)eth32.guiAssets.textColor2 },
	{ "titleleft",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.titleLeft },
	{ "titlecenter",	ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.titleCenter },
	{ "titleright",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.titleRight },
	{ "winleft",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.winLeft },
	{ "wintop",			ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.winTop },
	{ "wintopl",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.winTopLeft },
	{ "wincenter",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.winCenter },
	{ "txtinputl",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.txtinputLeft },
	{ "txtinputc",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.txtinputCenter },
	{ "txtinputr",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.txtinputRight },
	{ "btnl",			ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.btnLeft },	
	{ "btnc",			ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.btnCenter },
	{ "btnr",			ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.btnRight },
	{ "btnsell",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.btnselLeft },
	{ "btnselc",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.btnselCenter },
	{ "btnselr",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.btnselRight },
	{ "check",			ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.check },
	{ "checkbox",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.checkBox },
	{ "mouse",			ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.mousePtr },
	{ "dropboxarrow",	ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.dropboxArrow },
	{ "scrollarrow",	ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.scrollbarArrow },
	{ "scrollbtn",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.scrollbarBtn },
	{ "scrolltrack",	ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.scrollbarTrack },
	{ "sliderbtn",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.sliderBtn },
	{ "slidertrack",	ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.sliderTrack },
	{ "camcorner",		ASSET_SHADERNOMIP,		(void*)&eth32.guiAssets.camCorner },
};
