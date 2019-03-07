;********************************************************************************************************
;\file
;\brief      �����жϻ�����
;\version    1.0.0
;\date       2016\2\2
;\author     zdj
;
;can�Ĵ������ó���
;
;\verbatim
;------------------------Copyright (c)YUNDA Tech. Co.,Ltd----------------------------
;                 
;                 +------(NEW | MODify |ADD |DELete)------+
;                 |
;version          |    date(yyyy/mm/dd)  name        brief
;
;---------------------+----------------+---------------------------------------------
; 1.0.0         NEW       2016/2/2        zdj        create
;------------------------------------------------------------------------------------
;\endverbatim
;********************************************************************************************************

NON_BANKED:       section


;********************************************************************************************************
;                                           I/O �˿ڵ�ַ
;********************************************************************************************************

PPAGE:            equ    $0015         ; Addres of PPAGE register (assuming MC9S12XEP100 part)
RPAGE:            equ    $0016         ; Addres of RPAGE register (assuming MC9S12XEP100 part)
EPAGE:            equ    $0017         ; Addres of EPAGE register (assuming MC9S12XEP100 part)
GPAGE:            equ    $0010         ; Addres of GPAGE register (assuming MC9S12XEP100 part)


;********************************************************************************************************
;                                          ��������
;********************************************************************************************************

 ;    xdef   I2C0_ISR              ;I2C0�ж���������ں���

     xdef   Can0_TxISR            ;CAN0�����ж���������ں���
     xdef   Can0_RxISR            ;CAN0�����ж���������ں���
     xdef   Can0_ErrorISR         ;CAN0�����ж���������ں���
     
     xdef   Can1_TxISR            ;CAN1�����ж���������ں���
     xdef   Can1_RxISR            ;CAN1�����ж���������ں���
     xdef   Can1_ErrorISR         ;CAN1�����ж���������ں���
     
     xdef   Can2_TxISR            ;CAN2�����ж���������ں���
     xdef   Can2_RxISR            ;CAN2�����ж���������ں���
     xdef   Can2_ErrorISR         ;CAN2�����ж���������ں���
     
     xdef   Can3_TxISR            ;CAN3�����ж���������ں���
     xdef   Can3_RxISR            ;CAN3�����ж���������ں���
     xdef   Can3_ErrorISR         ;CAN3�����ж���������ں���
     
     xdef   Can4_TxISR            ;CAN4�����ж���������ں���
     xdef   Can4_RxISR            ;CAN4�����ж���������ں���
     xdef   Can4_ErrorISR         ;CAN4�����ж���������ں���
     
     xdef   SCI0_ISR              ;SCI0�ж���������ں���
     xdef   SCI2_ISR              ;SCI2�ж���������ں���

     xdef   ECT0_ISR              ;ECT0�ж���������ں���
     xdef   ECT1_ISR              ;ECT1�ж���������ں���
     xdef   ECT2_ISR              ;ECT2�ж���������ں���
     xdef   ECT3_ISR              ;ECT3�ж���������ں���

    
;********************************************************************************************************
;                                         �ⲿ���ú�������
;********************************************************************************************************

      xref   OSIntExit
      xref   OSIntNesting
      xref   OSTCBCur

  ;    xref   drv_i2c0_int                  ;I2C0�жϺ���

      xref   Can0_TansmitIsr_C             ;CAN0�����жϺ���
      xref   Can0_ReceiveIsr_C             ;CAN0�����жϺ���
      xref   Can0_ErrorIsr_C               ;CAN0�����жϺ���
      
      xref   Can1_TansmitIsr_C             ;CAN1�����жϺ���
      xref   Can1_ReceiveIsr_C             ;CAN1�����жϺ���
      xref   Can1_ErrorIsr_C               ;CAN1�����жϺ���

      xref   Can2_TansmitIsr_C             ;CAN2�����жϺ���
      xref   Can2_ReceiveIsr_C             ;CAN2�����жϺ���
      xref   Can2_ErrorIsr_C               ;CAN2�����жϺ���
      
      xref   Can3_TansmitIsr_C             ;CAN3�����жϺ���
      xref   Can3_ReceiveIsr_C             ;CAN3�����жϺ���
      xref   Can3_ErrorIsr_C               ;CAN3�����жϺ���
      
      xref   Can4_TansmitIsr_C             ;CAN4�����жϺ���
      xref   Can4_ReceiveIsr_C             ;CAN4�����жϺ���
      xref   Can4_ErrorIsr_C               ;CAN4�����жϺ���
      
      xref   drv_sci0_int                  ;SCI0�ж�,C����
      xref   drv_sci2_int                  ;SCI2�ж�,C����

      xref   drv_ect0_int                  ;ECT0�ж�,C����
      xref   drv_ect1_int                  ;ECT1�ж�,C����
      xref   drv_ect2_int                  ;ECT2�ж�,C����
      xref   drv_ect3_int                  ;ECT3�ж�,C����

