// Hemavathi.cpp : Defines the initialization routines for the DLL.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////AUTHOR : Sudheer HS	sudheer316@gmail.com////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////DATE : 6-apr-2006							////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////COMPANY : Maruthi Software Developers.,HASSAN - 573201 ,KARANATAKA, INDIA     ////////////////////////////////////////////////////////////////
////////////////Description : This processes key inputs and emulates kannada characters for the key pressed		////////////////////////////////////////////////////////////////
////////////////			 this reads the key pressed and then produces the required characters for kannada languagge		////////////////////////////////////////////////////////////////
////////////////Compiler Used : Microsoft Visual C++ 6.0////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	////////////////////////////////////////////////////////////////	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////  This has been done as a project for Hampi University ,Hampi,INDIA ////////////////////////////////////////////////////////////////
////////////////  this is part of the free software Kuvempu Kannada Thantramsha,launched by Hampi University ////////////////////////////////////////////////////////////////
////////////////  This code as is with out any kind of warranty ,Using or modifing the code or the library without ////////////////////////////////////////////////////////////////
////////////////  the written permission by the university is prohibited,Any such illegal activities is punishable offence as per ////////////////////////////////////////////////////////////////
////////////////  the copy rights ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
*
*Modified Added New chars pha ph with dots
*Date 11/03/2009 1:44 AM
*Author Sudheer HS 
*/
#include "stdafx.h"
#include "Hemavathi.h"
#include "..\headers\keyfuncts.h"
//#include "..\headers\flags.h"
#include <vector>
#include <windows.h>


#define SINGLE 1
#define SLASH 2
#define EE 3
#define CAPITALS 4
#define KGUNITHA 5
#define NUMERALS
#define F_OTTU	7



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma data_seg(".SHARDAT")
static HWND ghWndMain = 0 ;
static HHOOK ghKeyHook = NULL ;
#pragma data_seg()

static HHOOK ghCallWndProcRetHook = NULL;

HINSTANCE ghInstance = 0;
HOOKPROC glpfnHookProc = 0;


char cConsonnants[10] = {'a','A','e','E','i','I','u','U','o','O'};
char cVot[25] = {'Q','W','R','T','Y','P','S','D','G','H','J','K','L','Z','C','X','C','V','B','N','M','<','_','^','+'};

struct val_tab
{
	char key;								//----holds the character 
	int k_val[6];							//---holds the glyph codes of the corresponding above character eg;  
											//---for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}single_key[94] = {				//'`' , {33,-1},
								'!' , {33,-1},
   								'a' , {67,-1},
								'A' , {68,-1},
								'e' , {69,-1},
								'E' , {70,-1},
								'u' , {71,-1},
								'U' , {72,-1},
								'4' , {73,196,-1},
								'$' , {89,-1},
								'i' , {74,-1},
								'I' , {75,-1},
								'>' , {76,-1},
								'1' , {39,-1},
								'o' , {77,-1},
								'O' , {78,-1},
								'0' , {65,-1 },
								':' , {66,-1},
								'k' , {80,192,-1},
								'[' , {82,-1},
								'g' , {85,192,-1},
								'9' , {87,192,-1},
								'c' , {90,192,-1},
								'j' , {100,-1},
								'=' , {103,192,104,196,-1},
								't' , {108,-1},
								'5' , {111,192,-1},
								'%' , {215,-1},
								'd' , {113,192,-1},
								'z' , {116,-1},
								'w' , {118,192,-1},
								'3' , {120,192,-1},
								'#' , {220,-1},
								',' , {122,192,-1},
								'n' , {163,192,-1},
								'p' , {165,192,-1},
								'b' , {167,-1,-1},
								'm' , {170,192,196,-1},
								'y' , {65,105,192,196,-1},
								'r' , {103,192,-1},
								'l' , {174,-1},
								'v' , {170,192,-1},
								'q' , {177,192,-1},
								'\'', {181,192,-1},
								's' , {184,192,-1},
								'h' , {186,192,-1},
								'x' , {188,192,-1},
								'K' , {204,-1},
								'{' , {205,-1},
								'G' , {206,-1},
								'C' , {209,-1},
								'J' , {211,-1},
								'T' , {214,-1},
								'D' , {216,-1},
								'Z' , {218,-1},
								'W' , {219,-1},
							//	'?' , {221,-1},
								'N' , {223,-1},
								'P' , {224,-1},
								'B' , {226,-1},
								'M' , {228,-1},
								'Y' , {229,-1},
								'R' , {230,-1},
								'L' , {232,-1},
								'V' , {233,-1},
								'"' , {235,-1},
								'S' , {236,-1},
								'H' , {237,-1},
								'X' , {238,-1},
								';' , {195,-1},
								'Q' , {240,-1},
								'f' , {8,193,-1},
								']' , {-1,-1},
								'F' , {200,-1},
								'2' , {-1,-1},
								'6' , {107,-1},   //--------- --------//
								'^' , {213,-1},           //---------- -------//
								'7' , {170,192,197,-1},
								'8' , {165,192,197,-1},
								'-' , {98,192,-1},
								'_' , {210,-1},
								'(' , {207,-1},
								'<' , {221,-1},
								'?' , {63,-1},
								'/' , {47,-1},
							//	',' , {44,-1},
								'.' , {46,-1},
								'~' , {126,-1},
								'`' , {145,-1},
								'|' , {124,-1},
								'\\', {44,-1},
								'+' , {80,192,235,-1},
								'2' , {100,213,-1},
								')' , {132,-1},
								'@' , {242,-1},
								' ',  {32,-1},
								'&',  {234,-1}
								
};

//-----singlekey_doubleglyph-----//
//---Structure of vowels ----//
struct double_ON_SLASH
{
	char key;								//----holds the character 
	int k_val[7];							//---holds the glyph codes of the corresponding above character eg; 
								   //---- for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}double_key_slash[12] = {		

