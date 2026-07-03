// iOS interface bridging the LithUSS engine (initLUSS/synthesizeWholeText) to
// the Liepa_* C API consumed by Swift.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LithUSS.h"
#include "LithUSS_Error.h"
#include "LiepaTTS_interface.h"

static char  g_mainDir[1152] = "";
static char  g_voiceFolder[64] = "Regina/";
static char  g_loadedVoiceDir[1216] = "";
static short *g_outbuf = NULL;

static const char* mapVoice(const void *voice) {
    if (voice == NULL) return "Regina/";
    const char *v = (const char*)voice;
    if (strcmp(v, "en-ZA") == 0) return "Edvardas/";
    if (strcmp(v, "en-US") == 0) return "Aiste/";
    if (strcmp(v, "en-GB") == 0) return "Vladas/";
    return "Regina/"; // en-AU or unknown
}

extern "C" void Liepa_SetVoiceFolder(const char *folder) {
    if (folder && folder[0]) { strncpy(g_voiceFolder, folder, sizeof(g_voiceFolder)-1); g_voiceFolder[sizeof(g_voiceFolder)-1]=0; }
}

extern "C" Liepa_ERROR Liepa_Initialize(int buflength, const char *path, int options) {
    (void)buflength; (void)options;
    snprintf(g_mainDir, sizeof(g_mainDir), "%s/liepa-data/", path);
    char vdir[1216];
    snprintf(vdir, sizeof(vdir), "%s%s", g_mainDir, g_voiceFolder);
    int hr = initLUSS(g_mainDir, vdir);
    if (hr == NO_ERR) { strncpy(g_loadedVoiceDir, vdir, sizeof(g_loadedVoiceDir)-1); return EE_OK; }
    return EE_INTERNAL_ERROR;
}

extern "C" Liepa_ERROR Liepa_Synth(const void *text, size_t size,
    int greitis, int tonas, int skaiciai, int skyryba, int santrumpos, int emoji,
    const void *voice, short **outbuf1, unsigned int *numsamples1) {

    // Ensure the requested voice is loaded (engine caches by dir).
    char vdir[1216];
    snprintf(vdir, sizeof(vdir), "%s%s", g_mainDir, mapVoice(voice));
    if (strcmp(vdir, g_loadedVoiceDir) != 0) {
        if (initLUSS(g_mainDir, vdir) != NO_ERR) return EE_INTERNAL_ERROR;
        strncpy(g_loadedVoiceDir, vdir, sizeof(g_loadedVoiceDir)-1);
    }

    int textSize = (int)size;                      // number of UTF-16 units
    int evarrsize = textSize * 2 + 100;
    if (evarrsize < 7000) evarrsize = 7000;
    unsigned int signbufsize = (unsigned int)textSize * 1250u * 4u;
    if (signbufsize < 7000u * 1250u) signbufsize = 7000u * 1250u;

    g_outbuf = (short*)realloc(g_outbuf, signbufsize * sizeof(short));
    if (!g_outbuf) return EE_INTERNAL_ERROR;
    memset(g_outbuf, 0, signbufsize * sizeof(short));
    struct event *evarr = (struct event*)malloc(evarrsize * sizeof(struct event));
    if (!evarr) return EE_INTERNAL_ERROR;

    int hr = synthesizeWholeText((unsigned short*)text, textSize, g_outbuf, &signbufsize,
                                 evarr, &evarrsize, greitis, tonas,
                                 skaiciai, skyryba, santrumpos, emoji);
    free(evarr);
    *outbuf1 = g_outbuf;
    *numsamples1 = signbufsize;
    if (hr == NO_ERR) return EE_OK;
    return (signbufsize > 0) ? EE_BUFFER_FULL : EE_INTERNAL_ERROR;
}

extern "C" Liepa_ERROR Liepa_Terminate(void) {
    unloadLibraries();
    if (g_outbuf) { free(g_outbuf); g_outbuf = NULL; }
    g_loadedVoiceDir[0] = 0;
    return EE_OK;
}
