/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper164.cpp $
 * $Id: mapper164.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"

namespace
{
uint8_t Reg;

void	Sync (void)
{
	EMU->SetPRG_RAM8(0x6, 0);
	EMU->SetPRG_ROM32(0x8, Reg);
	EMU->SetCHR_RAM8(0, 0);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	SAVELOAD_BYTE(mode, offset, data, Reg);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Write (int Bank, int Addr, int Val)
{
	if (!(Addr & 0x300))
	{
		Reg = Val;
		Sync();
	}
}

BOOL	MAPINT	Load (void)
{
	iNES_SetSRAM();
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	iNES_SetMirroring();

	EMU->SetCPUWriteHandler(0x5, Write);
	EMU->SetCPUWriteHandler(0xD, Write);

	if (ResetType == RESET_HARD)
		Reg = 0xFF;

	Sync();
}

uint16_t MapperNum = 164;
} // namespace

const MapperInfo MapperInfo_164 =
{
	&MapperNum,
	_T("Mapper 164"),
	COMPAT_NEARLY,
	Load,
	Reset,
	NULL,
	NULL,
	NULL,
	SaveLoad,
	NULL,
	NULL
};
