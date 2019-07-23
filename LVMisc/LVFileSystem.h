/**
 * @file lv_fs.h
 *
 */

#ifndef LVFILDSYSTEM_H
#define LVFILDSYSTEM_H

/*********************
 *      INCLUDES
 *********************/

#include <lv_misc/lv_fs.h>

#if LV_USE_FILESYSTEM

#include "LVMemory.h"
#include "LVString.h"

/*********************
 *      DEFINES
 *********************/
#define LV_FS_MAX_FN_LENGTH 64

/**********************
 *      TYPEDEFS
 **********************/
enum LVFSResult : lv_fs_res_t
{
    FS_RES_OK          = LV_FS_RES_OK ,
    FS_RES_HW_ERR      = LV_FS_RES_HW_ERR,     /*Low level hardware error*/
    FS_RES_FS_ERR      = LV_FS_RES_FS_ERR,     /*Error in the file system structure */
    FS_RES_NOT_EX      = LV_FS_RES_NOT_EX,     /*Driver, file or directory is not exists*/
    FS_RES_FULL        = LV_FS_RES_FULL,       /*Disk full*/
    FS_RES_LOCKED      = LV_FS_RES_LOCKED,     /*The file is already opened*/
    FS_RES_DENIED      = LV_FS_RES_DENIED,     /*Access denied. Check 'fs_open' modes and write protect*/
    FS_RES_BUSY        = LV_FS_RES_BUSY,       /*The file system now can't handle it, try later*/
    FS_RES_TOUT        = LV_FS_RES_TOUT,       /*Process time outed*/
    FS_RES_NOT_IMP     = LV_FS_RES_NOT_IMP,    /*Requested function is not implemented*/
    FS_RES_OUT_OF_MEM  = LV_FS_RES_OUT_OF_MEM, /*Not enough memory for an internal operation*/
    FS_RES_INV_PARAM   = LV_FS_RES_INV_PARAM,  /*Invalid parameter among arguments*/
    FS_RES_UNKNOWN     = LV_FS_RES_UNKNOWN,    /*Other unknown error*/
};

enum LVFSMode
{
    FS_MODE_WR = LV_FS_MODE_WR,
    FS_MODE_RD = LV_FS_MODE_RD,
    FS_READWRITE = FS_MODE_WR|FS_MODE_RD
};

class LVFSDirver;


class LVFile : public lv_fs_file_t
{
    LV_MEMORY
protected:
    LVString m_path;
public:
    LVFile()
    {
        file_d = nullptr;
        drv = nullptr;
    }

    LVFile(const char * path)
        :LVFile()
    {
        m_path = path;
    }

    ~LVFile()
    {
        close();
    }

    bool isNull()
    {
        return file_d == nullptr || drv == nullptr || !m_path.length();
    }

