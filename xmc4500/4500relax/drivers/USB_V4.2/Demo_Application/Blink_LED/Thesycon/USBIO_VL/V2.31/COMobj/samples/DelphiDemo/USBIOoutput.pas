unit USBIOoutput;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

type
  Toutput = class(TForm)
    outputmemo: TMemo;
    procedure FormResize(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  output: Toutput;

implementation

{$R *.DFM}

procedure Toutput.FormResize(Sender: TObject);
begin
	outputmemo.Height:= output.Height-27;
  outputmemo.Width:= output.Width-8;
end;

end.
