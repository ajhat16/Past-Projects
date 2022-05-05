.text
.global  set_temp_from_ports
set_temp_from_ports:
### arg is
### %rdi = temp_t *temp
 
        movw    THERMO_SENSOR_PORT(%rip), %dx      # loads THERMO_SENSOR_PORT into the register %dx
        movb    THERMO_STATUS_PORT(%rip), %cl      # loads THERMO_STATUS_PORT into the register %cl
 
        cmpw    $28800,%dx                         # begins comparison on THERMO_SENSOR_PORT
        jg      .ERROR
        cmpw    $0,%dx
        jl      .ERROR
 
        movb    %cl,%r8b                           # copies value of THERMO_STATUS_PORT into a mask
        andb    $0b100,%r8b                        # checks if third bit is set
        cmpb    $0,%r8b                            # if third bit is set
        jg      .ERROR                             # then go to error
 
        movl    %edx,%r8d                          # copies value of THERMO_SENSOR_PORT to a mask
        sarl    $5,%r8d                            # shifts mask right by 5 bits
 
        movl    %edx,%r10d                         # copies value of THERMO_SENSOR_PORT to remainder
        andw    $0b11111,%r10w                     # remainder = remainder & 0b11111
 
        cmpw    $15,%r10w                          # increment temp->tenths_degrees by 1 if remainder > 15
        jg      .INC
        jmp     .CONT
 
.CELCIUS:
        movb    $1,2(%rdi)                         # temp->temp_mode = 1
        movw    %r8w,0(%rdi)
        movl    $0, %eax
        ret
 
.CONVERT_BACK:
        imulw   $-1,%ax                            # for converting a value back to negative (if needed)
        movw    %ax,0(%rdi)
        addw    $320,0(%rdi)                      
        movl    $0,%eax
        ret
 
.NEG_CONVERT:
        imull   $-1,%r8d                           # absolute value
        movl    $1,%r11d
 
.FAHRENHEIT:
        movb    $2,2(%rdi)                         # temp->temp_mode = 2
        cmpl    $0,%r8d
        jl      .NEG_CONVERT
 
        imull   $90,%r8d                           # temp->tenths_degrees * 90
 
        movl    %r8d,%eax                          # putting tenths_degrees * 90 into %ax
        cqto                                       # prep for division
        movl    $50,%r9d
        idivl   %r9d
        movw    %ax,0(%rdi)                        # temp->tenths_degrees = (temp->tenths_degrees * 90) / 50
 
        cmpl    $0,%r11d                           # if the number was originally negative
        jne     .CONVERT_BACK                      # then convert back
 
        addw    $320,0(%rdi)                       # temp->tenths_degrees = (temp->tenths_degrees * 90) / 50 + 320
        movl    $0,%eax
        ret
.INC:
        incl    %r8d                           # temp->tenths_degrees++
 
.CONT:
        addl    $-450,%r8d                      # temp->tenths_degrees += -450
 
        movl    $1,%r10d                            # creating a mask by setting %r8w to 1
        sall    $5,%r10d                            # 1 << 5
        andb    %cl,%r10b                           # mask = mask & THERMO_SENSOR_PORT
        movl    $0,%r11d
 
        cmpw    $0,%r10w                           # checking the mask to see if the temp_mode should be 2 or 1
        jne     .FAHRENHEIT                        # jump if not 0 (meaning 1 in the 5th bit)
        je      .CELCIUS                           # jump if 0 (meaning 0 in the 5th bit)
 
.ERROR:
        movw    $0,0(%rdi)                         # temp->tenths_degrees = 0
        movb    $3,2(%rdi)                         # temp->temp_mode = 3
        movl    $1, %eax
        ret
 
.data
       
an_int:                         # declare location an single integer named 'an_int'
        .int -1               # value 1234
 
other_int:                      # declare another int accessible via name 'other_int'
        .int 0b0101             # binary value as per C
 
# {0b1111011, 0b1001000, 0b0111101, 0b1101101, 0b1001110, 0b1100111, 0b1110111, 0b1001001, 0b1111111, 0b1101111}
an_array:                       
        .int 0b1111011 # 0                
        .int 0b1001000 # 1           
        .int 0b0111101 # 2           
        .int 0b1101101 # 3
        .int 0b1001110 # 4
        .int 0b1100111 # 5
        .int 0b1110111 # 6
        .int 0b1001001 # 7
        .int 0b1111111 # 8
        .int 0b1101111 # 9
 
