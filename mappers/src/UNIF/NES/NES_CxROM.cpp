/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/NES/NES_CxROM.cpp $
 * $Id: NES_CxROM.cpp 1352 2017-09-23 00:20:15Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"
#include	"..\..\Hardware\h_Latch.h"

namespace
{
void	Sync_CNROM (void)
{
	EMU->SetPRG_ROM16(0x8, 0);
	EMU->SetPRG_ROM16(0xC, 1);
	EMU->SetCHR_ROM8(0, Latch::Data & 0x03);
}
void	Sync_CPROM (void)
{
	EMU->SetPRG_ROM16(0x8, 0);
	EMU->SetPRG_ROM16(0xC, 1);
	EMU->SetCHR_RAM4(0, 0);
	EMU->SetCHR_RAM4(4, Latch::Data & 0x3);
}

BOOL	MAPINT	Load_CNROM (void)
{
	Latch::Load(Sync_CNROM, TRUE);
	return TRUE;
}
BOOL	MAPINT	Load_CPROM (void)
{
	Latch::Load(Sync_CPROM, TRUE);
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

const MapperInfo MapperInfo_NES_CNROM =
{
	"NES-CNROM",
	_T("Standard 8KB CHR switch"),
	COMPAT_FULL,
	Load_CNROM,
	Reset,
	Unload,
	NULL,
	NULL,
	Latch::SaveLoad_D,
	NULL,
	NULL
};
const MapperInfo MapperInfo_NES_CPROM =
{
	"NES-CPROM",
	_T("4KB CHR RAM switch"),
	COMPAT_FULL,
	Load_CPROM,
	Reset,
	Unload,
	NULL,
	NULL,
	Latch::SaveLoad_D,
	NULL,
	NULL
};