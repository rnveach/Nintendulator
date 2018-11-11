#ifndef MasterDump_H
#define MasterDump_H

#ifdef	ENABLE_DEBUGGER

namespace MasterDump
{

void	Init (void);
void	Destroy (void);
void	Update (void);
void	Save (void);
void	Load (void);

} // namespace MasterDump

#endif	/* !ENABLE_DEBUGGER */

#endif	/* !MASTERDUMP_H */
