#define RESET 0xA0000000
#define LIBRARIES 0xA0004000
#define INTTAB 0xA00F0000
#define TRAPTAB 0xA00F2000
#define CSA 64
#define XVWBUF 256

section_layout spe:tc:linear
{
	group stack "ustack" (size=8k);
}
section_layout spe:tc:linear
{
	group stack "istack" (size=1k);
}

section_layout spe:tc:linear
{
	group heap "heap" (size=16k);
}
memory ext_c
{
	mau = 8;
	size = 512k;
	type = rom;
	map (dest=bus:spe:fpi_bus, dest_offset=0xA0000000, size=512k);
}
memory ext_d
{
	mau = 8;
	size = 448k;
	type = ram;
	map (dest=bus:spe:fpi_bus, dest_offset=0xA0080000, size=448k);
}
memory vecttable
{
	mau = 8;
	size = 9k;
	type = rom;
	map (dest=bus:spe:fpi_bus, dest_offset=0xA00F0000, size=9k);
}
section_layout spe:tc:linear
{
	group main (ordered, run_addr=mem:ext_c)
	{
		select ".text.*.main";
	}
}
