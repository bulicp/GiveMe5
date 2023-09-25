
# --------------------------------------------------------------------
# FE310 - G002  M E M O R Y   M A P : 
# Pa3cio, UL FRI, 2023
# --------------------------------------------------------------------


# --------------------------------------------------------------------
# G P I O : 
# --------------------------------------------------------------------
.equ GPIO0_BASE_ADDRESS,        0x10012000      # GPIO0 Base Address

# --------------------------------------------------------------------
# C L I N T :
# --------------------------------------------------------------------
.equ CLINT_BASE,                0x02000000
.equ CLINT_MTIME,               0x0200bff8      # CLINT Timer Register -  a 64-bit read-write register that contains the number of cycles counted from the rtcclk
                                                # RTC should be driven by an external 32.768 kHz watch crystal oscillator
                                                # The 48-bit RTC counter width ensures there will be no counter rollover for over 270 years assuming
                                                # a 32.768 kHz low-frequency real-time clock source.
.equ CLINT_MTIME_CMP,           0x02004000 


# --------------------------------------------------------------------
# U A R T :
# --------------------------------------------------------------------
.equ UART0_BASE,                0x10013000
.equ UART1_BASE,                0x10023000

# --------------------------------------------------------------------
# P L I C  :
# --------------------------------------------------------------------
.equ PLIC_BASE,                 0x0C000000
