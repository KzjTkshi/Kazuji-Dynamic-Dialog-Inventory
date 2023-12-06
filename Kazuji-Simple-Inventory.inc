#include <a_samp>
#include <zcmd>
#include <sscanf>

enum 
{
	DIALOG_INVENTORY,
} // INI KALO LU MALES PAKE DEFINE PAKE INI AJA

// KALO MAU PAKE DEFINE INI

#define DIALOG_INVENTORY 99999 // 99999 BUKAN DARI JUMPLAHNYA, TAPI ITU ID DIALOG BIAR GA TABRAKAN SAMA DIALOG LAIN

// KEGUNAAN DARI INVENTORY & VARIABLE
#define MAX_SLOT 9
#define MAX_ITEM 3

// INI VARIABLE BUAT INVENTORY
new SlotInventory[MAX_PLAYERS][MAX_SLOT];
new AmmountItem[MAX_PLAYERS][MAX_ITEM];

// YANG GA TAU FUNGSINYA PASTI OTAKNYA 12 KB
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) 
{
	if(dialogid == DIALOG_INVENTORY) 
	{
		if(response) 
		{
			if(listitem < 9) 
			{
				if(SlotInventory[playerid][listitem] != 0) 
				{
					OnPlayerUseItem(playerid, SlotInventory[playerid][listitem] , listitem);
				}
			}
		}
		else if(!response) 
		{
			if(listitem < 9) 
			{
				if(SlotInventory[playerid][listitem] != 0) 
				{
					OnPlayerDropItem(playerid, SlotInventory[playerid][listitem] , listitem);
				}
			}
		}
	}
	return 1;
}

// INI KETIKA PEMAIN MEMILIH MENJATUHKAN ITEM
stock OnPlayerDropItem(playerid, itemid , slot) 
{
	if(AmmountItem[playerid][itemid] > 1) 
	{
		AmmountItem[playerid][itemid] -= 1;
		return 1;
	}
	else if(AmmountItem[playerid][itemid] <= 1) 
	{
		AmmountItem[playerid][itemid] = 0;
		SlotInventory[playerid][slot] = 0;
	}
	cmd_inv(playerid, ""); // INI DIPAKEIN ALIAS CMD BIAR MINIMALIST
	return 1;
}

// INI KETIKA PEMAIN MENGGUNAKAN ITEM DARI INVENTORY
stock OnPlayerUseItem(playerid, itemid , slot) 
{
	switch(itemid) 
	{
		case 1: GivePlayerWeapon(playerid, 24, 100);
		case 2: GivePlayerWeapon(playerid, 25, 100);
	}
	if(AmmountItem[playerid][itemid] > 1) 
	{
		AmmountItem[playerid][itemid] -= 1;
		return 1;
	}
	else if(AmmountItem[playerid][itemid] <= 1) 
	{
		AmmountItem[playerid][itemid] = 0;
		SlotInventory[playerid][slot] = 0;
	}
	return 1;
}

// INI BIAR TAU NAMA NAMA ITEMNYA YA
stock GetItemName(itemid) 
{
	new itemname[52];
	switch(itemid) 
	{
		case 0: itemname = "Empty";
		case 1: itemname = "Deagle";
		case 2: itemname = "Shotgun";
	}
	return itemname;
}

// INI MINIMALISIR SAAT MAKAI KEYBIND YA KONTOL
stock ShowKazujiInventory(playerid)
{
	new slot[120];
	for(new i = 0;i< MAX_SLOT ; i++) 
	{
		if(SlotInventory[playerid][i] != 0)
		{
			format(slot, sizeof(slot), "%s\n%s\t%d/100", slot,GetItemName(SlotInventory[playerid][i]),AmmountItem[playerid][SlotInventory[playerid][i]]);
		}
	    else strcat(slot, "\nEmpty");
	}
	format(slot, sizeof slot, "%s", slot);
	ShowPlayerDialog(playerid, DIALOG_INVENTORY, DIALOG_STYLE_LIST, "Kazuji - Inventory", slot, "Action", "Cancel");
	return 1;
}

// HANYA ATMIN WOAKO SETTING SENDIRI KONTOL
CMD:additem(playerid, params[]) 
{
	new target,itemid,jumplah;
	if(sscanf(params, "udd", target,itemid,jumplah)) return SendClientMessage(playerid, -1, "/additem [playerid] [itemid] [jumplah]");
	if(itemid < 0 || itemid >  MAX_ITEM) return SendClientMessage(playerid, -1, "Hanya ada 1 sampai 3 item saja.");
	if(!IsPlayerConnected(target)) return SendClientMessage(playerid, -1, "Pemain tidak digame.");
	for(new i = 0 ; i < MAX_SLOT ; i++) 
	{
		if(SlotInventory[playerid][i] == itemid) 
		{
			AmmountItem[playerid][itemid] += jumplah;
			return 1;
		}
	    else if(SlotInventory[playerid][i] == 0) 
		{
	    	SlotInventory[playerid][i] = itemid;
	    	AmmountItem[playerid][itemid] = jumplah;
	    	return 1;
	    }
	}
	return 1;
}

// INI JIKA LU GA MAU PAKE OTOT / KEYBINDS
CMD:inv(playerid, params[]) 
{
	ShowKazujiInventory(playerid);
	return 1;
}


// INI SYSTEM KEYBIND
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_YES))
	{
	    ShowKazujiInventory(playerid);
	}
	return 1;
}