    /**
     * Open a file
     * @param file_p pointer to a lv_fs_file_t variable
     * @param path path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
     * @param mode read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
     * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    LVFSResult open(const char * path, LVFSMode mode)
    {
        m_path = path;
        return open(mode);
    }

    LVFSResult open(LVFSMode mode)
    {
        if(!isNull()) close();
        LVFSResult ret = (LVFSResult)lv_fs_open(this,m_path,mode);
        if(ret != FS_RES_OK)
        {
            LV_LOG_WARN("LVFile::open failed");
        }
        return ret;
    }

    /**
     * Close an already opened file
     * @param file_p pointer to a lv_fs_file_t variable
     * @return  LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    LVFSResult close()
    {
        return (LVFSResult)lv_fs_close(this);
    }

    /**
     * Delete a file
     * @param path path of the file to delete
     * @return  LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    static LVFSResult remove(const char * path)
    {
        return (LVFSResult)lv_fs_remove(path);
    }

    LVFSResult remove()
    {
        if(!isNull()) close();
        return (LVFSResult)lv_fs_remove(m_path);
    }

    /**
     * Read from a file
     * @param file_p pointer to a lv_fs_file_t variable
     * @param buf pointer to a buffer where the read bytes are stored
     * @param btr Bytes To Read
     * @param br the number of real read bytes (Bytes Read). NULL if unused.
     * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    LVFSResult read(void * buf, uint32_t btr, uint32_t * br = nullptr)
    {
        return (LVFSResult)lv_fs_read(this ,buf, btr,br);
    }

    /**
     * Write into a file
     * @param file_p pointer to a lv_fs_file_t variable
     * @param buf pointer to a buffer with the bytes to write
     * @param btr Bytes To Write
     * @param br the number of real written bytes (Bytes Written). NULL if unused.
     * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    LVFSResult write(const void * buf, uint32_t btw, uint32_t * bw)
    {
        return (LVFSResult)lv_fs_write(this, buf, btw, bw);
    }

    /**
     * Set the position of the 'cursor' (read write pointer) in a file
     * @param file_p pointer to a lv_fs_file_t variable
     * @param pos the new position expressed in bytes index (0: start of file)
     * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    LVFSResult seek(uint32_t pos)
    {
        return (LVFSResult)lv_fs_seek(this, pos);
    }

    /**
     * Give the position of the read write pointer
     * @param file_p pointer to a lv_fs_file_t variable
     * @param pos_p pointer to store the position of the read write pointer
     * @return LV_FS_RES_OK or any error from 'fs_res_t'
     */
    LVFSResult tell(uint32_t * pos)
    {
        return (LVFSResult)lv_fs_tell(this, pos);
    }

    /**
     * Truncate the file size to the current position of the read write pointer
     * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_fs_open )
     * @return LV_FS_RES_OK: no error, the file is read
     *         any error from lv_fs_res_t enum
     */
    LVFSResult truncate()
    {
        return (LVFSResult)lv_fs_trunc(this);
    }

    /**
     * Give the size of a file bytes
     * @param file_p pointer to a lv_fs_file_t variable
     * @param size pointer to a variable to store the size
     * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    LVFSResult size(uint32_t * size)
    {
        return (LVFSResult)lv_fs_size(this, size);
    }

    /**
     * Rename a file
     * @param oldname path to the file
     * @param newname path with the new name
     * @return LV_FS_RES_OK or any error from 'fs_res_t'
     */
    static inline LVFSResult rename(const char * oldname, const char * newname)
    {
        return (LVFSResult)lv_fs_rename(oldname,newname);
    }

    inline LVFSResult rename(const char * newname)
    {
        if(!isNull()) close();
        return (LVFSResult)lv_fs_rename(m_path,newname);
    }

    /**
     * Return with the extension of the filename
     * @param fn string with a filename
     * @return pointer to the beginning extension or empty string if no extension
     */
    inline const char * getExtension()
    {
        return lv_fs_get_ext(m_path);
    }
};

class LVDir : public lv_fs_dir_t
{
    LV_MEMORY
protected:
    LVString m_path;
public:
    LVDir()
    {
        dir_d = nullptr;
        drv = nullptr;
    }

    LVDir(const char * path)
        :LVDir()
    {
        m_path = path;
    }

    ~LVDir()
    {
        close();
    }

    bool isNull()
    {
        return dir_d == nullptr || drv == nullptr || !m_path.length();
    }

    /**
     * Initialize a 'fs_dir_t' variable for directory reading
     * @param rddir_p pointer to a 'fs_read_dir_t' variable
     * @param path path to a directory
     * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    LVFSResult open( const char * path)
    {
        m_path = path;
        return open();
    }

    LVFSResult open()
    {
        if(!isNull()) close();
        LVFSResult ret = (LVFSResult)lv_fs_dir_open(this , m_path);
        if(ret != FS_RES_OK)
        {
            LV_LOG_WARN("LVDir::open failed");
        }
        return ret;
    }

    /**
     * Read the next filename form a directory.
     * The name of the directories will begin with '/'
     * @param rddir_p pointer to an initialized 'fs_rdir_t' variable
     * @param fn pointer to a buffer to store the filename
     * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    LVFSResult read( char * fn) //NOTE:????
    {
        return (LVFSResult)lv_fs_dir_read(this, fn);
    }

    /**
     * Close the directory reading
     * @param rddir_p pointer to an initialized 'fs_dir_t' variable
     * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    LVFSResult close()
    {
        return (LVFSResult)lv_fs_dir_close(this);
    }

    /**
     * Step up one level
     * @param path pointer to a file name
     * @return the truncated file name
     */
    static inline char * up(char * path)
    {
        return lv_fs_up(path);
    }

