/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper071.cpp $
 * $Id: mapper071.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"

namespace
{
uint8_t PRG;
uint8_t Mirror;

void	Sync (void)
{
	EMU->SetPRG_ROM16(0x8, PRG);
	EMU->SetPRG_ROM16(0xC, -1);
	EMU->SetCHR_RAM8(0, 0);
	if (Mirror & 0x80)
		iNES_SetMirroring();
	else if (Mirror & 0x10)
		EMU->Mirror_S1();
	else	EMU->Mirror_S0();
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	SAVELOAD_BYTE(mode, offset, data, PRG);
	SAVELOAD_BYTE(mode, offset, data, Mirror);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Write9 (int Bank, int Addr, int Val)
{
	Mirror = Val & 0x10;
	Sync();
}
void	MAPINT	WriteCDEF (int Bank, int Addr, int Val)
{
	PRG = Val;
	Sync();
}

void	MAPINT	Reset (RESET_TYPE ResetType)
{
	EMU->SetCPUWriteHandler(0x9, Write9);	/* Fire Hawk needs this */
	EMU->SetCPUWriteHandler(0xC, WriteCDEF);
	EMU->SetCPUWriteHandler(0xD, WriteCDEF);
	EMU->SetCPUWriteHandler(0xE, WriteCDEF);
	EMU->SetCPUWriteHandler(0xF, WriteCDEF);

	if (ResetType == RESET_HARD)
	{
		PRG = 0;
		Mirror = 0x80;
	}

	Sync();
}

uint16_t MapperNum = 71;
} // namespace

const MapperInfo MapperInfo_071 =
{
	&MapperNum,
	_T("Camerica BF9093/BF9097"),
	COMPAT_NEARLY,
	NULL,
	Reset,
	NULL,
	NULL,
	NULL,
	SaveLoad,
	NULL,
	NULL
};
