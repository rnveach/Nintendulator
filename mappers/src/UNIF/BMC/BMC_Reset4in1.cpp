/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/BMC/BMC_Reset4in1.cpp $
 * $Id: BMC_Reset4in1.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"

namespace
{
uint8_t Game;

void	Sync (void)
{
	EMU->SetCHR_ROM8(0, Game);
	EMU->SetPRG_ROM16(0x8, Game);
	EMU->SetPRG_ROM16(0xC, Game);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	SAVELOAD_BYTE(mode, offset, data, Game);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Reset (RESET_TYPE ResetType)
{
	if (ResetType == RESET_HARD)
		Game = 0;
	else	Game++;
	Sync();
	UNIF_SetMirroring(NULL);
}
} // namespace

const MapperInfo MapperInfo_BMC_Reset4in1 =
{
	"BMC-Reset4in1",
	_T("Pirate multicart mapper"),
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
