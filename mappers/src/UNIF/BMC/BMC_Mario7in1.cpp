/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/BMC/BMC_Mario7in1.cpp $
 * $Id: BMC_Mario7in1.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"
#include	"..\..\Hardware\h_MMC3.h"

namespace
{
uint8_t WhichGame;
uint8_t DidWrite;
FCPUWrite _Write67;

void	Sync (void)
{
	uint8_t PRGmask, CHRmask;
	uint8_t PRGbank, CHRbank;

	if (WhichGame & 0x8)
	{
		PRGmask = 0x0F;
		PRGbank = WhichGame & 0x07;
	}
	else
	{
		PRGmask = 0x1F;
		PRGbank = WhichGame & 0x06;
	}
	if (WhichGame & 0x40)
	{
		CHRmask = 0x7F;
		CHRbank = ((WhichGame & 0x20) >> 3) | ((WhichGame & 0x10) >> 4) | ((WhichGame & 0x04) >> 1);
	}
	else
	{
		CHRmask = 0xFF;
		CHRbank = ((WhichGame & 0x20) >> 3) | ((WhichGame & 0x10) >> 4);
	}
	MMC3::SyncMirror();
	MMC3::SyncWRAM();
	MMC3::SyncPRG(PRGmask, PRGbank << 4);
	MMC3::SyncCHR_ROM(CHRmask, CHRbank << 7);
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	offset = MMC3::SaveLoad(mode, offset, data);
	SAVELOAD_BYTE(mode, offset, data, WhichGame);
	SAVELOAD_BYTE(mode, offset, data, DidWrite);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Write67 (int Bank, int Addr, int Val)
{
	_Write67(Bank, Addr, Val);
	if (DidWrite)
		return;
	WhichGame = Val;
	DidWrite = 1;
	Sync();
}

BOOL	MAPINT	Load (void)
{
	MMC3::Load(Sync);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	_Write67 = EMU->GetCPUWriteHandler(0x6);
	EMU->SetCPUWriteHandler(0x6, Write67);
	EMU->SetCPUWriteHandler(0x7, Write67);

	if (ResetType == RESET_HARD)
	{
		WhichGame = 0;
		DidWrite = 0;
	}

	MMC3::Reset(ResetType);
}
void	MAPINT	Unload (void)
{
	MMC3::Unload();
}
} // namespace

const MapperInfo MapperInfo_BMC_Mario7in1 =
{
	"BMC-Mario7in1",
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
