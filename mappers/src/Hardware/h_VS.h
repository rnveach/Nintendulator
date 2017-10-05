/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/Hardware/h_VS.h $
 * $Id: h_VS.h 1352 2017-09-23 00:20:15Z quietust $
 */

#pragma once

#include	"..\interface.h"

namespace VS
{
void			Load		(void);
void			Reset		(RESET_TYPE);
void			Unload		(void);
int		MAPINT	SaveLoad	(STATE_TYPE,int,unsigned char *);
int		MAPINT	Read		(int,int);
void		MAPINT	CPUCycle	(void);
unsigned char	MAPINT	Config		(CFG_TYPE,unsigned char);
} // namespace VS
