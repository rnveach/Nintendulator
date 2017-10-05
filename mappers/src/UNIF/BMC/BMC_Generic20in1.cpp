/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/BMC/BMC_Generic20in1.cpp $
 * $Id: BMC_Generic20in1.cpp 1355 2017-09-23 17:47:18Z quietust $
 */

#include	"..\..\DLL\d_UNIF.h"
#include	"..\..\Hardware\h_Latch.h"

namespace
{
void	Sync (void)
{
	// rveach: eclipse doesn't support anonymous unions with anonymous structs
	union temp_union
	{
		struct
		{
			unsigned         : 1;
			unsigned PRG     : 4;
			unsigned PRGsize : 1;
			unsigned Mirror  : 2;
			unsigned         : 8;
		};
		uint16_t addr;
	};
	temp_union temp_var;

	temp_var.addr = Latch::Addr.s0;
	
	EMU->SetCHR_RAM8(0, 0);
	if (temp_var.PRGsize)
		EMU->SetPRG_ROM32(0x8, temp_var.PRG);
	else
	{
		EMU->SetPRG_ROM16(0x8, temp_var.PRG << 1);
		EMU->SetPRG_ROM16(0x8, temp_var.PRG << 1);
	}
	switch (temp_var.Mirror)
	{
	case 0:	EMU->Mirror_S0();		break;
	case 1:	EMU->Mirror_V();		break;
	case 2:	EMU->Mirror_H();		break;
	case 3:	EMU->Mirror_Custom(0, 1, 1, 1);	break;
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
} // namespace

const MapperInfo MapperInfo_BMC_Generic20in1 =
{
	"BMC-Generic20in1",
	_T("Pirate multicart mapper"),
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
