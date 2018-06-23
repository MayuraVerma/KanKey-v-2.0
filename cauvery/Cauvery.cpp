//Cauvery.cpp  Implementation File
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

#include "stdafx.h"
#include "Cauvery.h"
#include "..\headers\keyfuncts.h"
#include <windows.h>
#include <vector>

//#define ANUSWARA 0
#define SINGLE 1
#define EQUALS 2
#define PLUS 3
#define SQ_BRACKET 4
#define F 5
#define NUMERALS 6

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

HINSTANCE ghInstance=0;
HOOKPROC glpfnHookProc=0;



struct val_tab_SINGLE
{
	char key;								//----holds the character 
	int k_val[5];							//---holds the glyph codes of the corresponding above character eg;  
											//---for a 67 (first 3 values)for vowel and 192 for singlekey_doubleglyph (last value)
}singlekey_singleglyph[90] = { 
							     'a',  { 67  , -1  }  ,		
								 'A',  { 68  , -1  }  ,		
								 'e',  { 69  , -1  }  ,		
								 'u',  { 196  , -1  }  ,
								 'U',  {71,-1},
								 'i',  { 74  , -1  }  ,		
								 '.',  { 162  , -1  }  ,
								 '>',  {76,-1},
								 'o',  { 77  , -1  }  ,		
								 'm',  { 65  , -1  }  ,		
								 ':',  { 66  , -1  }  ,		
								 'k',  { 80  , 192  , -1  }  ,		
								 'H',  { 82  , -1  }  ,		
								 'g',  { 85  , 192  , -1  }  ,		
								 'E',  { 100 , 213  , -1  }  ,		
								 'c',  { 90  , 192  , -1  }  ,		
								 'j',  { 100 , -1  }  ,		
								 't',  { 108 , -1  }  ,		
								 'd',  { 113  , 192  , -1  }  ,		
								 'z',  { 116 , -1  }  ,		
								 'w',  { 118 , 192  , -1  }  ,		
								 ',',  { 122 , 192  , -1  }  ,		
								 'n',  { 163 , 192  , -1  }  ,		
								 'p',  { 165 , 192  , -1  }  ,		
								 'b',  { 167 , -1  }  ,		
								 'r',  { 103 , 192  , -1  }  ,		
								 'l',  { 174 , -1  }  ,		
								 'v',  { 170 , 192  , -1  }  ,		
								 'q',  { 177 , 192  , -1  }  ,		
								 's',  { 184 , 192  , -1  }  ,		
								 'h',  { 186 , 192  , -1  }  ,		
								 'x',  { 188 , 192  , -1  }  ,
								 'y',  { 105 , 192  , -1  }  ,
								 '8',  { 81  , -1  }  ,		
								 '5',  { 86  , -1  }  ,		
								 '-',  { 97  , -1  }  ,		
								 '3',  { 114 , -1  }  ,		
								 '2',  { 119 , -1  }  ,		
								 '.',  { 162 , -1  }  ,		
								 '/',  { 164 , -1  }  ,		
								 '[',  { 166 , -1  }  ,		
								 '4',  { 106 , -1  }  ,		
								 '9',  { 171 , -1  }  ,		
								 '1',  { 178 , -1  }  ,		
								 '\\', { 185 , -1  }  ,		
								 '6',  { 187 , -1  }  ,
								 '7',  { 170,192,197,-1},
								 '0',  { 189 , -1  }  ,		
								 'K',  { 204 , -1  }  ,		
								 'G',  { 206 , -1  }  ,		
								 'C',  { 209 , -1  }  ,		
								 'J',  { 211 , -1  }  ,		
								 'T',  { 214 , -1  }  ,		
								 '_',  { 215 , -1  }  ,		
								 'D',  { 216 , -1  }  ,		
								 'Z',  { 218 , -1  }  ,		
								 'W',  { 219 , -1  }  ,		
								 '<',  { 221 , -1  }  ,		
								 'N',  { 223 , -1  }  ,		
								 'P',  { 224 , -1  }  ,		
								 'B',  { 226 , -1  }  ,		
								 'M',  { 228 , -1  }  ,		
								 'Y',  { 229 , -1  }  ,		
								 'R',  { 230 , -1  }  ,		
								 'L',  { 232 , -1  }  ,		
								 'V',  { 233 , -1  }  ,		
								 'Q',  { 240 , -1  }  ,		
								 '"',  { 235 , -1  }  ,		
								 'S',  { 236 , -1  }  ,		
								 'X',  { 238 , -1  }  ,
								 'I',  { 200 , -1  }  ,
								 '=',  { 252 , -1  } ,
								 '!',  { 0x31,-1,33,-1} ,       //---Kannada Character ka---//
								 '@',  { 0x32,-1 } ,			//---Kannada Character ga---//	
								 '#',  { 0x33,-1 } ,			//---Kannada Character cha---//
								 '$',  { 0x34,-1 },
								 '%',  { 0x35,-1 } ,			//---Kannada Character dha---//
								 '^',  { 0x36,-1 } ,			//---Kannada Character tha---//
								 '&',  { 0x37,-1 } ,			//---Kannada Character da---//
								 '*',  { 0x38,-1 } ,			//---Kannada Character na---//
								 '(',  { 0x39,-1 } ,			//---Kannada Character pa---//
								 ')',  { 0x30,-1 },
								 ';',  { 195 , -1 }	,
								 '?',  { 63  , -1 }	,
								 '+',  { 46  , -1 } ,
								 'F',  { 95  , -1 },
								 '~',  { 126 , -1 },
								 '`',  { '|'  , -1 },
								 '|',  { 41  , -1 },
								 '{',  { 40  , -1 },
								
};




