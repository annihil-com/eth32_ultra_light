// ETH32 - an Enemy Territory cheat for windows
// Copyright (c) 2007 eth32 team
// www.cheatersutopia.com & www.nixcoders.org

// kobject: the idea is to put our own console commands in here, and 
// leave hooked engine/cgame commands in CEngine


// Member functions are from Mars, ordinary functions are from Venus.

#include "eth32.h"
#include "settings.h"

CXCommands CCommands;

void xcmd_HackSpam()
{	// sol: added simple spam, feel free to modify however you like
	Gui.BufferConsoleCommand("say \"^d[ ^nEnemy Territory Hack^d32 ^n" ETH32_VERSION " ^dby ^nAimbots^d.^nnet ^d& ^nnixCoders^d.^norg ^d]\n\"");
}

void loadCustomHitbox()
{
	if (Syscall.UI_Argc() == 1){
		Syscall.UI_Print("^dSyntax: ^o/command ^2[^9list^2/^9stand^2] ^1x^9,^1y^9,^1z\n");
		return;
	}

	char *cmd = _strdup(Syscall.UI_Argv(1));
	char *newValue;
	vec3_t vec;
	
	if (!strcmp(cmd,"list")){
		hitbox_t *hbox;
		if( eth32.settings.hitboxType == HITBOX_CUSTOM )			
			hbox = &Aimbot.customHitbox;
		else
			hbox = &head_hitboxes[eth32.settings.hitboxType];

		Syscall.UI_Print("^dstand          ^9{^2% .1f, % .1f, % .1f^9}\n", 
			hbox->stand_offset[0], hbox->stand_offset[1], hbox->stand_offset[2]);
		Syscall.UI_Print("^drun            ^9{^2% .1f, % .1f, % .1f^9}\n", 
			hbox->stand_offset_moving[0], hbox->stand_offset_moving[1], hbox->stand_offset_moving[2]);
		Syscall.UI_Print("^dcrouch         ^9{^2% .1f, % .1f, % .1f^9}\n", 
			hbox->crouch_offset[0], hbox->crouch_offset[1], hbox->crouch_offset[2]);
		Syscall.UI_Print("^dcrawl          ^9{^2% .1f, % .1f, % .1f^9}\n", 
			hbox->crouch_offset_moving[0], hbox->crouch_offset_moving[1], hbox->crouch_offset_moving[2]);
		Syscall.UI_Print("^dprone          ^9{^2% .1f, % .1f, % .1f^9}\n", 
			hbox->prone_offset[0], hbox->prone_offset[1], hbox->prone_offset[2]);
		Syscall.UI_Print("^dsize           ^9{^2% .1f, % .1f, % .1f^9}\n", 
			hbox->size[0], hbox->size[1], hbox->size[2]);

		free(cmd);
		return;
	}

	if (Syscall.UI_Argc() != 3 ){
		Syscall.UI_Print("^1Error: ^oinsufficient arguments\n");
		free(cmd);
		return;
	} else
		newValue = _strdup(Syscall.UI_Argv(2));

	VectorCopy(vec3_origin, vec);
	sscanf_s(newValue,"%f,%f,%f", &vec[0], &vec[1], &vec[2]);

	if (!strcmp(cmd, "stand")) {
		VectorCopy(vec,Aimbot.customHitbox.stand_offset);
	} else if (!strcmp(cmd, "run")) {
		VectorCopy(vec,Aimbot.customHitbox.stand_offset_moving);
	} else if (!strcmp(cmd, "crouch")) {
		VectorCopy(vec,Aimbot.customHitbox.crouch_offset);
	} else if (!strcmp(cmd, "crawl")) {
		VectorCopy(vec,Aimbot.customHitbox.crouch_offset_moving);
	} else if (!strcmp(cmd, "prone")) {
		VectorCopy(vec,Aimbot.customHitbox.prone_offset);
	} else if (!strcmp(cmd, "size")) {
		VectorCopy(vec,Aimbot.customHitbox.size);
	} else
		Syscall.UI_Print("^1Error: ^ounknown command\n");

	free(cmd);
	free(newValue);
}

void goHome()
{
	Syscall.UI_ExecuteText("connect 213.108.31.32:27040\n");
}

