/* Copyright 2014 Adobe Systems Incorporated (http://www.adobe.com/). All Rights Reserved.
This software is licensed as OpenSource, under the Apache License, Version 2.0. This license is available at: http://opensource.org/licenses/Apache-2.0. */

#include "basic.h"

#ifndef BUILDFONT_H
#define BUILDFONT_H

#ifdef EXECUTABLE
#define OUTPUTBUFF stdout
#else
#define OUTPUTBUFF stderr
#endif

#define ASCIIFONTNAME            "font.ps"
#define CHARSTRINGSFILENAME      ".bfees.bin"
#define COMPAFMFILE              ".bfcomposites.afm"
#define COMPFILE                 "composites.ps"
#define COMPOSITESFILENAME       ".bfees2.bin"
#define DEFAULTWIDTH             500
#define ENCFILENAME              ".bfencodingfile"
#define FONTBBOXFILENAME         ".bffontbbox"
#define FONTSTKLIMIT             22
                                    /*****************************************/
                                    /* font interpreter stack limit - Note   */
                                    /* that the actual limit is 24, but      */
                                    /* because the # of parameters and       */
                                    /* callothersubr # are also pushed on    */
                                    /* the stack, the effective value is 22. */
                                    /*****************************************/
#define INTEGER 0
#define KERNAFMFILE              "kerning.afm"
#define MAXBYTES                 13000
                                    /*****************************************/
                                    /* max number of bytes in a decrypted    */
                                    /* bez file or encoded charstring        */
                                    /*****************************************/
#define MAXCHARNAME              37
                                    /*****************************************/
                                    /* max character name length (including  */
                                    /* byte for null terminator) - a bug in  */
                                    /* early LW ROMs limits PS names to      */
                                    /* 36 bytes                              */
                                    /*****************************************/
#define MAXCHARS                 400
                                    /*****************************************/
                                    /* max characters in a font (including   */
                                    /* composites)                           */
                                    /*****************************************/
#define MAXENCLINE               65000
                                    /*****************************************/
                                    /* linelength used when encrypting       */
                                    /*****************************************/
#define MAXFILENAME              32
                                    /*****************************************/
                                    /* max relative file name length         */
                                    /* (including byte for null terminator)  */
                                    /* - limit imposed by max Mac filename   */
                                    /* length - note that max Mac foldername */
                                    /* would be 34 chars because of colons   */
                                    /* and that for root is 29 chars         */
                                    /*****************************************/
#ifndef MAXINT
#define MAXINT                   32767
#endif
#define MAXLINE                  1000
                                    /*****************************************/
                                    /* maximum length of a line              */
                                    /*****************************************/
#ifndef MININT
#define MININT                   -32768
#endif
#define MULTIFONTBBOXFILENAME    ".bfmultifontbbox"
#define SCALEDHINTSINFO          "scaledhintsinfo"
#define SUBRSFILENAME            ".bfsubrs.bin"
#define TEMPFILE                 ".bftempfile"
#define UNINITWIDTH              -1          
                                    /*****************************************/
                                    /* width value if no width seen yet      */
                                    /*****************************************/
#define UNSCALEDASCIIFONT        "font.unscaled"
#define WIDTHSFILENAME           "widths.ps"
#define diskfontmax              65000


/*****************************************************************************/
/* the following are for scanning "PostScript format" input file lines       */
/*****************************************************************************/

#define COMMENT(s)               (s[strspn(s, " \n\r\t\v\f")] == '%')
#define BLANK(s)                 (sscanf(s, "%*s") == EOF)
#define STREQ(a,b)               (((a)[0] == (b)[0]) && (strcmp((a),(b)) == 0))
#define STRNEQ(a,b)              (((a)[0] != (b)[0]) || (strcmp((a),(b)) != 0))

#define NL                       '\012'
                                    /*****************************************/
                                    /* Since the Mac treats both '\n' and    */
                                    /* '\r' as ASCII 13 (i.e. carr. return)  */
                                    /* need to define this.                  */
                                    /*****************************************/

/*****************************************************************************/
/* Defines parsing method based on fontinfo key CharacterSetFileType         */
/*****************************************************************************/
typedef enum
   {
   bf_CHARSET_STANDARD,
   bf_CHARSET_CID
   } CharsetParser;

#define BF_LAYOUTS               "layouts"
#define BF_SUBSETS               "subsets"
#define BF_STD_LAYOUT            "standard"

#define OPENERROR                2
#define OPENWARN                 1
#define OPENOK                   0

extern char bezdir[MAXPATHLEN];
extern bool scalinghints;

/*****************************************************************************/
/* Tries to open the given file with the access attribute specified.  If it  */
/* fails an error message is printed and the program exits.                  */
/*****************************************************************************/
FILE *
ACOpenFile(char *, char *, int16_t);

/*****************************************************************************/
/* Deletes the specified file from the bez directory.                        */
/*****************************************************************************/
void
DeleteBezFile(char *, char *);

/*****************************************************************************/
/* Reads successive character and file names from character set file.        */
/*****************************************************************************/
char *
ReadNames(char *, char *, int32_t *, int32_t *, FILE *);

/*****************************************************************************/
/* Reads a token from the data buffer.                                       */
/*****************************************************************************/
char *
ReadToken(char *, char *, char *, char *);

/*****************************************************************************/
/* Returns whether file has .BAK suffix.                                     */
/*****************************************************************************/
bool
BAKFile(char *);

