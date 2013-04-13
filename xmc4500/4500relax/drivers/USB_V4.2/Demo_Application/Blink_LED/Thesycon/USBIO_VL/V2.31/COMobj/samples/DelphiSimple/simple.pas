{
This is a simple demo program for the USBIO interface.
It asumes a device with an endpoint $81 for IN operation and
an endpoint $02 for OUT operation. The device should answer
something on pipe $81 is somesing is sent to pipe $02.

Please review the code and change the settings for your device.

The sample demonstrates the usage of two pipes at the same time.

Press the initDevice button. Than press the Write Button.

Exit the application to stop the reading.
}
unit simple;

interface

uses
	Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
	USBIOCOMLib_TLB,ActiveX, ComCtrls, StdCtrls, ExtCtrls, Menus;

type
	TForm1 = class(TForm)
		InitDevice: TButton;
		Write: TButton;
		Label1: TLabel;
		BytesReturned: TEdit;
		Label2: TLabel;
		Label3: TLabel;
		Bytes: TEdit;
		FillWith: TEdit;
		Text: TEdit;

		procedure OnCreate(Sender: TObject);
		procedure ReadComplete(Sender: TObject; var Obj: OleVariant);
		procedure GetWriteStatus(Sender: TObject; var Obj: OleVariant);
		procedure WriteComplete(Sender: TObject; var Obj: OleVariant);
		procedure InitDeviceClick(Sender: TObject);
		procedure WriteClick(Sender: TObject);
		procedure ShowError(Status: integer);

	private
		{ Private-Deklarationen }
	public
		{ Public-Deklarationen }
	end;


const
	// adapt these two settings for your device
	ReadPipe = $81;
	WritePipe = $02;

var
	Form1: TForm1;
	// a variable for pipe of the device
	Pipe1:  TUSBIOInterface3;
	Pipe2:  TUSBIOInterface3;

	// define guid of USBIO interface
	guid: widestring = '{325ddf96-938c-11d3-9e34-0080c82727f4}';


implementation

{$R *.DFM}

// simple helper function to show an error
procedure TForm1.ShowError(Status: integer);
begin
	if Status <> USBIO_ERR_SUCCESS then
		MessageDlg(Pipe1.ErrorText(Status), mtError, [mbOk], 0);
end;

// init the USBIO com object
procedure TForm1.OnCreate(Sender: TObject);
begin
	// create a com object instance for each pipe
	Pipe1 := TUSBIOInterface3.Create(Form1);
	Pipe2 := TUSBIOInterface3.Create(Form1);
	// setup the used callback functions
	Pipe1.OnReadComplete := Form1.ReadComplete;
	Pipe2.OnWriteComplete := Form1.WriteComplete;
	Pipe2.OnWriteStatusAvailable := Form1.GetWriteStatus;
	// connect to COM object
	try
		Pipe1.Connect;
	except
		MessageDlg('USBIOCOM not registered! Use "regsvr32 usbiocom.dll"', mtError, [mbOk], 0);
	end;
end;

// initialization of the USB device
procedure TForm1.InitDeviceClick(Sender: TObject);
var
	Status,NumberOfDevices: integer;
begin
	Pipe1.EnumerateDevices(guid,NumberOfDevices);
	if (NumberOfDevices = 0 ) then
		MessageDlg('No USB Device connected or USBIO driver not installed',mtError, [mbOk], 0)
	else
	begin
		// open the device, here pipe1 handle is used
		Pipe1.OpenDevice(0,Status);
		ShowError(Status);
		// add an interface for configuration
		Pipe1.AddInterface(0,0,4096,Status);
		ShowError(Status);
		// set configuration
		Pipe1.SetConfiguration(0,Status);
		ShowError(Status);
		// pind first pipe
		Pipe1.Bind(ReadPipe,Status);
		ShowError(Status);
		// start the reading on this pipe
		Pipe1.StartReading(Pipe1.EndpointFifoSize,5,5,Status);
		ShowError(Status);
		// open a handle for pipe2
		Pipe2.OpenDevice(0,Status);
		ShowError(Status);
		// bind it to an endpoint
		Pipe2.Bind(WritePipe,Status);
		ShowError(Status);
		// start writing on this channel
		Pipe2.StartWriting(Pipe2.EndpointFifoSize,5,5,1,Status);
		ShowError(Status);
		// the the default write size to fifo size
		Bytes.Text := inttostr(Pipe2.EndpointFifoSize);
	end;
end;


// this function is called if the device has sent data to the PC
procedure TForm1.ReadComplete(Sender: TObject; var Obj: OleVariant);
var
	i,ByteCount,Status: integer;
	v : byte;
	ReadBuffer: PSAFEARRAY;
	output : string;
begin
	// create a buffer, note: the buffer could be a global variable
	ReadBuffer :=  SafeArrayCreateVector(VT_UI1,0,Pipe1.EndpointFifoSize);
	// read the data from com object
	ByteCount := Pipe1.EndpointFifoSize;
	Pipe1.ReadData(ReadBuffer,ByteCount,Status);
	// print the data in a buffer
	if (Status = USBIO_ERR_SUCCESS) then
	begin
		Text.SetTextBuf('');
		for i:=0 to ByteCount-1 do
		begin
			SafeArrayGetElement(ReadBuffer,i,v);
			output := output + ' $' + inttohex(v,2);
		end;
		Text.Text := output;
		BytesReturned.Text := inttostr(ByteCount);
	end
	else
	begin
		ShowError(Status);
	end;
	// delete the buffer
	SafeArrayDestroy(ReadBuffer);
end;

// is called if a write is complete
// this simple application has nothing to do here
procedure TForm1.WriteComplete(Sender: TObject; var Obj: OleVariant);
var
	Status :integer;
begin
	Status := 0; // do a dumy action here or the compiler deletes the function ?!
	ShowError(Status);
end;

// get the status of the write operation
procedure TForm1.GetWriteStatus(Sender: TObject; var Obj: OleVariant);
var
	id,Status: integer;
begin
	Pipe2.GetWriteStatus(id,Status);
	ShowError(Status);
end;


// send data on press write button
procedure TForm1.WriteClick(Sender: TObject);
var
	i,ByteCount,Status: integer;
	v : byte;
	WriteBuffer: PSAFEARRAY;
begin
	// get the buffer length
	ByteCount := strtoint(bytes.Text);
	// limit it to buffer size
	if ByteCount > Pipe2.EndpointFifoSize then ByteCount := Pipe2.EndpointFifoSize;
	// allocate safe array
	WriteBuffer :=  SafeArrayCreateVector(VT_UI1,0,ByteCount);
	// fill it
	v := strtoint(FillWith.Text);
	for i:=0 to ByteCount-1 do SafeArrayPutElement(WriteBuffer,i,v);
	Pipe2.WriteData(WriteBuffer,0,Status);
	ShowError(Status);
	SafeArrayDestroy(WriteBuffer);
end;

end.
