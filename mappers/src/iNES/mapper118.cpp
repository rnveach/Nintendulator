/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper118.cpp $
 * $Id: mapper118.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace
{
void	Sync (void)
{
	MMC3::SyncPRG(0x3F, 0);
	MMC3::SyncWRAM();
	MMC3::SyncCHR_ROM(0x7F, 0);
	EMU->SetCHR_NT1(0x8, (MMC3::GetCHRBank(0) & 0x80) >> 7);
	EMU->SetCHR_NT1(0x9, (MMC3::GetCHRBank(1) & 0x80) >> 7);
	EMU->SetCHR_NT1(0xA, (MMC3::GetCHRBank(2) & 0x80) >> 7);
	EMU->SetCHR_NT1(0xB, (MMC3::GetCHRBank(3) & 0x80) >> 7);
	EMU->SetCHR_NT1(0xC, (MMC3::GetCHRBank(4) & 0x80) >> 7);
	EMU->SetCHR_NT1(0xD, (MMC3::GetCHRBank(5) & 0x80) >> 7);
	EMU->SetCHR_NT1(0xE, (MMC3::GetCHRBank(6) & 0x80) >> 7);
	EMU->SetCHR_NT1(0xF, (MMC3::GetCHRBank(7) & 0x80) >> 7);
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

uint16_t MapperNum = 118;
} // namespace

const MapperInfo MapperInfo_118 =
{
	&MapperNum,
	_T("TKSROM/TLSROM (MMC3)"),
	COMPAT_FULL,
	Load,
	Reset,
	Unload,
	NULL,
	MMC3::PPUCycle,
	MMC3::SaveLoad,
	NULL,
	NULL
};
