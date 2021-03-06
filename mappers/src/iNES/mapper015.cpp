/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper015.cpp $
 * $Id: mapper015.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"

namespace
{
uint8_t PRG[4];
uint8_t Mirror;

void	Sync (void)
{
	EMU->SetPRG_RAM8(0x6, 0);
	for (int i = 0; i < 4; i++)
		EMU->SetPRG_ROM8(0x8 | (i << 1), PRG[i]);
	EMU->SetCHR_RAM8(0, 0);
	if (Mirror)
		EMU->Mirror_H();
	else	EMU->Mirror_V();
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	for (int i = 0; i < 4; i++)
		SAVELOAD_BYTE(mode, offset, data, PRG[i]);
	SAVELOAD_BYTE(mode, offset, data, Mirror);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Write (int Bank, int Addr, int Val)
{
	uint8_t PRGbank = (Val & 0x3F) << 1;
	uint8_t PRGflip = (Val & 0x80) >> 7;
	Mirror = Val & 0x40;
	switch (Addr)
	{
	case 0x000:
		PRGbank &= 0x7C;
		PRG[0] = PRGbank | 0 ^ PRGflip;
		PRG[1] = PRGbank | 1 ^ PRGflip;
		PRG[2] = PRGbank | 2 ^ PRGflip;
		PRG[3] = PRGbank | 3 ^ PRGflip;
		break;
	case 0x001:
		PRG[0] = PRGbank | 0 ^ PRGflip;
		PRG[1] = PRGbank | 1 ^ PRGflip;
		PRG[2] = 0x7E | 0 ^ PRGflip;
		PRG[3] = 0x7F | 1 ^ PRGflip;
		break;
	case 0x002:
		PRG[0] = PRGbank ^ PRGflip;
		PRG[1] = PRGbank ^ PRGflip;
		PRG[2] = PRGbank ^ PRGflip;
		PRG[3] = PRGbank ^ PRGflip;
		break;
	case 0x003:
		PRG[0] = PRGbank | 0 ^ PRGflip;
		PRG[1] = PRGbank | 1 ^ PRGflip;
		PRG[2] = PRGbank | 0 ^ PRGflip;
		PRG[3] = PRGbank | 1 ^ PRGflip;
		break;
	}
	Sync();
}

BOOL	MAPINT	Load (void)
{
	iNES_SetSRAM();
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	EMU->SetCPUWriteHandler(0x8, Write);

	if (ResetType == RESET_HARD)
	{
		for (int i = 0; i < 4; i++)
			PRG[i] = i;
		Mirror = 0;
	}
	Sync();
}

uint16_t MapperNum = 15;
} // namespace

const MapperInfo MapperInfo_015 =
{
	&MapperNum,
	_T("100-in-1 Contra Function 16"),
	COMPAT_FULL,
	Load,
	Reset,
	NULL,
	NULL,
	NULL,
	SaveLoad,
	NULL,
	NULL
};
