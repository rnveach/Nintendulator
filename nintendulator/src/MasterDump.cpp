#include "stdafx.h"
#include "Nintendulator.h"
#include "MapperInterface.h"
#include "Debugger.h"
#include "CPU.h"
#include "PPU.h"
#include "States.h"
#include "MasterDump.h"

#ifdef	ENABLE_DEBUGGER

namespace MasterDump {

unsigned char *data;
// data is in the form:
//		PRG
//		Bank Positions

unsigned int size, addresses, banks;

void	Init()
{
	data = NULL;
	size = addresses = banks = 0;
}

void	Destroy()
{
	if (data)
	{
		delete data;
		data = NULL;
	}
	size = addresses = banks = 0;
}

__inline void	Set(int newAddresses, int newBanks)
{
	if (data)
	{
		Destroy();
	}

	addresses = newAddresses;
	banks = newBanks;
	size = addresses + banks;

	data = new unsigned char[size];
	memset(data, 0, size);
}

__inline bool Assign(unsigned short addr, unsigned char value) {
	register int a = EI.GetPRG_ROM4(addr>> 12);
	if (a >= 0)
	{
		data[(a << 12) + (addr & 0xFFF)] |= value;
		return true;
	}

	return false;
}

__inline void AssignBank() {
	for (register int a = 0; a < 8; a++) {
		int b = EI.GetPRG_ROM4(a | 0x8);
		if (b >= 0) {
			data[addresses + b] |= (1 << a);
		}
	}
}

__inline void	Update ()
{
	register char bytes = Debugger::AddrBytes[Debugger::TraceAddrMode[CPU::Opcode]];
	register short address = CPU::OpAddr;

	// save execution and interrupts

	unsigned char firstByte = DEBUG_BREAK_EXEC | DEBUG_BREAK_OPCODE;

	if (CPU::LastNMI)
		firstByte |= DEBUG_BREAK_NMI;
	if (CPU::LastIRQ)
		firstByte |= DEBUG_BREAK_IRQ;
	if (CPU::validOpEffectiveAddress) {
		if ((CPU::OpEffectiveAddress >= 0x2000) && (CPU::OpEffectiveAddress < 0x6000)) {
			firstByte |= DEBUG_BREAK_REGISTER;
		}
	}

	if (Assign(address, firstByte))
	{
		if (--bytes)
		{
			Assign(++address, DEBUG_BREAK_EXEC);

			if (--bytes)
			{
				Assign(++address, DEBUG_BREAK_EXEC);
			}
		}
	}

	// save bank assignment

	AssignBank();	//TODO: this could be moved to bank switch routines

	// save reads/writes

	if (CPU::validOpEffectiveAddress) {
		Assign(CPU::OpEffectiveAddress, Debugger::TraceIO[CPU::Opcode]);
	}
}

void Save()
{
	if (data)
	{
		TCHAR filename[MAX_PATH];

		_stprintf(filename, _T("%s\\Dumps\\%s.mtrace"), DataPath, States::BaseFilename);

		FILE *out = _tfopen(filename, _T("wb"));

		if (out != NULL)
		{
			fwrite(data, 1, size, out);

			fclose(out);
		}
		else
		{
			MessageBox(hMainWnd, _T("Unable to open Master Dump file!"), _T("Nintendulator"), MB_OK | MB_ICONERROR);
		}
	}
}

void Load()
{
	TCHAR filename[MAX_PATH];

	_stprintf(filename, _T("%s\\Dumps\\%s.mtrace"), DataPath, States::BaseFilename);

	FILE *out = _tfopen(filename, _T("rb"));

	if (out != NULL)
	{
		fread(data, 1, size, out);

		fclose(out);
	}
	else
	{
		MessageBox(hMainWnd, _T("Unable to open Master Dump file!"), _T("Nintendulator"), MB_OK | MB_ICONERROR);
	}
}

} // namespace MasterDump

#endif	/* !ENABLE_DEBUGGER */
