#ifndef LIEPA_UNRAR_H
#define LIEPA_UNRAR_H
#ifdef __cplusplus
extern "C" {
#endif
/// Extract every entry of the .rar at rarPath into destDir.
/// Returns 0 on success, negative on error.
int liepa_unrar_extract(const char *rarPath, const char *destDir);
#ifdef __cplusplus
}
#endif
#endif
