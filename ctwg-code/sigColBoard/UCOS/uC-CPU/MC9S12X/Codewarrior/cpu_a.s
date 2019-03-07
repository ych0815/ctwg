;********************************************************************************************************
;                                               uC/CPU
;                                    CPU CONFIGURATION & PORT LAYER
;
;                          (c) Copyright 2004-2007; Micrium, Inc.; Weston, FL
;
;               All rights reserved.  Protected by international copyright laws.
;
;               uC/CPU is provided in source form for FREE evaluation, for educational
;               use or peaceful research.  If you plan on using uC/CPU in a commercial
;               product you need to contact Micrium to properly license its use in your
;               product.  We provide ALL the source code for your convenience and to
;               help you experience uC/CPU.  The fact that the source code is provided
;               does NOT mean that you can use it without paying a licensing fee.
;
;               Knowledge of the source code may NOT be used to develop a similar product.
;
;               Please help us continue to provide the Embedded community with the finest
;               software available.  Your honesty is greatly appreciated.
;********************************************************************************************************


;********************************************************************************************************
;
;                                            CPU PORT FILE
;
;                                           Freescale MC9S12X
;                                          Codewarrior Compiler
;
; Filename      : cpu_a.s
; Version       : V1.00
; Programmer(s) : EHS
;********************************************************************************************************


;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

        xdef  CPU_SR_Save
        xdef  CPU_SR_Restore


;********************************************************************************************************
;                                               EQUATES
;********************************************************************************************************


;********************************************************************************************************
;                                  SAVE THE CCR AND DISABLE INTERRUPTS
;                                                  &
;                                              RESTORE CCR
;
; Description : These function implements OS_CRITICAL_METHOD #3 
;
; Arguments   : The function prototypes for the two functions are:
;               1) CPU_SR  CPU_SR_Save(void);
;                             where CPU_SR is the contents of the CCR register prior to disabling
;                             interrupts.
;               2) void    CPU_SR_Restore(CPU_SR cpu_sr);
;                             'cpu_sr' the the value of the CCR to restore.
;
; Note(s)     : 1) It's assumed that the compiler uses the D register to pass a single 16-bit argument
;                  to and from an assembly language function.
;********************************************************************************************************

CPU_SR_Save:
    tfr  ccrw,d                        ; It's assumed that 16-bit return value is in register D
    sei                                ; Disable interrupts
    rtc                                ; Return to caller with D containing the previous CCR

CPU_SR_Restore:
    tfr  d,ccrw                        ; D contains the CCR word value to restore, move D to CCR
    rtc


;$PAGE
;********************************************************************************************************
;                                     CPU ASSEMBLY PORT FILE END
;********************************************************************************************************

