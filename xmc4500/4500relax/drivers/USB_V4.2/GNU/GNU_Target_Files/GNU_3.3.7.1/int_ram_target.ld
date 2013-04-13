/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-tricore")
OUTPUT_ARCH(tricore)
ENTRY(_start)
SEARCH_DIR("/gnu/install-tricore/MinGW32.33/tricore/lib");
/*
 * NB: The memory map below works for TriCore simulators and some
 * evaluation boards.  You may need to change the values to match
 * your actual hardware setup and pass the modified script to the
 * linker using its "-T" option.
 */
MEMORY
{
  ext_cram (arx!p):	org = 0xd4000000, len = 32K
  ext_dram (aw!xp):	org = 0xafc00000, len = 64K
/*
  int_cram (ar!xp):	org = 0xc0000000, len = 0x10000
*/
  /* non cacheable region */
  int_cram (ar!xp):	org = 0xafc00000, len = 0x10000
  int_dram (aw!xp):	org = 0xd0000000, len = 0x7000
  pcp_data (awp!x):	org = 0xf0010000, len = 32K
  pcp_text (arxp):	org = 0xf0020000, len = 16K
}
/*
 * Define the end address + 1 of the RAM area; this must match the
 * definition of ext_dram above.
 */
/*
__RAM_END = 0xa0080000 + 1M ;
*/
__RAM_END = 0xafc00000 + 64K ;
/*
 * Define the sizes of the user and system stacks.
 */
__ISTACK_SIZE = DEFINED (__ISTACK_SIZE) ? __ISTACK_SIZE : 4K ;
__USTACK_SIZE = DEFINED (__USTACK_SIZE) ? __USTACK_SIZE : 20K ;
/*
 * The heap is the memory between the top of the user stack and
 * __RAM_END (as defined above); programs can dynamically allocate
 * space in this area using malloc() and various other functions.
 * Below you can define the minimum amount of memory that the heap
 * should provide.
 */
__HEAP_MIN = DEFINED (__HEAP_MIN) ? __HEAP_MIN : 512K ;
/*
 * Define the start address and the size of the context save area.
 */
__CSA_BEGIN = DEFINED (__CSA_BEGIN) ? __CSA_BEGIN : 0xd0000000 ;
__CSA_SIZE = DEFINED (__CSA_SIZE) ? __CSA_SIZE : 24k ;

