/* Copyright 2014 Adobe Systems Incorporated (http://www.adobe.com/). All Rights Reserved.
This software is licensed as OpenSource, under the Apache License, Version 2.0. This license is available at: http://opensource.org/licenses/Apache-2.0. */
/***********************************************************************/
/* enum.c */


#include "ac.h"
#include "bftoac.h"
#include "machinedep.h"

int IncludeFile(struct direct * direntry)
{

  if (strcmp(direntry->d_name, ".notdef") == 0) 
	return(TRUE); /* added 22Apr98 */

  /* skip dot and .BAK files */
  if (direntry->d_name[0] != '.' && !BAKFile(direntry->d_name))
    return (TRUE);
  return (FALSE);
}

boolean DoAllIgnoreTime(extracolor, includefile)
boolean extracolor;
	int (*includefile) (const struct direct *);
{
  indx ix;
  boolean result = TRUE;
  int16_t count;
  struct direct **namelist;
 
  count = BFscandir(inPrefix, &namelist, includefile, bf_alphasort);
  if (count == -1)
  {
    sprintf(globmsg, "Can't read the %s directory.\n", inPrefix);
    LogMsg(globmsg, LOGERROR, NONFATALERROR, TRUE);
  }
  
  for (ix = 0; ix < count; ix++)
    if (!DoFile(namelist[ix]->d_name, extracolor)) 
    {
      result = FALSE; 
      continue; 
    }
	ACFREEMEM(namelist);
  return result;
  }

boolean DoArgsIgnoreTime(cnt, nms, extracolor)
int cnt; char *nms[]; boolean extracolor; {
  int i;
  boolean result = TRUE;
  
  for (i = 0; i < cnt; i++) {
    if (!DoFile(nms[i], extracolor))
      result = FALSE;
    }
  return result;
  }

