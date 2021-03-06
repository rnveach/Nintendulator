/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/BMC/BMC_Generic115in1.cpp $
 * $Id: BMC_Generic115in1.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"
#include	"..\..\Hardware\h_Latch.h"

namespace
{
uint8_t Regs[4];

void	Sync (void)
{
	// rveach: eclipse doesn't support anonymous unions with anonymous structs
	union temp_union
	{
		struct
		{
			unsigned CHRbank : 6;
			unsigned PRG16   : 1;
			unsigned PRGbank : 5;
			unsigned PRGsize : 1;
			unsigned Mir_HV  : 1;
			unsigned PRGchip : 1;
			unsigned         : 1;
		};
		uint16_t addr;
	};
	temp_union temp_var;

	temp_var.addr = Latch::Addr.s0;
	EMU->SetCHR_ROM8(0, temp_var.CHRbank);
	if (temp_var.PRGsize)
	{
		EMU->SetPRG_ROM16(0x8, (temp_var.PRGchip << 6) | (temp_var.PRGbank << 1) | (temp_var.PRG16));
		EMU->SetPRG_ROM16(0xC, (temp_var.PRGchip << 6) | (temp_var.PRGbank << 1) | (temp_var.PRG16));
	}
	else	EMU->SetPRG_ROM32(0x8, (temp_var.PRGchip << 5) | temp_var.PRGbank);
	if (temp_var.Mir_HV)
		EMU->Mirror_H();
	else	EMU->Mirror_V();
}

int	MAPINT	SaveLoad (STATE_TYPE mode, int offset, unsigned char *data)
{
	offset = Latch::SaveLoad_A(mode, offset, data);
	for (int i = 0; i < 4; i++)
		SAVELOAD_BYTE(mode, offset, data, Regs[i]);
	if (mode == STATE_LOAD)
		Sync();
	return offset;
}

int	MAPINT	Read (int Bank, int Addr)
{
	if (Addr & 0x800)
		return Regs[Addr & 3];
	else	return 0;
}

void	MAPINT	Write (int Bank, int Addr, int Val)
{
	if (Addr & 0x800)
		Regs[Addr & 3] = Val & 0xF;
}

BOOL	MAPINT	Load (void)
{
	Latch::Load(Sync, FALSE);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	EMU->SetCPUReadHandler(0x5, Read);
	EMU->SetCPUWriteHandler(0x5, Write);
	Latch::Reset(ResetType);
	if (ResetType == RESET_HARD)
	{
		Regs[0] = Regs[2] = 0xF;
		Regs[1] = Regs[3] = 0x0;
	}
}
void	MAPINT	Unload (void)
{
	Latch::Unload();
}
} // namespace

const MapperInfo MapperInfo_BMC_Generic115in1 =
{
	"BMC-Generic115in1",
	_T("Pirate multicart mapper"),
	COMPAT_FULL,
	Load,
	Reset,
	Unload,
	NULL,
	NULL,
	SaveLoad,
	NULL,
	NULL
};
