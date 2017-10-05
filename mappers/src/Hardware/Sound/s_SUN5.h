/* Nintendulator Mapper DLLs
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/mappers/trunk/src/Hardware/Sound/s_SUN5.h $
 * $Id: s_SUN5.h 1352 2017-09-23 00:20:15Z quietust $
 */

#pragma once

namespace SUN5sound
{
void		Load		(void);
void		Reset		(RESET_TYPE);
void		Unload		(void);
void		Write		(int,int);
int	MAPINT	Get		(int);
int	MAPINT	SaveLoad	(STATE_TYPE,int,unsigned char *);
} // namespace SUN5sound
