/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper228.cpp $
 * $Id: mapper228.cpp 1355 2017-09-23 17:47:18Z quietust $
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
			unsigned CHRbank : 4;
			unsigned         : 1;
			unsigned PRGsize : 1;
			unsigned PRG16   : 1;
			unsigned PRGbank : 4;
			unsigned PRGchip : 2;
			unsigned Mir_HV  : 1;
			unsigned         : 2;
		};
		uint16_t addr;
	};
	temp_union temp_var;

	uint8_t openbus = 0;
	temp_var.addr = Latch::Addr.s0;

	if (temp_var.Mir_HV)
		EMU->Mirror_H();
	else	EMU->Mirror_V();
	
	switch (temp_var.PRGchip)
	{
	case 2:	openbus = 1;	break;
	case 3:	temp_var.PRGchip = 2;	break;
	}
	if (openbus)
	{
		for (openbus = 0x8; openbus <= 0xF; openbus++)
			EMU->SetPRG_OB4(openbus);
	}
	else
	{
		if (temp_var.PRGsize)
		{
			EMU->SetPRG_ROM16(0x8, (temp_var.PRGchip << 5) | (temp_var.PRGbank << 1) | (temp_var.PRG16));
			EMU->SetPRG_ROM16(0xC, (temp_var.PRGchip << 5) | (temp_var.PRGbank << 1) | (temp_var.PRG16));
		}
		else EMU->SetPRG_ROM32(0x8, (temp_var.PRGchip << 4) | (temp_var.PRGbank));
	}
	EMU->SetCHR_ROM8(0, (temp_var.CHRbank << 2) | (Latch::Data & 0x3));
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

uint16_t MapperNum = 228;
} // namespace

const MapperInfo MapperInfo_228 =
{
	&MapperNum,
	_T("Action 52"),
	COMPAT_FULL,
	Load,
	Reset,
	Unload,
	NULL,
	NULL,
	Latch::SaveLoad_AD,
	NULL,
	NULL
};
