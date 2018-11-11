#ifndef MEMORYFOLLOWER_H
#define MEMORYFOLLOWER_H

#ifdef	ENABLE_DEBUGGER

namespace MemoryFollower
{

#define DEBUG_MEMORYFOLLOW_MEMORYSIZE	 5

typedef unsigned int MEMORYFOLLOW_STRUCT;

enum MEMORYFOLLOW_TYPE {
	MF_REGISTER = 0, MF_MEMORY = 1, MF_PPU = 2, MF_STACK = 3
};
enum MEMORYFOLLOW_REGISTER {
	MFR_A = 0, MFR_X = 1, MFR_Y = 2, MFR_S = 3
};

void	Init (void);
void	Destroy (void);
void	Update (void);

} // namespace MemoryFollower

#endif	/* !ENABLE_DEBUGGER */

#endif	/* !MEMORYFOLLOWER_H */
