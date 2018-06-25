//Netravathi.cpp implemaentation file

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
#include "stdafx.h"
#include "netravathi.h"
//#include "..\headers\flags.h"
#include "..\headers\keyfuncts.h"
#include <ctype.h>
#include <windows.h>

#define ANUSWARA 0
#define VOWELS 1
#define CONSONANTS 2

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

int iVottaksharas[10] ={ -1 };

//---Structure of anuswara and visarga----//
struct anv_tab
{
          char key;								//----holds the character 
          int k_val[3];							//---holds the glyph codes of the corresponding above character eg; 
          //---for a 67 (first 3 values)for vowel and 192 for consonants (last value)
}anuswaranvisarga[5] = { 
						  '\\', {-1,-1}, 	
						  'M', {65,-1,-1 } ,
						  'H', {66,-1,-1 } ,
						  'F', {240,-1,-1} ,
						  ' ', {32 , -1}
						};


//---Structure of vowles ----//
struct val_tab
{
          char key;								//----holds the character 
          int k_val[11];							//---holds the glyph codes of the corresponding above character eg;  
          //---for a 67 (first 3 values)for vowel and 192 for consonants (last value)
}vowels[16] =   { 'a', { 67, -1,-1,-1,-1,-1,-1,- 1,-1,-1} ,        
				  'A', { 68, -1,-1,193,-1 ,-1,-1,-1,-1 } ,
				  'i', { 69, -1,-1, -1,-1 ,-1,-1,-1,-1 } ,
				  'I', { 70, -1,-1, -1,-1 ,-1,-1,-1 ,-1} ,
				  'u', { 71, -1,-1,196,-1 ,-1,-1,197 ,-1} , 
				  'U', { 72, -1,-1,198,-1,-1,-1,199 ,-1} ,
				  'R', { 73,196,-1,200 ,-1,-1,-1,-1,-1} ,
				  'e', { 74, -1,-1,201,-1 ,-1,-1,-1 ,-1} ,
				  'E', { 75, -1,-1,201,195 ,-1,-1 ,-1} ,
				  'Y', { 76, -1,-1,201,202,-1,-1  ,-1} ,
				  'o', { 77, -1,-1,201,198 ,-1,-1 ,201,199,-1} ,
				  'O', { 78, -1,-1,201,198 ,195,-1,201,199,195,-1} ,
				  'V', { 79, -1,-1,203,-1,-1,-1,-1 ,-1} ,
				  'X', { 251, -1}
                };



//---Structure of consonants ----//
struct con_tab
{
          char key;								//----holds the character 
          int k_val[7];							//---holds the glyph codes of the corresponding above character eg; 
          //---- for a 67 (first 3 values)for vowel and 192 for consonants (last value)
}consonants[35] = {   'k', {80,192,-1,-1,-1,204 ,-1} ,            //---Kannada Character ka---//
					  'K', {82,-1,-1,-1,-1,205 ,-1} ,			//---Kannada Character Kha---//	
					  'g', {85,192,-1,-1,-1,206 ,-1} ,			//---Kannada Character ga---//	
					  'G', {87,192,-1,-1,-1,207,-1 } ,			//---Kannada Character Gha---//
					  'Z', {89,-1,-1,-1,-1,208,-1 } ,		    //---Kannada Character nya---//
					  'c', {90,192,-1,-1,-1,209 ,-1} ,			//---Kannada Character cha---//	
					  'C', {98,192,-1,-1,-1,210 ,-1} ,		    //---Kannada Character CHA---//
					  'j', {100,-1,-1,-1,-1,211,-1 } ,			//---Kannada Character ja---//	
					  'J', {103,192,104,196,-1,212,-1 } ,	    //---Kannada Character Jha---//  
					  'z', {107,-1,-1,-1,-1,213 ,-1} ,			//---Kannada Character Inya---//	
					  'q', {108,-1,-1,-1,-1,214 ,-1} ,			//---Kannada Character Ta---//
					  'Q', {111,192,-1,-1,-1,215 ,-1} ,			//---Kannada Character TA---//
					  'w', {113,192,-1,-1,-1,216,-1 } ,			//---Kannada Character dha---//
					  'W', {113,115,192,-1,-1,217 ,-1} ,		//---Kannada Character DHA---//
					  'N', {116,-1,-1,-1,-1,218,-1 } ,			//---Kannada Character NA---//
					  't', {118,192,-1,-1,-1,219 ,-1} ,			//---Kannada Character tha---//
					  'T', {120,192,-1,-1,-1,220 ,-1} ,			//---Kannada Character THA---//
					  'd', {122,192,-1,-1,-1,221 ,-1} ,			//---Kannada Character da---//
					  'D', {122,115,192,-1,-1,222,-1 } ,		//---Kannada Character DA---//
					  'n', {163,192,-1,-1,-1,223 ,-1} ,			//---Kannada Character na---//
					  'p', {165,192,-1,-1,-1,224,-1} ,			//---Kannada Character pa---//
					  'P', {165,115,192,-1,-1,225 ,-1} ,		//---Kannada Character PHA---//
					  'b', {167,-1,-1,-1,-1,226 ,-1} ,			//---Kannada Character ba---//
					  'B', {168,115,192,-1,-1,227,-1 } ,		//---Kannada Character BHA---//
					  'm', {170,192,196,-1,-1,228 ,-1} ,		//---Kannada Character Ma---//	
					  'y', {65,105,192,196,-1,229,-1 } ,        //---Kannada Character Ya---//
					  'r', {103,192,-1,-1,-1,230,-1} ,		    //---Kannada Character ra---//
					  'l', {174,-1,-1,-1,-1,232 ,-1} ,			//---Kannada Character la---// 	
					  'v', {170,192,-1,-1,-1,233 ,-1} ,			//---Kannada Character va---//
					  'S', {177,192,-1,-1,-1,234 ,-1} ,			//---Kannada Character SHA---//
					  'x', {181,192,-1,-1,-1,235 ,-1} ,			//---Kannada Character sha---//
					  's', {184,192,-1,-1,-1,236 ,-1} ,			//---Kannada Character sa---//
					  'h', {186,192,-1,-1,-1,237 ,-1} ,			//---Kannada Character ha---//
					  'L', {188,192,-1,-1,-1,238 ,-1} ,			//---Kannada Character LA---//
				};  


