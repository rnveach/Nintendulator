/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/NES/NES_HxROM.cpp $
 * $Id: NES_HxROM.cpp 1352 2017-09-23 00:20:15Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"
#include	"..\..\Hardware\h_MMC6.h"

namespace
{
void	Sync_HKROM (void)
{
	MMC6::SyncPRG(0x3F, 0);
	MMC6::SyncCHR_ROM(0xFF, 0);
	MMC6::SyncMirror();
}

BOOL	MAPINT	Load_HKROM (void)
{
	UNIF_SetSRAM(1024);
	MMC6::Load(Sync_HKROM);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	MMC6::Reset(ResetType);
}
void	MAPINT	Unload (void)
{
	MMC6::Unload();
}
} // namespace

const MapperInfo MapperInfo_NES_HKROM =
{
	"NES-HKROM",
	_T("MMC6"),
	COMPAT_FULL,
	Load_HKROM,
	Reset,
	Unload,
	NULL,
	MMC6::PPUCycle,
	MMC6::SaveLoad,
	NULL,
	NULL
};
