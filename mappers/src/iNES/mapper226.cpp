/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper226.cpp $
 * $Id: mapper226.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"

namespace
{
uint8_t Reg0, Reg1;

void	Sync (void)
{
	// rveach: eclipse doesn't support anonymous unions with anonymous structs
	union temp_union
	{
		struct
		{
			unsigned PRGbank : 5;
			unsigned PRGsize : 1;
			unsigned Mir_VH  : 1;
			unsigned PRGhi   : 2;
			unsigned         : 7;
		};
		struct
		{
			unsigned byte0   : 8;
			unsigned byte1   : 8;
		};
	};
	temp_union temp_var;

	temp_var.byte0 = Reg0;
	temp_var.byte1 = Reg1;

	if (temp_var.Mir_VH)
		EMU->Mirror_V();
	else	EMU->Mirror_H();
	if (temp_var.PRGsize)
	{
		EMU->SetPRG_ROM16(0x8, (temp_var.PRGhi << 5) | temp_var.PRGbank);
		EMU->SetPRG_ROM16(0xC, (temp_var.PRGhi << 5) | temp_var.PRGbank);
	}
	else	EMU->SetPRG_ROM32(0x8, (temp_var.PRGhi << 4) | (temp_var.PRGbank >> 1));
	EMU->SetCHR_RAM8(0x0, 0);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	SAVELOAD_BYTE(mode, offset, data, Reg0);
	SAVELOAD_BYTE(mode, offset, data, Reg1);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Write (int Bank, int Addr, int Val)
{
	switch (Addr & 1)
	{
	case 0:	Reg0 = Val;		break;
	case 1:	Reg1 = Val;		break;
	}
	Sync();
}

void	MAPINT	Reset (RESET_TYPE ResetType)
{
	for (int i = 0x8; i < 0x10; i++)
		EMU->SetCPUWriteHandler(i, Write);

	if (ResetType == RESET_HARD)
		Reg0 = Reg1 = 0;

	Sync();
}

uint16_t MapperNum = 226;
} // namespace

const MapperInfo MapperInfo_226 =
{
	&MapperNum,
	_T("76-in-1"),
	COMPAT_FULL,
	NULL,
	Reset,
	NULL,
	NULL,
	NULL,
	SaveLoad,
	NULL,
	NULL
};
