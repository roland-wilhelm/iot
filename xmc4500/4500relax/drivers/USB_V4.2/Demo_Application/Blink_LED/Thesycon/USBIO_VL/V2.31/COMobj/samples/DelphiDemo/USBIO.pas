{
(c) 2001-2002 Thesycon Systemsoftware & Consulting GmbH


This program was developed with Delphi 5.

This is a sample program for the USBIOCOM interface. It
requires the registered USBIOCOM interface and the USBIO
device driver. Furthermore, an USB device is required.
This program does not use the complete functionality of 
the USBIOCOM interface. It is intended as a demonstration
of a typical usage scenario.

To compile the project the USBIOCOM object must be imported
into Delphi. Select "Project/Import Typelibrary ..." and import
the USBIOCOM object. Delphi generates a wrapper class
USBIOCOMLib_TLB.
Note: We deliver such a class with this project.
You should overwrite this class in the folder
where the project is installed.

An USB mouse or keyboard can be used as a demo device.
Note that those devices cannot be used as Windows 
input devices at the same time, e.g. as the system keyboard.

For more information about the USBIOCOM interface and the 
USBIO device driver refer to the documentation that can be 
found in usbiocom.pdf and usbioman.pdf.

For latest updates visit http://www.thesycon.de.


How to use this sample application:

1. Connect an USB device with at least one IN endpoint to the PC.

2. Use the USBIO install wizard to install the USBIO device driver
for this device.

3. Make sure that the USBIOCOM interface is registered on the PC.
Normally, this is done during installation.
You can run the command 
>regsvr32 usbiocom.dll
to register the USBIOCOM interface manually.

4. Run this application and carry out the following actions:
a) press "Enumerate" ->  Number of devices should be at least 1
b) press "Open"
c) switch to the "Interface" page
d) enter interface and alternate setting, press "Add Interface"
e) press "Set Conf"
f) enter the endpoint number (address), add 128 ($80) for IN endpoints
g) press "Bind"
h) switch to the "Read" page
i) press "Start Read"
j) press keys on the keyboard or move the mouse, 
   the file should contain the received data

}


unit USBIO;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, OleServer, USBIOCOMLib_TLB,ActiveX, ComCtrls, USBIOoutput,
  ExtCtrls;

