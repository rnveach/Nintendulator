/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper038.cpp $
 * $Id: mapper038.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"

namespace
{
uint8_t Reg;

void	Sync (void)
{
	EMU->SetPRG_ROM32(0x8, Reg & 0x03);
	EMU->SetCHR_ROM8(0, (Reg >> 2) & 0x3);
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

	EMU->SetCPUWriteHandler(0x7, Write);

	if (ResetType == RESET_HARD)
		Reg = 0;

	Sync();
}

uint16_t MapperNum = 38;
} // namespace

const MapperInfo MapperInfo_038 =
{
	&MapperNum,
	_T("Crime Busters (74138/74161)"),
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
