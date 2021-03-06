/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/BMC/BMC_Super1Min1.cpp $
 * $Id: BMC_Super1Min1.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"
#include	"..\..\Hardware\h_MMC3.h"

namespace
{
uint8_t Regs[4];
uint8_t Pos;

void	Sync (void)
{
	MMC3::SyncMirror();
	MMC3::SyncPRG(~Regs[3] & 0x3F, Regs[1]);
	MMC3::SyncCHR_ROM(0xFF >> ((~Regs[2]) & 0xF), (Regs[0]) | ((Regs[2] & 0xF0) << 4));
	MMC3::SyncWRAM();
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	offset = MMC3::SaveLoad(mode, offset, data);
	for (int i = 0; i < 4; i++)
		SAVELOAD_BYTE(mode, offset, data, Regs[i]);
	SAVELOAD_BYTE(mode, offset, data, Pos);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Write (int Bank, int Addr, int Val)
{
	MMC3::CPUWrite67(Bank, Addr, Val);
	if (Regs[3] & 0x40)
		return;
	Regs[Pos++] = Val;
	Pos &= 0x03;
	Sync();
}

BOOL	MAPINT	Load (void)
{
	MMC3::Load(Sync);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	if (ResetType == RESET_HARD)
	{
		for (int i = 0; i < 4; i++)
			Regs[i] = 0;
		Pos = 0;
	}
	MMC3::Reset(ResetType);

	EMU->SetCPUWriteHandler(0x6, Write);
	EMU->SetCPUWriteHandler(0x7, Write);
}
void	MAPINT	Unload (void)
{
	MMC3::Unload();
}
} // namespace

const MapperInfo MapperInfo_BMC_Super1Min1 =
{
	"BMC-Super1Min1",
	_T("Pirate multicart mapper"),
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
