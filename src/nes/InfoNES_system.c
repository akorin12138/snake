/*-------------------------------------------------------------------*/
/*  InfoNES_system.c                                                 */
/*-------------------------------------------------------------------*/
#include "InfoNES.h"

#include <string.h>
#include <stdio.h>

unsigned int FrameCount=0;

//*****************************************************************************
//
// The interrupt handler for the for Systick interrupt.
//
//*****************************************************************************



//*****************************************************************************
//
// Operation of Joy
//
//*****************************************************************************



/*-------------------------------------------------------------------*/
/*  Palette data                                                     */
/*-------------------------------------------------------------------*/
WORD NesPalette[64]={
#if 0
  0x738E,0x88C4,0xA800,0x9808,0x7011,0x1015,0x0014,0x004F,
  0x0148,0x0200,0x0280,0x11C0,0x59C3,0x0000,0x0000,0x0000,
  0xBDD7,0xEB80,0xE9C4,0xF010,0xB817,0x581C,0x015B,0x0A59,
  0x0391,0x0480,0x0540,0x3C80,0x8C00,0x0000,0x0000,0x0000,
  0xFFDF,0xFDC7,0xFC8B,0xFC48,0xFBDE,0xB39F,0x639F,0x3CDF,
  0x3DDE,0x1690,0x4EC9,0x9FCB,0xDF40,0x0000,0x0000,0x0000,
  0xFFDF,0xFF15,0xFE98,0xFE5A,0xFE1F,0xDE1F,0xB5DF,0xAEDF,
  0xA71F,0xA7DC,0xBF95,0xCFD6,0xF7D3,0x0000,0x0000,0x0000,
//#else
  0x738E,0x20D1,0x0015,0x4013,0x880E,0xA802,0xA000,0x7840,
  0x4140,0x0200,0x0280,0x01C2,0x19CB,0x0000,0x0000,0x0000,
  0xBDD7,0x039D,0x21DD,0x801E,0xB817,0xE00B,0xD940,0xCA41,
  0x8B80,0x0480,0x0540,0x0487,0x0411,0x0000,0x0000,0x0000,
  0xFFDF,0x3DDF,0x5C9F,0x445F,0xF3DF,0xFB96,0xFB8C,0xFCC7,
  0xF5C7,0x8682,0x4EC9,0x5FD3,0x075B,0x0000,0x0000,0x0000,
  0xFFDF,0xAF1F,0xC69F,0xD65F,0xFE1F,0xFE1B,0xFDD6,0xFED5,
  0xFF14,0xE7D4,0xAF97,0xB7D9,0x9FDE,0x0000,0x0000,0x0000,
#endif

	0x8E73,0xD120,0x1500,0x1340,0x0E88,0x02A8,0x00A0,0x4078,
	0x4041,0x0002,0x8002,0xC201,0xCB19,0x0000,0x0000,0x0000,
	0xD7BD,0x9D03,0xDD21,0x1E80,0x17B8,0x0BE0,0x40D9,0x41CA,
	0x808B,0x8004,0x4005,0x8704,0x1104,0x0000,0x0000,0x0000,
	0xDFFF,0xDF3D,0x9F5C,0x5F44,0xDFF3,0x96FB,0x8CFB,0xC7FC,
	0xC7F5,0x8286,0xC94E,0xD35F,0x5B07,0x0000,0x0000,0x0000,
	0xDFFF,0x1FAF,0x9FC6,0x5FD6,0x1FFE,0x1BFE,0xD6FD,0xD5FE,
	0x14FF,0xD4E7,0x97AF,0xD9B7,0xDE9F,0x0000,0x0000,0x0000,

};



/*-------------------------------------------------------------------*/
/*  Function prototypes                                              */
/*-------------------------------------------------------------------*/

/* Menu screen */
int InfoNES_Menu()
{
	return 0;
}

/* Read ROM image file */
extern const BYTE nes_rom[];
int InfoNES_ReadRom( const char *pszFileName )
{
/*
 *  Read ROM image file
 *
 *  Parameters
 *    const char *pszFileName          (Read)
 *
 *  Return values
 *     0 : Normally
 *    -1 : Error
 */

  
  /* Read ROM Header */
  BYTE * rom = (BYTE*)nes_rom;
  memcpy( &NesHeader, rom, sizeof(NesHeader));
  if ( memcmp( NesHeader.byID, "NES\x1a", 4 ) != 0 )
  {
    /* not .nes file */
    return -1;
  }
  rom += sizeof(NesHeader);

  /* Clear SRAM */
  memset( SRAM, 0, SRAM_SIZE );

  /* If trainer presents Read Triner at 0x7000-0x71ff */
  if ( NesHeader.byInfo1 & 4 )
  {
    //memcpy( &SRAM[ 0x1000 ], rom, 512);
	rom += 512;
  }

  /* Allocate Memory for ROM Image */
  ROM = rom;
  rom += NesHeader.byRomSize * 0x4000;

  if ( NesHeader.byVRomSize > 0 )
  {
    /* Allocate Memory for VROM Image */
	VROM = (BYTE*)rom;
	rom += NesHeader.byVRomSize * 0x2000;
  }


  /* Successful */
  return 0;
}