struct val_tab_ON_EQUALS
{
	char key;								//----holds the character 
	int k_val[5];							//---holds the glyph codes of the corresponding above character eg;  
											//---for a 67 (first 3 values)for vowel and 192 for singlekey_doubleglyph (last value)
}doublekey_equals[15] = { 
							'9',  { 8	, 99  , -1  }  ,		
							'3',  { 115 , -1  } ,		
							'd',  { 8	, 115	, 192	,	-1  }  ,		
							',',  { 8	, 115	, 192	,	-1  }  ,		
							'p',  { 8	, 252	, 192	,	-1  }  ,		
							'b',  { 8	, 168	, 115	,	192  , -1 }  ,		
							'[',  { 115 , -1  } ,		
							'V',  { 8	, 210	, -1  }  ,		
							'D',  { 8	, 217	, -1  }  ,		
							'<',  { 8	, 222	, -1  }  ,		
							'P',  { 8	, 225	, -1  }  ,		
							'B',  { 8	, 227	, -1  }  ,	
							'K',  { 8	, 205	, -1  }  ,
							'.',  { 252 , -1  } ,
							'v',  { 8   ,  8    , 98 , 192 , -1}
						
};




struct val_tab_ON_PLUS
{
	char key;								//----holds the character 
	int k_val[5];							//---holds the glyph codes of the corresponding above character eg;  
											//---for a 67 (first 3 values)for vowel and 192 for singlekey_doubleglyph (last value)
}doublekey_plus[4] = { 
						'4',  { 8  ,112 , -1  }  ,		
						'.',  { 8  ,162 , 115 , -1  }  ,		
						'r',  { 8  ,8   ,111  , 192 , -1  }  ,		
};


struct val_tab_ON_SQ_BRACKET
{
	char key;								//----holds the character 
	int k_val[5];							//---holds the glyph codes of the corresponding above character eg;  
											//---for a 67 (first 3 values)for vowel and 192 for singlekey_doubleglyph (last value)
}doublekey_sq_bracket[5] = { 
					 'j',  { 8   , 102  , -1  }  ,		
					 't',  { 8   , 110  , -1  }  ,		
					 'z',  { 194 , -1		  }  ,	
					 'H',  { 8   ,  166 , -1  }  ,
};

/*			
struct num_tab
{
	char key;								//----holds the character 
	int k_val[7];							//---holds the glyph codes of the corresponding above character eg; 
										   //---- for a 67 (first 3 values)for vowel and 192 for singlekey_doubleglyph (last value)
}numerals[43] = {				
				                '1', {49  , -1	, 33 , -1} ,            //---Kannada Character ka---//
				                '2', {50  , -1	, 64 , -1} ,			//---Kannada Character ga---//	
								'3', {51  , -1	, 35 , -1} ,			//---Kannada Character cha---//
								'4', {52  , -1	, 36 , -1} ,
								'5', {53  , -1	, 37 , -1} ,			//---Kannada Character dha---//
								'6', {54  , -1	, 94 , -1} ,			//---Kannada Character tha---//
								'7', {55  , -1	, 38 , -1} ,			//---Kannada Character da---//
								'8', {56  , -1	, 42 , -1} ,			//---Kannada Character na---//
								'9', {57  , -1	, 40 , -1} ,			//---Kannada Character pa---//
								'0', {48  , -1	, 41 , -1} ,
								'!', {33  , -1	, 33 , -1} ,            //---Kannada Character ka---//
				                '@', {64  , -1} ,			//---Kannada Character ga---//	
								'#', {35  , -1} ,			//---Kannada Character cha---//
								'$', {36  , -1}	,
								'%', {37  , -1} ,			//---Kannada Character dha---//
								'^', {94  , -1} ,			//---Kannada Character tha---//
								'&', {38  , -1} ,			//---Kannada Character da---//
								'*', {42  , -1} ,			//---Kannada Character na---//
								'(', {40  , -1} ,			//---Kannada Character pa---//
								')', {41  , -1}	,
								'+', {43  , -1}	,
								'=', {61  , -1}	,	
								'-', {45  , -1}	,
								'_', {95  , -1}	,
								'{', {123 , -1}	,
								'}', {125 , -1}	,
								'[', {91  , -1}	,
								']', {93  , -1}	,
								'|', {124 , -1}	,
								'\\',{92  , -1}	,
								':', {58  , -1}	,
								';', {59  , -1}	,
								'<', {60  , -1}	,
								'>', {62  , -1}	,
								'?', {63  , -1}	,
								'/', {47  , -1}	,
								',', {44  , -1}	,
								'.', {46  , -1}	,
								'~', {126 , -1}	,
								'`', {96  , -1} 


				};  */