    inline void up()
    {
        close();
        char temp[m_path.length()+1];
        strcpy(temp,m_path);
        lv_fs_up(temp);
        m_path = temp;
        open();
        return ;
    }

    /**
     * Delete a file
     * @param path path of the file to delete
     * @return  LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    static LVFSResult remove(const char * path)
    {
        return (LVFSResult)lv_fs_remove(path);
    }

    LVFSResult remove()
    {
        if(!isNull()) close();
        return (LVFSResult)lv_fs_remove(m_path);
    }
};

class LVFSDirver : public lv_fs_drv_t
{
    LV_MEMORY
public:
    LVFSDirver() {}
};

class LVFileSystem
{
    LV_MEMORY
protected:
    char m_letter;
public:
    LVFileSystem(char letter):m_letter(letter) {}


    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Initialize the File system interface
     */
    static inline void init(void)
    {
        lv_fs_init();
    }

    /**
     * Add a new drive
     * @param drv_p pointer to an lv_fs_drv_t structure which is inited with the
     * corresponding function pointers. The data will be copied so the variable can be local.
     */
    static inline void registerDirver(LVFSDirver * drv_p)
    {
        lv_fs_drv_register(drv_p);
    }

    /**
     * Test if a drive is rady or not. If the `ready` function was not initialized `true` will be
     * returned.
     * @param letter letter of the drive
     * @return true: drive is ready; false: drive is not ready
     */
    static inline bool isReady(char letter)
    {
        return lv_fs_is_ready(letter);
    }

    inline bool isReady()
    {
        return lv_fs_is_ready(m_letter);
    }

    /**
     * Get the free and total size of a driver in kB
     * @param letter the driver letter
     * @param total_p pointer to store the total size [kB]
     * @param free_p pointer to store the free size [kB]
     * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    static inline LVFSResult freeSpace(char letter, uint32_t * total_p, uint32_t * free_p)
    {
        return (LVFSResult)lv_fs_free_space( letter, total_p, free_p);
    }

    inline LVFSResult freeSpace(uint32_t * total_p, uint32_t * free_p)
    {
        return (LVFSResult)lv_fs_free_space(m_letter, total_p, free_p);
    }

    /**
     * Fill a buffer with the letters of existing drivers
     * @param buf buffer to store the letters ('\0' added after the last letter)
     * @return the buffer
     */
    static inline char * getLetters(char * buf)
    {
        return lv_fs_get_letters(buf);
    }

    /**
     * Delete a file
     * @param path path of the file to delete
     * @return  LV_FS_RES_OK or any error from lv_fs_res_t enum
     */
    static inline LVFSResult remove(const char * path)
    {
        return (LVFSResult)lv_fs_remove(path);
    }

    /**
     * Return with the extension of the filename
     * @param fn string with a filename
     * @return pointer to the beginning extension or empty string if no extension
     */
    static inline const char * getExtension(const char * fn)
    {
        return lv_fs_get_ext(fn);
    }

    /**
     * Step up one level
     * @param path pointer to a file name
     * @return the truncated file name
     */
    static inline char * up(char * path)
    {
        return lv_fs_up(path);
    }

    /**
     * Get the last element of a path (e.g. U:/folder/file -> file)
     * @param buf buffer to store the letters ('\0' added after the last letter)
     * @return pointer to the beginning of the last element in the path
     */
    static inline const char * getLast(const char * path)
    {
        return lv_fs_get_last(path);
    }

};

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_FILESYSTEM*/

#endif /*LVFILDSYSTEM_H*/