.text
.global  set_display_from_temp
 
## ENTRY POINT FOR REQUIRED FUNCTION
set_display_from_temp:
### args are
### %rdi = temp_t temp
### %rsi = int display*
 
        movq    %rdi,%rdx
        sarl    $16,%edx        # edx = edx >> 16
        andb    $0xFFFF,%dl     # dl = temp.temp_mode
 
        movl    $0,%eax
        cmpb    $1,%dl
        je      .CEL_ERROR      # if mode is 1 then go to CEL_ERROR
        jmp     .CONT2
 
 
.ERROR2:
        movl    $0b00000110111101111110111110000000,(%rsi)      # to display ERR
        movl    $1,%eax
        ret
 
.CEL_ERROR:
        movq    %rdi,%rdx
        andw    $0xFFFF,%dx     # dx = temp.tenths_degrees
 
        cmpw    $-450,%dx       # check if temp is in the boundaries
        jl      .ERROR2
        cmpw    $450,%dx
        jg      .ERROR2      
 
 .CONT2:
        movq    %rdi,%rdx
        sarl    $16,%edx        # edx = edx >> 16
        andb    $0xFFFF,%dl     # dl = temp.temp_mode
       
        cmpb    $2,%dl
        je      .FAHR_ERROR     # if mode is 2 then go to FAHR_ERROR
        jmp     .CONT3
       
.FAHR_ERROR:
        movq    %rdi,%rdx
        andw    $0xFFFF,%dx     # dx = temp.tenths_degrees
 
        cmpw    $-490,%dx       # check if temp is within the boundaries
        jl      .ERROR2
        cmpw    $1130,%dx
        jg      .ERROR2
 
.CONT3:
        movq    %rdi,%rdx
        sarl    $16,%edx        # edx = edx >> 16
        andb    $0xFFFF,%dl     # dl = temp.temp_mode
 
        cmpb    $1,%dl          # error if mode is not either 1 or 2
        jl      .ERROR2
        cmpb    $2,%dl
        jg      .ERROR2
 
        movl    $0,(%rsi)       # reset *display
 
        subq    $16,%rsp        # substract 16 from stack
 
 
        # {0b1111011, 0b1001000, 0b0111101, 0b1101101, 0b1001110, 0b1100111, 0b1110111, 0b1001001, 0b1111111, 0b1101111}
        leaq    an_array(%rip),%rcx
 
        movq    $0,%r8          # sets temp_thousands to 0
        movq    $0,%r9          # sets temp_hundreds to 0
        movq    $0,%r10         # sets temp_tens to 0
        movq    $0,%r11         # sets temp_ones to 0
 
.CHECK_SIGN:
        movq    %rdi,%rdx
        andw    $0xFFFF,%dx     # dx = temp.tenths_degrees
 
        cmpw    $0,%dx          # checks if temp.tenths_degrees is negative
        jl      .ABS
        movw    %dx,%ax
        jmp     .LOOP
 
.ABS:
        movw    %dx,%ax
        imulw   $-1,%ax
 
.LOOP:
        cmpw    $10,%ax         # if %ax <= 10, the loop ends
        jle     .END_OF_LOOP
        cmpw    $999,%ax
        jg      .TEMP_TH
        cmpw    $99,%ax
        jg      .TEMP_H
        jmp     .TEMP_TEN
 
.TEMP_TH:
        cqto                    # prep for division
        movl    $1000,%r8d      # divisor
        idivl   %r8d            # %ax / 1000
        movl    %eax,%r8d       # temp_thousands = temp_degrees / 1000
 
        movl    %edx,%eax       # temp_degrees = remainder
        jmp     .LOOP
 
.TEMP_H:
        cqto                    # prep for division
        movl    $100,%r9d       # divisor
        idivl   %r9d            # %ax / 100
        movl    %eax,%r9d       # temp_hundreds = temp_degrees / 100
 
        movl    %edx,%eax       # temp_degrees = remainder
        jmp     .LOOP
 
.TEMP_TEN:
        cqto                    # prep for division
        movl    $10,%r10d       # divisor
        idivl   %r10d           # %ax / 10
        movl    %eax,%r10d      # temp_tens = temp_degrees / 10
 
        movl    %edx,%eax       # temp_degrees = remainder
        jmp     .LOOP
 
