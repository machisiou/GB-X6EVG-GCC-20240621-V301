/* Linker script to configure memory regions. */
MEMORY
{
  TEXT    (rx)  : ORIGIN = 0x20000100, LENGTH = 0x40000
  DATA    (rw)  : ORIGIN = 0x20040000, LENGTH = 0x10000
  RAWDATA (rw)  : ORIGIN = 0x20050000, LENGTH = 0x0F000
  STACK   (rw)  : ORIGIN = 0x2005F000, LENGTH = 0x00FF0
}

REGION_ALIAS("SRAM_TEXT", TEXT);
REGION_ALIAS("SRAM_ARM", TEXT);
REGION_ALIAS("SRAM_DATA", DATA);
REGION_ALIAS("SRAM_BSS", DATA);
REGION_ALIAS("SRAM_HEAP", STACK);

ENTRY(Reset_Handler)

SECTIONS
{   
    .text :
    {
        KEEP(*(.vectors))
        . = ALIGN(4);
        *(.text*)
        *(.init)
        *(.fini)
        *(.ns.text)
        KEEP(*(.eh_frame*))
    } > SRAM_TEXT

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > SRAM_ARM
    __exidx_end = .;

    /* Location counter can end up 2byte aligned with narrow Thumb code but
       __etext is assumed by startup code to be the LMA of a section in RAM
       which must be 4byte aligned */
    . = ALIGN (4);
    __etext = ABSOLUTE(.);
    
    .data : AT (__etext)
    {
        . = ALIGN(4);
        __data_start__ = .;        
        *(.data*)
        
        . = ALIGN(4);
        *(.rodata*)

        . = ALIGN(4);
        KEEP(*(.version*))
        
        . = ALIGN(4);
        /* preinit data */
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);


        . = ALIGN(4);
        /* finit data */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE_HIDDEN (__fini_array_end = .);

        KEEP(*(.jcr*))
        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;
    } > SRAM_DATA

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss* .acpi_sram .kernel_sram)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > SRAM_BSS
            
    /DISCARD/ :
    {
        *(.ARM.attributes)
    }
    
    ASSERT(__data_start__ >= __etext,   "region TEXT overflowed with DATA")

    .heap (NOLOAD) : 
    {
        __heap_start__ = .;
        end = __heap_start__;
        _end = end;
        __end = end;
        KEEP(*(.heap))
        __heap_end__ = .;
        __HeapLimit = __heap_end__;
    } > SRAM_HEAP

    . = ALIGN(4);
    __StackLimit = .;
    __StackTop = ORIGIN(STACK) + LENGTH(STACK);
    PROVIDE(__stack = __StackTop);

    __RAWDATA_BEGIN__ = ORIGIN(RAWDATA);
    __RAWDATA_LENGTH__ = LENGTH(RAWDATA);

    ASSERT(__heap_end__ < __StackTop,  "region HEAP overflowed with STACK")
    ASSERT(__heap_start__ >= __bss_end__, "region DATA overflowed with STACK")
}