BEGIN_MESSAGE_MAP(CCauveryApp, CWinApp)
	//{{AFX_MSG_MAP(CCauveryApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCauveryApp construction




//------------This-function-is-repeatedly-called-this-executes-when-a-key-is-pressed-on-the-keyboard---/
LRESULT EXPORTED_DLL_FUNCTION SetKeyBoardCauvery(int nCode,WPARAM wParam,LPARAM lParam)
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


	if(wParam == VK_SPACE || wParam==(WPARAM)VK_BACK)
	{
		kFlag.c_bit = FALSE;
		kFlag.found = FALSE;
		kFlag.s_bit = TRUE;
		kFlag.previous_0 = NULL;
		kFlag.previous_1 = NULL;
		kFlag.previous_2 = NULL;
		kFlag.previous_3 = NULL;
	}


	if((GetKeyState(VK_SCROLL ) & 0x0001))
	{
		if(isNumPad(wParam))
		{
			return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
		}

		if(isalnum(ch) || ispunct(ch) )											 //---If key is pressed and is not a control key---//
		{
			if((lParam & 0x80000000) == 0x00000000)   //---If key is pressed and is not a control key---//
			{
				findKannadaCharacters(ch);									//---Find the glyph code--//
				pushBackspaces();
			}
			else // key released
			{
				pushKeys();
				if(!WIN_NT_SERVER)
					return TRUE;
				else
					return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
			}
		}

		if( (isalnum(ch) || ispunct(ch)) &&!(GetKeyState(VK_MENU) & 0x80))    //---If the key pressed is a alpha key and when not
		{                                                  //---- Alt is down posts only the the promted message--//
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

BOOL EXPORTED_DLL_FUNCTION InstallKeyboardHookCauveryExpEXP(HWND hWnd)
{
	InstallKeyboardHookCauvery();
		return TRUE;
}

//---------------Insatalls-the-Hook---//---This-is -called-by-the-.exe---//
BOOL __stdcall InstallKeyboardHookCauvery() 
{
	isWinNTServer();
    BOOL bSuccess = FALSE;
    if( !ghKeyHook) 
	{
		glpfnHookProc = (HOOKPROC) SetKeyBoardCauvery;
        bSuccess = (NULL != ( ghKeyHook = ::SetWindowsHookEx (WH_KEYBOARD, glpfnHookProc,ghInstance, NULL)));
		bSuccess = TRUE;
		ghCallWndProcRetHook = ::SetWindowsHookEx (WH_CALLWNDPROCRET, (HOOKPROC)callWndRetProc,ghInstance, NULL);
	}
	return bSuccess;
}


//---------------Un-Insatalls-the-Hook---//---This-is -called-by-the-.exe---//
BOOL __stdcall DeInstallKeyboardHookCauvery()
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

CCauveryApp::CCauveryApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCauveryApp object

CCauveryApp theApp;



BOOL CCauveryApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ghInstance = AfxGetInstanceHandle();
	return TRUE;

}

int CCauveryApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	DeInstallKeyboardHookCauvery();

	return CWinApp::ExitInstance();
}

BOOL CCauveryApp::PreTranslateMessage(MSG* pMsg) 
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

   	BOOL bHandledKeystroke = FALSE;
	kFlag.found	= 0;

if(ch == ']' && kFlag.s_bit == TRUE)
{
	kFlag.s_bit = FALSE;
	return ;
}
if(kFlag.s_bit == TRUE)
{
   kFlag.s_bit = FALSE;
	
/*
	for(int i=0;i<43;i++)
	{
		if(ch == numerals[i].key)
		{
		//	sendBackSpace(1);//Eleminate the space 
			displayCharacters(i,NUMERALS,0);
			kFlag.found = TRUE;
			return ;
		}
	}
	*/
}

