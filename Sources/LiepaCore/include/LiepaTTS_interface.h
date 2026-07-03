#ifndef __LIEPATTS_INTERFACE_H__
#define __LIEPATTS_INTERFACE_H__
#include <stddef.h>
typedef enum { EE_OK=0, EE_INTERNAL_ERROR=-1, EE_BUFFER_FULL=1, EE_NOT_FOUND=2 } Liepa_ERROR;
#ifdef __cplusplus
extern "C" {
#endif
void Liepa_SetVoiceFolder(const char *folder);
Liepa_ERROR Liepa_Initialize(int buflength, const char *path, int options);
Liepa_ERROR Liepa_Synth(const void *text, size_t size,
    int greitis, int tonas, int skaiciai, int skyryba, int santrumpos, int emoji,
    const void *voice, short **outbuf1, unsigned int *numsamples1);
Liepa_ERROR Liepa_Terminate(void);
#ifdef __cplusplus
}
#endif
#endif