;********************************************************************************************************
;                                           I2C ISR
;
; Description : This routine is the uC/Probe I2C interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your drv_i2c0_int and perhaps the call to
;                  the label name drv_i2c0_int.
;********************************************************************************************************

;I2C0_ISR:
;    ldaa   GPAGE                       ; Get current value of GPAGE register
;    psha                               ; Push GPAGE register onto current task's stack

;    ldaa   EPAGE                       ; Get current value of EPAGE register
;    psha                               ; Push EPAGE register onto current task's stack

;    ldaa   RPAGE                       ; Get current value of RPAGE register
;    psha                               ; Push RPAGE register onto current task's stack

;    ldaa   PPAGE                       ; Get current value of PPAGE register
;    psha                               ; Push PPAGE register onto current task's stack

;    inc    OSIntNesting                ; Notify uC/OS-II about ISR

;    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
;    cmpb   #$01
;    bne    i2c0_cont_int

;    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
;    sts    0,y                         ; }

;i2c0_cont_int:
;   call   drv_i2c0_int                ; Call drv_i2c0_int

;   cli                                ; Optionally enable interrupts to allow interrupt nesting

;   call   OSIntExit                   ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

;   pula                               ; Get value of PPAGE register
;   staa   PPAGE                       ; Store into CPU's PPAGE register

;   pula                               ; Get value of RPAGE register
;   staa   RPAGE                       ; Store into CPU's RPAGE register

;   pula                               ; Get value of EPAGE register
;   staa   EPAGE                       ; Store into CPU's EPAGE register

;   pula                               ; Get value of GPAGE register
;   staa   GPAGE                       ; Store into CPU's GPAGE register

;   rti                                ; Return from interrupt to interrupted task.


;********************************************************************************************************
;                                           CAN0 ISR
;
; Description : This routine is the uC/Probe can0 transmitter interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name send_can0_int.
;********************************************************************************************************
Can0_TxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    trans_can0_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


trans_can0_cont_int:
    call   Can0_TansmitIsr_C              ; Call Can0_TansmitIsr in can.c

;   cli                                 ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                   ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.


;********************************************************************************************************
;                                           CAN ISR
;
; Description : This routine is the uC/Probe CAN Rx interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name receive_can0_int.
;*******************************************************************************************************
Can0_RxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    recv_can0_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


recv_can0_cont_int:
    call   Can0_ReceiveIsr_C           ; Call receive_adc0_int

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           CAN ISR
;
; Description : This routine is the uC/Probe ERR interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
Can0_ErrorISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    err_can0_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


err_can0_cont_int:
    call   Can0_ErrorIsr_C                   ; Call Can0_ErrorIsr_C

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           CAN1 ISR
;
; Description : This routine is the uC/Probe can1 transmitter interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name send_can0_int.
;********************************************************************************************************
Can1_TxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    trans_can1_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


trans_can1_cont_int:
    call   Can1_TansmitIsr_C            ; Call Can1_TansmitIsr

;    cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.


