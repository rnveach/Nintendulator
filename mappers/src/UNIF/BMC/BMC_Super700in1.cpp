/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/UNIF/BMC/BMC_Super700in1.cpp $
 * $Id: BMC_Super700in1.cpp 1352 2017-09-23 00:20:15Z quietust $
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
			unsigned CHRhi   : 5;
			unsigned PRGsize : 1;
			unsigned PRGchip : 1;
			unsigned Mir_HV  : 1;
			unsigned PRG     : 6;
			unsigned         : 2;

			unsigned CHRlo   : 2;
			unsigned         : 6;
		};
		struct
		{
			unsigned addr    :16;
			unsigned data    : 8;
		};
	};
	temp_union temp_var;
	temp_var.addr = Latch::Addr.s0;
	temp_var.data = Latch::Data;

	EMU->SetCHR_ROM8(0, (temp_var.CHRhi << 2) | temp_var.CHRlo);

	if (temp_var.PRGsize)
	{
		EMU->SetPRG_ROM16(0x8, (temp_var.PRGchip << 6) | temp_var.PRG);
		EMU->SetPRG_ROM16(0xC, (temp_var.PRGchip << 6) | temp_var.PRG);
	}
	else	EMU->SetPRG_ROM32(0x8, ((temp_var.PRGchip << 6) | temp_var.PRG) >> 1);

	if (temp_var.Mir_HV)
		EMU->Mirror_H();
	else	EMU->Mirror_V();
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

const MapperInfo MapperInfo_BMC_Super700in1 =
{
	"BMC-Super700in1",
	_T("Pirate multicart mapper"),
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