////////
/////// for poo hoo vooo---------------------------------------
////////

	if(ch == 'f' && kFlag.previous_0 == 'u' && kFlag.previous_1 == '\'' && kFlag.previous_2 == '=' && kFlag.previous_3 == 'p' )
	{
		kFlag.found = TRUE;
		sendBackSpace(2);
		displayDoubleCharacter(73,196);
		return ;
	}
	if(ch == 'u' && kFlag.previous_0 == 'u' && kFlag.previous_1 == 'm')
	{
		kFlag.found = TRUE;
		sendBackSpace(2);
		displaySingleCharacter(212);
		return ;
	}
	if(ch == 'u' && kFlag.previous_0 == 'y' && kFlag.previous_1 == 'H' )
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displaySingleCharacter(199);
		return ;
	}
	if(ch == '}' && kFlag.previous_0 == 'K' )
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displaySingleCharacter(205);
		return ;
	}
    if(ch == 'f' && kFlag.previous_0 == 'u' && kFlag.previous_1 == '\'' && kFlag.previous_2 == 'p'  )
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displaySingleCharacter(199);
		return ;
	}
	if(ch == 'f' && kFlag.previous_0 == 'u' && kFlag.previous_1 == '\'' && kFlag.previous_2 == 'h'  )
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displaySingleCharacter(199);
		return ;
	}
	if(ch == 'f' && kFlag.previous_0 == '\'' && kFlag.previous_1 == '7')
	{
		//sendBackSpace(1);
		kFlag.found = TRUE;
		displaySingleCharacter(199);
		return ;
	}
	if(ch == 'f' && kFlag.previous_0 == 'u' && kFlag.previous_1 == '\'' && kFlag.previous_2 == 'E')
	{
		kFlag.found = TRUE;
		sendBackSpace(2);
		displayDoubleCharacter(198,213);
		return ;
	}
	if(ch == 'f' && kFlag.previous_0 == 'u' && kFlag.previous_1 == 'E')
	{
		kFlag.found = TRUE;
		sendBackSpace(2);
		displayDoubleCharacter(198,213);
		return ;
	}
	
	if(ch == ']' && kFlag.previous_0 == '=' && kFlag.previous_1 == 'P')
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displaySingleCharacter(207);
		return ;
	}

if(ch == '"' && kFlag.previous_0 == 'p')
{
	kFlag.found = TRUE;
	sendBackSpace(2);
	displayDoubleCharacter(181,192);
		return ;
}

if(ch == 'm' && kFlag.previous_0 == 'm')
{
	kFlag.found = TRUE;
	sendBackSpace(1);
	displaySingleCharacter(237);
	return ;
}
if(ch == '"' && kFlag.previous_0 == '[')
{
	kFlag.found = TRUE;
	sendBackSpace(1);
	displaySingleCharacter(182);
		return ;
}
if(ch == '=' && kFlag.previous_0 == 'q')
{
	kFlag.found = TRUE;
	sendBackSpace(2);
	displaySingleCharacter(234);
	return ;
}

if(ch == '=')
{
//	MessageBox(NULL,"fv","vfv",MB_OK);
	for(int i=0;i<=15;i++)
	{   
		if(kFlag.found == 0)
		if(kFlag.previous_0 == doublekey_equals[i].key)
			{
				 displayCharacters(i,EQUALS,0);
				 kFlag.found = TRUE;
				 copyLastChar0(ch);
				 return ;
			}//----End Of  if ---//
	}//----End of for----//
	if(kFlag.found == FALSE)
	{
	displaySingleCharacter(44);
	copyLastChar0(ch);
	return ;
	}
}

if(ch == '+')
{
//	MessageBox(NULL,"fv","vfv",MB_OK);
	if(kFlag.previous_0 == '=' && kFlag.previous_1 == '<')
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displaySingleCharacter(220);
			return ;
	}
	for(int i=0;i<=4;i++)
	{   
		if(kFlag.found == 0)
		if(kFlag.previous_0 == doublekey_plus[i].key)
			{
				 displayCharacters(i,PLUS,0);
				 kFlag.found = TRUE;
				 	return ;
			}//----End Of  if ---//
	}//----End of for----//
	if(!kFlag.found)
	{
		if(kFlag.previous_0 == 'F' && kFlag.previous_1 == 'r' && kFlag.found == 0)
		{
			displaySingleCharacter(70);
			kFlag.found = TRUE;
				return ;
		}
		if(kFlag.previous_0 == '=' && kFlag.previous_1 == ',' && kFlag.found == 0)
		{
			sendBackSpace(3);
			displayDoubleCharacter(120,192);
			kFlag.found = TRUE;
				return ;
		}
		if(kFlag.previous_0 == '=' && kFlag.previous_1 == '.' && kFlag.found == 0)
		{
			sendBackSpace(2);
			displaySingleCharacter(121);
			kFlag.found = TRUE;
			    return ;
		}
	}

}

