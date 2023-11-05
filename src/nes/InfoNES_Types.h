/*===================================================================*/
/*                                                                   */
/*  InfoNES_Types.h : Type definitions for InfoNES                   */
/*                                                                   */
/*  2000/5/4    InfoNES Project ( based on pNesX )                   */
/*                                                                   */
/*===================================================================*/

#ifndef InfoNES_TYPES_H_INCLUDED
#define InfoNES_TYPES_H_INCLUDED

/*-------------------------------------------------------------------*/
/*  Type definition                                                  */
/*-------------------------------------------------------------------*/
#ifndef DWORD
typedef unsigned long  DWORD;
#endif /* !DWORD */

#ifndef WORD
typedef unsigned short WORD;
#endif /* !WORD */

#ifndef BYTE
typedef unsigned char  BYTE;
#endif /* !BYTE */

/*-------------------------------------------------------------------*/
/*  NULL definition                                                  */
/*-------------------------------------------------------------------*/
#ifndef NULL
#define NULL  0
#endif /* !NULL */

/*-------------------------------------------------------------------*/
/*  Config 				                                                   */
/*-------------------------------------------------------------------*/
#define WORKFRAME_DOUBLE 2
#define WORKFRAME_SINGLE 1
#define WORKFRAME_NONE	 0

#if 1
#define WORKFRAME_DEFINE WORKFRAME_NONE
#define APU_NONE
#define TRANSPARENT_COLOR	0x0020
typedef WORD  PIXEL;
#define RAM_LACK  
#endif

#ifdef __MULTIPLATFORM__
#define WORKFRAME_DEFINE WORKFRAME_SINGLE
#define APU_NONE
#define TRANSPARENT_COLOR	0x00000001
typedef DWORD  PIXEL;
#define RAM_LACK  
#endif

#ifndef WORKFRAME_DEFINE
#define WORKFRAME_DEFINE WORKFRAME_SINGLE
#define TRANSPARENT_COLOR	0x8000
typedef WORD  PIXEL;
//#define RAM_LACK  
#endif


#endif /* !InfoNES_TYPES_H_INCLUDED */
