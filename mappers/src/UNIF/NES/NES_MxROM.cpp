/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/NES/NES_MxROM.cpp $
 * $Id: NES_MxROM.cpp 1352 2017-09-23 00:20:15Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"
#include	"..\..\Hardware\h_Latch.h"

namespace
{
void	Sync_MHROM (void)
{
	EMU->SetPRG_ROM32(0x8, (Latch::Data >> 4) & 0x1);
	EMU->SetCHR_ROM8(0, (Latch::Data >> 0) & 0x1);
}

BOOL	MAPINT	Load_MHROM (void)
{
	Latch::Load(Sync_MHROM, TRUE);
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

const MapperInfo MapperInfo_NES_MHROM =
{
	"NES-MHROM",
	_T("Super Mario Bros/Duck Hunt"),
	COMPAT_FULL,
	Load_MHROM,
	Reset,
	Unload,
	NULL,
	NULL,
	Latch::SaveLoad_D,
	NULL,
	NULL
};