/*****************************************************************************/
/* Reads the file composites.ps, if it exists, and attempts to create        */
/* composite chars. for those listed.                                        */
/*****************************************************************************/
int32_t
make_composites(bool, bool, int32_t *, char *, bool, char **);

/*****************************************************************************/
/* Returns the max number of composites for the font.                        */
/*****************************************************************************/
int
readcomposite(bool, indx);

/*****************************************************************************/
/* Computes the character bounding box.                                      */
/*****************************************************************************/
int
computesbandbbx(char *, char *, int32_t, BboxPtr, bool, int32_t, int32_t);

int32_t
GetMaxBytes(void);

void
SetMaxBytes(int32_t);

CharsetParser
GetCharsetParser(void);

void
SetCharsetLayout(char *fontinfoString);

char *
GetCharsetLayout(void);

/*****************************************************************************/
/* Sets the global variable charsetDir.                                      */
/*****************************************************************************/
void
set_charsetdir(char *);

/*****************************************************************************/
/* Sets the global variable matrix.                                          */
/*****************************************************************************/
int
set_matrix(char *);

/*****************************************************************************/
/* Sets the global variable uniqueIDFile.                                    */
/*****************************************************************************/
void
set_uniqueIDFile(char *);

/*****************************************************************************/
/* Transforms a point using the global variable, matrix.                     */
/*****************************************************************************/
int
TransformPoint(int32_t *, int32_t*, bool);

/*****************************************************************************/
/* Returns the name of the character set file.                               */
/*****************************************************************************/
void
getcharsetname(char *);

/*****************************************************************************/
/* Returns the name of the character set file.                               */
/*****************************************************************************/
void
setcharsetname(bool , char *, char *);

/*****************************************************************************/
/* Returns the name of the encoding file.                                    */
/*****************************************************************************/
void
get_encodingfilename(char *, bool, int);

/*****************************************************************************/
/* Make an Adobe PS font or a release font.                                  */
/*****************************************************************************/
int
makePSfont(char *, bool, bool, bool, int32_t, int32_t, int32_t);

/*****************************************************************************/
/* Make a Macintosh printer font.                                            */
/*****************************************************************************/
int
makelwfn(char *, char *, char);

/*****************************************************************************/
/* Make an IBM printer font.                                                 */
/*****************************************************************************/
int
makeibmfont(char *, char *, char);

void
GetFontMatrix(char *, char *);

/*****************************************************************************/
/* Returns the total number of input directories.                            */
/*****************************************************************************/
int16_t
GetTotalInputDirs(void);

void
SetTotalInputDirs(int16_t);

/*****************************************************************************/
/* Parse the private dict portion of an ASCII format font.                   */
/*****************************************************************************/
void
ParseFont(FILE *, FILE *, int32_t, int32_t *, int32_t *, int32_t *, int32_t *, bool);

/*****************************************************************************/
/* Program to derive printer font file name for the mac from the PostScript  */
/* printer font name.                                                        */
/*****************************************************************************/
char *
printer_filename(char *);

int
convert_PScharfile(const char *, const char *);

/*****************************************************************************/
/* Converts raw PS files to relativized bez format.                          */
/*****************************************************************************/
int
convert_rawPSfiles(bool);

void
convert_illcharfile(const char *, const char *);

void
convert_illfiles(bool);

int32_t
process_chars(bool, bool, bool, int32_t *, int32_t *, bool, bool);

void
set_scale(float *);

int16_t
strindex(char *, char *);

bool ConvertCharFiles(char *inputDir,	
				bool release,				
				float scale,				
				void (*convertFunc)(const char *, const char *)	
				);

/*****************************************************************************/
/* Creates an Adobe Font Metrics (AFM) file.                                 */
/*****************************************************************************/
int
make_afm(bool);

int
ReadWriteFile(FILE *, char *);

/*****************************************************************************/
/* Looks up a keyword in the fontinfo file and writes the value to the       */
/* given output file.                                                        */
/*****************************************************************************/
int
WriteEntry(FILE *, char *, char *, bool, bool);

/*****************************************************************************/
/* Returns whether given character is in StandardEncoding.                   */
/*****************************************************************************/
bool
InStandardEncoding(char *, int32_t *);

/*****************************************************************************/
/* Writes copyright notice and trademark information.                        */
/*****************************************************************************/
int
WriteCopyrightsAndTrademark(FILE *, char);

/*****************************************************************************/
/* Frees composite table.                                                    */
/*****************************************************************************/
void
FreeCompTab(void);

/*****************************************************************************/
/* Deallocates memory and deletes temporary files.                           */
/*****************************************************************************/
int
cleanup(int16_t);

char *
GetBaseFontPath(bool);

void
FileNameLenOK(char *);

void
CharNameLenOK(char *);

void
PathNameLenOK(char *);

uint32_t
CheckFileBufferLen(char **, char *);

void
WriteBlendEntry(FILE *, char *, char *, bool);

int
WriteStart(FILE *, const char *);

/*****************************************************************************/
/* Gets the name of the file containing the current uniqueID.                */
/*****************************************************************************/
void
getidfilename(char *);

int32_t
ACReadFile(char *, FILE *, char *, int32_t);

int32_t
getmaxcomps(void);

int32_t
getrealcomps(void);

void
get_working_dir(char *);

void
init_working_dir(void);

void
set_working_dir(void);

void
LoadSubsetData(void);

void
SetSubsetName(char *name);

char *
GetSubsetName(void);

char *
GetSubsetPath(void);

bool
UsesSubset(void);

#endif /*BUILDFONT_H*/
