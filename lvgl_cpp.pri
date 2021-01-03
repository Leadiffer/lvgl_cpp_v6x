
ALL_HEADERS = $$files($$PWD/*.h,true)
ALL_SOURCES = $$files($$PWD/*.c,true) $$files($$PWD/*.cpp,true) $$files($$PWD/*.hpp,true) $$files($$PWD/*.ipp,true)
ALL_DISTFILES = $$files($$PWD/*/CMakeLists.txt,true) $$files($$PWD/*/Kconfig,true)

SOURCES *= $$ALL_SOURCES
HEADERS *= $$ALL_HEADERS
DISTFILES *= $$ALL_DISTFILES

# add include paths
for(HFILE,ALL_HEADERS){
    HFILE_ABS_DIR = $$dirname(HFILE)
    INCLUDEPATH *= $$FILE_DIR

    HFILE_REL_DIR = $$relative_path($$HFILE_ABS_DIR,$$PWD)
    HFILE_DIR_NODES = $$split(HFILE_REL_DIR,"/")
    TEP_PATH = ""
    for(PATH_NODE,HFILE_DIR_NODES){
        TEP_PATH += $$PATH_NODE
        INCLUDEPATH *= $$join(TEP_PATH,"/","$$PWD/")
    }
}
