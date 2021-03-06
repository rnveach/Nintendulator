/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper097.cpp $
 * $Id: mapper097.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace
{
void	Sync (void)
{
	EMU->SetPRG_ROM16(0x8, -1);
	EMU->SetPRG_ROM16(0xC, Latch::Data & 0xF);
	EMU->SetCHR_RAM8(0, 0);
	switch ((Latch::Data & 0xC0) >> 6)
	{
	case 0:	EMU->Mirror_S0();	break;
	case 1:	EMU->Mirror_H();	break;
	case 2:	EMU->Mirror_V();	break;
	case 3:	EMU->Mirror_S1();	break;
	}
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

uint16_t MapperNum = 97;
} // namespace

const MapperInfo MapperInfo_097 =
{
	&MapperNum,
	_T("Kaiketsu Yanchamaru"),
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
