file(GLOB_RECURSE SOURCES *.cpp *.c)
idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS .
                    REQUIRES lvgl)
#定义宏来使用全中文字集
#add_definitions(-DFONT_FULL_CHINESE)