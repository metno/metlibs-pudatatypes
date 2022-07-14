#ifndef METLIBS_PUDATATYPES_VERSION_H
#define METLIBS_PUDATATYPES_VERSION_H

#define METLIBS_PUDATATYPES_VERSION_MAJOR 6
#define METLIBS_PUDATATYPES_VERSION_MINOR 0
#define METLIBS_PUDATATYPES_VERSION_PATCH 4

#define METLIBS_PUDATATYPES_VERSION_INT(major,minor,patch) \
    (1000000*major + 1000*minor + patch)
#define METLIBS_PUDATATYPES_VERSION_CURRENT_INT \
    METLIBS_PUDATATYPES_VERSION_INT(METLIBS_PUMET_VERSION_MAJOR, METLIBS_PUMET_VERSION_MINOR, METLIBS_PUMET_VERSION_PATCH)

#endif // METLIBS_PUDATATYPES_VERSION_H
