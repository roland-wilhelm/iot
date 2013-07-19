/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * (c)Copyright 2006 Hewlett-Packard Development Company, LP.
 *
 *  Extracted from sipp project : http://sipp.sourceforge.net
 *
 */
 
#ifndef _AUTH_H
#define _AUTH_H

//#ifdef __FreeBSD__
//#include <sys/types.h>
//#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "milenage.h"

#define MAX_HEADER_LEN  2049
#define MD5_HASH_SIZE 16
#define HASH_HEX_SIZE 2*MD5_HASH_SIZE


void hashToHex (unsigned char *_b, unsigned char *_h);

int createAuthHeaderMD5(char * user, char * password, char * method,
                     char * uri, char * msgbody, char * auth, 
                     char * algo, char * result);

int createAuthHeaderAKAv1MD5(char * user, char * OP,
                             char * AMF,
                             char * K,
                             char * method,
                             char * uri, char * msgbody, char * auth, char *algo,
                             char * result);

							
#endif /* _AUTH_H */