///---------------Structure for guntakshara---------------///
struct guni_tab
{
          char key;								//----holds the character 
          int k_val[4];							//---holds the glyph codes of the corresponding above character 
          //----eg;  for a 67 (first 3 values)for vowel and 192 for consonants (last value)
          }gunisu[35] = {     'k', {81,-1,-1,-1} ,          //---Kannada Character ki---//
							  'K', {84,-1,-1,-1} ,			//---Kannada Character Khi---//	
							  'g', {86,-1,-1,-1} ,			//---Kannada Character gi---//	
							  'G', {88,-1,-1,-1} ,			//---Kannada Character Ghi---//
							  'Z', {89,194,-1,-1} ,		    //---Kannada Character nyi---//
							  'c', {97,-1,-1,-1} ,			//---Kannada Character chi---//	
							  'C', {99,-1,-1,-1} ,		    //---Kannada Character CHi---//
							  'j', {102,-1,-1,-1} ,			//---Kannada Character ji---//	
							  'J', {106,104,196,-1} ,	    //---Kannada Character Jhi---//  
							  'z', {107,194,-1,-1} ,		//---Kannada Character Inyi---//	
							  'q', {110,-1,-1,-1} ,			//---Kannada Character Ti---//
							  'Q', {112,-1,-1,-1} ,			//---Kannada Character Ti---//
							  'w', {114,-1,-1,} ,			//---Kannada Character dhi---//
							  'W', {114,252,-1,-1} ,		//---Kannada Character DHi---//
							  'N', {116,194,-1,-1} ,		//---Kannada Character Ni---//
							  't', {119,-1,-1,-1} ,			//---Kannada Character thi---//
							  'T', {121,-1,-1,-1} ,			//---Kannada Character THi---//
							  'd', {162,-1,-1,-1} ,			//---Kannada Character di---//
							  'D', {162,252,-1,-1} ,		//---Kannada Character Di---//
							  'n', {164,-1,-1,-1} ,			//---Kannada Character ni---//
							  'p', {166,-1,-1,-1} ,			//---Kannada Character pi---//
							  'P', {166,252,-1,-1} ,		//---Kannada Character PHi---//
							  'b', {169,-1,-1,-1} ,			//---Kannada Character bi---//
							  'B', {169,252,-1,-1 } ,		//---Kannada Character BHi---//
							  'm', {171,196,-1,-1} ,		//---Kannada Character Mi---//	
							  'y', {172,196,-1,196} ,       //---Kannada Character Yi---//
							  'r', {106,-1,-1,-1} ,		    //---Kannada Character ri---//
							  'l', {176,-1,-1,-1} ,			//---Kannada Character li---// 	
							  'v', {171,-1,-1,-1} ,			//---Kannada Character vi---//
							  'S', {178,-1,-1,-1} ,			//---Kannada Character SHi---//
							  'x', {182,-1,-1,-1} ,			//---Kannada Character shi---//
							  's', {185,-1,-1,-1} ,			//---Kannada Character si---//
							  'h', {187,-1,-1,-1} ,			//---Kannada Character hi---//
							  'L', {189,-1,-1,-1} ,			//---Kannada Character Li---//
						};  



BEGIN_MESSAGE_MAP(CNetravathiApp, CWinApp)
//{{AFX_MSG_MAP(CNetravathiApp)
                    // NOTE - the ClassWizard will add and remove mapping macros here.
                    //    DO NOT EDIT what you see in these blocks of generated code!
                    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


