#ifndef __MYINTERRUPT_H
#define __MYINTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*myVoidFuncPtr)(void);

void myAttachInterrupt(void (*userFunc)(void));
void myDetachInterrupt(void);

#ifdef __cplusplus
}
#endif

#endif /* end __MYINTERRUPT_H */