						'c' , {8,8,98,192,-1},
						'd' ,  {8,115,192,-1},
						',' , {8,115,192,-1},
						'p' , {8,115,192,-1},
						'b' , {8,168,115,192,-1},
						'<' , {8,222,-1},
						'8' , {8,8,115,192,197,-1},
						'D' , {8,217,-1},
						'B' , {8,227,-1},
						'P' , {8,225,-1},
						'<' , {8,222,-1},
						'C' , {8,210,-1}
						};
//-----singlekey_doubleglyph-----//
//---Structure of vowels ----//

struct double_ON_EE
{
	char key;								//----holds the character 
	int k_val[8];							//---holds the glyph codes of the corresponding above character eg; 
												//---- for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}double_key_ee[32] = {		'k', {8,8,81,-1},
							'[', {8,84,-1},
							'g', {8,8,86,-1},
							'9', {8,8,88,-1},
							'c', {8,8,97,-1},
							'j', {8,102,-1},
							'=', {8,8,8,8,106,104,196,-1},
							't', {8,110,-1},
							'5', {8,8,112,-1},
							'd', {8,8,114,-1},
							'z', {194,-1},
							'w', {8,8,119,-1},
							'3', {8,8,121,-1},
							',', {8,8,162,-1},
							'n', {8,8,164,-1},
							'p', {8,8,166,-1},
							'b', {8,169,-1},
							'm', {8,8,8,171,196,-1},
							'y', {8,8,8,8,172,196,-1},
							'r', {8,8,106,-1},
							'l', {8,176,-1},
							'v', {8,8,171,-1},
							'q', {8,8,178,-1},
							'\'',{8,8,182,-1},
							's', {8,8,185,-1},
							'h', {8,8,187,-1} ,
							'x', {8,8,189,-1} ,
							'-', {8,8,99,-1} ,
							'+', {8,8,8,81,235,-1},
							'2', {8,8,102,213,-1},
	                        '6', {194,-1},
							'$', {194,-1}

};


struct double_ON_F
{
	char key;								//----holds the character 
	int k_val[8];							//---holds the glyph codes of the corresponding above character eg; 
												//---- for a 67 (first 3 values)for vowel and 192 for vowels (last value)
}double_key_F[22] = {
								'k' , {204,-1},
								'[' , {205,-1},
								'g' , {206,-1},
								'c' , {209,-1},
								'j' , {211,-1},
								't' , {214,-1},
								'd' , {216,-1},
								'z' , {218,-1},
								'w' , {219,-1},
								//'?' , {221,-1},
								'n' , {223,-1},
								'p' , {224,-1},
								'b' , {226,-1},
								'm' , {228,-1},
								'y' , {229,-1},
								'r' , {230,-1},
								'l' , {232,-1},
								'v' , {233,-1},
								'\'', {235,-1},
								's' , {236,-1},
								'h' , {237,-1},
								'x' , {238,-1},
	};
				
struct num_tab
{
	char key;								//----holds the character 
	int k_val[7];							//---holds the glyph codes of the corresponding above character eg; 
										   //---- for a 67 (first 3 values)for vowel and 192 for singlekey_doubleglyph (last value)
}numerals[43] = {				
				                '1', {49,-1,33,-1} ,            //---Kannada Character ka---//
				                '2', {50,-1,64,-1} ,			//---Kannada Character ga---//	
								'3', {51,-1,35,-1} ,			//---Kannada Character cha---//
								'4', {52,-1,36,-1},
								'5', {53,-1,37,-1} ,			//---Kannada Character dha---//
								'6', {54,-1,94,-1} ,			//---Kannada Character tha---//
								'7', {55,-1,38,-1} ,			//---Kannada Character da---//
								'8', {56,-1,42,-1} ,			//---Kannada Character na---//
								'9', {57,-1,40,-1} ,			//---Kannada Character pa---//
								'0', {48,-1,41,-1},
								'!', {33,-1,33,-1} ,            //---Kannada Character ka---//
				                '@', {64,-1} ,			//---Kannada Character ga---//	
								'#', {35,-1} ,			//---Kannada Character cha---//
								'$', {36,-1},
								'%', {37,-1} ,			//---Kannada Character dha---//
								'^', {94,-1} ,			//---Kannada Character tha---//
								'&', {38,-1} ,			//---Kannada Character da---//
								'*', {42,-1} ,			//---Kannada Character na---//
								'(', {40,-1} ,			//---Kannada Character pa---//
								')', {41,-1},
								'+', {43,-1},
								'=', {61,-1},
								'-', {45,-1},
								'_', {95,-1},
								'{', {123,-1},
								'}', {125,-1},
								'[', {91,-1},
								']', {93,-1},
								'|', {124,-1},
								'\\',{92,-1},
								':', {58,-1},
								';', {59,-1},
								'<', {60,-1},
								'>', {62,-1},
								'?', {63,-1},
								'/', {47,-1},
								',', {44,-1},
								'.', {46,-1},
								'~', {126,-1},
								'`', {96,-1},
								'e', {70,-1},
								'\'', {145,-1},
								'"' , {147,-1}
				};  

BEGIN_MESSAGE_MAP(CHemavathiApp, CWinApp)
	//{{AFX_MSG_MAP(CHemavathiApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHemavathiApp construction




