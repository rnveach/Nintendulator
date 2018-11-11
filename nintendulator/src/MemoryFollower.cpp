#include "stdafx.h"
#include "Nintendulator.h"
#include "MapperInterface.h"
#include "CPU.h"
#include "PPU.h"
#include "Debugger.h"
#include "MemoryFollower.h"

#ifdef	ENABLE_DEBUGGER

namespace MemoryFollower {

unsigned int REG[4][6], RAM[0x800][6], REGISTERS[0x20][6], PPU[0x3F20][6];
unsigned int PRG[0xB000][6];

void	Init (void)
{
	memset(&REG			, 0, sizeof(REG));
	memset(&RAM			, 0, sizeof(RAM));
	memset(&REGISTERS	, 0, sizeof(REGISTERS));
	memset(&PPU			, 0, sizeof(PPU));
	memset(&PRG			, 0, sizeof(PRG));
}

void	Destroy (void)
{
	// nothing
}

__inline MEMORYFOLLOW_STRUCT* Get_NES(MEMORYFOLLOW_TYPE type, unsigned int address, bool read)
{
	static MEMORYFOLLOW_STRUCT tmpMemFol[DEBUG_MEMORYFOLLOW_MEMORYSIZE + 1];
	int a;

	if (address == (unsigned)-1)
		return NULL;

retry:
	switch (type) {
	case MF_REGISTER:
		return REG[address & 3];
		break;
	case MF_MEMORY:
		if (address < 0x2000)
		{								//0000-1FFF
			//CPU RAM

			return RAM[address & 0x3FF];
		}
		else if (address < 0x5000)
		{
			if (address < 0x4000)
			{							//2000-3FFF
				//I/O Controls

				switch (address & 7) {
				case 2:
					return NULL;
					break;
				case 7:
					type = MF_PPU;
					address = PPU::/*VRAMAddr*/previousVRAMAddr;
					goto retry;
					//return Get_NES(MF_PPU, PPU::/*VRAMAddr*/previousVRAMAddr, read);
					break;
				default:
					if (!read)
						return REGISTERS[address & 7];
					break;
				}
			}
			else
			{							//4000-4FFF
				//I/O Controls Contd.
				if (!read)
					return REGISTERS[address % 24 + 8];
			}
		}
		else
		{								//5000-FFFF
			//PRG

			if (read)
			{
				//tmpMemFol[1] = EI.GetPRG_ROM4((unsigned short)(address) / 0x1000) * 0x1000 + ((unsigned short)(address) % 0x1000) + Debugger.headerSize;
				a = DebugPRGFileAddressFromPC(address);
				if (a < 0)
				{	//RAM PRG
					return PRG[address - 0x5000];
				}
				else
				{	//ROM PRG
					tmpMemFol[1] = a;
					tmpMemFol[0] = 1;
					return tmpMemFol;
				}
			}
			else
			{
				a = EI.GetPRG_RAM4(address >> 12);
				if (a >= 0)	//RAM PRG
					return PRG[address - 0x5000];
			}
		}
		break;
	case MF_PPU:
		if (address > 0x3FFF)
			address &= 0x3FFF;
		if (address > 0x3F1F)
			address &= 0x3F1F;

		if (address < 0x2000)
		{								//0000-1FFF
			if (read)
			{
				a = DebugPPUFileAddressFromPC(address);
				if (a < 0)
				{	//RAM CHR
					return PPU[address];
				}
				else
				{	//ROM CHR
					tmpMemFol[1] = a;
					tmpMemFol[0] = 1;
					return tmpMemFol;
				}

			}
			else
			{
				a = EI.GetCHR_RAM1(address >> 10);
				if (a >= 0)	//RAM CHR
					return PPU[address];
			}
		}
		else
		{								//2000-3F1F
			return PPU[address];
		}
		break;
	case MF_STACK:
		if (read)
			return RAM[0x100 | (CPU::SP + 1)];
		else
			return RAM[0x100 | CPU::SP];
		break;
	}

	return NULL;
}

__inline MEMORYFOLLOW_STRUCT* Get_FDS(MEMORYFOLLOW_TYPE type, unsigned int address, bool read)
{
	static MEMORYFOLLOW_STRUCT tmpMemFol[DEBUG_MEMORYFOLLOW_MEMORYSIZE + 1];

	switch (type) {
	case MF_MEMORY:
		if (address == 0x4031) {
			if (read) {
				int a = EI.GetPRG_ROM4(5); // my own customer mapper function to get file address
				if (a >= 0) {
					tmpMemFol[1] = DebugPRGFileAddress(a, CPU::ReadHandler[4](4, 0x40) & 0xFFF);
					tmpMemFol[0] = 1;
					return tmpMemFol;
				}
			}
		}
		// no break here
	default:
		return Get_NES(type, address, read);
		break;
	}

	return NULL;
}

MEMORYFOLLOW_STRUCT* Get(MEMORYFOLLOW_TYPE type, unsigned int address, bool read)
{
	switch (RI.ROMType) {
	case ROM_INES:
		return Get_NES(type, address, read);
		break;
	case ROM_FDS:
		return Get_FDS(type, address, read);
		break;
	default:
		return NULL;
	}
}

void Set(MEMORYFOLLOW_TYPE type, unsigned int address, MEMORYFOLLOW_STRUCT *in)
{
	MEMORYFOLLOW_STRUCT *temp = Get(type, address, false);
	if (temp)
	{
		if (!in)
		{
			temp[0] = 0;
		}
		else
		{
			for (int a = 0; a < DEBUG_MEMORYFOLLOW_MEMORYSIZE + 1; a++) {
				temp[a] = in[a];
			}
		}
	}
}

void Add(MEMORYFOLLOW_TYPE type, unsigned int address, MEMORYFOLLOW_STRUCT *in)
{
	if (in)
	{
		MEMORYFOLLOW_STRUCT *temp = Get(type, address, false);
		if (temp)
		{
			register unsigned int pos = 1;

			while ((temp[0] < DEBUG_MEMORYFOLLOW_MEMORYSIZE) && (in[0]+1 != pos)) {
				if (!((temp[0] > 0) && (temp[temp[0]] == in[pos])))
				{
					temp[0]++;
					temp[temp[0]] = in[pos];
				}

				pos++;
			}
		}
	}
}

// TODO: could this be incorporated into the CPU?
__inline void	Update()
{
	register const char *op = Debugger::TraceArr[CPU::Opcode];

	switch (op[1]) {
	case 'A':
		//ADC, AND
		if ((op[2] == 'D') || (op[2] == 'N')) {
			Add(MF_REGISTER, MFR_A, Get(MF_MEMORY, CPU::OpEffectiveAddress, true)); //ADC, AND
		}
		break;
	case 'E':
		//EOR
		Add(MF_REGISTER, MFR_A, Get(MF_MEMORY, CPU::OpEffectiveAddress, true));
		break;
	case 'L':
		//LDA, LDX, LDY
		if (op[2] == 'D') {
			switch (op[3]) {
			case 'A':	Set(MF_REGISTER, MFR_A, Get(MF_MEMORY, CPU::OpEffectiveAddress, true));	break; // LDA
			case 'X':	Set(MF_REGISTER, MFR_X, Get(MF_MEMORY, CPU::OpEffectiveAddress, true));	break; // LDX
			case 'Y':	Set(MF_REGISTER, MFR_Y, Get(MF_MEMORY, CPU::OpEffectiveAddress, true));	break; // LDY
			}
		}
		break;
	case 'O':
		//ORA
		Add(MF_REGISTER, MFR_A, Get(MF_MEMORY, CPU::OpEffectiveAddress, true));
		break;
	case 'P':
		//PLA, PHA
		if (op[3] == 'A') {
			if (op[2] == 'L') {
				Set(MF_REGISTER, MFR_A, Get(MF_STACK, 0, true)); // PLA
			} else if (op[2] == 'H') {
				Set(MF_STACK, 0, Get(MF_REGISTER, MFR_A, true)); // PHA
			}
		}
		break;
	case 'S':
		//STA, STX, STY
		//SBC
		if (op[2] == 'T') {
			switch (op[3]) {
			case 'A':	Set(MF_MEMORY, CPU::OpEffectiveAddress, Get(MF_REGISTER, MFR_A, true));	break; // STA
			case 'X':	Set(MF_MEMORY, CPU::OpEffectiveAddress, Get(MF_REGISTER, MFR_X, true));	break; // STX
			case 'Y':	Set(MF_MEMORY, CPU::OpEffectiveAddress, Get(MF_REGISTER, MFR_Y, true));	break; // STY
			}
		} else if (op[2] == 'B') { // SBC
			Add(MF_REGISTER, MFR_A, Get(MF_MEMORY, CPU::OpEffectiveAddress, true));
		}
		break;
	case 'T':
		//TAX, TAY, TSX, TXA, TXS, TYA
		MEMORYFOLLOW_STRUCT *tempMemFollow = NULL;

		switch (op[2]) {
		case 'A':	tempMemFollow = Get(MF_REGISTER, MFR_A, true);	break;
		case 'X':	tempMemFollow = Get(MF_REGISTER, MFR_X, true);	break;
		case 'Y':	tempMemFollow = Get(MF_REGISTER, MFR_Y, true);	break;
		case 'S':	tempMemFollow = Get(MF_REGISTER, MFR_S, true);	break;
		}

		switch (op[3]) {
		case 'A':	Set(MF_REGISTER, MFR_A, tempMemFollow);	break;
		case 'X':	Set(MF_REGISTER, MFR_X, tempMemFollow);	break;
		case 'Y':	Set(MF_REGISTER, MFR_Y, tempMemFollow);	break;
		case 'S':	Set(MF_REGISTER, MFR_S, tempMemFollow);	break;
		}
		break;
	// default:
		// ASL, BRK, DEC, DEX, DEY, INC, INX, INY, LSR, ROL, ROR
		// Pushes/Pops, Branches, Jumps, Returns, Flags
		// break;
	}
}

void GetDisplay(MEMORYFOLLOW_TYPE type, unsigned long addr, TCHAR* str, unsigned int start = 0, unsigned int count = (unsigned)-1)
{
	unsigned int a;
	MEMORYFOLLOW_STRUCT *temp = Get(type, addr, false);

	str[0] = 0;

	if (temp)
	{
		if (temp[0])
		{
			static TCHAR tpc[10];

			for (a = start+1; a < temp[0]+1; a++)
			{
				if (count)
					count--;

				_stprintf(tpc, _T("%06X"), temp[a]);
				_tcscat(str, tpc);

				if (a < temp[0])
					_tcscat(str, _T(", "));
				if (!count)
					break;
			}
		}
		else
		{
			if (!start)
				_tcscpy(str, _T("EMPTY"));
		}
	}
	else
	{
		if (!start)
			_tcscpy(str, _T("NULL"));
	}
}

} // namespace MemoryFollower

#endif	/* !ENABLE_DEBUGGER */
