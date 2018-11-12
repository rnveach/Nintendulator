#ifndef BreakPoints_H
#define BreakPoints_H

#ifdef	ENABLE_DEBUGGER

struct tBreakPoint
{
	unsigned int addr_start, addr_end;
	unsigned char type;
	bool enabled;
	unsigned char flag;
	// TODO: support opcode breakpoints

	struct tBreakPoint *prev, *next;
};

namespace BreakPoints
{

extern tBreakPoint 	*list;

void			EraseAll ();
tBreakPoint*	Get (int pos);
void			Add (tBreakPoint* nbp);
int				Delete (int pos);
TCHAR*			ToString(tBreakPoint* bp);

} // namespace MasterDump

#endif	/* !ENABLE_DEBUGGER */

#endif	/* !BREAKPOINTS_H */