//------------This-function-is-repeatedly-called-this-executes-when-a-key-is-pressed-on-the-keyboard---/
LRESULT EXPORTED_DLL_FUNCTION SetKeyBoardHemavathi(int nCode,WPARAM wParam,LPARAM lParam)
{

if(nCode<0)												//---Do not process further if a system key is pressed---//
{ 
	return CallNextHookEx (ghKeyHook,nCode,wParam,lParam);   //---Call the next hook procedure in the hook chain---//
}
if(nCode==HC_NOREMOVE)
{
		return CallNextHookEx (ghKeyHook,nCode,wParam,lParam); 
}

			char ch;
			BYTE ks[256];                                //---a byte for getting the keyboard ststus---//
		    WORD w;										 //---a word for holding the character value of the key---// 
														 //pressed used by the ToAsccii where the value is set into this---//	
			UINT scan=0; 					
		    ::GetKeyboardState(ks);         
			::ToAscii(wParam,scan,ks,&w,0);
            ch = char(w);

LRESULT retval;

	if( isspace(ch) || wParam == VK_BACK)
	{
		clearAllFlags();
		kFlag.c_bit = FALSE;
		kFlag.found = FALSE;
		kFlag.s_bit = TRUE;
		kFlag.previous_0 = NULL;
	}

	if((GetKeyState(VK_SCROLL ) & 0x0001))
	{
		if(isNumPad(wParam))
		{
			return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
		}
		if((isalpha(ch) || ispunct(ch) || isdigit(ch)))											 //---If key is pressed and is not a control key---//
		{
			if((lParam & 0x80000000) == 0x00000000)   //---If key is pressed and is not a control key---//
			{
				findKannadaCharacters(ch);									//---Find the glyph code--//
				pushBackspaces();
			}
			else // key released
			{
			    pushKeys();
					if( ch == '.' ||  ch == '?' || ch == '!' || ch == '\\' || ch == '`' || ch == '|' || ch == '~') 
					{
						kFlag.c_bit = FALSE;
					}
				if(isWinNTServer())
					{
						return CallNextHookEx(ghKeyHook,nCode,wParam,lParam);
					}
				else
					{
						return TRUE;
					}
			}
		}
		else
		{
			return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
			  //---Call the next hook procedure in the hook chain---//
		}


		if( (isalnum(ch) || ispunct(ch)) &&!(GetKeyState(VK_MENU) & 0x80))    //---If the key pressed is a alpha key and when not
		{                                                  //---- Alt is down posts only the the promted message--//
				if( ch == '.' ||  ch == '?' || ch == '!' || ch == '\\' || ch == '`' || ch == '|' || ch == '~') 
				{
					kFlag.c_bit = FALSE;
				}
			 return TRUE;
		}
		else
		{
			return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
			  //---Call the next hook procedure in the hook chain---//
		}

	}
	else 
		return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
}

/*	if((GetKeyState(VK_SCROLL ) & 0x0001))
	{
		if(isNumPad(wParam))
		{
			return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
		}
		if((isalpha(ch) || ispunct(ch) || isdigit(ch)))											 //---If key is pressed and is not a control key---//
		{
			if((lParam & 0x80000000) == 0x00000000)   //---If key is pressed and is not a control key---//
			{
				findKannadaCharacters(ch);									//---Find the glyph code--//
				pushBackspaces();
			}
			else // key released
			{
			    pushKeys();
				retval = TRUE;
			}
		}
		else
		{
			retval = CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
			  //---Call the next hook procedure in the hook chain---//
		}


		if( (isalnum(ch) || ispunct(ch)) &&!(GetKeyState(VK_MENU) & 0x80))    //---If the key pressed is a alpha key and when not
		{                                                  //---- Alt is down posts only the the promted message--//
			 retval = TRUE;
		}
		else
		{
			retval = CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
			  //---Call the next hook procedure in the hook chain---//
		}

	}
	else 
		return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
	if( ch == '.' ||  ch == '?' || ch == '!' || ch == '\\' || ch == '`' || ch == '|' || ch == '~') 
	{
//		vClear_All_Flags();
		kFlag.c_bit = FALSE;
//		kFlag.found = FALSE;
//		kFlag.s_bit = FALSE;
//		kFlag.previous_0 = NULL;

	}
		return retval;
}

*/

LRESULT callWndRetProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	if(nCode<0)
	{
		return CallNextHookEx(ghCallWndProcRetHook,nCode,wParam,lParam);
	}

	CWPRETSTRUCT *p=(CWPRETSTRUCT*)lParam;
	if(p->message==WM_KEYDOWN)
	{
		if(p->wParam==VK_BACK)
		{
			pushKeys();
		}
	}
		LRESULT ret=CallNextHookEx(ghCallWndProcRetHook,nCode,wParam,lParam);

	return ret;
}

BOOL EXPORTED_DLL_FUNCTION InstallKeyboardHookHemavathiExpEXP(HWND hWnd)
{
	InstallKeyboardHookHemavathi();
		return TRUE;
}

//---------------Insatalls-the-Hook---//---This-is -called-by-the-.exe---//
BOOL __stdcall InstallKeyboardHookHemavathi() 
{
	//isWinNTServer();
	BOOL bSuccess = FALSE;
    if( !ghKeyHook) 
	{
		glpfnHookProc = (HOOKPROC) SetKeyBoardHemavathi;
		bSuccess = (NULL != ( ghKeyHook = ::SetWindowsHookEx (WH_KEYBOARD, glpfnHookProc,ghInstance, NULL)));
		bSuccess = TRUE;
		ghCallWndProcRetHook = ::SetWindowsHookEx (WH_CALLWNDPROCRET, (HOOKPROC)callWndRetProc,ghInstance, NULL);
		
	}
	return bSuccess;
}


//---------------Un-Insatalls-the-Hook---//---This-is -called-by-the-.exe---//
BOOL __stdcall DeInstallKeyboardHookHemavathi()
{
	if(ghKeyHook) 
	{
		if( TRUE == (0 != ::UnhookWindowsHookEx (ghKeyHook)))
		{
			ghKeyHook = NULL;
		}
	}
	if(ghCallWndProcRetHook) 
	{
		if( TRUE == (0 != ::UnhookWindowsHookEx (ghCallWndProcRetHook)))
		{
			ghCallWndProcRetHook = NULL;
		}
		
	}
   return (NULL == ghKeyHook);
}


