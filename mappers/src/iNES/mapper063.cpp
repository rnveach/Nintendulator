/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/iNES/mapper063.cpp $
 * $Id: mapper063.cpp 1355 2017-09-23 17:47:18Z quietust $
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
			unsigned Mir_HV  : 1;
			unsigned PRGsizeL: 1;
			unsigned PRG16   : 1;
			unsigned PRGbank : 7;
			unsigned         : 1;
			unsigned PRGhigh : 1;
			unsigned         : 4;
		};
		uint16_t addr;
	};
	temp_union temp_var;

	temp_var.addr = Latch::Addr.s0;

	EMU->SetCHR_RAM8(0, 0);
	
	if ((temp_var.PRGbank & 0x60) == 0x60)
		for (int i = 0x8; i < 0x10; i++)
			EMU->SetPRG_OB4(i);
	if (temp_var.PRGsizeL)
		EMU->SetPRG_ROM32(0x8, temp_var.PRGbank);
	else
	{
		EMU->SetPRG_ROM16(0x8, (temp_var.PRGbank << 1) | temp_var.PRG16);
		EMU->SetPRG_ROM16(0xC, (temp_var.PRGbank << 1) | temp_var.PRG16);
	}
	if (temp_var.PRGhigh)
		EMU->SetPRG_ROM8(0xE, ((temp_var.PRGbank & 0x1F) << 2) | ((temp_var.PRGsizeL ? 1 : temp_var.PRG16) << 1) | 1);
	if (temp_var.Mir_HV)
		EMU->Mirror_H();
	else	EMU->Mirror_V();

	if (temp_var.PRGbank == 0)
	{	// hack
		EMU->GetPRG_Ptr4(0xF)[0x02A7] = 0x6F;
		EMU->GetPRG_Ptr4(0xF)[0x02A8] = 0xF2;
		EMU->GetPRG_Ptr4(0xF)[0x028A] = 0x6F;
		EMU->GetPRG_Ptr4(0xF)[0x028B] = 0xF2;
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

uint16_t MapperNum = 63;
} // namespace

const MapperInfo MapperInfo_063 =
{
	&MapperNum,
	_T("Hello Kitty 255 in 1"),
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
