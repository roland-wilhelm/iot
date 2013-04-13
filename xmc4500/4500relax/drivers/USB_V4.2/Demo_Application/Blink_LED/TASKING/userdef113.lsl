#include "tc1v1_3.lsl"

processor spe
{
	derivative = userdef113;
}

derivative userdef113
{
	core tc
	{
		architecture = TC1V1.3;
	}

	bus fpi_bus
	{
		mau = 8;
		width = 32;
		map (dest=bus:tc:fpi_bus, dest_offset=0, size=4G);
	}

	memory ldram
	{
		mau = 8;
		size = 28k;
		type = ram;
		map (dest=bus:tc:fpi_bus, dest_offset=0xD0000000, size=28k);
	}
}