CHemavathiApp::CHemavathiApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHemavathiApp object

CHemavathiApp theApp;



BOOL CHemavathiApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ghInstance = AfxGetInstanceHandle();
	return TRUE;

}


int CHemavathiApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	DeInstallKeyboardHookHemavathi();

	return CWinApp::ExitInstance();
}

BOOL CHemavathiApp::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
		return CWinApp::PreTranslateMessage(pMsg);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Finds The Character in The Tables in Found Calls     /////////////////////////////
/////////////////////////////  The Display Functions With Position (i),and The Starting Position  /////////////////////////////
/////////////////////////////  Of The Of The Message To Be Posted The Argument 					  /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void findKannadaCharacters(char ch) 
{       
   
	int no_bs = 0;//-------number of back spae--------//
	BOOL bHandledKeystroke = FALSE;
    kFlag.found = 0;
	no_bs = kFlag.o_count;
	kFlag.o_bit = FALSE;

	for(int i=0;i<24;i++)
	{
		if(ch == cVot[i])
		{   
			kFlag.o_bit = TRUE;
			if(kFlag.ei_bit == TRUE)
			{
				kFlag.ei_bit = FALSE;  // for second vottakshara
				displaySingleCharacter(246);
				if(ch == 'R')
				{
					displaySingleCharacter(231);
					return ;
				}

			}
			if(kFlag.f_bit == TRUE)
			{
				kFlag.f_bit = FALSE;
				kFlag.ei_bit = TRUE; // for second vottakshara
				
				if(ch == 'R')
				{
					displaySingleCharacter(231);
					return ;
				}
				displaySingleCharacter(246);
			}
			else
			{
				kFlag.f_bit = TRUE;
			}
		}
	}
	if(kFlag.o_bit == FALSE)
	{
		kFlag.f_bit = FALSE;
		kFlag.ei_bit = FALSE;
	}
	if(kFlag.s_bit == TRUE)
	{
		kFlag.s_bit = FALSE;
	}

if(kFlag.found == FALSE)
{

	if(ch == 'I')
	{
		for(int i = 0;i<24;i++)
		{
			if(cVot[i] == kFlag.previous_0)
			{
			displayDoubleCharacter(246,202);
				return ;
			}
		}
	}
	if(ch == 'F')
	{
		for(int i = 0;i<25;i++)
		{
			if(cVot[i] == kFlag.previous_0)
			{
			displaySingleCharacter(248);
				return ;
			}
		}
	}
   for(int i = 0;i<24;i++)
		{
			if(cVot[i] == ch && (kFlag.previous_0 == '+'))
			{
				displaySingleCharacter(246);///removed as its addind extra spaces for jha
			}
		}
   /**
   *Added for pha ph with dots
   *p/} p/}f p/}e p/}e; p/}u p/}U p/}F p/}i p/}i; p/}I p/}o p/}o; p/}O p/}0 P/}:
   *Sudheer HS 11/3/2009 1.44 AM
   */
   if(kFlag.previous_0 == '}' && kFlag.previous_1 == '/' && kFlag.previous_2 == 'p')
   {
	   switch(ch)
	   {
			case 'f':
				kFlag.found = TRUE;
				sendBackSpace(1);
				displaySingleCharacter(193);
				break;
			case 'e':
				kFlag.found = TRUE;
				sendBackSpace(4);
				displayTripleCharacter(166,252,251);
				break;
			case 'u':
				kFlag.found = TRUE;
			//	sendBackSpace(1);
				displaySingleCharacter(197);
			break;
			case 'U':
				kFlag.found = TRUE;
			//	sendBackSpace(1);
				displaySingleCharacter(199);
				break;
			case 'F':
				kFlag.found = TRUE;
			//	sendBackSpace(1);
				displaySingleCharacter(200);
				break;
			case 'i':
				kFlag.found = TRUE;
				sendBackSpace(1);
				displaySingleCharacter(201);
				break;
			case 'I':
				kFlag.found = TRUE;
				sendBackSpace(1);
				displayDoubleCharacter(201,202);
				break;
			case 'o':
				kFlag.found = TRUE;
				sendBackSpace(1);
				displayDoubleCharacter(201,199);
				break;
			case 'O':
				kFlag.found = TRUE;
				sendBackSpace(1);
				displaySingleCharacter(203);
				break;
		//	case ':':
			//	break;
	   }
   }
   else
   if(ch == 'R' && kFlag.previous_0 == 'u' && kFlag.previous_1 == 'v')  ////Addded for vru 11172009
	{
		//sendBackSpace(2);
		displaySingleCharacter(231);
		kFlag.found = TRUE;

	}
   else
   if(ch == 'e' && kFlag.previous_0 == '}' && kFlag.previous_1 == 'j')
	{
		sendBackSpace(2);
		displayDoubleCharacter(102,251);
		kFlag.found = TRUE;

	}
	else
	if(ch == 'O' && kFlag.previous_0 == 'o')
	{
		sendBackSpace(1);
		displaySingleCharacter(79);
		kFlag.found = TRUE;
	}
   if((ch == 'f' && kFlag.previous_0 == '7') )
   {
	   kFlag.found = TRUE;
	   sendBackSpace(1);
	   displaySingleCharacter(199);
   }
   else
   if(ch == 'f' && kFlag.previous_0 == 'e' && kFlag.previous_1 == 'm')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(2);
	   displayDoubleCharacter(171,198);
   }
   else
   if( (ch == 'f' && kFlag.previous_0 == '8') || ch == 'f' && kFlag.previous_0 == '/' && kFlag.previous_1 == '8')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(1);
	   displaySingleCharacter(199);
   }
   else 
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'd')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(3);
	   displayDoubleCharacter(114,115);
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == ',')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(3);
	   displayDoubleCharacter(162,115);
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(3);
	   displayDoubleCharacter(166,252);
	   kFlag.lastglyph = TRUE;
   }
   else
   if(kFlag.lastglyph == TRUE)
   {
	   kFlag.found = TRUE;
	   //sendBackSpace(1);
	   displaySingleCharacter(251);
	   kFlag.lastglyph = FALSE;
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'b')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(3);
	   displayDoubleCharacter(169,252);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'C')/// for 200 ie votersuli
   {
	   kFlag.found = TRUE;
	 //  sendBackSpace(1);
	   displaySingleCharacter(200);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'D')
   {
	   kFlag.found = TRUE;
	   //sendBackSpace(1);
	   displaySingleCharacter(200);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == ',')
   {
	   kFlag.found = TRUE;
	  // sendBackSpace(1);
	   displaySingleCharacter(200);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'P')
   {
	   kFlag.found = TRUE;
	  // sendBackSpace(1);
	   displaySingleCharacter(200);
   }
   else
   if(ch == 'F' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'B')
   {
	   kFlag.found = TRUE;
	  // sendBackSpace(1);
	   displaySingleCharacter(200);
   }
   else
   if(ch == 'e' && kFlag.previous_0 == '/' && kFlag.previous_1 == 'c')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(2);
	   displaySingleCharacter(99);
   }
   else
 if(ch == '/' && kFlag.previous_0 == 'j')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(1);
	   displaySingleCharacter(212);
   }
   else
   if(ch == '}' && kFlag.previous_0 == 'o')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(1);
	   displaySingleCharacter(208);
   }
   else
  /* if(ch == '/' && kFlag.previous_0 == 'q')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(2);
	   displaySingleCharacter(234);
   }
   else*/