void processGuntaksharas(int ch,int no_bs,int i,int glp_pos)
{
								  switch(ch)
                                      {	
                                                  case 'a':
                                                  kFlag.n_back = -1;
                                                  break;
                                                  case  'u' :
                                                  case  'U' :
                                                  case  'R' :
                                                  kFlag.n_back = -1;
												  break;

                                                  default :
                                                  kFlag.n_back = 1;
                                        }//-------------End of Switch------------//
                                                                                                                        
										if(kFlag.o_bit == 1)
                                        {
                                                  sendBackSpace(no_bs);
                                        }
                                        /////////////////////////////////////////////////////
                                                                                                                        
										if(ch == 'R')
                                        {

                                                  if(kFlag.o_bit == 1)  //-----------If an Ottakshara has to be processed-----------//
                                                  {
                                                            displayQueue();
                                                            clearQueue();
                                                            kFlag.o_bit = 0;
                                                            vowels[i].k_val[3] = 248;
                                                            displayCharacters(i,VOWELS,3);
                                        
												  }//------------EnD of o_bit  == 1---------//
                                                  else
                                                  {
                                                            kFlag.s_bit = 1;
                                                            vowels[i].k_val[3] = 200;
															displayCharacters(i,VOWELS,3);
												  }
                                                  
										}//----------------End of if(ch == R)-----------------//
                                        else
                                        if(ch == 'i')                   //---If an i is pressed after a consonant---//
                                        {   
                                                  kFlag.n_back = -1;
                                                  displayGunisu(ch);
										}
                                        else
                                        if(ch == 'I')                   //---If an i is pressed after a consonant---//
                                        {   
                                                  kFlag.n_back = -1;
                                                  displayGunisu(ch);
										}
                                        else
                                        switch (kFlag.previous_0)   
                                        {
                                                  case 'Z' :
                                                  case 'z' :
                                                  kFlag.n_back = -1;
                                                  displayCharacters(i,VOWELS,3) ;
                                                  break ;
                                        
												  case 'b' :
                                                  setGlyphsKaJaBa(ch,167,i);					//This function sets the glyph 
                                                  break;
                                                  
												  case 'K' :
                                                  setGlyphsKaJaBa(ch,82,i);					//This function sets the glyph 
                                                  break;
                                                  
												  case 'j' :
                                                  setGlyphsKaJaBa(ch,100,i);
                                                  break;
                                                  
												  case 'q' :
                                                  setGlyphsKaJaBa(ch,108,i);
                                                  break;
                                                  
												  case 'N' :
                                                  setGlyphsKaJaBa(ch,116,i);
                                                  break;

                                                  case 'l' :
                                                  setGlyphsKaJaBa(ch,174,i);
                                                  break;
                                                  case 'J' :					//----For the characters ya ,ma,Jha,---//
                                                  case 'm' :
                                                  //---ch the character and i the position in the vowles tab
                                                  
												  setGlyphsForJMY(ch,i);
                                                  break;
                                                  
												  case 'y' :
                                                  setGlyphsForJMY(ch,i);
                                                  break;
                                                  
												  default :	
                                                  //---For all other characters---//
                                                  glp_pos = 3;
                                                  switch(kFlag.previous_0)  //---------For Characters hu,vu,pu,Pu-------//
                                                  {
                                                            case 'p':
                                                            case 'P':
                                                            case 'v':
                                                            case 'h':
                                                            if(ch=='u'||ch=='U'||ch=='o'||ch=='O')
                                                            glp_pos = 7;
                                                            else
                                                            glp_pos = 3;
                                                  }
        
												  if(kFlag.x_bit == 1)
                                                  {
                                                            if(kFlag.previous_0 == 'P')
                                                            displayCharacterPHI(ch,i);
                                                            kFlag.x_bit = 0 ;
												  }
                                                  if(ch ==  'E' || ch == 'O') //for displaying the ottakshara beforf the Deerga
                                                  {
															if(ch == 'O')
                                                            switch(kFlag.previous_0)  //---------For Characters hu,vu,pu,Pu-------//
                                                            {
                                                                      case 'p':
                                                                      case 'P':
                                                                      case 'v':
                                                                      case 'h':
                                                                      glp_pos = 7;
																	  //MessageBox(NULL,"fvbg","bgfb",MB_OK);
															}

                                                            if(kFlag.o_bit)                           //---If an f f_bit was set ---//
                                                            {
                                                                      displayCharacters(i-1,VOWELS,glp_pos) ;	
                                                                      displayQueue();
                                                                      clearQueue();
                                                                      kFlag.o_bit = 0;
                                                                      kFlag.c_bit = 0;									 //------------inserted --------now 
                                                                      displaySingleCharacter(195);
															} 
                                                            else
                                                            displayCharacters(i,VOWELS,glp_pos) ;	
												  }
                                                 else	
                                                  if(ch == 'Y')
                                                  {
                                                            displayDoubleCharacter(VK_BACK,201) ;	
                                                            if(kFlag.o_bit)                           //---If an f f_bit was set ---//
                                                            {
                                                                      displayQueue();
                                                                      clearQueue();
																	  displaySingleCharacter(246);
                                                                      kFlag.o_bit = 0;
                                                                      kFlag.c_bit = 0;
																	  kFlag.o_count = 0;//------------inserted --------now 
																	  kFlag.n_back = -1;
															} 
                                                            displaySingleCharacter(202) ;	
												  }
                                                  else	
                                                  displayCharacters(i,VOWELS,glp_pos) ;		    //---Display --Glyphs from 3----//
                                                  ///----------pevious_0 value put to next line of c_bit
                                                  }
                                        kFlag.c_bit = 0;									///-------------Changed from last 

}

