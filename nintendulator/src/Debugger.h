/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/nintendulator/trunk/src/Debugger.h $
 * $Id: Debugger.h 1353 2017-09-23 00:27:51Z quietust $
 */

#pragma once

#ifdef	ENABLE_DEBUGGER

#define DEBUG_MODE_CPU	1
#define DEBUG_MODE_PPU	2

#define DEBUG_TRACELINES 13
#define DEBUG_MEMLINES 8

#define	DEBUG_BREAK_EXEC	0x01
#define	DEBUG_BREAK_READ	0x02
#define	DEBUG_BREAK_WRITE	0x04
#define	DEBUG_BREAK_OPCODE	0x08
#define	DEBUG_BREAK_NMI		0x10
#define	DEBUG_BREAK_IRQ		0x20
#define	DEBUG_BREAK_BRK		0x40
/* #define	DEBUG_BREAK_RST		0x80	/* unused */

// rveach: extended information
#define	DEBUG_BREAK_REGISTER	0x80

#define	DEBUG_DETAIL_NONE	0
#define	DEBUG_DETAIL_NAMETABLE	1
#define	DEBUG_DETAIL_SPRITE	2
#define	DEBUG_DETAIL_PATTERN	3
#define	DEBUG_DETAIL_PALETTE	4

namespace Debugger
{
extern BOOL	Enabled;
extern int	Mode;

extern BOOL	NTabChanged, PalChanged, PatChanged, SprChanged;

extern BOOL	Step;

// rveach: making this visible to all
enum ADDRMODE { IMP, ACC, IMM, ADR, ABS, IND, REL, ABX, ABY, ZPG, ZPX, ZPY, INX, INY, ERR, NUM_ADDR_MODES };

extern const enum ADDRMODE TraceAddrMode[256];
extern const unsigned char AddrBytes[NUM_ADDR_MODES];
extern const char TraceArr[256][5];

void	Init (void);
void	Destroy (void);
void	SetMode(int NewMode);
void	Update (int UpdateMode);
void	AddInst (void);
} // namespace Debugger
#endif	/* !ENABLE_DEBUGGER */