if(ch == '}' && kFlag.previous_0 == '/' &&kFlag.previous_1 == 'p')
   {
	   kFlag.found = TRUE;
	   sendBackSpace(1);
	   displayDoubleCharacter(243,192);
   }
   else
if(ch == '}' && kFlag.previous_0 == 'j' )
   {
	   kFlag.found = TRUE;
	   //sendBackSpace(1);
	   displaySingleCharacter(243);
   }
   else
   if(ch == '/')
   {
	   for(int i=0;i<12;i++)
	   {
			if(kFlag.previous_0 == double_key_slash[i].key)
			{
				kFlag.found = TRUE;
				displayCharacters(i,SLASH,0);
			}
	   }

   }
   else
   if(ch == 'e' || ch == ';' )
   {
	   if(kFlag.s_bit == TRUE)
	   {
		   displaySingleCharacter(70);
		   kFlag.found = TRUE;
		   kFlag.s_bit = FALSE;
		   kFlag.c_bit = FALSE;
	   }
	   else
		   if(ch == ';')
		   {
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
				{
                    kFlag.found = TRUE;
					sendBackSpace(3);
					displayTripleCharacter(166,252,195);
				}
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'c')
				{
                    kFlag.found = TRUE;
					sendBackSpace(3);
					displayDoubleCharacter(99,195);
				}
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == ',')
				{
                    kFlag.found = TRUE;
					sendBackSpace(3);
					displayTripleCharacter(162,252,195);
				}
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'd')
				{
                    kFlag.found = TRUE;
					sendBackSpace(3);
					displayTripleCharacter(114,252,195);
				}
			 if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'b')
				{
                    kFlag.found = TRUE;
					sendBackSpace(3);
					displayTripleCharacter(169,252,195);
				}
			 kFlag.c_bit = FALSE;//----------dont use further next if vowel display vowel
		   }
	   if(kFlag.found == FALSE)
	   for(int i=0;i<32;i++)
	   {
			if(kFlag.previous_0 == double_key_ee[i].key)
			{
				kFlag.found = TRUE;
				displayCharacters(i,EE,0);
				if(ch == ';')
		        displaySingleCharacter(195); //only when gudisu is to bo displayed 
				kFlag.c_bit = FALSE;		
			}
	   }
   }
}

if(kFlag.found == FALSE)
{
	for(int i=0;i<94;i++)
	{
		if(ch == single_key[i].key)
		{
			kFlag.last_consonant = FALSE;
			kFlag.found = TRUE;

			if( (ch == 'f' || 
				 ch == 'u' ||
				 ch == 'U' || 
				 ch == 'I' || 
				 ch == 'i' || 
				 ch == 'o' || 
				 ch == 'O' || 
				 ch  == ']' 
				) &&   kFlag.c_bit == TRUE)
			{
					kFlag.c_bit = FALSE;
					displayGunitakshara(ch);
					
			}
			else
			displayCharacters(i,SINGLE,0);


			for (int j = 0;j<10;j++)
			{
				if(ch == cConsonnants[j])
				{
					kFlag.u_bit = TRUE;
				}
			}

			if(kFlag.u_bit == FALSE )
			{
				kFlag.c_bit = TRUE;
			}
			else
			{
			    kFlag.u_bit = FALSE;
			}
		}
	}
}

if( isalpha(ch) || ispunct(ch) || isdigit(ch) )
copyLastChar0(ch);