type
  TMainDlg = class(TForm)
    ErrorText: TEdit;
    ClearError: TButton;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Enumerate: TButton;
    NumberOfDevices: TEdit;
    OpenDevice: TButton;
    DeviceNumber: TEdit;
    CloseDevice: TButton;
    GroupBox2: TGroupBox;
    DriverInfo: TButton;
    ApiVersion: TEdit;
    DriverVersion: TEdit;
    BuildVersion: TEdit;
    DriverFlags: TEdit;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    GroupBox3: TGroupBox;
    GetStringDesc: TButton;
    StringDesc: TEdit;
    StringIndex: TEdit;
    TabSheet3: TTabSheet;
    GroupBox4: TGroupBox;
    AddInterface: TButton;
    DeleteInterface: TButton;
    InterfaceIndex: TEdit;
    AlternateSetting: TEdit;
    MaxTransferSize: TEdit;
    GroupBox5: TGroupBox;
    SetConf: TButton;
    ConfIndex: TEdit;
    UnConfigure: TButton;
    GroupBox6: TGroupBox;
    Bind: TButton;
    PipeNumber: TEdit;
    UnBind: TButton;
    TabSheet4: TTabSheet;
    GroupBox7: TGroupBox;
    StartReading: TButton;
    BufferSize: TEdit;
    NoOfBuffer: TEdit;
    MaxErrorCount: TEdit;
    StopRead: TButton;
    IsIso: TCheckBox;
    FileName: TEdit;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    ProgressBar1: TProgressBar;
    TabSheet5: TTabSheet;
    GroupBox8: TGroupBox;
    CyclePort: TButton;
    ResetDevice: TButton;
    getframeno: TButton;
    frmno: TEdit;
    GroupBox9: TGroupBox;
    GetDevicePathName: TButton;
    GetDevicePathNamefield: TEdit;
    PowerState: TGroupBox;
    getpowerstate: TButton;
    getpowerstatefield: TEdit;
    setpowerstate: TButton;
    powerstatecombo: TComboBox;
    GroupBox10: TGroupBox;
    getstatus: TButton;
    statusindex: TEdit;
    statuscombo: TComboBox;
    statusout: TEdit;
    Label18: TLabel;
    Label19: TLabel;
    Devicedescriptorbox: TGroupBox;
    getdevicedescriptor: TButton;
    Feature: TTabSheet;
    Featurebox: TGroupBox;
    setfeature: TButton;
    featurecombo: TComboBox;
    featurefield: TEdit;
    featureindexfield: TEdit;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    clearfeature: TButton;
    GroupBox11: TGroupBox;
    GetDesc: TButton;
    DescType: TEdit;
    DescIndex: TEdit;
    DescSize: TEdit;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    TabSheet6: TTabSheet;
    GroupBox12: TGroupBox;
    StartWrite: TButton;
    StopWrite: TButton;
    writebuffersize: TEdit;
    writenumberofbuffers: TEdit;
    writeerrorcount: TEdit;
    Label26: TLabel;
    Label27: TLabel;
    Label28: TLabel;
    writeisocheck: TCheckBox;
    writefile: TEdit;
    WriteStatusCheck: TCheckBox;
    OpenDialog1: TOpenDialog;
    OpenFile: TButton;
    FromFileCheck: TCheckBox;
    FilledWith: TEdit;
    Label29: TLabel;
    SaveDialog1: TSaveDialog;
    SaveFile: TButton;
    Label31: TLabel;
    WriteToFile: TCheckBox;
    Timer1: TTimer;
    PnPNotification: TGroupBox;
    EnablePnPNotification: TButton;
    DisablePnPNotification: TButton;
    TabSheet7: TTabSheet;
    showwindow: TButton;
    hidewindow: TButton;
    clearoutput: TButton;
    ClassOrVendorRequestBox: TGroupBox;
    VendorDirectionCombo: TComboBox;
    VendorTypeCombo: TComboBox;
    VendorRecipientCombo: TComboBox;
    VendorDirectionLabel: TLabel;
    VendorTypeLabel: TLabel;
    VendorRecipientLabel: TLabel;
    VendorRequestLabel: TLabel;
    VendorValueText: TEdit;
    VendorValueLabel: TLabel;
    VendorIndexText: TEdit;
    VendorIndexLabel: TLabel;
    VendorBufferSizeText: TEdit;
    VendorBufferText: TEdit;
    VendorBufferSizeLabel: TLabel;
    VendorBufferLabel: TLabel;
    VendorSendButton: TButton;
    VendorRequest: TEdit;
    DisableProgressBar: TCheckBox;
    GroupBox13: TGroupBox;
    QueryStatistics: TButton;
    Label33: TLabel;
    Label34: TLabel;
    Label35: TLabel;
    Label36: TLabel;
    Label37: TLabel;
    ActualAveragingIntervalEdit: TEdit;
    AverageRateEdit: TEdit;
    BytesTransferredEdit: TEdit;
    RequestsSucceededEdit: TEdit;
    RequestsFailedEdit: TEdit;
    GroupBox14: TGroupBox;
    GetBandwidthInfo: TButton;
    Label38: TLabel;
    Label39: TLabel;
    TotalBandwidthEdit: TEdit;
    ConsumedBandwidthEdit: TEdit;
    SetupPipeStatistics: TButton;
    AveragingIntervalEdit: TEdit;
    AveragingInterval: TLabel;
    GroupBox15: TGroupBox;
    GetDeviceInfo: TButton;
    GetDeviceInfoCheck: TCheckBox;
    ResetStatistics: TButton;
    Label30: TLabel;
    Label32: TLabel;
    AcquireButton: TButton;
    ReleaseButton: TButton;
    procedure EnumerateClick(Sender: TObject);
    procedure OpenDeviceClick(Sender: TObject);
    procedure ClearErrorClick(Sender: TObject);
    procedure CloseDeviceClick(Sender: TObject);
    procedure DriverInfoClick(Sender: TObject);
    procedure GetStringDescClick(Sender: TObject);
    procedure DeleteInterfaceClick(Sender: TObject);
    procedure AddInterfaceClick(Sender: TObject);
    procedure SetConfClick(Sender: TObject);
    procedure UnConfigureClick(Sender: TObject);
    procedure StartReadingClick(Sender: TObject);
    procedure StopReadClick(Sender: TObject);
    procedure BindClick(Sender: TObject);
    procedure UnBindClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure ShowError(Status: integer);
   
    procedure CyclePortClick(Sender: TObject);
    procedure ResetDeviceClick(Sender: TObject);
    procedure getframenoClick(Sender: TObject);
    procedure GetDevicePathNameClick(Sender: TObject);
    procedure getpowerstateClick(Sender: TObject);
    procedure setpowerstateClick(Sender: TObject);
    procedure getstatusClick(Sender: TObject);
    procedure setfeatureClick(Sender: TObject);
    procedure clearfeatureClick(Sender: TObject);
    procedure getdevicedescriptorClick(Sender: TObject);
    procedure showwindowClick(Sender: TObject);
    procedure hidewindowClick(Sender: TObject);
    procedure GetDescClick(Sender: TObject);
    procedure clearoutputClick(Sender: TObject);
    procedure StartWriteClick(Sender: TObject);
    procedure OpenFileClick(Sender: TObject);
    procedure StopWriteClick(Sender: TObject);
    procedure SaveFileClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Timer1Timer(Sender: TObject);
    procedure EnablePnPNotificationClick(Sender: TObject);
    procedure DisablePnPNotificationClick(Sender: TObject);
    procedure VendorSendButtonClick(Sender: TObject);

    // The following are the call-back functions.
    // They have to be implemented in the scope of a class; 
    // we use the main dialog class here.
    procedure ReadComplete(Sender: TObject; var Obj: OleVariant);
    procedure WriteComplete(Sender: TObject;  var Obj: OleVariant);
    procedure WriteStatus(Sender: TObject;  var Obj: OleVariant);
    procedure PnPAddNotification(Sender: TObject;  var Obj: OleVariant);
    procedure PnPRemoveNotification(Sender: TObject;  var Obj: OleVariant);
    procedure QueryStatisticsClick(Sender: TObject);
    procedure GetBandwidthInfoClick(Sender: TObject);
    procedure SetupPipeStatisticsClick(Sender: TObject);
    procedure GetDeviceInfoClick(Sender: TObject);
    procedure ResetStatisticsClick(Sender: TObject);
    procedure AcquireButtonClick(Sender: TObject);
    procedure ReleaseButtonClick(Sender: TObject);


  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  // main dialog with the GUI
  MainDlg: TMainDlg;

  // The instance of the USBIOCOM interface.
  // TUSBIOInterface is defined in USBIOCOMlib_TLB which is
  // generated automatically from the USBIOCOM type library.
  // The instance must be initialized with TUSBIOInterface.Create(MainDlg).
  // Furthermore, the call-back functions have to be assigned.
	// For these steps, see the procedure InitUSBIOCom at the end of this file.
	USBIOInterface:  TUSBIOInterface3;

  // The default GUID of the USBIO driver interface.
  // IMPORTANT: This should be replaced by a private GUID in a production version.
  // For details, refer to the manual and usbio.inf.
  USBIO_Default_GUID : string = '{325ddf96-938c-11d3-9e34-0080c82727f4}';


  // some helper variables
  status: integer;
  helpstatus : longword;
  UserId: integer;
  OutputFile: file;
  InputFile: textfile;
  IsIsoFlag: Boolean;
  FileOpenFlag: Boolean = false;
  IsReadStarted: Boolean = false;
  IsWriteStarted: Boolean = false;
  WriteSt: Boolean = false;
  // global arrays for read and isoread
  readbuffer,infobuffer,writebuffer, StatusArray: PSAFEARRAY;
	
  // forward declarations
  procedure SendBuffer();
	procedure InitUSBIOCom();