if(ch == ']')
{
//	MessageBox(NULL,"fv","vfv",MB_OK);
	for(int i=0;i<5;i++)
	{   
		if(kFlag.found == 0)
		if(kFlag.previous_0 == doublekey_sq_bracket[i].key)
			{
				 displayCharacters(i,SQ_BRACKET,0);
				 kFlag.found = TRUE;
			}//----End Of  if ---//
	}//----End of for----//
	if(!kFlag.found)
	{
	if(kFlag.previous_0 == '=' && kFlag.previous_1 == 'p' && kFlag.found == 0)
		{
			sendBackSpace(3);
			displayDoubleCharacter(87,192);
			kFlag.found = TRUE;
				return ;
		}
	if(kFlag.previous_0 == '=' && kFlag.previous_1 == '[' && kFlag.found == 0)
		{
			sendBackSpace(2);
			displaySingleCharacter(88);
			kFlag.found = TRUE;
				return ;
		}
	}
}

if(ch == 'u' )
{
	if(!kFlag.found)
	{
	if(kFlag.previous_0 == 'Y' && kFlag.previous_1 == 'H' && kFlag.found == 0)
		{
			sendBackSpace(2);
			displayTripleCharacter(83,192,196);
			kFlag.found = TRUE;
			return ;
		}
	else
	if(kFlag.previous_0 == 'Y' && kFlag.previous_1 == 'm' && kFlag.found == 0)
		{
			sendBackSpace(2);
			displayFourCharacter(65,105,192,196);
			kFlag.found = TRUE;
			return ;
		}
	else//-------------------For Four keyed Values----------------------------------//
	if(kFlag.previous_0 == '=' && kFlag.previous_1 == 'u' && kFlag.previous_2 == 'r'&& kFlag.found == 0)
		{
			sendBackSpace(2);
			displayDoubleCharacter(104,196);
			kFlag.found = TRUE;
			return ;
		}
	else
	if(kFlag.previous_0 == '=' && kFlag.previous_1 == 'u'&& kFlag.previous_2 == '4' && kFlag.found == 0)
		{
			sendBackSpace(2);
			displayTripleCharacter(106,104,196);
			kFlag.found = TRUE;
			return ;
		}
	else
	if(kFlag.previous_0 == ']' && kFlag.previous_1 == 'u'&& kFlag.previous_2 == 'm' && kFlag.found == 0)
		{
			sendBackSpace(2);
			displayDoubleCharacter(172,196);
			kFlag.found = TRUE;
			return ;
		}
	else
	if(kFlag.previous_0 == 'p' || kFlag.previous_0 == 'h')
	{
		kFlag.found = 1;
		displaySingleCharacter(197);
	}
	else
	if(kFlag.previous_0 == 'E' )
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displayDoubleCharacter(196,213);
	}
	}
}
else
if(ch == 'i' && kFlag.previous_0 == '}' )
{
	sendBackSpace(1);
	displaySingleCharacter(75);
	kFlag.found = TRUE;
		return ;
}
else
if(ch == 'o' && kFlag.previous_0 == '}' )
{
	sendBackSpace(1);
	displaySingleCharacter(78);
	kFlag.found = TRUE;
		return ;
}
else
if(ch == 'O' && kFlag.previous_0 == 'o' )
{
	sendBackSpace(1);
	displaySingleCharacter(79);
	kFlag.found = TRUE;
	return ;
}
else
if(ch == 'I' &&kFlag.previous_0 == '\'')
				 {	 
					//setGlyphs(ch,
					displaySingleCharacter(202);
					kFlag.found = TRUE;
				 }
				 else
				 if(ch == '\'' && kFlag.c_bit == TRUE)
				 {
					 kFlag.c_bit = FALSE;
					switch(kFlag.previous_0)
					{
							case 'b' :
							 if(kFlag.o_bit == 0)
							 {
								setGlyphs(ch,167);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								displaySingleCharacter(201);
								kFlag.found = TRUE;
							 }
							 else
							 {
							 kFlag.o_bit = 0;
							 sendBackSpace(1);
							 displaySingleCharacter(201);
							 kFlag.found = TRUE;
							 }
								
							break;
						    case 'H' :
								setGlyphs(ch,82);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								displaySingleCharacter(201);
								kFlag.found = TRUE;
							break;
							case 'j' :
								setGlyphs(ch,100);
								kFlag.n_back = 0;
								displaySingleCharacter(201);
								kFlag.found = TRUE;
							break;
							case 't' :
								setGlyphs(ch,108);
								displaySingleCharacter(201);
								kFlag.found = TRUE;
							break;
							case 'z' :
								setGlyphs(ch,116);
								displaySingleCharacter(201);
								kFlag.found = TRUE;
							break;
							case 'l' :
								setGlyphs(ch,174);
								displaySingleCharacter(201);
								kFlag.found = TRUE;
							break;
							case 'E' :
								kFlag.found = TRUE;
								sendBackSpace(2);
								displayTripleCharacter(101,201,213);
							break;
							default:
								sendBackSpace(1);
								displaySingleCharacter(201);
								kFlag.found = TRUE;
					}//----End of switch (previous_0)----//

				 }
				 else
				 if (ch == 'f' && kFlag.c_bit == TRUE)
				 {
					kFlag.c_bit = FALSE;
					switch(kFlag.previous_0)
					{
							case 'b' :
							 if(kFlag.o_bit == 0)
							 {
								 //sendBackSpace(1);
								setGlyphs(ch,167);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								displaySingleCharacter(193);
								kFlag.found = TRUE;
							 }
							 else
							 {
							 kFlag.o_bit = 0;
							 sendBackSpace(1);
							 displaySingleCharacter(193);
							 kFlag.found = TRUE;
							 }
								
							break;
						    case 'H' :
								setGlyphs(ch,82);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								displaySingleCharacter(193);
								kFlag.found = TRUE;
							break;
							case 'j' :
								setGlyphs(ch,100);
								kFlag.n_back = 0;
								displaySingleCharacter(193);
								kFlag.found = TRUE;
							break;
							case 't' :
								setGlyphs(ch,108);
								displaySingleCharacter(193);
								kFlag.found = TRUE;
							break;
							case 'z' :
								setGlyphs(ch,116);
								displaySingleCharacter(193);
								kFlag.found = TRUE;
							break;
							case 'l' :
								setGlyphs(ch,174);
								displaySingleCharacter(193);
								kFlag.found = TRUE;
							break;
							case 'U' :
								sendBackSpace(1);
								displaySingleCharacter(72);
								kFlag.found = TRUE;
								break;
							case '7' :
								sendBackSpace(1);
								displaySingleCharacter(199);
								kFlag.found = TRUE;
								break;
							case 'u' :
										kFlag.found = TRUE;
										displayDoubleCharacter(8,198);
								break;
							case 'E' :
										kFlag.found = TRUE;
										sendBackSpace(2);
										displayTripleCharacter(101,193,213);
								break;
							default:
								sendBackSpace(1);
								displaySingleCharacter(193);
								kFlag.found = TRUE;
					}//----End of switch (previous_0)----//


				 }
     		    else
				 if(ch == ']' && kFlag.c_bit == TRUE)
				 {
					kFlag.c_bit = FALSE ;
					switch(kFlag.previous_0)
					{
						
						case 'b' :
							 if(kFlag.o_bit == 0)
							 {
								 sendBackSpace(1);
								setGlyphs(ch,167);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								displaySingleCharacter(169);
								kFlag.found = TRUE;
							 }
							 else
							 {
								kFlag.o_bit = 0;
								kFlag.s_bit = 1;  //---------To be used for further ie; for bhi-------//
								sendBackSpace(1);			//This function sets the glyph 
										            //---patterns for thes specified characters
								displaySingleCharacter(169);
								kFlag.found = TRUE;
							 }
							break;
						    case 'H' :
								sendBackSpace(1);				//This function sets the glyph 
								                    //---patterns for thes specified characters
								displaySingleCharacter(84);
								kFlag.found = TRUE;
							break;
							case 'j' :
								sendBackSpace(1);
								kFlag.n_back = 0;
								displaySingleCharacter(102);
								kFlag.found = TRUE;
							break;
							case 't' :
								sendBackSpace(1);
								displaySingleCharacter(110);
								kFlag.found = TRUE;
							break;
							
							case 'l' :
								sendBackSpace(1);
								displaySingleCharacter(176);
								kFlag.found = TRUE;
							break;
						/*	case '=' :
								sendBackSpace(2);
								displaySingleCharacter(88);
								kFlag.found = TRUE;
							break;*/
							case '\\' :
								sendBackSpace(2);
								displaySingleCharacter(182);
								kFlag.found = TRUE;
							break;
							case 'y' :
								sendBackSpace(3);
								displaySingleCharacter(172);
								kFlag.found = TRUE;
							break;
							case 'E' :
								kFlag.found = TRUE;
								sendBackSpace(2);
								displayDoubleCharacter(102,213);
								break;
							default:
							break;
					}//----End of switch (previous_0)----//
		
				 }
				 else
					 if(ch == '}' && kFlag.c_bit == TRUE)
					 {
						 kFlag.c_bit = FALSE;
						 switch(kFlag.previous_0)
						{
							case 'i':
							sendBackSpace(1);
							displaySingleCharacter(75);
							kFlag.found = TRUE;
							break;		
							case 'o':
							sendBackSpace(1);
							displaySingleCharacter(78);
							kFlag.found = TRUE;
							break;		
					
							case 'b' :
							 if(kFlag.o_bit == 0)
							 {
								setGlyphs(ch,167);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								displaySingleCharacter(239);
								kFlag.found = TRUE;
							 }
							 else
							 {
							 kFlag.o_bit = 0;
							 sendBackSpace(1);
							 displaySingleCharacter(239);
							 kFlag.found = TRUE;
							 }
							break;
						    case 'H' :
								setGlyphs(ch,82);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								displaySingleCharacter(239);
								kFlag.found = TRUE;
							break;
							case 'j' :
								setGlyphs(ch,100);
								kFlag.n_back = 0;
								displaySingleCharacter(239);
								kFlag.found = TRUE;
							break;
							case 't' :
								setGlyphs(ch,108);
								displaySingleCharacter(239);
								kFlag.found = TRUE;
							break;
							case 'z' :
								setGlyphs(ch,116);
								displaySingleCharacter(239);
								kFlag.found = TRUE;
							break;
							case 'l' :
								setGlyphs(ch,174);
								displaySingleCharacter(239);
								kFlag.found = TRUE;
							break;
							case 'E' :
								kFlag.found = TRUE;
								sendBackSpace(2);
								displayTripleCharacter(101,239,213);
							break;
							default:
								sendBackSpace(1);
								displaySingleCharacter(239);
								kFlag.found = TRUE;
						 }//----End of switch (previous_0)----//
					 }
					 if(ch == 'O')
					 {
						 switch(kFlag.previous_0)
						 {
							case 'b' :
							 if(kFlag.o_bit == 0)
							 {
								setGlyphs(ch,167);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								displaySingleCharacter(203);
								kFlag.found = TRUE;
							 }
							 else
							 {
							 kFlag.o_bit = 0;
							 sendBackSpace(1);
							 displaySingleCharacter(203);
							 kFlag.found = TRUE;
							 }
							 break;
						    case 'H' :
								setGlyphs(ch,82);					//This function sets the glyph 
								kFlag.n_back = -1;                    //---patterns for thes specified characters
								displaySingleCharacter(203);
								kFlag.found = TRUE;
							break;
							case 'j' :
								setGlyphs(ch,100);
								kFlag.n_back = 0;
								displaySingleCharacter(203);
								kFlag.found = TRUE;
							break;
							case 't' :
								setGlyphs(ch,108);
								displaySingleCharacter(203);
								kFlag.found = TRUE;
							break;
							case 'z' :
								setGlyphs(ch,116);
								displaySingleCharacter(203);
								kFlag.found = TRUE;
							break;
							case 'l' :
								setGlyphs(ch,174);
								displaySingleCharacter(203);
								kFlag.found = TRUE;
							break;
							case 'E' :
								kFlag.found = TRUE;
								sendBackSpace(2);
								displayTripleCharacter(101,203,213);
							break;

						 
							 break;
						 default :
							 sendBackSpace(1);
							 displaySingleCharacter(203);
						 }
							 
					 }
	if(ch == ';'&& kFlag.previous_0 == 'F' && kFlag.previous_1 == 'r')
					{
						kFlag.found = TRUE;
						sendBackSpace(3);
						displaySingleCharacter(70);
					}     
	if(ch == 'f' && kFlag.previous_0 == 'u' && kFlag.previous_1 == 'v')
					{
						kFlag.found = TRUE;
						sendBackSpace(1);
						displayDoubleCharacter(105,193);
					}
	if(ch == 'f' && kFlag.previous_0 == 'u' && (kFlag.previous_1 == 'p' || kFlag.previous_1 == 'h'))
					{
						kFlag.found = TRUE;
						sendBackSpace(1);
						displaySingleCharacter(199);
					}
	if(ch == 'O' &&  kFlag.previous_0 == 'u' && kFlag.previous_1 == 'y' && kFlag.previous_2 == 'm')
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displayDoubleCharacter(105,203);
	}
	if(ch == 'O' &&  kFlag.previous_0 == 'u' && kFlag.previous_1 == '=' && kFlag.previous_2 == 'u'&& kFlag.previous_3 == 'r')
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displayDoubleCharacter(105,203);
	}
	if(ch == 'O' &&  kFlag.previous_0 == 'u' && kFlag.previous_1 == 'v')
	{
		kFlag.found = TRUE;
		sendBackSpace(1);
		displayDoubleCharacter(105,203);
	}


