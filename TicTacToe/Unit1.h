//---------------------------------------------------------------------------


#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------


#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Colors.hpp>
//---------------------------------------------------------------------------


class TForm1 : public TForm
{
__published:
	TButton *b1;
	TButton *b2;
	TButton *b3;
	TButton *b4;
	TButton *b5;
	TButton *b6;
	TButton *b7;
	TButton *b8;
	TButton *b9;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *cPlay;
	TLabel *Label3;
	TButton *Replay;
	TButton *Exit;
    void __fastcall FormCreate(TObject *Sender);
	void __fastcall ButtonClick(TObject *Sender);
	void __fastcall ReplayClick(TObject *Sender);
	void __fastcall ExitClick(TObject *Sender);
private:	// User declarations
	bool TForm1::Winn();
	bool TForm1::IsDraw();
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------


class TColorB : public TButton {
public:
	__fastcall TColorB(TComponent* Owner);
    __property Font;
};
//---------------------------------------------------------------------------


extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------


#endif