/* Release a memory for ROM */
void InfoNES_ReleaseRom()
{
}

/* Transfer the contents of work frame on the screen */
void InfoNES_LoadFrame()
{
	//char buf[20];
	//printf( "%02d fps\n",FrameCount);
	//LCD_DisplayStringLine(0x110,buf);
}

/* Transfer the contents of work line on the screen */
//void InfoNES_LoadLine()
//{
//	//int i;
//	if(PPU_Scanline==100)
//	{
//		FrameCount++;
//	}
//	//InfoNES_LoadFrame();
//	//ILI9341_DrawLineOne(PPU_Scanline,WorkLine);
//	ILI9341_DrawLine(PPU_Scanline,WorkLine);
//	//printf("PPU_Scanline:%d\n",PPU_Scanline);
//
//}
/* Transfer the contents of work line on the screen */
void InfoNES_LoadLine()
{
  int i;
  for(i=0;i<256;i++)
  {
	  if(WorkLine[i]!=0)
		  if(WorkLine[i]!=40828)
			  if(WorkLine[i]!=57343)
			  printk("WorkLine[%d]:%x,PPU_Scanline:%d\n",i,WorkLine[i],PPU_Scanline);
//    GrContextForegroundSet(&sContext, WorkLine[i]);
//  GrPixelDraw(&sContext, i, PPU_Scanline);

  }
}
/* Get a joypad state */
//#ifdef GPIO_UP
//extern bool up_key;
//#endif
//#ifdef GPIO_DOWN
//extern bool down_key;
//#endif
//#ifdef GPIO_LFT
//extern bool lft_key;
//#endif
//#ifdef GPIO_RHT
//extern bool rht_key;
//#endif
//#ifdef GPIO_START
//extern bool start_key;
//#endif
//#ifdef GPIO_A
//extern bool a_key;
//#endif
//#ifdef GPIO_B
//extern bool b_key;
//#endif


void InfoNES_PadState( DWORD *pdwPad1, DWORD *pdwPad2, DWORD *pdwSystem )
{
  
//    *pdwPad1 = 0;
//#ifdef GPIO_UP
//	if(up_key)
//	{
//		*pdwPad1 |= PAD_JOY_UP;
//		//printf("up\n");
//	}
//#endif
//#ifdef GPIO_DOWN
//	if(down_key)
//	{
//		*pdwPad1 |= PAD_JOY_DOWN;
//		//printf("DOWN\n");
//	}
//#endif
//#ifdef GPIO_LFT
//	if(lft_key)
//	{
//		*pdwPad1 |= PAD_JOY_LEFT;
//		//printf("LEFT\n");
//	}
//#endif
//#ifdef GPIO_RHT
//	if(rht_key)
//	{
//		*pdwPad1 |= PAD_JOY_RIGHT;
//		//printf("RIGHT\n");
//	}
//#endif
//#ifdef GPIO_START
//	if(start_key)
//	{
//		*pdwPad1 |= PAD_JOY_START;
//		//printf("start\n");
//	}
//#endif
//#ifdef GPIO_A
//	if(a_key)
//	{
//		*pdwPad1 |= PAD_JOY_A;
//		//printf("A\n");
//	}
//#endif
//#ifdef GPIO_B
//	if(b_key)
//	{
//		*pdwPad1 |= PAD_JOY_B;
//		//printf("B\n");
//	}
//#endif
//
//
//
}

/* memcpy */
void *InfoNES_MemoryCopy( void *dest, const void *src, int count ){return memcpy(dest,src,count);}

/* memset */
void *InfoNES_MemorySet( void *dest, int c, int count ){return memset(dest,c,count);}

/* Print debug message */
void InfoNES_DebugPrint( char *pszMsg )
{
}

/* Wait */
void InfoNES_Wait()
{

}

/* Sound Initialize */
void InfoNES_SoundInit( void )
{
	
}

/* Sound Open */
int InfoNES_SoundOpen( int samples_per_sync, int sample_rate )
{
  return 0;
}

/* Sound Close */
void InfoNES_SoundClose( void )
{
}

/* Sound Output 5 Waves - 2 Pulse, 1 Triangle, 1 Noise, 1 DPCM */
void InfoNES_SoundOutput(int samples, BYTE *wave1, BYTE *wave2, BYTE *wave3, BYTE *wave4, BYTE *wave5)
{
}

/* Print system message */
void InfoNES_MessageBox( char *pszMsg, ... )
{
}

