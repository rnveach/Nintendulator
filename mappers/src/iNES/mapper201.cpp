/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper201.cpp $
 * $Id: mapper201.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace
{
void	Sync (void)
{
	EMU->SetPRG_ROM32(0, Latch::Addr.b0);
	EMU->SetCHR_ROM8(0, Latch::Addr.b0);
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

uint16_t MapperNum = 201;
} // namespace

const MapperInfo MapperInfo_201 =
{
	&MapperNum,
	_T("21-in-1"),
	COMPAT_NEARLY,
	Load,
	Reset,
	Unload,
	NULL,
	NULL,
	Latch::SaveLoad_AL,
	NULL,
	NULL
};