SECTIONS
{
 . = 0xd4000000 ;

  /*
   * The startup code should be placed where the CPU expects it after a reset.
   */
  .startup :
  {
    KEEP (*crt0.o(.startup_code))
    KEEP (*/crt0.o(.startup_code))
    KEEP (*/*/crt0.o(.startup_code))
    KEEP (*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
    KEEP (*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/crt0.o(.startup_code))
  } > ext_cram =0
  /*
   * Allocate space for absolute addressable sections; this requires that
   * "ext_cram" starts at a TriCore segment (256M) and points to
   * some RAM area!  If these conditions are not met by your particular
   * hardware setup, you should either not use absolute data, or you
   * must move .{z,b}{data,bss}{,.*} input sections to some appropriate
   * memory area.
   */
  .zbss ALIGN(8) (NOLOAD) :
  {
    ZBSS_BASE = . ;
    *(.zbss)
    *(.zbss.*)
    *(.gnu.linkonce.zb.*)
    *(.bbss)
    *(.bbss.*)
    ZBSS_END = . ;
  } > ext_cram
  .zdata ALIGN(8) : AT(_enddata)
  {
    ZDATA_BASE = . ;
    *(.zdata)
    *(.zdata.*)
    *(.gnu.linkonce.z.*)
    *(.bdata)
    *(.bdata.*)
    ZDATA_END = . ;
  } > ext_cram
  /*
   * Allocate .text and other read-only sections.
   */
  .text ALIGN(4) :
  {
    *(.text)
    *(.text.*)
    *(.gnu.linkonce.t.*)
  } > ext_cram =0
  .rodata ALIGN(8) :
  {
    *(.rodata)
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    *(.rodata1)
    *(.toc)
    /*
     * Create the clear and copy tables that tell the startup code
     * which memory areas to clear and to copy, respectively.
     */
    . = ALIGN(4) ;
    PROVIDE(__clear_table = .) ;
    LONG(0 + ADDR(.bss));     LONG(SIZEOF(.bss));
    LONG(0 + ADDR(.sbss));    LONG(SIZEOF(.sbss));
    LONG(0 + ADDR(.zbss));    LONG(SIZEOF(.zbss));
    LONG(-1);                 LONG(-1);
    PROVIDE(__copy_table = .) ;
/*
    LONG(LOADADDR(.data));    LONG(ABSOLUTE(DATA_BASE)); LONG(SIZEOF(.data));
*/
    LONG(LOADADDR(.sdata));   LONG(ABSOLUTE(SDATA_BASE));LONG(SIZEOF(.sdata));
    LONG(LOADADDR(.zdata));   LONG(ABSOLUTE(ZDATA_BASE));LONG(SIZEOF(.zdata));
    LONG(LOADADDR(.pcpdata)); LONG(ABSOLUTE(PRAM_BASE)); LONG(SIZEOF(.pcpdata));
    LONG(LOADADDR(.pcptext)); LONG(ABSOLUTE(PCODE_BASE));LONG(SIZEOF(.pcptext));
    LONG(-1);                 LONG(-1);                  LONG(-1);
  } > ext_cram
  /*
   * C++ exception handling tables.  NOTE: gcc emits .eh_frame
   * sections when compiling C sources with debugging enabled (-g).
   * If you can be sure that your final application consists
   * exclusively of C objects (i.e., no C++ objects), you may use
   * the -R option of the "strip" and "objcopy" utilities to remove
   * the .eh_frame section from the executable.
   */
  .eh_frame ALIGN(8) :
  {
    *(.gcc_except_table)
    __EH_FRAME_BEGIN__ = . ;
    KEEP (*(.eh_frame))
    __EH_FRAME_END__ = . ;
  } > ext_cram
  /*
   * Constructors and destructors.
   */
  .ctors ALIGN(4) :
  {
    __CTOR_LIST__ = . ;
    LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2);
    *(.ctors)
    LONG(0) ;
    __CTOR_END__ = . ;
  } > ext_cram
  .dtors ALIGN(4) :
  {
    __DTOR_LIST__ = . ;
    LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2);
    *(.dtors)
    LONG(0) ;
    __DTOR_END__ = . ;
  } > ext_cram
  /*
   * Allocate trap and interrupt vector tables.
   */
  .text2 ALIGN(4) :
  {
    *(.traptab)
    *(.inttab)
    /*
     * .gnu.warning sections are handled specially by elf32.em.
     */
    *(.gnu.warning)
  } > ext_cram
  _etext = ALIGN(4) ;
  PROVIDE(etext = _etext) ;
  /*
   * We're done now with the text part of the executable.  The
   * following sections are special in that their initial code or
   * data (if any) must also be stored in said text part of an
   * executable, but they "live" at completely different addresses
   * at runtime -- usually in RAM areas.  NOTE: This is not really
   * necessary if you use a special program loader (e.g., a debugger)
   * to load a complete executable consisting of code, data, BSS, etc.
   * into the RAM of some target hardware or a simulator, but it *is*
   * necessary if you want to burn your application into non-volatile
   * memories such as EPROM or FLASH.
   */
  .pcptext : AT(_etext)
  {
    PCODE_BASE = . ;
    *(.pcptext)
    *(.pcptext.*)
    . = ALIGN(4) ;
    PCODE_END = . ;
  } > pcp_text
  .pcpdata : AT(LOADADDR(.pcptext) + SIZEOF(.pcptext))
  {
    PRAM_BASE = . ;
    *(.pcpdata)
    *(.pcpdata.*)
    . = ALIGN(4) ;
    PRAM_END = . ;
  } > pcp_data

/*
  .data : AT(LOADADDR(.pcpdata) + SIZEOF(.pcpdata))
*/
  .data :
  {
    . = ALIGN(8) ;
    DATA_BASE = ABSOLUTE(.) ;
    *(.data)
    *(.data.*)
    *(.gnu.linkonce.d.*)
    SORT(CONSTRUCTORS)
    DATA_END = ABSOLUTE(.) ;
  } > int_cram
  .sdata  : AT(LOADADDR(.data) + SIZEOF(.data))
  {
    . = ALIGN(8) ;
    SDATA_BASE = ABSOLUTE(.) ;
    _enddata = ABSOLUTE(.) ;
    PROVIDE(__sdata_start = .);
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
  } > int_cram
  .sbss ALIGN(8) (NOLOAD) :
  {
    . = ALIGN(8) ;
    _edata = . ;
    PROVIDE(edata = _edata) ;
    PROVIDE(__sbss_start = .);
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
  } > int_cram
  /*
   * Allocate space for BSS sections.
   */
  .bss ALIGN(8) (NOLOAD) :
  {
    BSS_BASE = ABSOLUTE(.) ;
    *(.bss)
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(8) ;
    __ISTACK = ABSOLUTE (. + __ISTACK_SIZE) ;
    __USTACK = __ISTACK + __USTACK_SIZE ;
    __HEAP = __USTACK ;
    __HEAP_END = __RAM_END ;
  } > int_cram
  _end = __HEAP_END ;
  PROVIDE(end = _end) ;
  /* Allocate space for the CSA.  */
  __CSA_END = __CSA_BEGIN + __CSA_SIZE ;
  /* Make sure CSA, stack and heap addresses are properly aligned.  */
  _. = ASSERT ((__CSA_BEGIN & 0x3f) == 0 , "illegal CSA start address") ;
  _. = ASSERT ((__CSA_SIZE & 0x3f) == 0 , "illegal CSA size") ;
  _. = ASSERT ((__ISTACK & 7) == 0 , "ISTACK not doubleword aligned") ;
  _. = ASSERT ((__USTACK & 7) == 0 , "USTACK not doubleword aligned") ;
  _. = ASSERT ((__HEAP_END & 7) == 0 , "HEAP not doubleword aligned") ;
  /* Make sure enough memory is available for stacks and heap.  */
/*
  _. = ASSERT (__ISTACK <= __RAM_END , "not enough memory for ISTACK") ;
  _. = ASSERT (__USTACK <= __RAM_END , "not enough memory for USTACK") ;
  _. = ASSERT ((__HEAP_END - __HEAP) >= __HEAP_MIN ,
               "not enough memory for HEAP") ;
*/
  /* Define a default symbol for address 0.  */
  NULL = DEFINED (NULL) ? NULL : 0 ;
  /*
   * DWARF debug sections.
   * Symbols in the DWARF debugging sections are relative to the
   * beginning of the section, so we begin them at 0.
   */
  /*
   * DWARF 1
   */
  .comment         0 : { *(.comment) }
  .debug           0 : { *(.debug) }
  .line            0 : { *(.line) }
  /*
   * GNU DWARF 1 extensions
   */
  .debug_srcinfo   0 : { *(.debug_srcinfo) }
  .debug_sfnames   0 : { *(.debug_sfnames) }
  /*
   * DWARF 1.1 and DWARF 2
   */
  .debug_aranges   0 : { *(.debug_aranges) }
  .debug_pubnames  0 : { *(.debug_pubnames) }
  /*
   * DWARF 2
   */
  .debug_info      0 : { *(.debug_info) }
  .debug_abbrev    0 : { *(.debug_abbrev) }
  .debug_line      0 : { *(.debug_line) }
  .debug_frame     0 : { *(.debug_frame) }
  .debug_str       0 : { *(.debug_str) }
  .debug_loc       0 : { *(.debug_loc) }
  .debug_macinfo   0 : { *(.debug_macinfo) }
  .debug_ranges    0 : { *(.debug_ranges) }
  /*
   * SGI/MIPS DWARF 2 extensions
   */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /*
   * Optional sections that may only appear when relocating.
   */
  /*
   * Optional sections that may appear regardless of relocating.
   */
  .boffs           0 : { KEEP (*(.boffs)) }
}
