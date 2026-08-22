MEMORY {
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS {
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    }

    .text :
    {
        *(.text*)
    } > FLASH

    .rodata :
    {
        *(.rodata*)
    } > FLASH

    
    .data :
    {
        _sdata = .;

        *(.data*)

        _edata = .;
    } > SRAM AT > FLASH
    
    _flashtopdata = LOADADDR(.data);


    .bss :
    {
        _sbss = .;
        *(.bss*)
        _ebss = .;
    } > SRAM


}