/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper093.cpp $
 * $Id: mapper093.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace
{
void	Sync (void)
{
	EMU->SetPRG_ROM16(0x8, (Latch::Data & 0xF0) >> 4);
	EMU->SetPRG_ROM16(0xC, -1);
	if (ROM->INES_CHRSize)
		EMU->SetCHR_ROM8(0, 0);
	else	EMU->SetCHR_RAM8(0, 0);
	if (Latch::Data & 0x01)
		EMU->Mirror_H();
	else	EMU->Mirror_V();
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

uint16_t MapperNum = 93;
} // namespace

const MapperInfo MapperInfo_093 =
{
	&MapperNum,
	_T("Fantasy Zone"),
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