if(kFlag.found == FALSE)
	{
	for(int i=0;i<=90;i++)
		{   
			if(kFlag.found == 0)
			if(ch == singlekey_singleglyph[i].key)
				{
					kFlag.c_bit = TRUE;
 					displayCharacters(i,SINGLE,0);
					kFlag.found = TRUE;
				}//----End Of  if ---//
		}//----End of for----//
	}
	if(!kFlag.found)
	{
		displayGunitakshara(ch);
	}
	


	if(isspace(ch))
	{
	kFlag.s_bit = 1;
    kFlag.c_bit = 0 ;
    kFlag.q_bit = 0;
	}

	copyLastChar0(ch);

	return ;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Finds The Character in The Tables in Found Calls     /////////////////////////////
/////////////////////////////  The Display Functions With Position (i),and The Starting Position  /////////////////////////////
/////////////////////////////  Of The Of The Message To Be Posted The Argument 					  /////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void displayCharacters(int nval,int indicator,int j)   //indictor value is 0 for anuswara ,1 for singlekey_singleglyph , 2 for singlekey_doubleglyph
{    
			int k = j ;   // --------index for glyph codes---// 
			 HWND myWnd;
	         myWnd =  getActiveWindowHandle();


		while(kFlag.n_back>=1)
			{
//				::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
			addKey(8);
			kFlag.n_back--;
			}


	
		   if(indicator==SINGLE)	
			{
			while(singlekey_singleglyph[nval].k_val[k]!=-1)
				{
					  //  ::PostMessage(myWnd,WM_CHAR,(WPARAM)singlekey_singleglyph[nval].k_val[k],(LPARAM)1);
				addKey(singlekey_singleglyph[nval].k_val[k]);
						k++;
				}
			}
		  else
		  if(indicator==EQUALS)	
			{
			while(doublekey_equals[nval].k_val[k]!=-1)
				{
					    //::PostMessage(myWnd,WM_CHAR,(WPARAM)numerals[nval].k_val[k],(LPARAM)1);
					addKey(doublekey_equals[nval].k_val[k]);
						k++;
				}
			}
		  else
		  if(indicator==PLUS)	
			{
			while(doublekey_plus[nval].k_val[k]!=-1)
				{
					    //::PostMessage(myWnd,WM_CHAR,(WPARAM)numerals[nval].k_val[k],(LPARAM)1);
					addKey(doublekey_plus[nval].k_val[k]);
						k++;
				}
			}
		  else
		  if(indicator==SQ_BRACKET)	
			{
			while(doublekey_sq_bracket[nval].k_val[k]!=-1)
				{
					    //::PostMessage(myWnd,WM_CHAR,(WPARAM)numerals[nval].k_val[k],(LPARAM)1);
					addKey(doublekey_sq_bracket[nval].k_val[k]);
						k++;
				}
			}
	/*	  else
		  if(indicator==NUMERALS)	
			{
			while(numerals[nval].k_val[k]!=-1)
				{
					    //::PostMessage(myWnd,WM_CHAR,(WPARAM)numerals[nval].k_val[k],(LPARAM)1);
					addKey(numerals[nval].k_val[k]);
						k++;
				}
			}*/
	
		  kFlag.s_bit = FALSE;
			kFlag.n_back = -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Set The Glypha For Kha,ja,.... ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch ===>character , gval ===> pevious_0 GlypH value//

void setGlyphs(char ch,int gval)
{
		
	switch (ch)
	{
	case 'f' :
	case '{' :	
	case 'O' :
	case 'i' :
	case '}' :
	case '\'':
		sendBackSpace(1);
		addKey(gval+1);
	
	break;
	default :
	 break; 
	
	}
	kFlag.n_back = -1;
}


void displayGunitakshara(char ch)
{
	switch(ch)
	{
	case ',':
			
	break;
	case ']':

	break;
	case 'I':

	break;
	case '}':

	break;
	}
}

void copyLastChar0(char ch)
{   
	kFlag.previous_3 = kFlag.previous_2;
	kFlag.previous_2 = kFlag.previous_1;
	kFlag.previous_1 = kFlag.previous_0;
	kFlag.previous_0 = ch;
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