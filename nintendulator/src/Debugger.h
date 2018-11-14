/* Nintendulator - Win32 NES emulator written in C++
 * Copyright (C) QMT Productions
 *
 * $URL: file:///svn/p/nintendulator/code/nintendulator/trunk/src/Debugger.h $
 * $Id: Debugger.h 1353 2017-09-23 00:27:51Z quietust $
 */

#pragma once

#ifdef	ENABLE_DEBUGGER

#define DEBUG_MODE_CPU			0x01
#define DEBUG_MODE_PAL			0x02
#define DEBUG_MODE_PT			0x04
#define DEBUG_MODE_PAL_PT		(DEBUG_MODE_PAL | DEBUG_MODE_PT)
#define DEBUG_MODE_NT			0x08
#define DEBUG_MODE_ALL1			(DEBUG_MODE_PAL_PT | DEBUG_MODE_NT)
#define DEBUG_MODE_SPR			0x10
#define DEBUG_MODE_DUMPS		0x20
#define DEBUG_MODE_ALL2			(DEBUG_MODE_ALL1 | DEBUG_MODE_SPR | DEBUG_MODE_DUMPS | DEBUG_MODE_CPU)
#define DEBUG_MODE_MEMFOLLOW	0x40
#define DEBUG_MODE_MASTERDUMP	0x80
#define DEBUG_MODE_LOGGER		0x100

#define DEBUG_MODE_ALL			0xFFFF
#define DEBUG_MODE_NONGRAPHICS	(DEBUG_MODE_CPU | DEBUG_MODE_DUMPS | DEBUG_MODE_MEMFOLLOW | DEBUG_MODE_MASTERDUMP)
#define DEBUG_MODE_GRAPHICS		(DEBUG_MODE_PAL_PT | DEBUG_MODE_NT | DEBUG_MODE_SPR)

#define DEBUG_TRACELINES		13
#define DEBUG_DETAILLINES		10

#define	DEBUG_BREAK_NOTHING		0x00
#define	DEBUG_BREAK_EXEC		0x01
#define	DEBUG_BREAK_READ		0x02
#define	DEBUG_BREAK_WRITE		0x04
#define	DEBUG_BREAK_READWRITE	(DEBUG_BREAK_READ | DEBUG_BREAK_WRITE)
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

#define D_PAL_S		16
#define D_PAL_W		(16 * D_PAL_S)
#define D_PAL_H		(2 * D_PAL_S)

#define D_PAT_W 	256
#define D_PAT_H		128

#define D_NAM_W		512
#define D_NAM_H		480

#define D_SPR_S		2
#define D_SPR_W		(64 * D_SPR_S)
#define D_SPR_H		(128 * D_SPR_S)

#define D_DET_W		260
#define D_DET_H		200

#define D_DET_TILE_S	8
#define D_DET_TILE_X	190
#define D_DET_TILE_Y	10

#define DEBUG_BACKGROUND		COLOR_BTNFACE
#define DEBUG_FONTWIDTH			7
#define DEBUG_FONTHEIGHT		12
#define DEBUG_FONTSPACING		2

namespace Debugger
{
extern BOOL	Enabled, EnabledGraphics;
extern int	Mode;

extern BOOL	NTabChanged, PalChanged, PatChanged, SprChanged, DetChanged;

extern BOOL	Step;
// resetstep = means we did a reset and there is a BP that is for that line
// execute BPs are for the next instruction, and this causes us to miss the reset instruction
extern BOOL ResetStep;
extern int	StepOver, StepOut;

// rveach: making this visible to all
enum ADDRMODE { IMP, ACC, IMM, ADR, ABS, IND, REL, ABX, ABY, ZPG, ZPX, ZPY, INX, INY, ERR, NUM_ADDR_MODES };

extern const enum ADDRMODE TraceAddrMode[256];
extern const unsigned char AddrBytes[NUM_ADDR_MODES];
extern const char TraceArr[256][5];

extern unsigned int		romHeaderSize;
extern unsigned int		PRGSize, CHRSize;
extern unsigned int		numPRG, numCHR;

void	Init (void);
void	Destroy (void);
void	SetMode(int NewMode);
void	Update (int UpdateMode);
void	AddInst (void);
} // namespace Debugger
#endif	/* !ENABLE_DEBUGGER */
