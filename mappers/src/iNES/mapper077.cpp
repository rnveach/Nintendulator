/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper077.cpp $
 * $Id: mapper077.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace
{
void	Sync (void)
{
	EMU->SetPRG_ROM32(0x8, Latch::Data & 0x0F);
	EMU->SetCHR_ROM2(0, (Latch::Data & 0xF0) >> 4);
	EMU->SetCHR_RAM2(2, 0);
	EMU->SetCHR_RAM2(4, 1);
	EMU->SetCHR_RAM2(6, 2);
}

BOOL	MAPINT	Load (void)
{
	Latch::Load(Sync, FALSE);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	iNES_SetMirroring();
	Latch::Reset(ResetType);
}
void	MAPINT	Unload (void)
{
	Latch::Unload();
}

uint16_t MapperNum = 77;
} // namespace

const MapperInfo MapperInfo_077 =
{
	&MapperNum,
	_T("Napoleon Senki"),
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
