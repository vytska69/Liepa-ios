#include "rar.hpp"   // sets up platform types (HANDLE/UINT/PASCAL) + includes dll.hpp
#include "liepa_unrar.h"
#include <string.h>

extern "C" int liepa_unrar_extract(const char *rarPath, const char *destDir) {
    struct RAROpenArchiveDataEx od;
    memset(&od, 0, sizeof(od));
    od.ArcName = (char *)rarPath;
    od.OpenMode = RAR_OM_EXTRACT;
    HANDLE h = RAROpenArchiveEx(&od);
    if (h == 0 || od.OpenResult != 0) return -1;

    struct RARHeaderDataEx hd;
    memset(&hd, 0, sizeof(hd));
    int rc;
    while ((rc = RARReadHeaderEx(h, &hd)) == ERAR_SUCCESS) {
        if (RARProcessFile(h, RAR_EXTRACT, (char *)destDir, 0) != ERAR_SUCCESS) {
            RARCloseArchive(h);
            return -2;
        }
    }
    RARCloseArchive(h);
    return (rc == ERAR_END_ARCHIVE) ? 0 : -3;
}
