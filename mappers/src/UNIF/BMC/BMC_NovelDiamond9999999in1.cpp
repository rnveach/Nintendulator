/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/BMC/BMC_NovelDiamond9999999in1.cpp $
 * $Id: BMC_NovelDiamond9999999in1.cpp 1352 2017-09-23 00:20:15Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"
#include	"..\..\Hardware\h_Latch.h"

namespace
{
void	Sync (void)
{
	EMU->SetPRG_ROM32(0x8, Latch::Addr.b0 & 0x3);
	EMU->SetCHR_ROM8(0, Latch::Addr.b0 & 0x7);
}

BOOL	MAPINT	Load (void)
{
	Latch::Load(Sync, FALSE);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	Latch::Reset(ResetType);
	UNIF_SetMirroring(NULL);
}
void	MAPINT	Unload (void)
{
	Latch::Unload();
}
} // namespace

const MapperInfo MapperInfo_BMC_NovelDiamond9999999in1 =
{
	"BMC-NovelDiamond9999999in1",
	_T("Pirate multicart mapper"),
	COMPAT_FULL,
	Load,
	Reset,
	Unload,
	NULL,
	NULL,
	Latch::SaveLoad_AL,
	NULL,
	NULL
};