.END_OF_LOOP:
        cqto                    # prep for divison
        movl    $10,%r11d       # divisor
        idivl   %r11d           # %ax / 10
        movl    %edx,%r11d      # temp_ones = remainder
 
        cmpl    $0,%r8d         # checks if thousands is not 0
        jne     .THOUSANDS_MASK
        cmpl    $0,%r9d         # checks if hundreds is not 0
        jne     .HUNDREDS_MASK
       
        movl    (%rcx,%r11,4),%eax      # get bitstring from array
        movl    (%rcx,%r10,4),%r11d     # get bitstring from array
        sall    $7,%r11d                # shifts bits to the correct spots
        orl     %r11d,%eax              # set mask in %eax
 
        movq    %rdi,%rdx      
        andw    $0xFFFF,%dx             # dx = temp.tenths_degrees
        cmpw    $0,%dx
        jl      .CHECK_TENS_SIGN        # check if negative is needed
        jmp     .CONT4
 
 
.THOUSANDS_MASK:
        movl    (%rcx,%r11,4),%eax      # get bits from array
        movl    (%rcx,%r10,4),%r11d
        sall    $7,%r11d                # shifts to correct spot
        orl     %r11d,%eax              # put bits in mask
        movl    (%rcx,%r9,4),%r10d      # get bits from array
        sall    $14,%r10d               # shifts to correct spot
        orl     %r10d,%eax              # put bits in mask
        movl    (%rcx,%r8,4),%r9d       # get bits from array
        sall    $21,%r9d                # shift to correct spot
        orl     %r9d,%eax               # put bits in mask
        jmp     .CONT4
 
 
.HUNDREDS_MASK:
        movl    (%rcx,%r11,4),%eax      # get bits from array
        movl    (%rcx,%r10,4),%r11d
        sall    $7,%r11d                # shift to correct spot
        orl     %r11d,%eax              # put bits in mask
        movl    (%rcx,%r9,4),%r10d      # get bits from array
        sall    $14,%r10d               # shift to correct spot
        orl     %r10d,%eax              # put bits in mask
 
        movq    %rdi,%rdx
        andw    $0xFFFF,%dx             # dx = temp.tenths_degrees
        cmpw    $0,%dx
        jge     .CONT4
 
 
.CHECK_HUNDRED_SIGN:
        movl    $0b0000100,%r8d         # puts negative in correct spot for hundreds
        sall    $21,%r8d
        orl     %r8d,%eax
        jmp     .CONT4
 
.CHECK_TENS_SIGN:
        movl    $0b0000100,%r8d         # puts negative in correct spot for tens
        sall    $14,%r8d
        orl     %r8d,%eax
 
.CONT4:
        movq    %rdi,%rdx
        sarl    $16,%edx        # edx = edx >> 16
        andb    $0xFFFF,%dl     # dl = temp.temp_mode
 
        cmpb    $1,%dl
        je      .CEL_SIGN       # put celcius icon
        movl    $0b0010,%r8d    # otherwise put fahrenheit icon
        sall    $28,%r8d
        orl     %r8d,%eax       # shift into mask
        jmp     .END
 
.CEL_SIGN:
        movl    $0b0001,%r8d
        sall    $28,%r8d
        orl     %r8d,%eax       # put into mask
 
.END:
        movl    %eax,(%rsi)     # set display to mask
        addq    $16,%rsp        # reset stack pointer
        movl    $0,%eax
        ret
 
.text
.global  thermo_update
 
## ENTRY POINT FOR REQUIRED FUNCTION
thermo_update:
 
        subq    $8,%rsp
        pushq   %rbx
        leaq    0(%rsp),%rdi
        call    set_temp_from_ports
        movw    0(%rdi),%r8w            # store values from temp into rsp
        movw    %r8w,0(%rsp)
        movb    2(%rdi),%r9b
        movb    %r9b,2(%rsp)
        movl    %eax,%ebx
       
        movq    (%rdi),%rdi
        leaq    THERMO_DISPLAY_PORT(%rip),%rsi        # sets rsi to THERMO_DISPLAY_PORT
        call    set_display_from_temp
        movl    %eax,%r9d               # return value of set_display_from_temp is stored
        
        cmpl    $0,%ebx
        jne     .ERROR3
        cmpl    $0,%r9d
        jne     .ERROR3
        movl    $0,%eax
        popq    %rbx
        addq    $8,%rsp
        ret
 
.ERROR3:
        movl    $1,%eax
        popq    %rbx
        addq    $8,%rsp
        ret
 