program simprj;

uses
  Forms,
  simple in 'simple.pas' {Form1},
  USBIOCOMLib_TLB in 'USBIOCOMLib_TLB.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'USBIO Simple Demo';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