implementation

{$R *.DFM}

// *****************************************************
// Enumeration Page
// *****************************************************
procedure TMainDlg.EnumerateClick(Sender: TObject);
var
  Device: integer;
begin
  USBIOInterface.EnumerateDevices(USBIO_Default_GUID,Device);
  MainDlg.NumberOfDevices.Text := inttostr(Device);
end;

// open device
procedure TMainDlg.OpenDeviceClick(Sender: TObject);
begin
  USBIOInterface.OpenDevice(strtoint(MainDlg.DeviceNumber.Text),status);
  ShowError(status);
end;

// close device
procedure TMainDlg.CloseDeviceClick(Sender: TObject);
begin
  USBIOInterface.CloseDevice;
end;

// get driver info
procedure TMainDlg.DriverInfoClick(Sender: TObject);
var
  api,drv,drvbuild,flags : integer;
begin
  USBIOInterface.GetDriverInfo(api,drv,drvbuild,flags,status);
  ShowError(status);
  if status = USBIO_ERR_SUCCESS then
  begin
    MainDlg.ApiVersion.Text := IntToHex(api div 256,1) + '.'+IntToHex(api mod 256,2);
    MainDlg.DriverVersion.Text := inttostr(drv div 256)+'.'+inttostr(drv mod 256);
    MainDlg.BuildVersion.Text := inttostr(drvbuild);
    MainDlg.DriverFlags.Text := inttostr(flags);
  end;
end;

// Enable PnP Notification
procedure TMainDlg.EnablePnPNotificationClick(Sender: TObject);
begin
  USBIOInterface.EnablePnPNotification(USBIO_Default_GUID,Status);
  ShowError(Status);
end;

// Disable PnP Notification
procedure TMainDlg.DisablePnPNotificationClick(Sender: TObject);
begin
  USBIOInterface.DisablePnPNotification(USBIO_Default_GUID,Status);
  ShowError(Status);
end;

// PnPAddNotification
procedure TMainDlg.PnPAddNotification(Sender: TObject; var Obj: OleVariant);
begin
  ErrorText.Text:='Device added !!!';
end;

// PnPRemoveNotification
procedure TMainDlg.PnPRemoveNotification(Sender: TObject; var Obj: OleVariant);
begin
  ErrorText.Text:='Device removed !!!';
end;


// *****************************************************
// Descriptor Page
// *****************************************************

// get string descriptor from device
procedure TMainDlg.GetStringDescClick(Sender: TObject);
type
  PByte = ^byte;
var
  ps: PSAFEARRAY;
  sp: tagSAFEARRAYBOUND;
  pb: PByte;
  p: pointer;
  s: string;
  z,size,index: integer;