;********************************************************************************************************
;                                           CAN1 ISR
;
; Description : This routine is the uC/Probe CAN1 Rx interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name receive_can0_int.
;*******************************************************************************************************
Can1_RxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    recv_can1_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


recv_can1_cont_int:
    call   Can1_ReceiveIsr_C            ; Call Can1_ReceiveIsr

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           CAN1 ISR
;
; Description : This routine is the uC/Probe ERR interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
Can1_ErrorISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    err_can1_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


err_can1_cont_int:
    call   Can1_ErrorIsr_C            ; Call Can1_ErrorIsr_C

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

 ;********************************************************************************************************
;                                           CAN2 ISR
;
; Description : This routine is the uC/Probe can2 transmitter interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name send_can0_int.
;********************************************************************************************************
Can2_TxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    trans_can2_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


trans_can2_cont_int:
    call   Can2_TansmitIsr_C            ; Call Can2_TansmitIsr_C

;    cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.


;********************************************************************************************************
;                                           CAN2 ISR
;
; Description : This routine is the uC/Probe CAN1 Rx interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name receive_can0_int.
;*******************************************************************************************************
Can2_RxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    recv_can2_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


recv_can2_cont_int:
    call   Can2_ReceiveIsr_C            ; Call Can2_ReceiveIsr_C

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           CAN2 ISR
;
; Description : This routine is the uC/Probe ERR interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
Can2_ErrorISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    err_can2_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


err_can2_cont_int:
    call   Can2_ErrorIsr_C            ; Call Can2_ErrorIsr_C

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           CAN3 ISR
;
; Description : This routine is the uC/Probe can3 transmitter interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name send_can0_int.
;********************************************************************************************************
Can3_TxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    trans_can3_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


trans_can3_cont_int:
    call   Can3_TansmitIsr_C            ; Call Can3_TansmitIsr_C

;    cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.


;********************************************************************************************************
;                                           CAN3 ISR
;
; Description : This routine is the uC/Probe CAN3 Rx interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name receive_can0_int.
;*******************************************************************************************************
Can3_RxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    recv_can3_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


recv_can3_cont_int:
    call   Can3_ReceiveIsr_C            ; Call Can3_ReceiveIsr_C

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           CAN3 ISR
;
; Description : This routine is the uC/Probe CAN3 ERR interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
Can3_ErrorISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    err_can3_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


err_can3_cont_int:
    call   Can3_ErrorIsr_C            ; Call Can3_ErrorIsr_C

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           CAN4 ISR
;
; Description : This routine is the uC/Probe can4 transmitter interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name send_can0_int.
;********************************************************************************************************
Can4_TxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    trans_can4_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


trans_can4_cont_int:
    call   Can4_TansmitIsr_C            ; Call Can4_TansmitIsr_C

;    cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.


;********************************************************************************************************
;                                           CAN4 ISR
;
; Description : This routine is the uC/Probe CAN4 Rx interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name receive_can0_int.
;*******************************************************************************************************
Can4_RxISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    recv_can4_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


recv_can4_cont_int:
    call   Can4_ReceiveIsr_C            ; Call Can4_ReceiveIsr_C

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           CAN4 ISR
;
; Description : This routine is the uC/Probe CAN4 ERR interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
Can4_ErrorISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    err_can4_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


err_can4_cont_int:
    call   Can4_ErrorIsr_C            ; Call Can4_ErrorIsr_C

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.



;********************************************************************************************************
;                                           SCI ISR
;
; Description : This routine is the uC/Probe ERR interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
SCI0_ISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    sci0_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


sci0_cont_int:
    call   drv_sci0_int               ; Call drv_sci0_int

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           SCI2 ISR
;
; Description : This routine is SCI2 interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
SCI2_ISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    sci2_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


sci2_cont_int:
    call   drv_sci2_int               ; Call drv_sci2_int

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.
    
;********************************************************************************************************
;                                           ECT0 ISR
;
; Description : This routine is ECT0 interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
ECT0_ISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    ect0_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


