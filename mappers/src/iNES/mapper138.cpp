/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper138.cpp $
 * $Id: mapper138.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"

namespace
{
uint8_t Cmd, CHRH, CHRL0, CHRL1, CHRL2, CHRL3, PRG, CHRO, Mirror;
FCPUWrite _Write4;

void	Sync (void)
{
	EMU->SetPRG_ROM32(0x8, PRG);
	if (Mirror & 1)
	{
		EMU->SetCHR_ROM2(0, (CHRH << 3) | CHRL0);
		EMU->SetCHR_ROM2(2, (CHRH << 3) | CHRL0);
		EMU->SetCHR_ROM2(4, (CHRH << 3) | CHRL0);
		EMU->SetCHR_ROM2(6, (CHRH << 3) | CHRL0);
	}
	else
	{
		EMU->SetCHR_ROM2(0, (CHRH << 3) | CHRL0);
		EMU->SetCHR_ROM2(2, (CHRH << 3) | CHRL1);
		EMU->SetCHR_ROM2(4, (CHRH << 3) | CHRL2);
		EMU->SetCHR_ROM2(6, (CHRH << 3) | CHRL3);
	}
	switch (Mirror >> 1)
	{
	case 0:	EMU->Mirror_Custom(0, 0, 0, 1);	break;
	case 1:	EMU->Mirror_H();		break;
	case 2:	EMU->Mirror_V();		break;
	case 3:	EMU->Mirror_S0();		break;
	}
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	SAVELOAD_BYTE(mode, offset, data, Cmd);
	SAVELOAD_BYTE(mode, offset, data, CHRH);
	SAVELOAD_BYTE(mode, offset, data, CHRL0);
	SAVELOAD_BYTE(mode, offset, data, CHRL1);
	SAVELOAD_BYTE(mode, offset, data, CHRL2);
	SAVELOAD_BYTE(mode, offset, data, CHRL3);
	SAVELOAD_BYTE(mode, offset, data, PRG);
	SAVELOAD_BYTE(mode, offset, data, CHRO);
	SAVELOAD_BYTE(mode, offset, data, Mirror);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Write (int Bank, int Addr, int Val)
{
	if (Bank == 4)
		_Write4(Bank, Addr, Val);
	Val &= 0x07;
	switch (Addr & 0x101)
	{
	case 0x100:
		Cmd = Val;	break;
	case 0x101:
		switch (Cmd)
		{
		case 0:	CHRL0 = Val;	break;
		case 1:	CHRL1 = Val;	break;
		case 2:	CHRL2 = Val;	break;
		case 3:	CHRL3 = Val;	break;
		case 4:	CHRH = Val;	break;
		case 5:	PRG = Val;	break;
		case 6:	CHRO = Val;	break;
		case 7:	Mirror = Val;	break;
		}			break;
	}
	Sync();
}

void	MAPINT	Reset (RESET_TYPE ResetType)
{
	_Write4 = EMU->GetCPUWriteHandler(0x4);
	for (int i = 0x4; i < 0x6; i++)
		EMU->SetCPUWriteHandler(i, Write);

	if (ResetType == RESET_HARD)
		Cmd = CHRH = CHRL0 = CHRL1 = CHRL2 = CHRL3 = PRG = CHRO = Mirror = 0;

	Sync();
}

uint16_t MapperNum = 138;
} // namespace

const MapperInfo MapperInfo_138 =
{
	&MapperNum,
	_T("Sachen (SA8259A)"),
	COMPAT_FULL,
	NULL,
	Reset,
	NULL,
	NULL,
	NULL,
	SaveLoad,
	NULL,
	NULL
};
