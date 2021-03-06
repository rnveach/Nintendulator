/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper070.cpp $
 * $Id: mapper070.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace
{
void	Sync (void)
{
	EMU->SetPRG_ROM16(0x8, (Latch::Data & 0x70) >> 4);
	EMU->SetPRG_ROM16(0xC, 0x7);
	EMU->SetCHR_ROM8(0, Latch::Data & 0xF);
	if (Latch::Data & 0x80)
		EMU->Mirror_S1();
	else	EMU->Mirror_S0();
}

BOOL	MAPINT	Load (void)
{
	Latch::Load(Sync, FALSE);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	Latch::Reset(ResetType);
}
void	MAPINT	Unload (void)
{
	Latch::Unload();
}

uint16_t MapperNum = 70;
} // namespace

const MapperInfo MapperInfo_070 =
{
	&MapperNum,
	_T("Bandai 74161/7432"),
	COMPAT_FULL,
	Load,
	Reset,
	Unload,
	NULL,
	NULL,
	Latch::SaveLoad_D,
	NULL,
	NULL
};
