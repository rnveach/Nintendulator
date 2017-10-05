/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper227.cpp $
 * $Id: mapper227.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\DLL\d_iNES.h"
#include	"..\Hardware\h_Latch.h"

namespace
{
void	Sync (void)
{
	// rveach: eclipse doesn't support anonymous unions with anonymous structs
	union temp_union
	{
		struct
		{
			unsigned PRGsize : 1;
			unsigned Mir_HV  : 1;
			unsigned PRG16   : 1;
			unsigned PRGbank : 4;
			unsigned CHRprot : 1;
			unsigned PRGchip : 1;
			unsigned LastBank: 1;
			unsigned         : 9;
		};
		uint16_t addr;
	};
	temp_union temp_var;

	temp_var.addr = Latch::Addr.s0;

	if (temp_var.Mir_HV)
		EMU->Mirror_H();
	else	EMU->Mirror_V();
	if (temp_var.PRGsize)
		EMU->SetPRG_ROM32(0x8, (temp_var.PRGchip << 4) | (temp_var.PRGbank));
	else
	{
		EMU->SetPRG_ROM16(0x8, (temp_var.PRGchip << 5) | (temp_var.PRGbank << 1) | (temp_var.PRG16));
		EMU->SetPRG_ROM16(0xC, (temp_var.PRGchip << 5) | (temp_var.PRGbank << 1) | (temp_var.PRG16));
	}

	if (temp_var.CHRprot)
	{
		for (int i = 0; i < 8; i++)
		{
			EMU->SetCHR_RAM1(i, i);
			EMU->SetCHR_Ptr1(i, EMU->GetCHR_Ptr1(i), FALSE);
		}
	}
	else
	{	EMU->SetCHR_RAM8(0, 0);
		if (temp_var.LastBank)
			EMU->SetPRG_ROM16(0xC, (temp_var.PRGchip << 5) | (temp_var.PRGbank << 1) |  7);
		else	EMU->SetPRG_ROM16(0xC, (temp_var.PRGchip << 5) | (temp_var.PRGbank << 1) & ~7);
	}
}

BOOL	MAPINT	Load (void)
{
	Latch::Load(Sync, FALSE);
	return TRUE;
}
void	MAPINT	Reset (RESET_TYPE ResetType)
{
	Latch::Reset(ResetType);
}
void	MAPINT	Unload (void)
{
	Latch::Unload();
}

uint16_t MapperNum = 227;
} // namespace

const MapperInfo MapperInfo_227 =
{
	&MapperNum,
	_T("1200-in-1"),
	COMPAT_FULL,
	Load,
	Reset,
	Unload,
	NULL,
	NULL,
	Latch::SaveLoad_A,
	NULL,
	NULL
};
