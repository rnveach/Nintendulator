/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper194.cpp $
 * $Id: mapper194.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace
{
void	Sync (void)
{
	MMC3::SyncMirror();
	MMC3::SyncPRG(0x3F, 0);
	MMC3::SyncWRAM();
	for (int i = 0; i < 8; i++)
	{
		uint8_t bank = MMC3::GetCHRBank(i);
		if ((bank & 0xFE) == 0x00)
			EMU->SetCHR_RAM1(i, bank & 0x01);
		else	EMU->SetCHR_ROM1(i, bank & 0xFF);
	}
}

BOOL	MAPINT	Load (void)
{
	MMC3::Load(Sync);
	iNES_SetSRAM();
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	MMC3::Reset(ResetType);
}
void	MAPINT	Unload (void)
{
	MMC3::Unload();
}

uint16_t MapperNum = 194;
} // namespace

const MapperInfo MapperInfo_194 =
{
	&MapperNum,
	_T("Mapper 194 (Pirate MMC3)"),
	COMPAT_NEARLY,
	Load,
	Reset,
	Unload,
	NULL,
	MMC3::PPUCycle,
	MMC3::SaveLoad,
	NULL,
	NULL
};
