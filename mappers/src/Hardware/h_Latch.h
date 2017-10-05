/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/Hardware/h_Latch.h $
 * $Id: h_Latch.h 1355 2017-09-23 17:47:18Z quietust $
 */

#pragma once

#include	"..\interface.h"

#define	BUS_CONFLICTS	/* Enable bus conflicts */

namespace Latch
{
extern uint8_t Data;
extern uint16_n Addr;

void		Load		(FSync,BOOL);
void		Reset		(RESET_TYPE);
void		Unload		(void);
int	MAPINT	SaveLoad_AD	(STATE_TYPE,int,unsigned char *);
int	MAPINT	SaveLoad_AL	(STATE_TYPE,int,unsigned char *);
int	MAPINT	SaveLoad_A	(STATE_TYPE,int,unsigned char *);
int	MAPINT	SaveLoad_D	(STATE_TYPE,int,unsigned char *);
void	MAPINT	Write		(int,int,int);
} // namespace Latch
