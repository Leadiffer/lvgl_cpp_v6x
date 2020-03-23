/**
 * @file LVLog.h
 *
 */

#pragma once

#ifndef LVLOG_H_
#define LVLOG_H_


/*********************
 *      INCLUDES
 *********************/
#include <lv_misc/lv_log.h>
#include "../LVCore/LVCallBack.h"
#include "stdarg.h"

/*********************
 *      DEFINES
 *********************/

#if LV_USE_LOG
/**********************
 *      TYPEDEFS
 **********************/

class LVLog;

/*Possible log level. For compatibility declare it independently from `LV_USE_LOG`*/
enum LogLevel : lv_log_level_t
{
    LEVEL_TRACE = LV_LOG_LEVEL_TRACE , /*A lot of logs to give detailed information*/
    LEVEL_INFO  = LV_LOG_LEVEL_INFO  , /*Log important events*/
    LEVEL_WARN  = LV_LOG_LEVEL_WARN  , /*Log if something unwanted happened but didn't caused problem*/
    LEVEL_ERROR = LV_LOG_LEVEL_ERROR , /*Only critical issue, when the system may fail*/
};

/**
 * Log print function. Receives "Log Level", "File path", "Line number" and "Description".
 * same as lv_log_print_g_cb_t
 */
using LVLogPrintCallBack = LVCallBack<void(LogLevel, const char *, uint32_t, const char *),void>;

class LVLog
{
protected:

#if LV_LOG_PRINTF == 0
    static LVLogPrintCallBack & s_callback()
    {
        static LVLogPrintCallBack callback; //!< 处理日志的回调
        return callback;
    }
#endif


    LVLog(){}
    ~LVLog(){}
public:

    /**********************
     * PROTOTYPES
     **********************/

    /**
     * Register custom print/write function to call when a log is added.
     * It can format its "File path", "Line number" and "Description" as required
     * and send the formatted log message to a consol or serial port.
     * @param print_cb a function pointer to print a log
     */
#if LV_LOG_PRINTF == 0
    static void registerPrintCallBack(LVLogPrintCallBack print_cb)
    {

        s_callback() = print_cb;
        lv_log_register_print_cb((lv_log_print_g_cb_t)lvLogPrintCallBackAgent);

    }

#endif

#if LV_LOG_PRINTF == 0
    static void resetPrintCallBack( lv_log_print_g_cb_t cb = (lv_log_print_g_cb_t)defaultLogPrintCallBack)
    {
        lv_log_register_print_cb(cb);
    }

#endif

    /**
     * Add a log
     * @param level the level of log. (From `lv_log_level_t` enum)
     * @param file name of the file when the log added
     * @param line line number in the source code where the log added
     * @param dsc description of the log
     */
    static inline void add(LogLevel level, const char * file, int line, const char * dsc)
    {
        //判断是否注册了日志函数
        //if(!LVLog::s_callback())
        //    lv_log_register_print_cb((lv_log_print_g_cb_t)defaultLogPrintCallBack);

        lv_log_add(level,file,line,dsc);
    }

    static inline void addf(LogLevel level, const char * file, int line ,const char * format,...)
    {
        char tempStr[256];
        va_list args;
        va_start(args,format);
        vsprintf(tempStr,format,args);
        add(level,file,line,tempStr);
    }

#if LV_LOG_PRINTF == 0
    /**
     * @brief logPrintCallBackAgent
     *  兼容lvgl的log函数调用
     *  Receives "Log Level", "File path", "Line number" and "Description".
     * @param level
     */
    static void lvLogPrintCallBackAgent (lv_log_level_t level, const char * file, uint32_t line, const char * desc)
    {
        if(LVLog::s_callback())
            LVLog::s_callback()(LogLevel(level),file,line,desc);
    }

    static void defaultLogPrintCallBack(lv_log_level_t level, const char * file, uint32_t line, const char * desc)
    {
        static const char * lvl_prefix[] = {"Trace", "Info ", "Warn ", "Error"};
        printf("%s: %s \t(%s #%d)\n", lvl_prefix[level], desc, file, line);
    }
#endif

};

/**********************
 *      MACROS
 **********************/

#define lvTrace(format,args...) LVLog::addf(LEVEL_TRACE , __FILE__, __LINE__, format, ##args);
#define  lvInfo(format,args...) LVLog::addf(LEVEL_INFO  , __FILE__, __LINE__, format, ##args);
#define  lvWarn(format,args...) LVLog::addf(LEVEL_WARN  , __FILE__, __LINE__, format, ##args);
#define lvError(format,args...) LVLog::addf(LEVEL_ERROR , __FILE__, __LINE__, format, ##args);

//#define lvTrace(descrip) LVLog::add(LEVEL_TRACE , __FILE__, __LINE__, descrip);
//#define  lvInfo(descrip) LVLog::add(LEVEL_INFO  , __FILE__, __LINE__, descrip);
//#define  lvWarn(descrip) LVLog::add(LEVEL_WARN  , __FILE__, __LINE__, descrip);
//#define lvError(descrip) LVLog::add(LEVEL_ERROR , __FILE__, __LINE__, descrip);

#else /*LV_USE_LOG*/

/*Do nothing if `LV_USE_LOG  0`*/
#define lvTrace(dsc,args...) {;}
#define lvInfo(dsc,args...)  {;}
#define lvWarn(dsc,args...)  {;}
#define lvError(dsc,args...) {;}
#endif /*LV_USE_LOG*/


#endif /*LVLOG_H_*/