begin
  size:=256;
  index:=strtoint(StringIndex.text);
  // create SAFEARRAY
  ps:=SafeArrayCreateVector(VT_UI1,0,256);
  // call USBIO
  USBIOInterface.GetStringDescriptor(ps,size,index,0,status);
  ShowError(status);
  if status = USBIO_ERR_SUCCESS then
  begin
    // format UNICODE string descriptor
    MainDlg.StringDesc.Text:='';
    SafeArrayAccessData(ps,p);
    sp:=ps^.rgsabound[0];
    pb:=p;
    // skip the first two entries: length and type
    inc(pb);
    inc(pb);
    if index = 0 then
    begin
      // this is the language ID
      s := 'LanguageID: ';
      inc(pb);
      if (pb^ < 10 ) then s:= s+'0';
      s := s + inttostr(pb^);
      dec(pb);
      if (pb^ < 10 ) then s:= s+'0';
      s := s + inttostr(pb^);
    end
    else
    begin
      // this is an unicode string
      for z:=1 to (sp.cElements div 2) do
      begin
        s := s + chr(pb^);
        inc(pb);
        inc(pb);
      end;
    end;
    MainDlg.StringDesc.Text := s;
  end;
  SafeArrayUnAccessData(ps);
  // we have to free the buffer
  SafeArrayDestroy(ps);
end; // GetStringDescClick


procedure TMainDlg.GetDescClick(Sender: TObject);
var
  data: PSAFEARRAY;
  by:byte;
  i,s,size : integer;
  OutputString: string;
begin
  // number of bytes to read from the descriptor
  s:=strtoint(descsize.text);
  // create SafeArray
  data:=SafeArrayCreateVector(VT_UI1,0,s);
  // call USBIO
  USBIOInterface.GetDescriptor(data,s,0,strtoint(desctype.text),strtoint(descindex.text),0,status);
  MainDlg.ShowError(status);
  if status = USBIO_ERR_SUCCESS then
  begin
    output.outputmemo.Lines.Append('Descriptor , type '+ (desctype.text) + ', index '+ (descindex.text));
    if s>0 then
    begin
      size:=0;
      for i:=0 to s-1 do
      begin
        // print data in readable form
        SafeArrayGetElement(data,i,by);
        if size> i then
          OutputString := OutputString + inttohex(by,2)+' '
        else
        begin
          size:= size + by;
          if i<>0 then output.outputmemo.Lines.Append(OutputString);
          OutputString := inttohex(by,2)+' ';
        end;
      end;
      output.outputmemo.Lines.Append(OutputString);
    end;
  end;
  // destroy SafeArray
  SafeArrayDestroy(data);
end; // GetDescClick


// get devicedescriptor
procedure TMainDlg.getdevicedescriptorClick(Sender: TObject);
var
  data: PSAFEARRAY;
  by: byte;
  i,s,size: integer;
  OutputString: string;
begin
  // number of bytes to read from the descriptor
  s:=4096;
  // create SafeArray
  data:=SafeArrayCreateVector(VT_UI1,0,4096);
  // call USBIO
  USBIOInterface.GetDeviceDescriptor(data,s,status);
  MainDlg.ShowError(status);
  if status = USBIO_ERR_SUCCESS then
  begin
    output.outputmemo.Lines.Append('');
    output.outputmemo.Lines.Append('Device Descriptor');
    output.outputmemo.Lines.Append('');
    if s>0 then
    begin
      size:=0;
      for i:=0 to s-1 do
      begin
        // print data in readable form
        SafeArrayGetElement(data,i,by);
        if size> i then
          OutputString := OutputString + inttohex(by,2)+' '
        else
        begin
          size:= size + by;
          if i<>0 then output.outputmemo.Lines.Append(OutputString);
          OutputString := inttohex(by,2)+' ';
        end;
      end;
      output.outputmemo.Lines.Append(OutputString);
    end;
  end;
  // destroy SafeArray
  SafeArrayDestroy(data);
end;


// output window control
procedure TMainDlg.showwindowClick(Sender: TObject);
begin
  output.Show;
end;

procedure TMainDlg.hidewindowClick(Sender: TObject);
begin
  output.Hide;
end;

procedure TMainDlg.clearoutputClick(Sender: TObject);
begin
  output.outputmemo.Clear;
end;


// *****************************************************
// Interface Page
// *****************************************************

// Add Interface
procedure TMainDlg.AddInterfaceClick(Sender: TObject);
begin
  USBIOInterface.AddInterface(
    StrToInt(MainDlg.InterfaceIndex.text),
    StrToInt(MainDlg.AlternateSetting.text),
    StrToInt(MainDlg.MaxTransferSize.text),
    status
    );
  ShowError(status);
end;

// delete interfaces
procedure TMainDlg.DeleteInterfaceClick(Sender: TObject);
begin
  USBIOInterface.DeleteInterfaces;
end;

// set configuration
procedure TMainDlg.SetConfClick(Sender: TObject);
begin
  USBIOInterface.SetConfiguration(strtoint(MainDlg.ConfIndex.text),status);
  ShowError(status);
end;

// unconfigure the device
procedure TMainDlg.UnConfigureClick(Sender: TObject);
begin
  USBIOInterface.UnconfigureDevice(Status);
  ShowError(status);
end;

// bind an endpoint
procedure TMainDlg.BindClick(Sender: TObject);
begin
  USBIOInterface.Bind(strtoint(MainDlg.PipeNumber.text),status);
  ShowError(status);
end;

// unbind an endpoint
procedure TMainDlg.UnBindClick(Sender: TObject);
begin
  USBIOInterface.Unbind(status);
  ShowError(status);
end;


// *****************************************************
// Read Page
// *****************************************************