ect0_cont_int:
    call   drv_ect0_int               ; Call drv_ect0_int

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           ECT1 ISR
;
; Description : This routine is ECT0 interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
ECT1_ISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    ect1_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


ect1_cont_int:
    call   drv_ect1_int               ; Call drv_ect1_int

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           ECT2 ISR
;
; Description : This routine is ECT0 interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
ECT2_ISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    ect2_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


ect2_cont_int:
    call   drv_ect2_int               ; Call drv_ect2_int

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           ECT3 ISR
;
; Description : This routine is ECT0 interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
ECT3_ISR:
    ldaa   GPAGE                       ; Get current value of GPAGE register
    psha                               ; Push GPAGE register onto current task's stack

    ldaa   EPAGE                       ; Get current value of EPAGE register
    psha                               ; Push EPAGE register onto current task's stack

    ldaa   RPAGE                       ; Get current value of RPAGE register
    psha                               ; Push RPAGE register onto current task's stack

    ldaa   PPAGE                       ; Get current value of PPAGE register
    psha                               ; Push PPAGE register onto current task's stack

    inc    OSIntNesting                ; Notify uC/OS-II about ISR

    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
    cmpb   #$01
    bne    ect3_cont_int

    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
    sts    0,y                         ; }


ect3_cont_int:
    call   drv_ect3_int               ; Call drv_ect3_int

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

    pula                               ; Get value of PPAGE register
    staa   PPAGE                       ; Store into CPU's PPAGE register

    pula                               ; Get value of RPAGE register
    staa   RPAGE                       ; Store into CPU's RPAGE register

    pula                               ; Get value of EPAGE register
    staa   EPAGE                       ; Store into CPU's EPAGE register

    pula                               ; Get value of GPAGE register
    staa   GPAGE                       ; Store into CPU's GPAGE register

    rti                               ; Return from interrupt to interrupted task.

;********************************************************************************************************
;                                           TIMER ISR
;
; Description : This routine is the uC/Probe ERR interrupt service routine
;
; Arguments   : none
;
; Notes       : 1) All USER interrupts should be modeled EXACTLY like this where the only
;                  line to be modified is the call to your ISR_Handler and perhaps the call to
;                  the label name can0_err.
;********************************************************************************************************
;TIMER0_ISR:
;    ldaa   GPAGE                       ; Get current value of GPAGE register
;    psha                               ; Push GPAGE register onto current task's stack

;    ldaa   EPAGE                       ; Get current value of EPAGE register
;    psha                               ; Push EPAGE register onto current task's stack

;    ldaa   RPAGE                       ; Get current value of RPAGE register
;    psha                               ; Push RPAGE register onto current task's stack

;    ldaa   PPAGE                       ; Get current value of PPAGE register
;    psha                               ; Push PPAGE register onto current task's stack

;    inc    OSIntNesting                ; Notify uC/OS-II about ISR

;    ldab   OSIntNesting                ; if (OSIntNesting == 1) {
;    cmpb   #$01
;    bne    timer0_cont_int

;    ldy    OSTCBCur                    ;     OSTCBCur->OSTCBStkPtr = Stack Pointer
;    sts    0,y                         ; }


;timer0_cont_int:
;    call   drv_timer0_int               ; Call drv_sci0_int

;   cli                               ; Optionally enable interrupts to allow interrupt nesting

;    call   OSIntExit                  ; Notify uC/OS-II about end of ISR, a context switch may occur from within OSIntExit().

;    pula                               ; Get value of PPAGE register
;    staa   PPAGE                       ; Store into CPU's PPAGE register

;    pula                               ; Get value of RPAGE register
;    staa   RPAGE                       ; Store into CPU's RPAGE register

;    pula                               ; Get value of EPAGE register
;    staa   EPAGE                       ; Store into CPU's EPAGE register

;    pula                               ; Get value of GPAGE register
;    staa   GPAGE                       ; Store into CPU's GPAGE register

;    rti                               ; Return from interrupt to interrupted task.