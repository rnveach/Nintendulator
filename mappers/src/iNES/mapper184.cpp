/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper184.cpp $
 * $Id: mapper184.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"

namespace
{
uint8_t Reg;

void	Sync (void)
{
	EMU->SetPRG_ROM32(0x8, 0);
	EMU->SetCHR_ROM4(0, Reg & 0xF);
	EMU->SetCHR_ROM4(4, (Reg >> 4) & 0xF);
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
	Reg = Val;
	Sync();
}

void	MAPINT	Reset (RESET_TYPE ResetType)
{
	iNES_SetMirroring();

	EMU->SetCPUWriteHandler(0x6, Write);
	EMU->SetCPUWriteHandler(0x7, Write);

	if (ResetType == RESET_HARD)
		Reg = 0;

	Sync();
}

uint16_t MapperNum = 184;
} // namespace

const MapperInfo MapperInfo_184 =
{
	&MapperNum,
	_T("SUNSOFT-1"),
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