// start reading
procedure TMainDlg.StartReadingClick(Sender: TObject);
begin
  if  not(IsWriteStarted) and not(IsReadStarted) then
  begin
    IsIsoFlag := MainDlg.IsIso.Checked;
    IsReadStarted := true;
		if not(IsIsoFlag and ((strtoint(MainDlg.BufferSize.text)*
      strtoint(MainDlg.NoOfBuffer.text))>1024)) then
    begin
      // reset the pipe, work-around for a bug in the UHC driver
      USBIOInterface.ResetPipe(status);
      MainDlg.ShowError(status);
      if (status = USBIO_ERR_SUCCESS) then
      begin
        USBIOInterface.StartReading(
          strtoint(MainDlg.BufferSize.text),
          strtoint(MainDlg.NoOfBuffer.text),
          strtoint(MainDlg.MaxErrorCount.text),
          status
        );
				ShowError(status);
				if (status = USBIO_ERR_SUCCESS) then Timer1.Enabled := true;
				if IsIsoFlag then
        begin
          // create bufferarray for isochronous read
          readbuffer:=SafeArrayCreateVector(VT_UI1,0,strtoint(BufferSize.text)*USBIOInterface.EndpointFifoSize);
          infobuffer:=SafeArrayCreateVector(VT_UI4,0,strtoint(BufferSize.text));
        end
        else
          // create bufferarray for bulk read
          readbuffer:=SafeArrayCreateVector(VT_UI1,0,strtoint(BufferSize.text));
        if (status = USBIO_ERR_SUCCESS) and (FileOpenFlag = false) and (WriteToFile.Checked) then
        begin
          // open/create file
          AssignFile(OutputFile, MainDlg.FileName.Text);
          Rewrite(OutputFile,1);
          FileOpenFlag := true;
          IsReadStarted := true;
				end;
			end;
		end
    else MessageDlg('Frames per buffer * Number of buffers <= 1024"', mtError, [mbOk], 0);
  end;
end;  // StartReadingClick


// stop reading
procedure StopReading;
begin
  if  not(IsWriteStarted) and IsReadStarted then
  begin
    IsReadStarted := false;
    USBIOInterface.StopReading;
    SafeArrayDestroy(readbuffer);
    if IsIsoFlag then SafeArrayDestroy(infobuffer);
    if FileOpenFlag then
    begin
      // close File
      CloseFile(OutputFile);
      FileOpenFlag := false;
    end;
  end;
end; // StopReading


// stop reading
procedure TMainDlg.StopReadClick(Sender: TObject);
begin
  Timer1.Enabled:=false;
  StopReading;
end;


// call-back function: called when a read buffer has been completed
procedure TMainDlg.ReadComplete(Sender: TObject; var Obj: OleVariant);
type
  PByte = ^Byte;
var
  nob: integer;
  datapointer: pointer;
begin
  if IsReadStarted then
  begin
    // read data
    if IsIsoFlag then USBIOInterface.ReadIsoData(readbuffer,nob,infobuffer,status)
    else USBIOInterface.ReadData(readbuffer,nob,status);
    MainDlg.ShowError(status);
    helpstatus:=status;
    if status = USBIO_ERR_SUCCESS then
    begin
      if FileOpenFlag then
      begin
        // write data buffer to file
        SafeArrayAccessData(readbuffer,datapointer);
        Blockwrite(OutputFile,datapointer^,nob);
        SafeArrayUnAccessData(readbuffer);
			end;
		end
    else
      if helpstatus <> USBIO_ERR_POWER_DOWN then StopReading;
        // This special error code is returned if the
        // PC enters the suspend state and a read operation
        // is still in progress. We can ignore this error code.
        // The reading operation is continued after the PC wakes up.
     

      // isochronous transfer errors are ignored here
      // check infobuffer if needed

    // move the progress bar
    if not DisableProgressBar.Checked then
    begin
      if (ProgressBar1.Max<=ProgressBar1.Position) then ProgressBar1.Position:=0;
      ProgressBar1.StepBy(1);
    end;
  end;
end;  // TMainDlg.ReadComplete


procedure TMainDlg.SaveFileClick(Sender: TObject);
begin
  if MainDlg.SaveDialog1.Execute then
    MainDlg.FileName.Text:=MainDlg.SaveDialog1.FileName;
end;


// *****************************************************
// Write Page
// *****************************************************

// stop writing
procedure StopWriting;
begin
  if  IsWriteStarted and not(IsReadStarted) then
  begin
    IsWriteStarted := false;
    USBIOInterface.StopWriting;
    SafeArrayDestroy(writebuffer);
    if IsIsoFlag then SafeArrayDestroy(infobuffer);
    if WriteSt then SafeArrayDestroy(StatusArray);
  end;
end; // StopWriting


// write data to the COM object
procedure SendBuffer();
begin
  if IsWriteStarted then
  begin
    repeat
      if IsIsoFlag then
        // write iso data buffer
        USBIOInterface.WriteIsoData(writebuffer,infobuffer,UserId,status)
      else
        // write bulk data buffer
        USBIOInterface.WriteData(writebuffer,UserId,status);
    until status <> USBIO_ERR_SUCCESS;
    helpstatus:=status;
    If (helpstatus <> USBIO_ERR_NO_BUFFER) and (helpstatus <> USBIO_ERR_SUCCESS) Then
    begin
      MainDlg.ShowError(status);
      StopWriting;
    end;
  end;