//------------This-function-is-repeatedly-called-this-executes-when-a-key-is-pressed-on-the-keyboard---/
LRESULT EXPORTED_DLL_FUNCTION SetKeyBoardNetravathi(int nCode,WPARAM wParam,LPARAM lParam)
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
         
		  
		  if((GetKeyState(VK_SCROLL ) & 0x0001))
          {
                if(ispunct(ch) || isdigit(ch) || (wParam == VK_SPACE) || (wParam == VK_BACK ))
                {
					clearAllFlags();
					//Sleep(5000);
	      		}
                 
			    if( isalpha(ch)||wParam == VK_SPACE)   //---If key is pressed and is not a control key---//
					{                        
							if (((DWORD)lParam & 0x80000000)==0x000000000)  //---If key is pressed and is not a control key---//
							{
										findKannadaCharacters(ch);									//---Find the glyph code--//
                                        pushBackspaces();
							}
							else 
							{
                                        pushKeys();
										if(WIN_NT_SERVER)
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
							  if(wParam != VK_SHIFT)
							  clearAllFlags();

                              return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
					}
                    
			 	if((isalpha(ch)||wParam == VK_SPACE)&&!(GetKeyState(VK_MENU) & 0x80))    //---If the key pressed is a alpha key and when not
				{                                                  //---- Alt is down posts only the the promted message--//
                              return TRUE;
                }
				else
                return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
                              //---Call the next hook procedure in the hook chain---//
		
		  }	
		  else
          return CallNextHookEx(ghKeyHook,nCode,wParam,lParam); 
}




LRESULT __stdcall callWndRetProc(int nCode,WPARAM wParam,LPARAM lParam)
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

BOOL EXPORTED_DLL_FUNCTION InstallKeyboardHookNetravathiExpEXP(HWND hWnd)
{
	InstallKeyboardHookNetravathi();

	return TRUE;
}

//---------------Insatalls-the-Hook---//---This-is -called-by-the-.exe---//
BOOL __stdcall InstallKeyboardHookNetravathi() 
{

		 // isWinNTServer();
          BOOL bSuccess = FALSE;
          if( !ghKeyHook) 
          {
                    glpfnHookProc = (HOOKPROC) SetKeyBoardNetravathi;
                    bSuccess = (NULL != ( ghKeyHook = ::SetWindowsHookEx (WH_KEYBOARD, glpfnHookProc,ghInstance, NULL)));
                    ghCallWndProcRetHook = ::SetWindowsHookEx (WH_CALLWNDPROCRET, (HOOKPROC)callWndRetProc,ghInstance, NULL);
          }
          return bSuccess;
}


//---------------Un-Insatalls-the-Hook---//---This-is -called-by-the-.exe---//
BOOL __stdcall DeInstallKeyboardHookNetravathi()
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