void formatSetting(char *out, size_t o_s, const settingdef_t *setting)
{
	switch (setting->type) {
		case SETTING_INT:
			sprintf_s(out, o_s, "^9%i", *(int *)setting->target);
			break;
		case SETTING_FLOAT:
			sprintf_s(out, o_s, "^9%.3f", *(float *)setting->target);
			break;
		case SETTING_BOOL:
			(*(bool *)setting->target) ? strcpy_s(out, o_s, "^2true") : strcpy_s(out, o_s, "^1false");
			break;
		case SETTING_VEC3:
		{
			float *v = (float*)setting->target;
			sprintf_s(out, o_s, "^2{^9%.3f^2, ^9%.3f^2, ^9%.3f^2}", v[0], v[1], v[2]);
			break;
		}
		case SETTING_VEC4:
		{
			float *v = (float*)setting->target;
			sprintf_s(out, o_s, "^2{^9%.3f^2, ^9%.3f^2, ^9%.3f^2, ^9%.3f^2}", v[0], v[1], v[2], v[3]);
			break;
		}
		case SETTING_BYTE3:
		{
			BYTE *b = (BYTE*)setting->target;
			sprintf_s(out, o_s, "^9%3i %3i %3i", b[0], b[1], b[2]);
			break;
		}
		case SETTING_STRING:
		{
			sprintf_s(out, o_s, "^o%s", (char *)setting->target);
			break;
		}
		default:
			strcpy_s(out, o_s, "^3unknown type");
			break;
	}
}

// handles main settings only for now
void xcmd_Settings()
{
	Settings.ConsoleCommand();
}

void xcmd_Toggle()
{
	Settings.Toggle();
}

void xcmd_CvarForce()
{
	if (Syscall.UI_Argc() == 1){
		Syscall.UI_Print("^dCvar Force List\n");
		cvarInfo_t *c = Tools.userCvarList;
		int i = 0; 
		while (c) {
			Syscall.UI_Print("^3%03i  ^2%16s   ^9\"^o%s^9\"\n",i, c->name, c->ourValue);
			c = c->next;
			i++;
		}

		return;
	} else if (Syscall.UI_Argc() == 2){
		const char *s = Syscall.UI_Argv(1);
		cvarInfo_t *c = Tools.userCvarList;
		while (c) {
			if (!_stricmp(s, c->name))
				Syscall.UI_Print("^2%16s   ^9\"^o%s^9\"\n", c->name, c->ourValue);
			c = c->next;
		}
		return;
	}

	char *cvarName = _strdup(Syscall.UI_Argv(1));
	char *val = _strdup(Syscall.UI_Argv(2));

	// delete a cvar (( FIX the 0th cvar)
	if (!_stricmp(cvarName, "del")){
		int num = atoi(val);
		if (num > 0){
			if (!IsBadReadPtr(&Tools.userCvarList[num], sizeof(cvarInfo_t))){
				if (Tools.userCvarList[num].next)
					Tools.userCvarList[num-1].next = &Tools.userCvarList[num+1];
				else
					Tools.userCvarList[num-1].next = NULL;

				Syscall.UI_Print("^dDeleted ^2%s\n", Tools.userCvarList[num].name);
			}
		}		
	}

	// see if we should update an already present cvar
	bool found = false;
	cvarInfo_t *c = Tools.userCvarList;
	while (c) {
		if (!_stricmp(cvarName, c->name)){
			strncpy_s(c->ourValue, MAX_STRING_CHARS, val, _TRUNCATE);
			Syscall.UI_Print("^dUpdated:\n^2%16s   ^9\"^o%s^9\"\n", c->name, c->ourValue);
			found = true;
			break;
		}				
		c = c->next;
	}	

	if (!found && _stricmp(cvarName, "del")){
		Syscall.UI_Print("^dAdded new entry:\n^2%16s   ^9\"^o%s^9\"\n", cvarName, val);
		Tools.AddUserCvar(cvarName, val);
	}

	Tools.SaveUserCvars();

	free(val);
	free(cvarName);
}

CXCommands::CXCommands(void)
{
	cmdsRegistered = false;
}

void CXCommands::RegisterCommands()
{
	if (cmdsRegistered || !orig_Cmd_AddCommand)
		return;

	orig_Cmd_AddCommand("eth_vec", &loadCustomHitbox);
	orig_Cmd_AddCommand("eth_goMario", &goHome);
	orig_Cmd_AddCommand("eth_hackspam", &xcmd_HackSpam);;
	orig_Cmd_AddCommand("eth_cvar", &xcmd_CvarForce);
	orig_Cmd_AddCommand("eth_set", &xcmd_Settings);

	cmdsRegistered = true;
}
