//******************************************************************************
//! @file $RCSfile: at90can_drv.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains intrinsic macros of AT90CAN128/64/32.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413528/WinAVR-20070122.
//!
//! @version $Revision: 3.20 $ $Name: jtellier $
//!
//!
//! @todo
//! @bug

//******************************************************************************
//! Modified by Atlantis Specialist Technologies by James Blakey-Milner, 1 Aug 2017.
//! Ported the library to the Arduino platform
//! Note! AST modifications are in early development
//! (alpha) and are likely to change without notice.

//******************************************************************************

#ifndef _AT90CAN_MCU_H_
#define _AT90CAN_MCU_H_

//_____ I N C L U D E S ________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________
#define     SRAM_BYTE_AT        *(U8*)
#define     REG_BYTE_AT         *(U8 volatile*)

//_____ D E C L A R A T I O N S ________________________________________________

//_____ M A C R O S ____________________________________________________________

//------------------------------------------------------------------------------
//  @fn MACRO: Sram_rd_byte
//!
//! Get SRAM value.
//!
//! @warning none
//!
//! @param SRAM address (from 0x0 up to 0xFFFF)
//!
//! @return SRAM byte value
//!
//------------------------------------------------------------------------------
#define     Sram_rd_byte(addr_byte)     ( SRAM_BYTE_AT(addr_byte) )

//------------------------------------------------------------------------------
//  @fn MACRO: Reg_rd_byte
//!
//! Get register value when register is address declared.
//! Example: temp = Reg_rd_byte(&RAMPZ);
//!               or
//!          temp = Reg_rd_byte(0x5B);
//!               or
//!          i = 0x5B;
//!          temp = Reg_rd_byte(i);
//!
//! @warning none
//!
//! @param Register address (from 0x20 up to 0xFF)
//!
//! @return Register value
//!
//------------------------------------------------------------------------------
#define Reg_rd_byte(addr)  ( REG_BYTE_AT(addr) )

//------------------------------------------------------------------------------
//  @fn MACRO: Reg_wr_byte
//!
//! Put register value when register is address declared.
//!
//! @warning none
//!
//! @param Register address (from 0x20 up to 0xFF)
//!        Data (to write) value
//!
//! @return none
//!
//------------------------------------------------------------------------------
#define Reg_wr_byte(addr, data)  ( REG_BYTE_AT(addr) = data )

//------------------------------------------------------------------------------
//  @fn MACRO: Enable_interrupt
//!
//! Set the Global Interrupt flag (I) in SREG (Status REGister).
//!
//! @warning none
//!
//! @param none
//!
//! @return none
//!
//------------------------------------------------------------------------------
#define Enable_interrupt()      { asm ("sei"::) ; }

//------------------------------------------------------------------------------
//  @fn MACRO: Disable_interrupt
//!
//! Clear the Global Interrupt flag (I) in SREG (status register).
//!
//! @warning none
//!
//! @param none
//!
//! @return none
//!
//------------------------------------------------------------------------------
#define Disable_interrupt()     { asm ("cli"::) ; }

//------------------------------------------------------------------------------
//  @fn MACRO: Nop_insert
//!
//! Insertion of a 'nop' instruction.
//!
//! @warning none
//!
//! @param none
//!
//! @return none
//!
//------------------------------------------------------------------------------
#define Nop_insert()      { asm ("nop"::) ; }

//------------------------------------------------------------------------------
//  @fn MACRO-FUNCTION Indirect_jump_to
//!
//! Jump within the lowest 64K words (128K bytes) section of Flash.
//!
//! @warning: WORD address as parameter
//!
//! @param: WORD address (PC <- Z(15:0))
//!
//! @return none
//!
//------------------------------------------------------------------------------
#define     Indirect_jump_to(jump_addr)             \
            ({                                      \
                asm                                 \
                (                                   \
                    "movw r30, %0"    "\n\t"        \
                    "ijmp"            "\n\t"        \
                    :                               \
                    : "r" ((U16)jump_addr)          \
                    : "r30", "r31"                  \
                );                                  \
            })

//------------------------------------------------------------------------------
//  @fn MACRO-FUNCTION Direct_jump_to_zero
//!
//! Jump at the addresse 0x0000 (not a reset !)
//!
//! @warning: not a reset!
//!
//! @param none
//!
//! @return none
//!
//------------------------------------------------------------------------------
#define Direct_jump_to_zero()   { asm ("jmp 0"::); }


//------------------------------------------------------------------------------
//  @fn MACRO-FUNCTION Hard_reset
//!
//! RESET device with Watchdog Timer.
//!
//! @warning: Watchdog Timer used
//!           Check BOOTRST fuse setting
//!
//! @param none
//!
//! @return none
//!
//------------------------------------------------------------------------------
#define Hard_reset()    { WDTCR |= 1<<WDE;  while(1); }

//______________________________________________________________________________

#endif // _AT90CAN_MCU_H_