kFlag.s_bit = FALSE;
return ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Finds The Character in The Tables in Found Calls     /////////////////////////////
/////////////////////////////  The Display Functions With Position (i),and The Starting Position  /////////////////////////////
/////////////////////////////  Of The Of The Message To Be Posted The Argument 					  /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void displayCharacters(int nval,int indicator,int j)   //indictor value is 0 for anuswara ,1 for consonants , 2 for vowels
{    
			int k = j ;   // --------index for glyph codes---// 
			


		while(kFlag.n_back>=1)
			{
				addKey(VK_BACK);
				kFlag.n_back--;
			}
		   if(indicator==SINGLE)	
			{
				while(single_key[nval].k_val[k]!=-1)
				{
						addKey(single_key[nval].k_val[k]);
						k++;
				}
			}
		    else
		    if(indicator == SLASH)
			{
				while(double_key_slash[nval].k_val[k]!=-1)
				{
					   
						addKey(double_key_slash[nval].k_val[k]);
						k++;
				}
			
			}
			else
		    if(indicator == EE)
			{
				while(double_key_ee[nval].k_val[k]!=-1)
				{
					  
						addKey(double_key_ee[nval].k_val[k]);
						k++;
				}
			
			}
			else
		    if(indicator == F_OTTU)
			{
				while(double_key_F[nval].k_val[k]!=-1)
				{
					  
						addKey(double_key_F[nval].k_val[k]);
						k++;
				}
			
			}
			
			kFlag.n_back = -1;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Set The Glypha For Kha,ja,.... ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch ===>character , gval ===> pevious_0 GlypH value//
void setGlyphs(char ch,int gval)
{

	if(kFlag.previous_0 == '}')
	{
		sendBackSpace(2);
		displayDoubleCharacter(gval+1,243);
	}
	switch(kFlag.previous_0)
	{
	case '[' :
	case 'j' :	
	case 't' :
	case 'b' :
	case 'l' :
	case 'z' :
			 sendBackSpace(1);
			 displaySingleCharacter(gval+1);
	break;		 
	default :
	break; 
	
	}
	kFlag.n_back = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Set The Glypha For ma,JHa,ya.... ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch ===>character , gval ===> pevious_0 GlypH value//
void setGlyphsForJMY(char ch,int i)
{
		switch(kFlag.previous_0)
		{
		case 'y' :				//-----------For The Characters ya,ma-----------//
		case 'm' :
			switch(ch)
			{
				case 'f' :
				sendBackSpace(1);
				displayDoubleCharacter(105,193);
				break;
				case 'i' :
					sendBackSpace(2);
					displayDoubleCharacter(201,196);
				break;
				case 'I' :
					sendBackSpace(2);
					displayTripleCharacter(201,196,202);
				break;
				case 'o' :
					sendBackSpace(2);
					displayDoubleCharacter(201,198);
				break ;
				case  'O' :
					sendBackSpace(1);
					displayDoubleCharacter(105,203);
				break;

				case  ']' :
					sendBackSpace(1);
					displayDoubleCharacter(105,239);
				break;

			}//---------End of Switch(ch)--for the characters ma,ya ------//
		 break; //---------------End of the case y , m instance 1
		 case '=' :				//-----------For The Characters JHA-----------//
			switch(ch)
			{
				case 'f' :
				    sendBackSpace(1);
					displayDoubleCharacter(105,193);
				break;
				case 'i' :
					sendBackSpace(3);
					displayTripleCharacter(201,104,196);
				break;
				case 'I' :
					sendBackSpace(3);
					displayTripleCharacter(202,104,196);
				break;
				case 'o' :
					sendBackSpace(3);
					displayTripleCharacter(201,104,198);
				break ;
				case  'O' :
					sendBackSpace(1);
					displayDoubleCharacter(105,203);
				break;
				case  ']' :
					sendBackSpace(1);
					displayDoubleCharacter(105,239);
				break;
			}//-------------------End of Switch(ch)----for JHA ---------------//
		break ;
		}//---------End of Switch(pevious_0)--------//
		kFlag.slash_bit = 0;
kFlag.n_back = -1;
}//-------End OF The function setGlyphsForJMY----------//

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Set The Glypha For ma,JHa,ya.... ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch ===>character , gval ===> pevious_0 GlypH value//
void setGlyphsForKXHA_GYNA(char ch,int i)
{
		switch(kFlag.previous_0)
		{
		case '+':				//-----------For The Characters ya,ma-----------//
			switch(ch)
			{
				case 'f' :
					sendBackSpace(2);
					displayDoubleCharacter(193,235);
				break;

				case 'u' :
					sendBackSpace(2);
					//displayDoubleCharacter(196,235);
					displayTripleCharacter(192,196,235); ///corrected 11/17/2009 kshuoo
				break;

				case 'U' :
					sendBackSpace(2);
					//displayDoubleCharacter(198,235);
					displayTripleCharacter(192,198,235);  ///corrected 11/17/2009 kshuoo
				break;

				case 'e' :
					sendBackSpace(2);
					displayDoubleCharacter(81,235);
				break;

				case 'i' :
					sendBackSpace(2);
					displayDoubleCharacter(201,235);
				break;
				case 'I' :
					sendBackSpace(2);
					displayFourCharacter(201,235,246,202);
				break;

				case 'o' :
					sendBackSpace(2);
					displayTripleCharacter(201,198,235);
				break ;

				case  'O' :
					sendBackSpace(2);
					displayDoubleCharacter(203,235);
				break;
				case  ']' :
					//sendBackSpace(1);
					displaySingleCharacter(239);
				break;
			}//---------End of Switch(ch)--for the characters ma,ya ------//
		 break; //---------------End of the case y , m instance 1Á
		 case '2' :				//-----------For The Characters JHA-----------//
			switch(ch)
			{
				case 'f' :
				    sendBackSpace(2);
					displayTripleCharacter(101,193,213);
				break;

				case 'u' :
					sendBackSpace(2);
					displayDoubleCharacter(196,213);
				break;

				case 'U' :
					sendBackSpace(2);
					displayDoubleCharacter(198,213);
				break;
				case 'e' :
					sendBackSpace(2);
					displayDoubleCharacter(102,213);
				break;

				case 'i' :
					sendBackSpace(2);
					displayTripleCharacter(101,201,213);
				break;
				case 'I' :
					sendBackSpace(3);
					displayTripleCharacter(101,202,213);
				break;

				case 'o' :
					sendBackSpace(2);
					//displayFourCharacter(101,201,198,213);
					displayFourCharacter(201,235,246,202);
				break ;

				case  'O' :
					sendBackSpace(2);
					displayTripleCharacter(101,203,213);
				break;
				case  ']' :
					//sendBackSpace(1);
					displaySingleCharacter(239);
				break;

			}//-------------------End of Switch(ch)----for JHA ---------------//
		break ;
		}//---------End of Switch(pevious_0)--------//
		kFlag.slash_bit = 0;
kFlag.n_back = -1;
}//-------End OF The function SetGlyphs_for_kxha_Gyna----------//


void setGlyphsNyaInya(char ch,int i)
{
			switch(ch)
			{
				case 'f' :
		//			sendBackSpace(2);
					displaySingleCharacter(193);
				break;

				case 'u' :
					//sendBackSpace(2);
					displaySingleCharacter(196);
				break;

				case 'U' :
					displaySingleCharacter(198);
				break;

				case 'e' :
					displaySingleCharacter(194);
				break;

				case 'i' :
					displaySingleCharacter(201);
				break;
				case 'I' :
					displayDoubleCharacter(201,202);
				break;

				case 'o' :
					displayDoubleCharacter(201,198);
				break ;

				case  'O' :
					displaySingleCharacter(203);
				break;
			}//---------End of Switch(ch)--for the characters ma,ya ------//
}// end of setGlyphsNyaInya

void setGlyphsBaCa(char ch,int i)
{
		switch(kFlag.previous_1)
		{
		case 'c':				//-----------For The Characters ya,ma-----------//
			switch(ch)
			{
				case 'f' :
					sendBackSpace(1);
					displaySingleCharacter(193);
				break;

				case 'u' :
				//	sendBackSpace(2);
					displaySingleCharacter(196);
				break;

				case 'U' :
					//sendBackSpace(2);
					displaySingleCharacter(198);
				break;

				case 'e' :
					sendBackSpace(2);
					displaySingleCharacter(99);
				break;

				case 'i' :
					sendBackSpace(1);
					displaySingleCharacter(201);
				break;
				case 'I' :
					sendBackSpace(1);
					displayDoubleCharacter(201,202);
				break;

				case 'o' :
					sendBackSpace(1);
					displayDoubleCharacter(201,198);
				break ;

				case  'O' :
					sendBackSpace(1);
					displaySingleCharacter(203);
				break;
			}//---------End of Switch(ch)--for the characters ma,ya ------//
		 break; //---------------End of the case y , m instance 1Á
	}//---------End of Switch(pevious_0)--------//
		kFlag.slash_bit = 0;
kFlag.n_back = -1;

}
void copyLastChar0(char ch)
{   
	kFlag.previous_2 = kFlag.previous_1;
	kFlag.previous_1 = kFlag.previous_0;
	kFlag.previous_0 = ch;
}



void displayGunitakshara(char ch)
{

	kFlag.c_bit = FALSE; //no gunitakshara for next character
	switch(ch)
	{
	case 'u':
		switch(kFlag.previous_0)
		{
		case '+':
		case '2':
			setGlyphsForKXHA_GYNA(ch,1);
		return ;
		default :
			if(kFlag.previous_0 == 'p' || kFlag.previous_0 == 'v' || kFlag.previous_0 == 'h')
				displaySingleCharacter(197);
			else
			if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
				displaySingleCharacter(197);
			else
		displaySingleCharacter(196);
		}
	break;

	case 'U':
		switch(kFlag.previous_0)
		{
		case '+':
		case '2':
			setGlyphsForKXHA_GYNA(ch,1);
		return ;

		default:
			if(kFlag.previous_0 == 'p' || kFlag.previous_0 == 'v' || kFlag.previous_0 == 'h')
				displaySingleCharacter(199);
			else
			if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
				displaySingleCharacter(199);
			else
		displaySingleCharacter(198);
		}
	break;

	case 'f' :
		switch(kFlag.previous_0)
		{
		case '}' :
			setGlyphs(ch,100);
			break;
		case '[' :
			setGlyphs(ch,82);
			break;
		case 'j' :	
			setGlyphs(ch,100);
			break;
		case 't' :
			setGlyphs(ch,108);
			break;
		case 'b' :
			setGlyphs(ch,167);
		break;
		case 'l' :
			setGlyphs(ch,174);
		break;

		case '$' :
		case '6' :
			setGlyphsNyaInya(ch,1);
		return;

		case 'z' :
		 	setGlyphs(ch,116);
		break;
	
		case '+':
		case '2':
			setGlyphsForKXHA_GYNA(ch,1);
		return;

//		case '/' :
//			::MessageBox(NULL,"sdc","csdc",MB_OK);
//				setGlyphsBaCa(ch,1);
//		return ;

		case '=' :
		case 'y' :
		case 'm' :
			setGlyphsForJMY(ch,1);
		return;
	
	 default :
			sendBackSpace(1);
		}
		displaySingleCharacter(193);
	break;
  
   case 'o':
   switch(kFlag.previous_0)
	{
	   		case '}' :
			setGlyphs(ch,100);
			break;
	case '[' :
			setGlyphs(ch,82);
			break;
		case 'j' :	
			setGlyphs(ch,100);
			break;
		case 't' :
			setGlyphs(ch,108);
			break;
		case 'b' :
			setGlyphs(ch,167);
		break;
		case 'l' :
			setGlyphs(ch,174);
			break;
		case '$' :
		case '6' :
			setGlyphsNyaInya(ch,1);
		return;

			setGlyphs(ch,174);
		break;

			
		case 'z' :
			setGlyphs(ch,116);
		break;
		case '+':
		case '2':
		setGlyphsForKXHA_GYNA(ch,1);
		return;
		case 'y' :
		case 'm' :
		case '=' :
			setGlyphsForJMY(ch,1);
			return ;
		
//		case '/' :
//		setGlyphsBaCa(ch,1);
//		return ;

         
		default :
			if(kFlag.previous_0 == 'p' || kFlag.previous_0 == 'v' || kFlag.previous_0 == 'h')
			{
				sendBackSpace(1);
				displayDoubleCharacter(201,199);
				return ;
			}
			else
			if(kFlag.previous_0 == '/' && kFlag.previous_1 == 'p')
			{
				sendBackSpace(1);
				displayDoubleCharacter(201,199);
				return ;
			}
			else
			{	
			 sendBackSpace(1);
			 }
		}
		displayDoubleCharacter(201,198);
	break;

	case 'O':
		switch(kFlag.previous_0)
		{
					case '}' :
			setGlyphs(ch,100);
			break;
		case '[' :
			setGlyphs(ch,82);
			break;
		case 'j' :	
			setGlyphs(ch,100);
			break;
		case 't' :
			setGlyphs(ch,108);
			break;
		case 'b' :
			setGlyphs(ch,167);
		break;
		case 'l' :
			setGlyphs(ch,174);
			break;
		case '$' :
		case '6' :
			setGlyphsNyaInya(ch,1);
		return;

				
		case 'z' :
			setGlyphs(ch,116);
		break;
		
		case '+':
		case '2':
		setGlyphsForKXHA_GYNA(ch,1);
		return;
		
		case 'y' :
		case 'm' :
		case '=' :
			setGlyphsForJMY(ch,1);
		return ;
		
//		case '/' :
//		setGlyphsBaCa(ch,1);
//		return ;

		
		default :
			sendBackSpace(1);
		}
		displaySingleCharacter(203);
	break;

	case 'I':
		switch(kFlag.previous_0)
		{
					case '}' :
			setGlyphs(ch,100);
			break;
		case '[' :
			setGlyphs(ch,82);
			break;
		case 'j' :	
			setGlyphs(ch,100);
			break;
		case 't' :
			setGlyphs(ch,108);
			break;
		case 'b' :
			setGlyphs(ch,167);
		break;
		case 'l' :
			setGlyphs(ch,174);
			break;
		case '$' :
		case '6' :
			setGlyphsNyaInya(ch,1);
		return;
		
		case 'z' :
			setGlyphs(ch,116);
		break;

		case '+':
		case '2':
		setGlyphsForKXHA_GYNA(ch,1);
		return;
		
		case 'y' :
		case 'm' :
		case '=' :
			setGlyphsForJMY(ch,1);
		return ;
		 break;

//		case '/' :
//		setGlyphsBaCa(ch,1);
//		return ;

		
		default :
			sendBackSpace(1);
		}
		displayDoubleCharacter(201,202);
		break;
		
		// to display eaatva//
	case 'i':
	switch(kFlag.previous_0)
		{
				case '}' :
			setGlyphs(ch,100);
			break;
		case '[' :
			setGlyphs(ch,82);
			break;
		case 'j' :	
			setGlyphs(ch,100);
			break;
		case 't' :
			setGlyphs(ch,108);
			break;
		case 'b' :
			setGlyphs(ch,167);
		break;
		case 'l' :
			setGlyphs(ch,174);
		break;
		case '$' :
		case '6' :
			setGlyphsNyaInya(ch,1);
		return;
		
		case 'z' :
			setGlyphs(ch,116);
		break;

		case '+':
		case '2':
		setGlyphsForKXHA_GYNA(ch,1);
		return;
		

		case 'y' :
		case 'm' :
		case '=' :
			setGlyphsForJMY(ch,1);
			return ;

//		case '/' :
//		setGlyphsBaCa(ch,1);
//		return ;
		
		
		default :
			sendBackSpace(1);
		}
		displaySingleCharacter(201);
		break;

	case ']': // ardakshara 
		switch(kFlag.previous_0)
		{
					case '}' :
			setGlyphs(ch,100);
			break;
	case '[' :
			setGlyphs(ch,82);
			break;
		case 'j' :	
			setGlyphs(ch,100);
			break;
		case 't' :
			setGlyphs(ch,108);
			break;
		case 'b' :
			setGlyphs(ch,167);
		break;
		case 'l' :
			setGlyphs(ch,174);
			break;
		case '$' :
		case '6' :
			setGlyphsNyaInya(ch,1);
		return;
		
		case 'z' :
			setGlyphs(ch,116);
		break;

		case '+':
		case '2':
		setGlyphsForKXHA_GYNA(ch,1);
		return;
		

		case 'y' :
		case 'm' :
		case '=' :
			setGlyphsForJMY(ch,1);
			return ;

//		case '/' :
//		setGlyphsBaCa(ch,1);
//		return ;

		
		default :
			sendBackSpace(1);
		}
		displaySingleCharacter(239);
		break;
	}
}


void clearQueue()
{

}

void clearAllFlags()
{
				              kFlag.q_bit  = 0;
                              kFlag.f_bit = 0;
                              kFlag.s_bit = 0;
                              kFlag.p_bit = 0;
                              kFlag.g_bit = 0;
                              kFlag.c_bit = 0;
                              kFlag.o_bit = 0;
                              kFlag.x_bit = 0;
                              kFlag.so_bit = 0;
                              kFlag.b_bit = 0;
                              kFlag.u_bit  = 0;
                              kFlag.ei_bit = 0;
                              kFlag.ipressed = 0;
                              kFlag.space_bit = 0;
                              kFlag.j_bit = 0;
                              kFlag.first_o = 0;
//                            kFlag.derg_bit = 1;
//                            kFlag.derg_count ;
                              kFlag.spec_kgun = 0;
                              kFlag.spec_kgun_val;
                              kFlag.slash_bit = 0;
							  kFlag.f_pressed_Once = 0;
	                          clearQueue();
}