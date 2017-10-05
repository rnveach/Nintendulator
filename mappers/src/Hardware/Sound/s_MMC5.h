/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/Hardware/Sound/s_MMC5.h $
 * $Id: s_MMC5.h 1352 2017-09-23 00:20:15Z quietust $
 */

#pragma once

namespace MMC5sound
{
void		Load		(void);
void		Reset		(RESET_TYPE);
void		Unload		(void);
void		Write		(int,int);
int		Read		(int);
int	MAPINT	Get		(int);
int	MAPINT	SaveLoad	(STATE_TYPE,int,unsigned char *);
BOOL		HaveIRQ		(void);
} // namespace MMC5sound