end;


// start a write operation
procedure TMainDlg.StartWriteClick(Sender: TObject);
var
  a: char;
  i,ws: integer;
  fifosize: integer;
  value: byte;
begin
  if not(IsWriteStarted) and not(IsReadStarted) then
  begin
    IsWriteStarted := true;
    IsIsoFlag := MainDlg.writeisocheck.Checked;
    // query fifo size 
    fifosize := USBIOInterface.EndpointFifoSize;
    // prepare buffers for write
    if IsIsoFlag then
    begin
      // iso transfer
      writebuffer:=SafeArrayCreateVector(VT_UI1,0,(strtoint(writebuffersize.text)* fifosize));
      infobuffer:=SafeArrayCreateVector(VT_UI4,0,(strtoint(writebuffersize.text)));
      if MainDlg.WriteStatusCheck.checked then
        // create status array
        StatusArray := SafeArrayCreateVector(VT_UI4,0,(strtoint(writebuffersize.text)));
      // setup info buffer
      for i:=0 to strtoint(writebuffersize.text) do
      begin
        // put an element into the SafeArray
        SafeArrayPutElement(infobuffer,i,fifosize);
      end;
    end
    else
      // bulk or interrupt transfer
      writebuffer:=SafeArrayCreateVector(VT_UI1,0,strtoint(writebuffersize.text));

    // fill the buffer from file or with constant values
    if FromFileCheck.Checked then
    begin
      if not(FileExists(MainDlg.writefile.Text)) then
        FileExists(MainDlg.writefile.Text)
      else
      // read one buffer from file
      begin
        AssignFile(InputFile, MainDlg.writefile.Text);
        Reset(InputFile);
        for i:=0 to (strtoint(writebuffersize.text)) do
        begin
          read(InputFile,a);
          value:=ord(a);
          SafeArrayPutElement(writebuffer,i,value);
        end;
      end;
    end
    else
      // fill buffer with constant values
      for i:=0 to (strtoint(writebuffersize.text)) do
      begin
        value:=strtoint(FilledWith.Text);
        // put an element into the SafeArray
        SafeArrayPutElement(writebuffer,i,value);
      end;
    // setup
    if MainDlg.WriteStatusCheck.checked then
    begin
      ws:=1;
      WriteSt:=true;
    end
    else
    begin
      ws:=0;
      WriteSt:=false;
    end;
    // reset the pipe
    USBIOInterface.ResetPipe(status);
    MainDlg.ShowError(status);
    if status = USBIO_ERR_SUCCESS then
    begin
      USBIOInterface.StartWriting(
        strtoint(writebuffersize.text),
        strtoint(writenumberofbuffers.text),
        strtoint(writeerrorcount.text),
        ws,
        status
        );
      MainDlg.ShowError(status);
      // send the prepared data until an error is returned
      if status = USBIO_ERR_SUCCESS then
        SendBuffer();
    end;
  end;
end; // TMainDlg.StartWriteClick



procedure TMainDlg.StopWriteClick(Sender: TObject);
begin
  StopWriting;
end;


// called when a free buffer is available
procedure TMainDlg.WriteComplete(Sender: TObject; var Obj: OleVariant);
begin
  // send further buffers
  SendBuffer();
end;


// called when a write operation is finished
// and the final status of the write operation is available
procedure TMainDlg.WriteStatus(Sender: TObject; var Obj: OleVariant);
var
  ByteCount,i,st: integer;
begin
  if IsWriteStarted then
  begin
    if IsIsoFlag then
    begin
      USBIOInterface.GetIsoWriteStatus(UserId,StatusArray,ByteCount,status);
      for i:=0 to bytecount do
      begin
        // get an element from the Safearray
        SafeArrayGetElement(StatusArray,i,st);
        MainDlg.ShowError(st);
      end;
    end
    else
      USBIOInterface.GetWriteStatus(UserId,status);
    MainDlg.ShowError(status);
    if status <> USBIO_ERR_SUCCESS then
      StopWriting;
  end;
end; // TMainDlg.WriteStatus

procedure TMainDlg.OpenFileClick(Sender: TObject);
begin
  if MainDlg.OpenDialog1.Execute then
    MainDlg.writefile.Text:=MainDlg.OpenDialog1.FileName;
end;


// *****************************************************
// Feature Page
// *****************************************************

// set feature
procedure TMainDlg.setfeatureClick(Sender: TObject);
begin
  USBIOInterface.SetFeature(
    featurecombo.itemindex,
    strtoint(featurefield.text),
    strtoint(featureindexfield.text),
    status
    );
  ShowError(status);
end;

// clear feature
procedure TMainDlg.clearfeatureClick(Sender: TObject);
begin
  USBIOInterface.ClearFeature(
    featurecombo.itemindex,
    strtoint(featurefield.text),
    strtoint(featureindexfield.text),
    status
    );
  ShowError(status);
end;


