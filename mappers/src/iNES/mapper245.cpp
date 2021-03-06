/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper245.cpp $
 * $Id: mapper245.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

// need access to these internals, since I don't feel like copy/pasting the entire MMC3 here
namespace MMC3
{
extern uint8_t Cmd;
extern uint8_t CHR[8];
}
namespace
{
void	Sync (void)
{
	MMC3::SyncMirror();
	MMC3::SyncWRAM();
	MMC3::SyncPRG(0x3F, (MMC3::CHR[0] & 0x2) << 5);
	if (!ROM->INES_CHRSize)
	{
		EMU->SetCHR_RAM4(0, ((MMC3::Cmd & 0x80) >> 7) ^ 0);
		EMU->SetCHR_RAM4(4, ((MMC3::Cmd & 0x80) >> 7) ^ 1);
	}
	else	MMC3::SyncCHR_ROM(0xFF, 0);
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

uint16_t MapperNum = 245;
} // namespace

const MapperInfo MapperInfo_245 =
{
	&MapperNum,
	_T("Waixing MMC3 clone"),
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
