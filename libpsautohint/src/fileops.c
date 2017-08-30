/*
 * Copyright 2014 Adobe Systems Incorporated (http://www.adobe.com/).
 * All Rights Reserved.
 *
 * This software is licensed as OpenSource, under the Apache License, Version
 * 2.0.
 * This license is available at: http://opensource.org/licenses/Apache-2.0.
 */

#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define getcwd _getcwd
static char Delimiter[] = "\\";
#else
#include <unistd.h>
static char Delimiter[] = "/";
#endif

#include "ac.h"
//#include "afmcharsetdefs.h"
#include "buildfont.h"
#include "charpath.h"
//#include "cryptdefs.h"
#include "fontinfo.h"

#define BAKSUFFIX ".BAK"

static char subsetPath[MAXPATHLEN];
static char subsetname[MAXPATHLEN];
static int16_t total_inputdirs = 1;  /* number of input directories           */
static int32_t MaxBytes;
char globmsg[MAXMSGLEN + 1]; /* used to format messages               */
static char initialWorkingDir[MAXPATHLEN];
static int initialWorkingDirLength;

typedef struct
{
    int lo;
    int hi;
} SubsetData;

extern bool multiplemaster; /* from buildfont.c */

int16_t strindex(char *s, char *t) /* return index of t in s, -1 if none    */
{
    indx i, n;

    n = (indx)strlen(t);
    for (i = 0; s[i] != '\0'; i++)
        if (!strncmp(s + i, t, n))
            return i;
    return -1;
}

/* Returns the full name of the input directory. */
static void GetInputDirName(char* name,
char* suffix)
{
    char currdir[MAXPATHLEN];

    getcwd(currdir, MAXPATHLEN);
    sprintf(name, "%s%s%s", currdir, Delimiter, suffix);
}

/* ACOpenFile tries to open a file with the access attribute
   specified.  If fopen fails an error message is printed
   and the program exits if severity = FATAL. */
FILE*
ACOpenFile(char* filename, char* access, int16_t severity)
{
    FILE* stream;
    char dirname[MAXPATHLEN];

    stream = fopen(filename, access);
    if (stream == NULL) {
        GetInputDirName(dirname, "");
        switch (severity) {
            case (OPENERROR):
                LogMsg(LOGERROR, NONFATALERROR,
                       "The %s file does not exist or is not "
                       "accessible (currentdir='%s').\n",
                       filename, dirname);
                break;
            case (OPENWARN):
                LogMsg(WARNING, OK, "The %s file does not exist or is not "
                                    "accessible (currentdir='%s').\n",
                       filename, dirname);
                break;
            default:
                break;
        }
    }
    return (stream);
}

void FileNameLenOK(char* filename)
{
    if (strlen(filename) >= MAXFILENAME) {
        LogMsg(LOGERROR, FATALERROR, filename, (int)MAXFILENAME);
    }
}

void CharNameLenOK(char* charname)
{
    if (strlen(charname) >= MAXCHARNAME) {
        LogMsg(LOGERROR, FATALERROR,
               "Character name: %s exceeds maximum allowable length of %d.\n",
               charname, (int)MAXCHARNAME);
    }
}

void PathNameLenOK(char* pathname)
{
    if (strlen(pathname) >= MAXPATHLEN) {
        LogMsg(LOGERROR, FATALERROR,
               "File name: %s exceeds maximum allowable length of %d.\n",
               pathname, (int)MAXPATHLEN);
    }
}

bool BAKFile(char* filename)
{
    int16_t length = (int16_t)strlen(filename);
    if (length <= 4)
        return false;
    if (!strcmp(&filename[length - 4], BAKSUFFIX))
        return true;
    return false;
}

int32_t
GetMaxBytes(void)
{
    return MaxBytes;
}

void SetMaxBytes(int32_t value)
{
    MaxBytes = value;
}

#define INCREMENT 3
static SubsetData* subsetdata = NULL;
static int allocation = INCREMENT;
static int allocated = 0;
static bool usesSubset = false;

bool
UsesSubset(void)
{
    return usesSubset;
}

void
SetSubsetName(char* name)
{
    strcpy(subsetname, name);
    subsetdata =
      (SubsetData*)AllocateMem(INCREMENT, sizeof(SubsetData), "SetSubsetName");
    usesSubset = true;
}

char*
GetSubsetName(void)
{
    return (subsetname);
}

char*
GetSubsetPath(void)
{
    return (subsetPath);
}

void
LoadSubsetData(void)
{
    FILE* fp = ACOpenFile(subsetPath, "r", OPENERROR);
    int lo;
    int hi;
    int scanned;

    while ((scanned = fscanf(fp, "%d-%d", &lo, &hi)) > 0) {
        if (scanned == 1)
            subsetdata[allocated].lo = subsetdata[allocated].hi = lo;
        else {
            subsetdata[allocated].lo = lo;
            subsetdata[allocated].hi = hi;
        }

        if (++allocated >= allocation) {
            allocation += INCREMENT;
            subsetdata = (SubsetData*)ReallocateMem(
              (char*)subsetdata, allocation * sizeof(SubsetData),
              "LoadSubsetData");
        }
    }

    fclose(fp);
}

bool
InSubsetData(int cid)
{
    int i;

    for (i = 0; i < allocated; i++) {
        if ((cid >= subsetdata[i].lo) && (cid <= subsetdata[i].hi))
            return true;
    }

    return false;
}

int16_t
GetTotalInputDirs(void)
{
    return total_inputdirs;
}

void
SetTotalInputDirs(int16_t total)
{
    total_inputdirs = total;
}

bool
IsHintRowMatch(char* hintDirName, char* rowDirName)
{
    char fontDirName[MAXPATHLEN];
    int fontDirLength;

    /**************************************************************************/
    /* It is necessary to concatenate the hintDirName and rowDirName when     */
    /* doing comparisons because each of these may involve multiple path      */
    /* components: a/b and x/y/z -> a/b/x/y/z                                 */
    /**************************************************************************/
    sprintf(fontDirName, "%s/%s/", hintDirName, rowDirName);
    fontDirLength = (int)strlen(fontDirName);
    return ((initialWorkingDirLength >= fontDirLength) &&
            (strcmp(initialWorkingDir + initialWorkingDirLength - fontDirLength,
                    fontDirName) == 0));
}
