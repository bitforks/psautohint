/* Copyright 2014 Adobe Systems Incorporated (http://www.adobe.com/). All Rights
Reserved.
This software is licensed as OpenSource, under the Apache License, Version 2.0.
This license is available at: http://opensource.org/licenses/Apache-2.0. */
/***********************************************************************/
/* machinedep.h - defines machine dependent procedures used by
   buildfont.

history:

Judy Lee: Mon Jul 18 14:13:03 1988
End Edit History
*/

#include "basic.h"

#ifndef MACHINEDEP_H
#define MACHINEDEP_H

#ifdef _WIN32
#include <dir.h>
#include <math.h>
#else
#include <sys/dir.h>
#endif

#define fileeof(p) feof(p)
#define fileerror(p) ferror(p)

/* zero length file to indicate that AC
   is running in current directory. */
#define ACFILE ".ACLOCK"

/* zero length file to indicate that buildfont
   is running in current directory. */
#define BFFILE ".BFLOCK"

void FlushLogMsg(void);

bool createlockfile(char*, char*);

void set_errorproc(int (*)(int16_t));

void closefiles(void);

void get_filedelimit(char*);

void get_time(time_t*);

/* Gets the date and time. */
void get_datetime(char*);

/* delimits str with / or : */
void get_filename(char*, char*, const char*);

/* Returns name of AFM file. */
void get_afm_filename(char*);

/* Returns name of IBM printer file. */
void get_ibm_fontname(char*);

/* Returns name of Mac printer file. */
void get_mac_fontname(char*);

/* Returns the full path name given ref num and dirID.
   If dirID is MININT then it returns the pathname of
   the current working directory. On UNIX it always
   returns the current working directory. */
void GetFullPathname(char*, int16_t, int32_t);

char* CheckBFPath(char*);

void GetInputDirName(char*, char*);

uint32_t ACGetFileSize(char*);

/* Checks if the character set directory exists. */
bool DirExists(char*, bool, bool, bool);

/* Checks for the existence of the specified file. */
bool FileExists(const char*, int16_t);

/* Checks for the existence of the specified file. */
bool CFileExists(const char*, int16_t);

void MoveDerivedFile(char*, char*, char*, char*);

/* Creates the resource file for the Macintosh downloadable printer font. */
void CreateResourceFile(char*);

void RenameFile(char*, char*);

void set_current_dir(char*);

void get_current_dir(char*);

void SetMacFileType(char*, char*);

void ScanBezFiles(bool, indx, bool);

void ScanDirFiles(bool, char*);

void AppendFile(char*, char*);

void FlushLogFiles(void);
void OpenLogFiles(void);
typedef int (*includeFile)(const struct direct*);
typedef int (*sortFn)(const struct direct**, const struct direct**);

#ifdef _WIN32
int BFscandir(char* dirName, struct direct*** nameList, includeFile IncludeFile,
              sortFn Sort);
#else
int BFscandir(const char* dirName, struct direct*** nameList,
              includeFile IncludeFile, sortFn Sort);
#endif
char* GetPathName(char*);

int bf_alphasort(const struct direct** f1, const struct direct** f2);

#endif /*MACHINEDEP_H*/