// *****************************************************
// Class or Vendor request page
// *****************************************************

procedure TMainDlg.VendorSendButtonClick(Sender: TObject);
var
  buffer: PSAFEARRAY;
  typ,recipient,request,value,index,bufsize,pos,i: integer;
  BufferString: string;
  pb: byte;
begin
  // out request
  if VendorDirectionCombo.ItemIndex = 0 then
  begin
    // set variables
    typ := VendorTypeCombo.ItemIndex +1;
    recipient := VendorRecipientCombo.ItemIndex +1;
    request := strtoint(VendorRequest.Text);
    value := strtoint(VendorValueText.Text);
    index := strtoint(VendorIndexText.Text);
    bufsize := strtoint(VendorBufferSizeText.Text);
    // create SafeArray
    buffer := SafeArrayCreateVector(VT_UI1,0,bufsize);
    // get buffer string
    BufferString := VendorBufferText.Text;
    // fill the SafeArray
    for i:=0 to bufsize-1 do
    begin
      pos:=AnsiPos('$',BufferString);
      if pos = 0 then pb:=0
        else pb:=strtoint(Copy(BufferString,pos,3));
      // put element into SafeArray
      SafeArrayPutElement(Buffer,i,pb);
      Delete(BufferString,1,pos);
    end;
    // out request
    USBIOInterface.ClassOrVendorOutRequest(buffer,0,typ,recipient,0,request,value,index,status);
    ShowError(status);
    // destroy SafeArray
    SafeArrayDestroy(buffer);
  end;
  // in request
  if VendorDirectionCombo.ItemIndex = 1 then
  begin
    // set variables
    typ := VendorTypeCombo.ItemIndex +1;
    recipient := VendorRecipientCombo.ItemIndex +1;
    request := strtoint(VendorRequest.Text);
    value := strtoint(VendorValueText.Text);
    index := strtoint(VendorIndexText.Text);
    bufsize := strtoint(VendorBufferSizeText.Text);
    // create SafeArray
    buffer := SafeArrayCreateVector(VT_UI1,0,bufsize);
    // in request
    USBIOInterface.ClassOrVendorInRequest(buffer,bufsize,0,typ,recipient,0,request,value,index,status);
    ShowError(status);
    // if success
    If Status=0 then
    begin
      BufferString:='';
      // print to output window
      OutPut.OutputMemo.Lines.Append('Vendor in request');
      for i:=0 to bufsize-1 do
      begin
        // get one element from the SafeArray
        SafeArrayGetElement(buffer,i,pb);
        BufferString:=BufferString + inttohex(pb,2) + ' ';
        if (i mod 8) = 7 then
        begin
          OutPut.OutputMemo.Lines.Append(BufferString);
          BufferString:='';
        end;
      end;
      OutPut.OutputMemo.Lines.Append(BufferString);
    end;
    // destroy SafeArray
    SafeArrayDestroy(buffer);
  end;
end;


// *****************************************************
// Other Page
// *****************************************************

// cycle port simulates a device disconnect/connect
procedure TMainDlg.CyclePortClick(Sender: TObject);
begin
  USBIOInterface.CyclePort(status);
  ShowError(status);
end;

// reset device
procedure TMainDlg.ResetDeviceClick(Sender: TObject);
begin
  USBIOInterface.ResetDevice(status);
  ShowError(status);
end;

// get the current USB frame number from host controller
procedure TMainDlg.getframenoClick(Sender: TObject);
var
  FrmNumber : integer;
begin
  USBIOInterface.GetCurrentFrameNumber(FrmNumber,status);
  ShowError(status);
  if status = 0 then frmno.Text:=inttohex(FrmNumber,8);
end;

// get device path, the path can be used to open the native
// interface of the USBIO device driver directly
procedure TMainDlg.GetDevicePathNameClick(Sender: TObject);
begin
  GetDevicePathNameField.Text:=USBIOInterface.DevicePathName;
end;

// get powerstate
procedure TMainDlg.getpowerstateClick(Sender: TObject);
var
  PowerState: integer;
begin
  USBIOInterface.GetDevicePowerState(PowerState, status);
  ShowError(status);
  if status =0  then getpowerstatefield.Text:=inttostr(PowerState);
end;

// set powerstate
procedure TMainDlg.setpowerstateClick(Sender: TObject);
begin
  USBIOInterface.SetDevicePowerState(powerstatecombo.ItemIndex,status);
  ShowError(status);
end;

// get status
procedure TMainDlg.getstatusClick(Sender: TObject);
var
  DeviceStatus: integer;
begin
  USBIOInterface.GetStatus(
    DeviceStatus,
    statuscombo.itemindex,
    strtoint(statusindex.text),
    status
    );
  ShowError(status);
  if status = 0 then statusout.text:=inttostr(DeviceStatus);
end;



// *****************************************************
// Internal helper functions
// *****************************************************

// show an error
procedure TMainDlg.ShowError(Status: integer);
var
  error: string;
begin
  if Status <> USBIO_ERR_SUCCESS then
    // get error text for the code
    error := USBIOInterface.ErrorText(Status);
    MainDlg.ErrorText.Text := error;
end;