CNetravathiApp::CNetravathiApp()
{
          // TODO: add construction code here,
          // Place all significant initialization in InitInstance
	//isWinNTServer();
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CNetravathiApp object

CNetravathiApp theApp;

BOOL CNetravathiApp::InitInstance() 
{
          // TODO: Add your specialized code here and/or call the base class
		  
          AFX_MANAGE_STATE(AfxGetStaticModuleState());
		  ghInstance = AfxGetInstanceHandle();
          return TRUE;
          }
int CNetravathiApp::ExitInstance() 
{
          // TODO: Add your specialized code here and/or call the base class
                    DeInstallKeyboardHookNetravathi();
                    return CWinApp::ExitInstance();
}


BOOL CNetravathiApp::PreTranslateMessage(MSG* pMsg) 
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
          //	HWND  myWnd;  //---------Window Handel---//
          
          int no_bs = kFlag.o_count;//-------number of back spae--------//
          int glp_pos = 0; //---Glyph position ----//
		  int i = 0;
          kFlag.found = FALSE;
                    
		  switch(ch)
          {
                case 'f':
                if(kFlag.c_bit == 1)
                {
					kFlag.f_bit = 1;
				}
                 
					if(isPreviousF(ch))
						kFlag.f_bit = 0;
					else
					  	kFlag.f_bit = 1;


				if((kFlag.o_bit== 1)&&kFlag.c_bit == 1)
                    {   
                              kFlag.so_bit = 1;
                              sendBackSpace(no_bs);
                              displayCharactersF(ch) ;
                              displayQueue();
					}
                    
		        else
                  if(kFlag.c_bit == 1)
				  {
                              displayCharactersF(ch) ;
                              kFlag.c_bit = 0;
                              kFlag.so_bit = 0;        
				  }

                break ;
				default:
					isPreviousF(ch);
		   }


          for(i=0;i<=4;i++)
		  {
		    if(ch==anuswaranvisarga[i].key)
			  {   
						kFlag.found = TRUE;							//----if found then set the bit 
																//---so no comparision in the further loops
						kFlag.c_bit = 0;  
						if(kFlag.previous_0 == 'E' && kFlag.previous_1 == 'd'&& ch == 'F')
						{
								  sendBackSpace(1);
								  displayDoubleCharacter(240,195);
               			}
						else
						displayCharacters(i,ANUSWARA,0) ;		//---Display --Glyphs from 0-----
																//---if previos is consonant then reset the bit;
			  }
		  }
        

		 			  
		  if(!kFlag.found)	
			{
                    if(ch == 'X')			//---if an X is press after the keys  P and j this displays ".." and return no further processing---//
					{
							switch(kFlag.previous_0)
							{
									  case 'P':
		                              case 'j':
                                        kFlag.x_bit = 1;
                                        displayCharacters(13,VOWELS,0);
                    					return ;
                                        //break;
                    
							  }  
							return;
					}//------End of Switch(previous_0)----------//
			  //	else
			  for(i=0;i<=14;i++)
			  if(ch == vowels[i].key)		// ---search the structure for the key pressed
			   { 
                              kFlag.found = 1;

                              if(kFlag.c_bit == 1)							//--- if pevious_0 character is a consonant
                              { 
								  processGuntaksharas( ch, no_bs, i, glp_pos);
								  kFlag.n_back = -1;
                              }
							  else                              //---Displays ordinary Vowels---//
							  {
											if((kFlag.previous_0 == 'R')&&(kFlag.x_bit  == 1))
											{
													  if(kFlag.s_bit == 1) //--------To Display RX followed by a consonant ie;
													  {
																sendBackSpace(1);
																displaySingleCharacter(241);
																kFlag.s_bit = 0; 
																kFlag.x_bit = 0;
													  }//-----------End of s_bit == 1------------//
													  else
													  {
																kFlag.x_bit = 0;
																sendBackSpace(2);
																displaySingleCharacter(73) ;
																displaySingleCharacter(198) ;
													  }//-----------End of else ------------//
											}//----------End of previous_0-////-------End of if x_bit == 1 --------//
											else
											{
													  kFlag.n_back = 0;	
													  displayCharacters(i,VOWELS,0) ;
													  kFlag.c_bit = 0;                                  //---if Found display corresponding glyphs
											}//----------End Of Else--------//
								}


                              if(kFlag.o_bit)                        //---If an f f_bit was set ---//
                              {
                                        displayQueue();
                                        clearQueue();
                                        kFlag.o_bit = 0;
                                        kFlag.c_bit = 0;									 //------------inserted --------now 
							  } 
			  }
		  }//----------------------End Of vowels ------------------//
          //------if found == 0 for vowels-----end------------//
          if(kFlag.found==0)
          {
                    for(i=0;i<=34;i++)
                    if(ch==consonants[i].key)		// ---search the structure for the key pressed
                    {         
						      kFlag.found = 1;
                              kFlag.c_bit = 1;
                              
						  if(kFlag.f_bit == 1)
                          {   
                                        sendBackSpace(no_bs);//------------for deleting previous ---and displaying --required glyphs
                                        setForFBit(ch,i); 
                                        kFlag.f_bit = 0 ;
                                        switch(ch)
                                        {
                                                  case 'r':
                                                  if(kFlag.so_bit == 1)
                                                  {
                                                      kFlag.so_bit = 0;	
                                                      consonants[i].k_val[5] = 231;								  
												  }
                                                  else
                                                  consonants[i].k_val[5] = 230;
                                                  break;
                                                  default:
													  if(kFlag.so_bit)				//---------inserted at 1.48 p m now ---------//
													  {
														  kFlag.so_bit = 0;
														  iVottaksharas[kFlag.o_count++] = 246;		//---------inserted at 1.48 p m now ---------//
													  }
                                        //--------end of switch------------//
										}											

								  iVottaksharas[kFlag.o_count++] = consonants[i].k_val[5];
								  kFlag.o_bit  = 1;
								  kFlag.so_bit = 1;
								  displayQueue();
						  } 
						  else
							{
									  clearQueue();    //---Clear the _Vottaksharas no-procesing further---//
									  kFlag.o_bit =  0;      //---Clear the bit so no-procesing further---//
									  displayCharacters(i,CONSONANTS,0) ;	//---if Found display corresponding glyphs
							}
					}
          kFlag.n_back = -1;
		  }

		  if(isspace(ch))
		  kFlag.c_bit = 0 ;
		  
		  if(!(isalpha(ch))&&!(GetKeyState(VK_SHIFT))||isspace(ch))
		  {
          clearQueue();
          kFlag.f_bit = 0;
		  kFlag.f_pressed_Once = 0;
		  }

if(isalpha(ch)&&(ch!='f')&&(ch!='X')&&!(kFlag.o_bit))
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

void displayCharacters(int nval,int indicator,int j)   //indictor value is 0 for anuswara ,1 for vowels , 2 for consonants
{    

int k = j ;   // --------index for glyph codes---// 

while(kFlag.n_back>=1)
	{
          
			  addKey(VK_BACK);
			  kFlag.n_back--;
	}
	if(indicator==0)	
	{
          
			  addKey(anuswaranvisarga[nval].k_val[0]);
			  kFlag.n_back = -1;
	}
	else
	if(indicator==1)	
	{
			  while(vowels[nval].k_val[k]!=-1)
			  {
						addKey(vowels[nval].k_val[k]);
						k++;
			  }
	}
	else
	if(indicator == 2)
	{
			  while(consonants[nval].k_val[k]!=-1)
			  {
						addKey(consonants[nval].k_val[k]);
						k++;
			  }
	}
kFlag.n_back = -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// This Function Post the message for the ACTIVE window of the Specified Character  in "ch"  ////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//--- ch ===>character ---//
struct chars_for_f
{
	char ch;
	int iVal[4];
}Chars_After_F[11] = {  'z' , {239 , -1 },
						'Z', {239,-1 },
						'K', {8,83,239,-1},
						'j', {8,101,239,-1},
						'J', {8,105,239,-1},
						'y', {8,105,239,-1},
						'm', {8,105,239,-1},
						'q', {8,109,239,-1},
						'b', {8,168,239,-1},
						'l', {8,175,239,-1},
						'N', {8,117,239,-1},
					};

void displayCharactersF(char ch)  //-----While f is pressed
{    

int i = 0 ;
int j = 0 ;   // --------index for glyph codes---// 
int found = FALSE;

	for(j=0;j<11;j++)
	{
		if(kFlag.previous_0 == Chars_After_F[j].ch)
		{
			found = TRUE;
			while(Chars_After_F[j].iVal[i]!=-1) 
			{
				addKey(Chars_After_F[j].iVal[i]);
				i++;
			}
		}
	}

	if(!found)
	{
		addKey(8);
		addKey(239);
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function Set The Glypha For Kha,ja,.... ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ch ===>character , gval ===> pevious_0 GlypH value//


void setGlyphsKaJaBa(char ch,int gval,int i)
{

kFlag.n_back = -1;
switch (ch)
{

          case 'a' :
          return ;
          case 'A' :
          case 'e' :
          case 'o' :
          case 'V' :
			  if(kFlag.x_bit == 1)
			  {
				  sendBackSpace(1);
			  }
			  sendBackSpace(1);
			  displaySingleCharacter(gval+1);
			  if(kFlag.x_bit ==1)
			  {
			  displaySingleCharacter(243);
			  kFlag.x_bit = 0;
			  }
			  displayCharacters(i,VOWELS,3) ;
          break;
		  
		  case 'u':
		  case 'U':
		  displayCharacters(i,VOWELS,3);
          break;

		  case 'Y' :
          if(kFlag.x_bit == 1)
		     sendBackSpace(1);
        
		  sendBackSpace(1);
          
          displaySingleCharacter(gval+1);
          if(kFlag.x_bit ==1)
          {
		  displaySingleCharacter(243);
          kFlag.x_bit = 0;
		  }
		  displaySingleCharacter(201) ;	
          if(kFlag.o_bit)                           //---If an f f_bit was set ---//
          {
           
			        displayQueue();
					displaySingleCharacter(246);
                    clearQueue();
                    kFlag.o_bit = 0;
                    kFlag.c_bit = 0;									 //------------inserted --------now 
		  } 
          displaySingleCharacter(202) ;	
          break;

          
          case 'E':
          case 'O':
          if(kFlag.x_bit == 1)
          sendBackSpace(1);

          sendBackSpace(1);
                    displaySingleCharacter(gval+1);
                    if(kFlag.x_bit ==1)
          displaySingleCharacter(243);
          
		  if(kFlag.x_bit == 1)
			kFlag.x_bit = 0;
          
		  if(kFlag.o_bit)                           //---If an f f_bit was set ---//
          {
                    displayCharacters(i-1,VOWELS,3) ;	
                    displayQueue();
                    clearQueue();
                    kFlag.o_bit = 0;
                    kFlag.c_bit = 0;									 //------------inserted --------now 
                    displaySingleCharacter(195);
		  } 
          else
          displayCharacters(i,VOWELS,3) ;	
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
                    case 'A' :
                    case 'V' :
                    displayDoubleCharacter(VK_BACK,105);
                    if(ch == 'A')
                    displaySingleCharacter(193);
                    else
                    displaySingleCharacter(203);
                    break;
                    
                    case 'u':
                    case 'U':
                    displayCharacters(i,1,3) ;
                    break;
                    
					case 'e' :
                    sendBackSpace(2);
                    displayDoubleCharacter(201,196);
                    break;
                                        
					case 'E' :
                    case 'Y' :
                    sendBackSpace(2);
                    displayDoubleCharacter(201,196);
                    
					if(ch == 'E')
                    {
                              if(kFlag.o_bit)                           //---If an f f_bit was set ---//
                              {
								        displayQueue();
                                        clearQueue();
                                        kFlag.o_bit = 0;
                                        kFlag.c_bit = 0;									 //------------inserted --------now 
							  } 
                              displaySingleCharacter(195);
					}
					else 
					if(ch == 'Y')
					{
                              if(kFlag.o_bit)                           //---If an f f_bit was set ---//
                              {
								  
								        displayQueue();
										displaySingleCharacter(246);
                                        clearQueue();
                                        kFlag.o_bit = 0;
                                        kFlag.c_bit = 0;									 //------------inserted --------now 
                              } 
                        displaySingleCharacter(202) ;	
                    }

                    break;
                    
                    case 'o' :
                    sendBackSpace(2);
                    displayDoubleCharacter(201,198);
                    break ;
          
										
			        case  'O' :
                    sendBackSpace(2);
                    if(kFlag.o_bit)                           //---If an f f_bit was set ---//
                    {
                              displaySingleCharacter(198);
                              displayCharacters(i-1,VOWELS,3) ;	
                              displayQueue();
                              clearQueue();
                              kFlag.o_bit = 0;
                              kFlag.c_bit = 0;									 //------------inserted --------now 
                              displaySingleCharacter(195);
                              } 
                    else
                                        
					displayTripleCharacter(201,198,195);
                    break;
                    }//---------End of Switch(ch)--for the characters ma,ya ------//
          break; //---------------End of the case y , m instance 1
          

		  case 'J' :				//-----------For The Characters JHA-----------//
		  switch(ch)
          {
                    case 'A' :
                    case 'V' :
						displayDoubleCharacter(VK_BACK,105);
						if(ch == 'A')
							displaySingleCharacter(193);
						else
							displaySingleCharacter(203);
					break;
                    
					case 'u':
                    case 'U':
                    displayCharacters(i,1,3) ;
                    break;
                    
					case 'e' :
                    sendBackSpace(3);
                    displayTripleCharacter(201,104,196);
                    break;
 
					case 'E' :
                    case 'Y' :
                    sendBackSpace(3);
					displayTripleCharacter(201,104,196);
                    if(ch == 'E')
                    {
						      if(kFlag.o_bit)                           //---If an f f_bit was set ---//
                              {
                                        displayQueue();
                                        clearQueue();
                                        kFlag.o_bit = 0;
                                        kFlag.c_bit = 0;									 //------------inserted --------now 
                               } 
                          displaySingleCharacter(195);
                     }
                    else 
                    if(ch == 'Y')
                    {
                              if(kFlag.o_bit)                           //---If an f f_bit was set ---//
                              {
                                                                                
								        displayQueue();
										displaySingleCharacter(246);
                                        clearQueue();
                                        kFlag.o_bit = 0;
                                        kFlag.c_bit = 0;									 //------------inserted --------now 
							  } 
                              displaySingleCharacter(202) ;	
					}
                    break;
                    
					case 'o' :
                    sendBackSpace(3);
                    displayTripleCharacter(201,104,198);
                    break ;
                    
					case  'O' :
                    sendBackSpace(3);
                    if(kFlag.o_bit)                           //---If an f f_bit was set ---//
                    {
                              displaySingleCharacter(201);
                              displayDoubleCharacter(104,198);
                              displayQueue();
                              clearQueue();
                              kFlag.o_bit = 0;
                              kFlag.c_bit = 0;									 //------------inserted --------now 
                              displaySingleCharacter(195);
					} 
                    else
                         displayFourCharacter(201,104,198,195);
                    break;
                    }//-------------------End of Switch(ch)----for JHA ---------------//
                    break ;
          }//---------End of Switch(pevious_0)--------//
kFlag.n_back = -1;
}//-------End OF The function setGlyphsForJMY----------//


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// This Function Displays GuniSu for of the previosly entered character /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void displayGunisu(char ch)
{

int position = 0;
int k = 0;
char char_1 = kFlag.previous_0;

for(int i=0;i<=34;i++)
if(char_1== consonants[i].key)		// ---search the structure//for the key pressed 
{
          position = i;			

}
switch(char_1)
{

          case 'z' :				//---for these characters display 
          //---the corresponding Gunisu ---//
          case 'Z' :
          case 'N' :
          //	::PostMessage(myWnd,WM_CHAR,194,(LPARAM)1);
          displaySingleCharacter(194);
          break;

          case 'K':				//---for these characters send a single 
          //---back space and display the corresponding Gunisu---//
          case 'j':
          if(kFlag.x_bit == 1)
          displaySingleCharacter(VK_BACK);
          /*------common back space-----*/
          displaySingleCharacter(VK_BACK);
          
		  while(gunisu[position].k_val[k]!=-1)
          {
                    addKey(gunisu[position].k_val[k]);
                    k++;
          }
          if(kFlag.x_bit == 1)
          {
                    displaySingleCharacter(251);
                    kFlag.x_bit = 0; 
          }
          break ;
          
		  case 'P':
          if(kFlag.x_bit == 1)
          sendBackSpace(1);

          sendBackSpace(3);
          displayDoubleCharacter(166,252);
          if(kFlag.x_bit == 1)
          {
                    displaySingleCharacter(251);
                    kFlag.x_bit = 0; 
		  }
          break;
          
		  case 'q':
          case 'b':
          case 'l':
          //::PostMessage(myWnd,WM_CHAR,VK_BACK,(LPARAM)1);
		  sendBackSpace(1);
          while(gunisu[position].k_val[k]!=-1)
          {
                    addKey(gunisu[position].k_val[k]);
                   k++;
          }
          break;
 
		  case 'D' :
          sendBackSpace(3);
          displayDoubleCharacter(162,252);
          break;
          
		  case 'W' :
          sendBackSpace(3);
          displayDoubleCharacter(114,252);
          break;
          
		  case 'B' :
          case 'm' :	
          //---for these characters send a triple back 
          //---space and display the corresponding Gunisu---//
          sendBackSpace(3);
          while(gunisu[position].k_val[k]!=-1)
          {
                    addKey(gunisu[position].k_val[k]);
                    k++;
          }
          break;
                    case 'J':		//---for these characters send a four back space 
          
						
						//---and display the corresponding Gunisu---//
          case 'y':
          sendBackSpace(4);
          while(gunisu[position].k_val[k]!=-1)
          {
                    addKey(gunisu[position].k_val[k]);
                    k++;
          }
          break;
          case 'd':
          sendBackSpace(2);
          while(gunisu[position].k_val[k]!=-1)
          {
                    addKey(gunisu[position].k_val[k]);
                    k++;
          }
          break;

          default :		//---for these characters send a double 
          //---back space and display the corresponding Gunisu---//
          sendBackSpace(2);//-----------replaced by 2 vk_back meassages-----------// 
          while(gunisu[position].k_val[k]!=-1)
          {
                    
                    addKey(gunisu[position].k_val[k]);
                    k++;
		  }     
	}
	if(ch == 'I')
	{
          if(kFlag.o_bit)                        //---If an f f_bit was set ---//
          {
                    displayQueue();
                    clearQueue();
                    kFlag.o_bit = 0;
                    kFlag.c_bit = 0;									 //------------inserted --------now 
		  } 
                    displaySingleCharacter(195);
	}
kFlag.n_back = -1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  This Function copies the character the in ch ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setForFBit(char ch,int i)  //--------The Position i ,ch the character ---//
{

	int j = 0 ;
	switch(kFlag.previous_0)
	{
			  case 'K' :
			  case 'Z' :
			  case 'j' :
			  case 'z' :
			  case 'q' :
			  case 'N' :
			  case 'b' :
			  case 'l' :
			  kFlag.n_back = 2;
			  for(j=0;j<=34;j++)
			  if(kFlag.previous_0==consonants[j].key)
			  {
						displayCharacters(j,CONSONANTS,0);
			  }
			  break;

			  case 'J' :
			  case 'y' :
			  kFlag.n_back = 5;
			  for(j=0;j<=34;j++)
			  if(kFlag.previous_0==consonants[j].key)
			  {
						displayCharacters(j,CONSONANTS,0);
			  }
			  break;
			  
			  case 'm' :
			  kFlag.n_back = 4;
			  
			  for(j=0;j<=34;j++)
			  if(kFlag.previous_0==consonants[j].key)
			  {
						displayCharacters(j,CONSONANTS,0);
			  }
			  break;
			  
			  default:
			  kFlag.n_back = 1;
			  displayCharacters(0,CONSONANTS,1) ;
    }
kFlag.f_bit = 0;
kFlag.f_pressed_Once = 0;
kFlag.o_bit = 1;
kFlag.n_back = -1;
} 


//-----------------------For P with ..--------------------------//
void displayCharacterPHI(char ch,int i)
{
switch(ch)
{
          case 'A' :
          case 'V' :
          case 'e' :
          case 'E' :
          case 'o' :
          case 'O' :
          case 'Y' :
          sendBackSpace(4);
          displayFourCharacter(165,243,115,192);
          break;					
                    }//------End of Switch(ch)-----//
}




void copyLastChar0(char ch)
{   
	kFlag.previous_1 = kFlag.previous_0;
	kFlag.previous_0 = ch;
}



void displayQueue()
{
	int i = 0;
	while(iVottaksharas[i]!=-1)
	{
			  addKey(iVottaksharas[i]);
			  i++;
	}
}


void clearQueue()
{
	for (int i=0;i<=10;i++)
	iVottaksharas[i] = -1;
	kFlag.o_count = 0;
	kFlag.o_bit  = 1;
	kFlag.so_bit = 1;
}



void displayChar(char ch)
{
	for(int i=0;i<=34;i++)
	if(ch == consonants[i].key)
	addKey((WPARAM)consonants[i].k_val);
}

int isPreviousF(char ch)
{
	f2 = f1;
	f1 = ch;
	if(ch == 'f' && f2 == 'f')
	{
		kFlag.c_bit = 0;
		return 1;
	}
	else
		return 0;
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