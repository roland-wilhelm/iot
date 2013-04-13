program P;
{$APPTYPE CONSOLE}


// small internal TEST
//
//  * install the USBIO driver on a standard USB mouse
//  * run the application in a cmd or command window
//

uses
  sysutils,windows,
  USBIO            in '.\..\units\usbio.pas',
  USBIObuf         in '.\..\units\usbiobuf.pas',
  USBIOPipe        in '.\..\units\usbiopipe.pas',
  USBIO_I          in '.\..\units\Usbio_i.pas',
  USBSPEC          in '.\..\units\Usbspec.pas',
  usbio_i_delphi   in '.\..\units\usbio_i_delphi.pas';

const
  CONFIG_INDEX                         = 0;
  CONFIG_NB_OF_INTERFACES              = 1;
  CONFIG_INTERFACE                     = 0;
  CONFIG_ALT_SETTING                   = 0;
  CONFIG_TRAN_SIZE                     = 4096;
  ENDPOINT_ADDRESS                     = $81;
	BUFFER_SIZE                          = 64;
  NB_OF_BUFFERS                        = 5;
var
  test             : tusbio;
  pi               : TusbioPipe;
  BufPool          : TUsbIoBufPool;
  mbuf             : TUsbIoBuf;
  ep               : HDEVINFO;
  desc             : USB_DEVICE_DESCRIPTOR;
  PStrDesc         : PUSB_STRING_DESCRIPTOR;
  StrDescSize      : DWORD = sizeof(USB_STRING_DESCRIPTOR);
  status           : DWORD;
  conf             : USBIO_SET_CONFIGURATION;
  confInfo         : USBIO_CONFIGURATION_INFO;
  buf1             : array[0..100] of byte;
  bytecnt          : DWORD;
  i                : integer;
  beideMausTasten  : boolean;
  FifoSize         : integer;

label Exit;

begin

//=================================================
// Usbio test....
//=================================================

  test:=tusbio.Create;
  ep:=test.CreateDeviceList(@USBIO_IID);

	status:=test.open(0,ep,@USBIO_IID);
	if status <> USBIO_ERR_SUCCESS then
		begin
		writeln('OPEN:',test.errortext(status));
		goto Exit;
		end
	else
		writeln('OPEN Device ok');

	Status:=test.GetDeviceDescriptor(@desc);
	if status <> USBIO_ERR_SUCCESS then
		begin
		writeln('GetDeviceDescriptor:',test.errortext(status));
		goto Exit;
		end
	else
		writeln('GetDeviceDescriptor:',' ',desc.idVendor,' ',desc.idProduct);

// get the string descriptor, our mouse was buggy, so we skip the test

	getmem(PStrDesc,StrDescSize);
  ZeroMemory(PStrDesc,StrDescSize);
	status:=test.GetStringDescriptor(PStrDesc,StrDescSize,1);
	if status <> USBIO_ERR_SUCCESS then
		begin
		writeln('GetStringDescriptor:',test.errortext(status));
		goto Exit;
		end
	else
		writeln('GetStringDescriptor: ',WideCharToString(PStrDesc^.bString));



	Conf.ConfigurationIndex:=CONFIG_INDEX;
	Conf.NbOfInterfaces:=CONFIG_NB_OF_INTERFACES;
	Conf.InterfaceList[0].InterfaceIndex:=CONFIG_INTERFACE;
	Conf.InterfaceList[0].AlternateSettingIndex:=CONFIG_ALT_SETTING;
	Conf.InterfaceList[0].MaximumTransferSize:=CONFIG_TRAN_SIZE;
	Status:=test.SetConfiguration(@Conf);
	if status <> USBIO_ERR_SUCCESS then
		begin
		writeln('SetConfiguration:',test.errortext(status));
		goto Exit;
		end
	else
		writeln('SetConfiguration ok');

  Status:=test.GetConfigurationInfo(@confInfo);
	if status <> USBIO_ERR_SUCCESS then
		begin
		writeln('GetConfigurationInfo:',test.errortext(status));
		goto Exit;
		end
	else
		writeln('GetConfigurationInfo ok');

  FifoSize := BUFFER_SIZE;
  if confInfo.NbOfPipes > 0 then
    FifoSize := confInfo.PipeInfo[0].MaximumPacketSize;

	pi:=TusbioPipe.Create;
	status:=pi.Bind(0,ENDPOINT_ADDRESS,ep,@Usbio_IID);
	if status <> USBIO_ERR_SUCCESS then
		begin
		writeln('Bind:',test.errortext(status));
		goto Exit;
		end
	else
		writeln('Bind ok');

//=================================================
// readSYNC testen....
//=================================================

	BeideMausTasten:=false;
	Writeln('Move mouse! Press both mouse buttons to stop');
	while not(BeideMausTasten) do
		begin
			bytecnt:=FifoSize;
			Status := pi.ReadSync(@Buf1,bytecnt);
			if (Status <> USBIO_ERR_SUCCESS) then
				begin
				writeln('ReadSync:',test.errortext(status));
				BeideMausTasten := true;
				end
			else
				begin
				if bytecnt>0 then
					for i:=0 to bytecnt-1 do write(buf1[i]:3);
				Writeln;
				beideMausTasten:=(buf1[0]=3);
				end;
	 end;



	writeln;
	writeln;

//=================================================
// Buf testen....
//=================================================

	BufPool:=TUsbIoBufPool.create;
	BufPool.Allocate(FifoSize,NB_OF_BUFFERS);
	Writeln('Test buffer pool');
	Writeln('Move mouse! Press both mouse buttons to stop');

//=================================================
// read testen....
//=================================================


	BeideMausTasten:=false;
	while not(BeideMausTasten) do
		begin
			mBuf:=BufPool.get;
			mBuf.NumberOfBytesToTransfer:=FifoSize;
			pi.Read(mbuf);
			Status := pi.WaitForCompletion(mbuf,INFINITE);
			if (mbuf.bytestransferred>0) and (Status = USBIO_ERR_SUCCESS) then
				begin
				for i:=0 to mbuf.bytestransferred-1 do write(byte(pchar(mbuf.buffer)[i]):3);
				beideMausTasten:=(byte(pchar(mbuf.buffer)[0])=3);
				end
			else
				begin
				writeln('Read:',test.errortext(status));
				beideMausTasten:=true;
				end;
			Writeln;
			BufPool.put(mBuf);
		end;

	bufpool.destroy;

Exit:
	test.DestroyDeviceList(@USBIO_IID);

end.