// clear error message
procedure TMainDlg.ClearErrorClick(Sender: TObject);
begin
  MainDlg.ErrorText.Text := '';
end;


// init the USBIOCOM object here
procedure InitUSBIOCom;
begin
  // create the USBIOCOM object instance
  USBIOInterface := TUSBIOInterface3.Create(MainDlg);
  // set the call-back handlers, they have to be methods of a class
  USBIOInterface.OnReadComplete := MainDlg.ReadComplete;
  USBIOInterface.OnWriteComplete := MainDlg.WriteComplete;
  USBIOInterface.OnWriteStatusAvailable := MainDlg.WriteStatus;
  USBIOInterface.OnPnPAddNotification := MainDlg.PnPAddNotification;
  USBIOInterface.OnPnPRemoveNotification := MainDlg.PnPRemoveNotification;
  try
    USBIOInterface.Connect;
  except
    MessageDlg('USBIOCOM not registered! Use "regsvr32 usbiocom.dll"', mtError, [mbOk], 0);
  end;
end;


// this procedure is called during startup
procedure TMainDlg.FormCreate(Sender: TObject);
begin
  // init COM object
  InitUSBIOCom;
  // init combo boxes
  featurecombo.ItemIndex:=0;
  powerstatecombo.ItemIndex:=0;
  statuscombo.ItemIndex:=0;
  VendorDirectionCombo.ItemIndex:=0;
  VendorRecipientCombo.ItemIndex:=0;
  VendorTypeCombo.ItemIndex:=0;
end;


// this procedure is called during shutdown
procedure TMainDlg.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  // we try to stop read and write operations 
  // these functions will do nothing if no read/write operation is in progress
  StopWriting();
  StopReading();
end;

// timer procedure
procedure TMainDlg.Timer1Timer(Sender: TObject);
begin
	QueryStatisticsClick(Sender);
	Timer1.Enabled:=true;
end;

procedure TMainDlg.QueryStatisticsClick(Sender: TObject);
var
        ActualAveragingInterval,AverageRate,BytesTransferredL,BytesTransferredH,RequestsSucceeded,RequestsFailed: integer;
begin
				USBIOInterface.QueryPipeStatistics(ActualAveragingInterval,AverageRate,BytesTransferredL,BytesTransferredH,RequestsSucceeded,RequestsFailed,0,status);
        ShowError(status);
        if status = USBIO_ERR_SUCCESS then
        begin
                ActualAveragingIntervalEdit.Text := inttostr(ActualAveragingInterval);
                AverageRateEdit.Text := inttostr(AverageRate);
                BytesTransferredEdit.Text := inttostr((BytesTransferredH shl 32)+BytesTransferredL);
                RequestsSucceededEdit.Text := inttostr(RequestsSucceeded);
                RequestsFailedEdit.Text := inttostr(RequestsFailed);
        end;

end;

procedure TMainDlg.GetBandwidthInfoClick(Sender: TObject);
var
        TotalBandwidth,ConsumedBandwidth: integer;
begin
        USBIOInterface.GetBandwidthInfo(TotalBandwidth,ConsumedBandwidth,status);
        ShowError(status);
        if status = USBIO_ERR_SUCCESS then
        begin
                TotalBandwidthEdit.Text := inttostr(TotalBandwidth);
                ConsumedBandwidthEdit.Text := inttostr(ConsumedBandwidth);
        end;
end;

procedure TMainDlg.SetupPipeStatisticsClick(Sender: TObject);
begin
				USBIOInterface.SetupPipeStatistics(strtoint(AveragingIntervalEdit.Text),status);
        ShowError(status);
end;

procedure TMainDlg.GetDeviceInfoClick(Sender: TObject);
begin
				if USBIOInterface.IsOperatingAtHighSpeed <> 0 then
					GetDeviceInfoCheck.Checked :=  true
				else
					GetDeviceInfoCheck.Checked :=  false;
end;

procedure TMainDlg.ResetStatisticsClick(Sender: TObject);
var
        ActualAveragingInterval,AverageRate,BytesTransferredL,BytesTransferredH,RequestsSucceeded,RequestsFailed: integer;
begin
				USBIOInterface.QueryPipeStatistics(ActualAveragingInterval,
																						AverageRate,
																						BytesTransferredL,
																						BytesTransferredH,
																						RequestsSucceeded,
																						RequestsFailed,
																						USBIOCOM_QPS_FLAG_RESET_ALL_COUNTERS,
																						status);
				ShowError(status);
				if status = USBIO_ERR_SUCCESS then
				begin
                ActualAveragingIntervalEdit.Text := inttostr(ActualAveragingInterval);
								AverageRateEdit.Text := '0';
								BytesTransferredEdit.Text := '0';
								RequestsSucceededEdit.Text := '0';
                RequestsFailedEdit.Text := '0';
        end;
end;

procedure TMainDlg.AcquireButtonClick(Sender: TObject);
begin
        USBIOInterface.AcquireDevice(status);
        ShowError(status);
end;

procedure TMainDlg.ReleaseButtonClick(Sender: TObject);
begin
        USBIOInterface.ReleaseDevice(status);
        ShowError(status);
end;

end.

