program DelphiApp;

uses
  Forms,
  USBIO in 'USBIO.pas' {MainDlg},
  USBIOoutput in 'USBIOoutput.pas' {output},
  USBIOCOMLib_TLB in 'USBIOCOMLib_TLB.pas';

{$R *.RES}

begin
	Application.Initialize;
	Application.Title := 'USBIOCOM Delphi Demo Application';
  Application.CreateForm(TMainDlg, MainDlg);
  Application.CreateForm(Toutput, output);
  Application.Run;
end. 
