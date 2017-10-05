/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/nintendulator/trunk/src/AVI.h $
 * $Id: AVI.h 1353 2017-09-23 00:27:51Z quietust $
 */

#pragma once

DECLARE_HANDLE(HAVI);

namespace AVI
{
extern HAVI handle;

void	Init		(void);
void	Start		(void);
void	AddVideo	(void);
void	AddAudio	(void);
void	End		(void);
} // namespace AVI
