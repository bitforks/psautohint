/* Copyright 2014 Adobe Systems Incorporated (http://www.adobe.com/). All Rights Reserved.
This software is licensed as OpenSource, under the Apache License, Version 2.0. This license is available at: http://opensource.org/licenses/Apache-2.0. */
/***********************************************************************
 * SCCS Id:    @(#)pubtypes.h	1.4
 * Changed:    7/25/95 18:37:56
 ***********************************************************************/

#ifndef _PUBTYPES_H
#define _PUBTYPES_H


/***********************************************************************/
/* THIS FILE IS PROVIDED FOR BACKWARD COMPATIBILITY ONLY!!!            */
/* Its use for new programs is not recommended because it contains     */
/* constructs that have been demonstrated to cause integration         */
/* problems.                                                           */
/***********************************************************************/

/***********************************************************************/
/* Numeric definitions                                                 */
/***********************************************************************/

#include <stdint.h>

typedef int32_t               Fixed;


typedef int32_t               Int32;
#define MAX_INT32             ((Int32)0x7FFFFFFF)
#define MIN_INT32             ((Int32)0x80000000)

typedef uint32_t              Card32;
#define MAX_CARD32            ((Card32)0xFFFFFFFF)

typedef int16_t               Int16;
#define MAX_INT16             ((Int16)0x7FFF)
#define MIN_INT16             ((Int16)0x8000)

typedef uint16_t              Card16;
#define MAX_CARD16            ((Card16)0xFFFF)

typedef uint8_t               Card8;
#define MAX_CARD8             ((Card8)0xFF)


typedef Int16                 *PInt16;
typedef Int32                 *PInt32;
typedef Card8                 *PCard8;
typedef Card16                *PCard16;
typedef Card32                *PCard32;

#define MAXInt32              MAX_INT32
#define MINInt32              MIN_INT32

typedef Int32                 integer;
#define MAXinteger            MAX_INT32
#define MINinteger            MIN_INT32
typedef Card16                cardinal;
typedef Card32                longcardinal;

#define MAXCard32             MAX_CARD32
#define MAXlongcardinal       MAX_CARD32
#define MAXunsignedinteger    MAX_CARD32
#define MAXCard16             MAX_CARD16
#define MAXcardinal           MAX_CARD16
#define MAXCard8              MAX_CARD8

/***********************************************************************/
/* Other definitions                                                   */
/***********************************************************************/
#ifndef VAXC
#define readonly
#define exitNormal 1
#define exitError 2
#else
#define exitNormal 0
#define exitError 1
#endif

#define _inline
#define _priv           extern

                                    /***********************************/
                                    /* Control Constructs              */
                                    /***********************************/
#define until(x)        while (!(x))
#define endswitch       default:;

                                    /***********************************/
                                    /* Inline Functions                */
                                    /***********************************/
#ifndef ABS
#define ABS(x) ((x)<0?-(x):(x))
#endif
#ifndef MIN
#define MIN(a,b)        ((a)<(b)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b)        ((a)>(b)?(a):(b))
#endif

                                    /***********************************/
                                    /* Declarative Sugar               */
                                    /***********************************/
#ifndef true
#define true            1
#define false           0
#endif 

typedef integer         (*PIntProc)();

                                    /***********************************/
                                    /* Canonical type for sizes of     */
                                    /* things -- will change to size_t */
                                    /* when we are completely          */
                                    /* converted to ANSI conventions.  */
                                    /***********************************/
typedef int32_t         ps_size_t;

                                    /***********************************/
                                    /* Bit fields                      */
                                    /***********************************/
#ifndef BitField
#define BitField        unsigned
#endif

                                    /***********************************/
                                    /* Reals and Fixed point           */
                                    /***********************************/
typedef float           real;
typedef real            *Preal;
typedef double          longreal;

typedef Fixed           *PFixed;

                                    /***********************************/
                                    /* Coordinates                     */
                                    /***********************************/
typedef real ACComponent;

typedef struct _t_RCd {
  ACComponent x, y;
} RCd, *PRCd;

typedef struct _t_FCd {
  Fixed x, y;
} FCd, *PFCd;

                                    /***********************************/
                                    /* Characters and strings          */
                                    /***********************************/
typedef unsigned char   character;
typedef character       *string;
typedef character       *charptr;

#ifdef NUL
#undef NUL
#endif
#define NUL             '\0'

                                    /***********************************/
                                    /* Generic Pointers                */
                                    /***********************************/
#ifndef NULL
#define NULL            0
#endif

#ifdef NIL
#undef NIL
#endif
#define NIL             NULL

typedef void            (*PVoidProc)();
                                    /* Pointer to procedure returning  */
                                    /* no result                       */
typedef Card32          GenericID;  /* Generic ID for contexts,        */
                                    /* spaces, name cache, etc.        */
                                    /* Opaque type used in public      */
                                    /* interfaces                      */

#if 0
#define BitsInGenericIndex      10
#define BitsInGenericGeneration (32 - BitsInGenericIndex)

#define MAXGenericIDIndex       ((Card32)((1<<BitsInGenericIndex) - 1))
#define MAXGenericIDGeneration  ((Card32)((1<<BitsInGenericGeneration) - 1))

typedef union {                     /* Representation of GenericID     */
  struct {
    BitField index:BitsInGenericIndex;
                                    /* Reusable component              */
    BitField generation:BitsInGenericGeneration;
                                    /* Non-reusable component          */
  } id;
  GenericID stamp;                  /* Unique combined id (index,      */
                                    /* generation)                     */
} GenericIDRec;
#endif

/***********************************************************************/
/* Following is the standard opaque handle for a stream. This is all   */
/* that most clients should need. The concrete data structure is       */
/* defined in stream.h.                                                */
/***********************************************************************/
typedef struct _t_StmRec        *Stm;

typedef struct _t_StringList {
  integer numStrings;
  integer refCnt;
  string  str[1];
                                    /* Space for additional strings    */
                                    /* is malloc'ed starting here      */
} StringList, *PStringList;

#endif/*_PUBTYPES_H*/
