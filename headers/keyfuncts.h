////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////AUTHOR : Sudheer HS	sudheer316@gmail.com////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////DATE : 6-apr-2006							////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////COMPANY : KanForge.,HASSAN - 573201 ,KARANATAKA, INDIA     ////////////////////////////////////////////////////////////////
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
#include <vector>
#include <windows.h>
#include "..\headers\flags.h"

std::vector<int> g_keystoadd;

void displayQueue();
void sendSpace(int);
void clearQueue();
void sendBackSpace(int back);
void displayCharacterPHI(char ch,int i);
void displayCharactersjPwX(char ch,int i);
void displayChar(char ch);
void setForFBit(char ch,int i);
void setGlyphsFoeJMY(char ch,int i);
void setGlyphsNyaInya(char ch,int i);
void setGlyphsBaCa(char ch,int i);
void setGlyphs(char ch , int gval);
void displayCharacters(int nval,int v_bit,int j) ;
void displayCharactersF(char ch) ;
void displayGunisu(char ch) ;
void displayCharactersA(int nval,int v_bit,int j) ;
void copyLastChar0(char ch);
void copyLastChar1(char ch);
void setGlyphsForKXHA_GYNA(char ch,int i);
void setGlyphsForJMY(char ch,int i);
void setGlyphsKaJaBa(char ch , int gval,int i);
void findKannadaCharacters(char ch) ;
void displayGunitakshara(char ch);
void displayCharactersF(char ch);
void displayChar(char ch);
void clearAllFlags();

void processGuntaksharas(int ch,int no_bs,int i,int glp_pos);

int  isPreviousF(char ch);


void isWinNTServer();


HWND getActiveWindowHandle();

char f1,f2;

static int WIN_NT_SERVER = FALSE;

UINT scan=0; 


void addKey(int ch)
{
          g_keystoadd.push_back(ch);
}


void pushBackspaces()
{
          HWND hWnd;
          hWnd =  getActiveWindowHandle();
          do
          {
                    if((g_keystoadd.size()>0) && (g_keystoadd[0]==8))
                    {
                              ::PostMessage(hWnd,WM_KEYDOWN,(WPARAM)VK_BACK,(LPARAM)((0x0e<<16)|1));
                              ::PostMessage(hWnd,WM_KEYUP,(WPARAM)VK_BACK,(LPARAM)((0x0e<<16)|1|(1<<31)));
                              g_keystoadd.erase(g_keystoadd.begin());
					}
                    else
                    break;
		  } 
		  while (g_keystoadd.size()>0);
}


void pushKeys()
{
          if(g_keystoadd.size()==0)
          return;
          HWND hWnd;
          hWnd =  getActiveWindowHandle();
          while(g_keystoadd.size()>0)
          {
							  ::PostMessageA(hWnd,WM_CHAR,(WPARAM)g_keystoadd[0],(LPARAM)1);
                     g_keystoadd.erase(g_keystoadd.begin());
		  }
}



void displaySingleCharacter(int fval) 
{
addKey(fval);
}


void displayDoubleCharacter(int fval,int sval) 
{
addKey(fval);
addKey(sval);
}


void displayTripleCharacter(int fval,int sval,int tval) 
{
addKey(fval);
addKey(sval);
addKey(tval);
}


void displayFourCharacter(int fval,int sval,int tval,int fhval) 
{
addKey(fval);
addKey(sval);
addKey(tval);
addKey(fhval);
}



void sendBackSpace(int back)
{
		while(back>=1)
		{
          addKey(VK_BACK);
          back--;
		}
}


HWND getActiveWindowHandle()
{
	HWND  hWnd;  //---------Window Handel---//
	hWnd  = GetFocus ();
	
	if (hWnd == NULL)
		hWnd = GetForegroundWindow ();
	return hWnd;
}

void sendSpace(int s)
{
while(s-->=1)
	{
          addKey((WPARAM)246);
    }
}

int isNumPad(WPARAM wParam)
{
	if(wParam == VK_SUBTRACT  ||
       wParam == VK_NUMPAD0   ||
	   wParam == VK_NUMPAD1   ||
	   wParam == VK_NUMPAD2   ||
	   wParam == VK_NUMPAD3   ||
	   wParam == VK_NUMPAD4   ||
	   wParam == VK_NUMPAD5   ||
	   wParam == VK_NUMPAD6   ||
	   wParam == VK_NUMPAD7   ||
	   wParam == VK_NUMPAD8   ||
	   wParam == VK_NUMPAD9   ||
	   wParam == VK_DIVIDE    ||
	   wParam == VK_ADD       ||
	   wParam == VK_MULTIPLY  ||
	   wParam == VK_DECIMAL   )
	{
		
		return 1;
	}
	else
		return 0;
}


void isWinNTServer()
{
    OSVERSIONINFO osvi;
    BOOL bIsWindowsNTServer;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

    bIsWindowsNTServer  = 
       ( (osvi.dwMajorVersion == 4) );

	AfxMessageBox("I am on NT",1);

    if(bIsWindowsNTServer)
	{       
	   WIN_NT_SERVER = TRUE;
	  // AfxMessageBox("I am on NT",1);
	   //return TRUE;
	}
	else
	{
		WIN_NT_SERVER = FALSE;
	    //AfxMessageBox("I am not on NT",1);
	//	return FALSE;
	}

}