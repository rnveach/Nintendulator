/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper049.cpp $
 * $Id: mapper049.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_MMC3.h"

namespace
{
uint8_t Reg;

void	Sync (void)
{
	MMC3::SyncMirror();
	if (Reg & 1)
		MMC3::SyncPRG(0xF, (Reg & 0xC0) >> 2);
	else	EMU->SetPRG_ROM32(0x8, (Reg & 0x30) >> 4);
	MMC3::SyncCHR_ROM(0x7F, (Reg & 0xC0) << 1);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	offset = MMC3::SaveLoad(mode, offset, data);
	SAVELOAD_BYTE(mode, offset, data, Reg);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Write (int Bank, int Addr, int Val)
{
	Reg = Val;
	Sync();
}

BOOL	MAPINT	Load (void)
{
	MMC3::Load(Sync);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	MMC3::Reset(ResetType);
	for (int i = 0x6; i < 0x8; i++)
		EMU->SetCPUWriteHandler(i, Write);
	if (ResetType == RESET_HARD)
	{
		Reg = 0;
		Sync();
	}
}
void	MAPINT	Unload (void)
{
	MMC3::Unload();
}

uint16_t MapperNum = 49;
} // namespace

const MapperInfo MapperInfo_049 =
{
	&MapperNum,
	_T("1993 Super HiK 4-in-1 (MMC3)"),
	COMPAT_FULL,
	Load,
	Reset,
	Unload,
	NULL,
	MMC3::PPUCycle,
	SaveLoad,
	NULL,
	NULL
};
