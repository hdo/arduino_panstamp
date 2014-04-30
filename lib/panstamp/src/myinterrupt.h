#ifndef __MYINTERRUPT_H
#define __MYINTERRUPT_H

typedef void (*myVoidFuncPtr)(void);

void myAttachInterrupt(void (*userFunc)(void));
void myDetachInterrupt(void);

#endif /* end __MYINTERRUPT_H */
