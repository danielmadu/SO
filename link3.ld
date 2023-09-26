OUTPUT_FORMAT("binary")
ENTRY(start)
phys = 0x00100000;
SECTIONS
{
  .text phys : AT(phys) {
 /* discardable kernel code */
	g_d_code = .; _g_d_code = .;
	*(.dtext*)
	. = ALIGN(4096);
/* kernel code */
	g_code = .; _g_code = .;
	*(.text*)
  }
  .data : AT(phys + (data - code))
  {
  /* discardable kernel data */
	g_d_data = .; _g_d_data = .;
	*(.ddata*)
	. = ALIGN(4096);
/* kernel data */
	g_data = .; _g_data = .;
	*(.data*)
	. = ALIGN(4096);
  }
  .bss : AT(phys + (bss - code))
  {
 /* discardable kernel BSS */
	g_d_bss = .; _g_d_bss = .;
	*(.dbss*)
	. = ALIGN(4096);
/* kernel BSS */
	g_bss = .; _g_bss = .;
	*(.bss*)
	*(COMMON) /* "common" variables */
	. = ALIGN(4096);
  }
    g_end = .; _g_end = .;

}

