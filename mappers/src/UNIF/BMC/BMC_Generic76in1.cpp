/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/BMC/BMC_Generic76in1.cpp $
 * $Id: BMC_Generic76in1.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"

namespace
{
uint8_t Regs[2];

void	Sync (void)
{
	// rveach: eclipse doesn't support anonymous unions with anonymous structs
	union temp_union
	{
		struct
		{
			unsigned PRGbank : 5;
			unsigned PRGsize : 1;
			unsigned Mir_VH  : 1;
			unsigned PRGhi   : 2;
			unsigned         : 7;
		};
		struct
		{
			unsigned byte0   : 8;
			unsigned byte1   : 8;
		};
	};
	temp_union temp_var;

	temp_var.byte0 = Regs[0];
	temp_var.byte1 = Regs[1];

	if (temp_var.Mir_VH)
		EMU->Mirror_V();
	else	EMU->Mirror_H();
	if (temp_var.PRGsize)
	{
		EMU->SetPRG_ROM16(0x8, ((temp_var.PRGhi) << 5) | (temp_var.PRGbank));
		EMU->SetPRG_ROM16(0xC, ((temp_var.PRGhi) << 5) | (temp_var.PRGbank));
	}
	else	EMU->SetPRG_ROM32(0x8, ((temp_var.PRGhi) << 4) | (temp_var.PRGbank >> 1));
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	for (int i = 0; i < 2; i++)
		SAVELOAD_BYTE(mode, offset, data, Regs[i]);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

void	MAPINT	Write (int Bank, int Addr, int Val)
{
	Regs[Addr & 1] = Val;
	Sync();
}

void	MAPINT	Reset (RESET_TYPE ResetType)
{
	for (int i = 0x8; i < 0x10; i++)
		EMU->SetCPUWriteHandler(i, Write);
	for (int i = 0; i < 2; i++)
		Regs[i] = 0;
	Sync();
}
} // namespace

const MapperInfo MapperInfo_BMC_Generic76in1 =
{
	"BMC-Generic76in1",
	_T("Pirate multicart mapper"),
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
