
// d8888b. db    db       d8888b. d8888b. d88888b .d8888.  .d88b.  d8888b. d88888b db    db
// 88  `8D `8b  d8'       88  `8D 88  `8D 88'     88'  YP .8P  Y8. 88  `8D 88'     88    88
// 88oooY'  `8bd8'        88oooY' 88oobY' 88ooooo `8bo.   88    88 88   88 88ooooo Y8    8P
// 88~~~b.    88          88~~~b. 88`8b   88~~~~~   `Y8b. 88    88 88   88 88~~~~~ `8b  d8'
// 88   8D    88          88   8D 88 `88. 88.     db   8D `8b  d8' 88  .8D 88.      `8bd8'
// Y8888P'    YP          Y8888P' 88   YD Y88888P `8888Y'  `Y88P'  Y8888D' Y88888P    YP

#include <iostream>
#include <windows.h>
#include <iostream>
#include <vector>
#include <conio.h> 
#include <TlHelp32.h>
#include <stdio.h> 
#include <tchar.h>  
 

using namespace std;

void Menus(int enume);
void AplicarOpcao(int menu, int opcao);
void DRAW_RECT(int posx, int posy, int tamx, int tamy, int r, int g, int b);
void DRAW_TEXT(int posx, int posy, int textor, int textog, int textob);
int main();

/// <summary>
/// Enumerador de Menus
/// </summary>
enum Menus
{
	Fechado,
	Principal,
	Cores,
};

/// <summary>
/// Enumerador de Cores
/// </summary>
enum Cores
{
	Preto,
	AzulMarinho,
	VerdeEscuro,
	Aqua,
	Vermelho,
	Violeta,
	Cinza,
	CinzaEscuro,
	AzulEscuro,
	VerdeLima,
	Cyano,
};

#pragma region GAME CONFIG
LPCWSTR Jogo = TEXT("blablabla");		//Nome da janela do jogo
LPCWSTR Jogo_exe = TEXT("blabla.exe");		//Nome do executavel do jogo .exe
#pragma endregion

#pragma region LAYOUT
int x = 50;									//Posicao X inicial do menu
int y = 50;									//Posicao Y inicial do menu
int transparencia = 230;					//Transparencia do menu. Valor max = 255
bool showhide = true;						//Bool usada para exibir/ocultar o menu
int posX = 70;								//Posicao X inicial do menu
int posY = 150;								//Posicao Y inicial do menu
int width = 300;							//Largura do mod
int height = 450;							//Altura do mod
int velocidade = 100;						//Velocidade da navegacao. Valor Min = 1,
int menuAtual = 1;							//Index usada para setar o menu que esta sendo exibido atualmente
int menuAnterior = 1;						//Index identificando o menu anterior
int opcaoAtual = 1;							//Index da opcao atual ao mudar de menu
int ponteiroOpcao;							//Index da opcao na navegaçao do menu
int maxOpcoes = 10;							//Numero max de opcoes do menu atual
int corBanner = 30;							//Cor do Banner. Consulte o enumedor de cores para ver outras opcoes
int corScroller = 30;						//Cor do scroller de opcoes . Consulte o enumedor de cores para ver outras opcoes
int corScroller2 = CinzaEscuro;				//Cor de fundo das opcoes. Consulte o enumedor de cores para ver outras opcoes
bool Detach = false;						//Bool usada para desativar o menu permanentemente
std::string espacamentoMenu = "   ";		//Espacamento da direita das opcoes. pode ser alterado caso quiser

#pragma endregion

#pragma region EXEMPLOS
//AddInt
int intss = 1;

//AddFloat
float flouut = 1.0;

//AddBool
bool Booul = false;

//AddArray
int ArrayIndex = 0;
std::string Arrays[11] = { "Paulo", "Ana", "Carlos", "Eduardo", "Pedro", "Maria", "Joao", "Alborguetti", "Pedro de Lara", "Anibal", "Chris" };

#pragma endregion

#pragma region CONSOLE DESIGN

/// <summary>
/// Define o tamanho da fonte do menu
/// </summary>
void tamanhoFonte(int tamanho)
{
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX;
    lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	lpConsoleCurrentFontEx->dwFontSize.X = tamanho;
	lpConsoleCurrentFontEx->dwFontSize.Y = tamanho;
	swprintf_s(lpConsoleCurrentFontEx->FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, lpConsoleCurrentFontEx); 
}

/// <summary>
/// Define a cor do menu
/// </summary>
void SetMenuColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

/// <summary>
/// Mantem o menu sob outras janelas
/// </summary>
void SetTopMost(HWND hWnd)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, posX, posY, width, height, SWP_SHOWWINDOW);
}

/// <summary>
/// Desativa o menu
/// </summary>
void SetBOTTOM(HWND hWnd)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, posX, posY, width, height, SWP_HIDEWINDOW);
}

/// <summary>
/// Start do menu, onde faz todas as configuracoes de layout
/// </summary>
void MenuSetWindow(int posX, int posY, int width, int height, bool Transparent)
{
	HWND console_window = GetConsoleWindow();
	if (Transparent == true)
	{
		SetWindowLong(console_window, GWL_EXSTYLE,
		GetWindowLong(console_window, GWL_EXSTYLE) & !WS_EX_TRANSPARENT & !WS_EX_RIGHTSCROLLBAR);
	}
	SetLayeredWindowAttributes(console_window, 0, transparencia, LWA_ALPHA);
	SetWindowPos(console_window, 0, posX, posY, width, height, SWP_NOZORDER);
	HWND hWnd = GetConsoleWindow();
	RECT rcScr, rcWnd, rcClient;
	RECT aaa;
	GetWindowRect(hWnd, &rcWnd);
	GetWindowRect(hWnd, &aaa);
	GetWindowRect(GetDesktopWindow(), &rcScr);
	GetClientRect(hWnd, &rcClient);
	SetWindowRgn(hWnd, CreateRectRgn(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom), TRUE);
}

/// <summary>
/// Void usada para atualizar o layout, caso seja modificado valores pelo menu
/// </summary>
void UpdateMenuLayout()
{
	HWND console_window = GetConsoleWindow();
	SetLayeredWindowAttributes(console_window, 0, transparencia, LWA_ALPHA);
	HWND hWnd = GetConsoleWindow();
	RECT rcScr, rcWnd, rcClient;
	GetWindowRect(hWnd, &rcWnd);
	GetWindowRect(GetDesktopWindow(), &rcScr);
	GetClientRect(hWnd, &rcClient);
	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
	SetWindowRgn(hWnd, CreateRectRgn(posX, posY, width, height), TRUE);
	ShowWindow(hWnd, 1);
	SetMenuColor(3);
	SetConsoleTextAttribute(console_window, 100);
	MenuSetWindow(posX, posY, width, height, 0);
	SetTopMost(hWnd);
	tamanhoFonte(15);
	//Menus(1);
}

/// <summary>
/// Toggle que exibe/esconde o menu
/// </summary>
void MenuShowHide()
{
	if (GetAsyncKeyState(VK_DELETE))
	{
		HWND hConsole = GetConsoleWindow();
		if (showhide == false)
		{
			showhide = true;
			SetTopMost(hConsole);
			Sleep(500);
		}
		else
		{
			showhide = false;
			SetBOTTOM(hConsole);
			Sleep(500);
		}
	}
}

#pragma endregion

#pragma region ADDOPTIONS 

/// <summary>
/// Adiciona uma opcao simples, onde clica e executa algo
/// </summary>
/// <param name="Texto da opcao que sera exibido na tela"></param>
/// <param name="Numero da opcao na tela"></param>
void AddOption(std::string Texto, int opcao = 10000)
{
	if (opcao == opcaoAtual)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller);
		std::cout << espacamentoMenu << Texto << std::endl;
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller2);
		std::cout << espacamentoMenu << Texto << std::endl;
	}
}

/// <summary>
/// Adiciona os creditos no rodape do menu
/// </summary>
/// <param name="Nome do criador"></param>
void AddCredits(std::string Texto)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << espacamentoMenu << Texto << std::endl;
}

 
/// <summary>
/// Adiciona um titulo e subtitulo para o menu
/// </summary>
/// <param name="Titulo"></param>
/// <param name="Subtitulo"></param>
/// <param name="Numero maximo de opcoes do menu atual"></param>
void AddTitle(std::string Texto , std::string SubTexto, int maxOpcoesMenuAtual)
{
	//Title
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, corBanner);
	//tamanhoFonte(intss);
	std::cout << espacamentoMenu << Texto << "    " << std::endl;
	//Subtitle 
	SetConsoleTextAttribute(hConsole, 12);
	//tamanhoFonte(18);
	std::cout << espacamentoMenu << SubTexto << "   " << opcaoAtual << "/" << maxOpcoes << "    " << std::endl;
	maxOpcoes = maxOpcoesMenuAtual;
	tamanhoFonte(15);
}

/// <summary>
/// Usado para adicionar uma opcao que precise ativar/desativar. Ex: God Mod
/// </summary>
/// <param name="Texto da opcao"></param>
/// <param name="BOOL relacionada a funcao que quer ativar"></param>
/// <param name="Numero da opcao no menu"></param>
void AddBool(std::string Texto, bool boleta, int opcao)
{
	if (opcao == opcaoAtual)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller);
		if (boleta)
			std::cout << espacamentoMenu << Texto << ": Ativado" << std::endl;
		else
			std::cout << espacamentoMenu << Texto << ": Desativado" << std::endl;
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller2);
		if (boleta)
			std::cout << espacamentoMenu << Texto << ": Ativado" << std::endl;
		else
			std::cout << espacamentoMenu << Texto << ": Desativado" << std::endl;
	}
}


/// <summary>
/// Usado para adicionar opcoes onde voce pode alterar o valor de um INT
/// </summary>
/// <param name="Texto da opcao"></param>
/// <param name="Variavel INT que voce quer modificar"></param>
/// <param name="Numero da opcao no menu"></param>
void AddInt(std::string Texto, int inteiro, int opcao)
{
	if (opcao == opcaoAtual)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller);
		std::cout << espacamentoMenu << Texto << " < " << inteiro << " >" << std::endl;
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller2);
		std::cout << espacamentoMenu << Texto << " < " << inteiro << " >" << std::endl;
	}
}




/// <summary>
/// Usado para adicionar opcoes onde voce pode alterar o valor de um FLOAT
/// </summary>
/// <param name="Texto da opcao"></param>
/// <param name="Variavel FLOAT que voce quer modificar"></param>
/// <param name="Numero da opcao no menu"></param>
void AddFloat(std::string Texto, float flutuante, int opcao)
{
	if (opcao == opcaoAtual)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller);
		std::cout << espacamentoMenu << Texto << " < " << flutuante << " >" << std::endl;
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller2);
		std::cout << espacamentoMenu << Texto << " < " << flutuante << " >" << std::endl;
	}
}

/// <summary>
/// Usado para adicionar opcoes onde voce pode alterar o valor de um Array
/// </summary>
/// <param name="Texto da opcao"></param>
/// <param name="Variavel INT que vais er usada como ponteiro no array"></param>
/// <param name="Array que sera percorrido pelo ponteiro"></param>
/// <param name="Numero da opcao no menu"></param>
void AddArray(std::string Texto, int ponteiro, std::string arrays[], int opcao)
{
	if (opcao == opcaoAtual)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller);
		std::cout << espacamentoMenu << Texto << " < " << arrays[ponteiro] << " >" << std::endl;
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller2);
		std::cout << espacamentoMenu << Texto << " < " << arrays[ponteiro] << " >" << std::endl;
	}
}

/// <summary>
/// Usado para dar um espacamento entre as opcoes
/// </summary>
/// <param name="Texto do espaco (opcional)"></param>
/// <param name="Numero de linhas que ficarao em branco"></param>
void AddBreak(std::string Texto = "", int linhas = 1)
{
	int linha = 1;
	while (linha <= linhas)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller2);
		std::cout << "" << std::endl;
		linha++;
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << espacamentoMenu << Texto << std::endl;
}


/// <summary>
/// Usado no inicio de cada menu, para definir o menu anterior, caso o usuario queira voltar para o menu anterior
/// </summary>
/// <param name="ENUM ou INT do menu"></param>
void DefinirMenuAnterior(int menu)
{
	menuAnterior = menu;
	//opcaoAtual = 1;
}

/// <summary>
/// Muda para um menu/submenu especifico
/// </summary>
/// <param name="ENUM ou INT correspondente ao menu"></param>
void ProxMenu(int menu)
{
	menuAtual = menu;
	opcaoAtual = 1;
}

/// <summary>
/// Volta ao menu anterior.     
/// OBS: Use o DefinirMenuAnterior() antes de usar essa funcao
/// </summary>
void MenuAnterior()
{
	menuAtual = menuAnterior;
	opcaoAtual = 1;
}

/// <summary>
/// Funcao usada para desativar o menu. Apos chamada, voce nao podera mais usar o menu
/// </summary>
void detachMenu()
{
	Detach = true;
	main();
	system("exit");
 }

#pragma endregion

#pragma region CONTROLES

/// <summary>
/// Void que checka as teclas pressionadas, para navegar/abrir/fechar/selecionar
/// </summary>
void Controles()
{
	if (showhide == true && menuAtual != 0)
	{
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (opcaoAtual == maxOpcoes)
			{
				opcaoAtual = 1;
				system("cls");
				Menus(menuAtual);
				Sleep(velocidade);
			}
			else
			{
				opcaoAtual++;
				system("cls");
				Menus(menuAtual);
				Sleep(velocidade);
			}
		}
		if (GetAsyncKeyState(VK_UP))
		{
			if (opcaoAtual == 1)
			{
				opcaoAtual = maxOpcoes;
				system("cls");
				Menus(menuAtual);
				Sleep(velocidade);
			}
			else
			{
				opcaoAtual--;
				system("cls");
				Menus(menuAtual);
				Sleep(velocidade);
			}
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			AplicarOpcao(menuAtual, opcaoAtual);
			system("cls");
			Menus(menuAtual);
			Sleep(velocidade);
		}
		if (GetAsyncKeyState(VK_BACK))
		{
			if (menuAtual != Principal)
			{
				system("cls");
				MenuAnterior();
				Menus(menuAtual);
				Sleep(velocidade);
			}
			else
			{
				HWND hConsole = GetConsoleWindow();
				showhide = false;
				SetBOTTOM(hConsole);
			}
		} 
	}
}
#pragma endregion

#pragma region PONTEIROS DE MEMORIA
/// <summary>
/// Funcao usada para pegar o endereço de um jogo, para poder usar jogo.exe + ponteiro, como no Cheat Engine
/// </summary>
/// <param name="ID do processo"></param>
/// <param name="Nome"></param>
/// <returns></returns>
uintptr_t GetModuleBaseAddress(DWORD procId, const TCHAR* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!lstrcmpi(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

/// <summary>
/// Funcao usada para percorer 1 ponteiro a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <returns></returns>
DWORD Jump_Ponteiro1(DWORD EnderecoAdicional, DWORD ponteiro1)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	return base;
}

/// <summary>
///  Funcao usada para percorer 2 ponteiros a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <param name="ponteiro2"></param>
/// <returns></returns>
DWORD Jump_Ponteiro2(DWORD EnderecoAdicional, DWORD ponteiro1, DWORD ponteiro2)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	DWORD address2 = 0;
	ReadProcessMemory(hProc, (void*)address, &address2, sizeof(address2), nullptr);
	address2 += ponteiro2;
	return address2;
}
/// <summary>
/// Funcao usada para percorer 3 ponteiros a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <param name="ponteiro2"></param>
/// <param name="ponteiro3"></param>
/// <returns></returns>
DWORD Jump_Ponteiro3(DWORD EnderecoAdicional, DWORD ponteiro1, DWORD ponteiro2, DWORD ponteiro3)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	DWORD address2 = 0;
	ReadProcessMemory(hProc, (void*)address, &address2, sizeof(address2), nullptr);
	address2 += ponteiro2;
	DWORD address22 = 0;
	ReadProcessMemory(hProc, (void*)address2, &address22, sizeof(address22), nullptr);
	address22 += ponteiro3;
	return address22;
}
/// <summary>
/// Funcao usada para percorer 4 ponteiros a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <param name="ponteiro2"></param>
/// <param name="ponteiro3"></param>
/// <param name="ponteiro4"></param>
/// <returns></returns>
DWORD Jump_Ponteiro4(DWORD EnderecoAdicional, DWORD ponteiro1, DWORD ponteiro2, DWORD ponteiro3, DWORD ponteiro4)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	DWORD address2 = 0;
	ReadProcessMemory(hProc, (void*)address, &address2, sizeof(address2), nullptr);
	address2 += ponteiro2;
	DWORD address22 = 0;
	ReadProcessMemory(hProc, (void*)address2, &address22, sizeof(address22), nullptr);
	address22 += ponteiro3;
	DWORD address222 = 0;
	ReadProcessMemory(hProc, (void*)address22, &address222, sizeof(address222), nullptr);
	address222 += ponteiro4;
	return address222;
}
/// <summary>
/// Funcao usada para percorer 5 ponteiros a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <param name="ponteiro2"></param>
/// <param name="ponteiro3"></param>
/// <param name="ponteiro4"></param>
/// <param name="ponteiro5"></param>
/// <returns></returns>
DWORD Jump_Ponteiro5(DWORD EnderecoAdicional, DWORD ponteiro1, DWORD ponteiro2, DWORD ponteiro3, DWORD ponteiro4, DWORD ponteiro5)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	DWORD address2 = 0;
	ReadProcessMemory(hProc, (void*)address, &address2, sizeof(address2), nullptr);
	address2 += ponteiro2;
	DWORD address22 = 0;
	ReadProcessMemory(hProc, (void*)address2, &address22, sizeof(address22), nullptr);
	address22 += ponteiro3;
	DWORD address222 = 0;
	ReadProcessMemory(hProc, (void*)address22, &address222, sizeof(address222), nullptr);
	address222 += ponteiro4;
	DWORD address2222 = 0;
	ReadProcessMemory(hProc, (void*)address222, &address2222, sizeof(address2222), nullptr);
	address2222 += ponteiro5;
	return address2222;
}
/// <summary>
/// Funcao usada para percorer 6 ponteiros a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <param name="ponteiro2"></param>
/// <param name="ponteiro3"></param>
/// <param name="ponteiro4"></param>
/// <param name="ponteiro5"></param>
/// <param name="ponteiro6"></param>
/// <returns></returns>
DWORD Jump_Ponteiro6(DWORD EnderecoAdicional, DWORD ponteiro1, DWORD ponteiro2, DWORD ponteiro3, DWORD ponteiro4, DWORD ponteiro5, DWORD ponteiro6)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	DWORD address2 = 0;
	ReadProcessMemory(hProc, (void*)address, &address2, sizeof(address2), nullptr);
	address2 += ponteiro2;
	DWORD address22 = 0;
	ReadProcessMemory(hProc, (void*)address2, &address22, sizeof(address22), nullptr);
	address22 += ponteiro3;
	DWORD address222 = 0;
	ReadProcessMemory(hProc, (void*)address22, &address222, sizeof(address222), nullptr);
	address222 += ponteiro4;
	DWORD address2222 = 0;
	ReadProcessMemory(hProc, (void*)address222, &address2222, sizeof(address2222), nullptr);
	address2222 += ponteiro5;
	DWORD address22222 = 0;
	ReadProcessMemory(hProc, (void*)address2222, &address22222, sizeof(address22222), nullptr);
	address22222 >= ponteiro6;
	return address22222;
}
/// <summary>
/// Funcao usada para percorer 7 ponteiros a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <param name="ponteiro2"></param>
/// <param name="ponteiro3"></param>
/// <param name="ponteiro4"></param>
/// <param name="ponteiro5"></param>
/// <param name="ponteiro6"></param>
/// <param name="ponteiro7"></param>
/// <returns></returns>
DWORD Jump_Ponteiro7(DWORD EnderecoAdicional, DWORD ponteiro1, DWORD ponteiro2, DWORD ponteiro3, DWORD ponteiro4, DWORD ponteiro5, DWORD ponteiro6, DWORD ponteiro7)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	DWORD address2 = 0;
	ReadProcessMemory(hProc, (void*)address, &address2, sizeof(address2), nullptr);
	address2 += ponteiro2;
	DWORD address22 = 0;
	ReadProcessMemory(hProc, (void*)address2, &address22, sizeof(address22), nullptr);
	address22 += ponteiro3;
	DWORD address222 = 0;
	ReadProcessMemory(hProc, (void*)address22, &address222, sizeof(address222), nullptr);
	address222 += ponteiro4;
	DWORD address2222 = 0;
	ReadProcessMemory(hProc, (void*)address222, &address2222, sizeof(address2222), nullptr);
	address2222 += ponteiro5;
	DWORD address22222 = 0;
	ReadProcessMemory(hProc, (void*)address2222, &address22222, sizeof(address22222), nullptr);
	address22222 >= ponteiro6;
	DWORD address222222 = 0;
	ReadProcessMemory(hProc, (void*)address22222, &address222222, sizeof(address222222), nullptr);
	address222222 += ponteiro7;
	return address222222;
}
/// <summary>
/// Funcao usada para percorer 8 ponteiros a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <param name="ponteiro2"></param>
/// <param name="ponteiro3"></param>
/// <param name="ponteiro4"></param>
/// <param name="ponteiro5"></param>
/// <param name="ponteiro6"></param>
/// <param name="ponteiro7"></param>
/// <param name="ponteiro8"></param>
/// <returns></returns>
DWORD Jump_Ponteiro8(DWORD EnderecoAdicional, DWORD ponteiro1, DWORD ponteiro2, DWORD ponteiro3, DWORD ponteiro4, DWORD ponteiro5, DWORD ponteiro6, DWORD ponteiro7, DWORD ponteiro8)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	DWORD address2 = 0;
	ReadProcessMemory(hProc, (void*)address, &address2, sizeof(address2), nullptr);
	address2 += ponteiro2;
	DWORD address22 = 0;
	ReadProcessMemory(hProc, (void*)address2, &address22, sizeof(address22), nullptr);
	address22 += ponteiro3;
	DWORD address222 = 0;
	ReadProcessMemory(hProc, (void*)address22, &address222, sizeof(address222), nullptr);
	address222 += ponteiro4;
	DWORD address2222 = 0;
	ReadProcessMemory(hProc, (void*)address222, &address2222, sizeof(address2222), nullptr);
	address2222 += ponteiro5;
	DWORD address22222 = 0;
	ReadProcessMemory(hProc, (void*)address2222, &address22222, sizeof(address22222), nullptr);
	address22222 >= ponteiro6;
	DWORD address222222 = 0;
	ReadProcessMemory(hProc, (void*)address22222, &address222222, sizeof(address222222), nullptr);
	address222222 += ponteiro7;
	DWORD address2222222 = 0;
	ReadProcessMemory(hProc, (void*)address222222, &address2222222, sizeof(address2222222), nullptr);
	address2222222 += ponteiro8;
	return address2222222;
}
/// <summary>
/// Funcao usada para percorer 9 ponteiros a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <param name="ponteiro2"></param>
/// <param name="ponteiro3"></param>
/// <param name="ponteiro4"></param>
/// <param name="ponteiro5"></param>
/// <param name="ponteiro6"></param>
/// <param name="ponteiro7"></param>
/// <param name="ponteiro8"></param>
/// <param name="ponteiro9"></param>
/// <returns></returns>
DWORD Jump_Ponteiro9(DWORD EnderecoAdicional, DWORD ponteiro1, DWORD ponteiro2, DWORD ponteiro3, DWORD ponteiro4, DWORD ponteiro5, DWORD ponteiro6, DWORD ponteiro7, DWORD ponteiro8, DWORD ponteiro9)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	DWORD address2 = 0;
	ReadProcessMemory(hProc, (void*)address, &address2, sizeof(address2), nullptr);
	address2 += ponteiro2;
	DWORD address22 = 0;
	ReadProcessMemory(hProc, (void*)address2, &address22, sizeof(address22), nullptr);
	address22 += ponteiro3;
	DWORD address222 = 0;
	ReadProcessMemory(hProc, (void*)address22, &address222, sizeof(address222), nullptr);
	address222 += ponteiro4;
	DWORD address2222 = 0;
	ReadProcessMemory(hProc, (void*)address222, &address2222, sizeof(address2222), nullptr);
	address2222 += ponteiro5;
	DWORD address22222 = 0;
	ReadProcessMemory(hProc, (void*)address2222, &address22222, sizeof(address22222), nullptr);
	address22222 >= ponteiro5;
	DWORD address222222 = 0;
	ReadProcessMemory(hProc, (void*)address22222, &address222222, sizeof(address222222), nullptr);
	address222222 += ponteiro7;
	DWORD address2222222 = 0;
	ReadProcessMemory(hProc, (void*)address222222, &address2222222, sizeof(address2222222), nullptr);
	address2222222 += ponteiro8;
	DWORD address22222222 = 0;
	ReadProcessMemory(hProc, (void*)address2222222, &address22222222, sizeof(address22222222), nullptr);
	address22222222 += ponteiro9;
	return address22222222;
}
/// <summary>
/// Funcao usada para percorer 10 ponteiros a partir de um offset e retornar o valor final
/// </summary>
/// <param name="EnderecoAdicional"></param>
/// <param name="ponteiro1"></param>
/// <param name="ponteiro2"></param>
/// <param name="ponteiro3"></param>
/// <param name="ponteiro4"></param>
/// <param name="ponteiro5"></param>
/// <param name="ponteiro6"></param>
/// <param name="ponteiro7"></param>
/// <param name="ponteiro8"></param>
/// <param name="ponteiro9"></param>
/// <param name="ponteiro10"></param>
/// <returns></returns>
DWORD Jump_Ponteiro10(DWORD EnderecoAdicional, DWORD ponteiro1, DWORD ponteiro2, DWORD ponteiro3, DWORD ponteiro4, DWORD ponteiro5, DWORD ponteiro6, DWORD ponteiro7, DWORD ponteiro8, DWORD ponteiro9, DWORD ponteiro10)
{
	DWORD pId;
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	DWORD ac_client = GetModuleBaseAddress(pId, Jogo_exe);
	DWORD base = ac_client + EnderecoAdicional;
	DWORD address = 0;
	ReadProcessMemory(hProc, (void*)base, &address, sizeof(address), nullptr);
	address += ponteiro1;
	DWORD address2 = 0;
	ReadProcessMemory(hProc, (void*)address, &address2, sizeof(address2), nullptr);
	address2 += ponteiro2;
	DWORD address22 = 0;
	ReadProcessMemory(hProc, (void*)address2, &address22, sizeof(address22), nullptr);
	address22 += ponteiro3;
	DWORD address222 = 0;
	ReadProcessMemory(hProc, (void*)address22, &address222, sizeof(address222), nullptr);
	address222 += ponteiro4;
	DWORD address2222 = 0;
	ReadProcessMemory(hProc, (void*)address222, &address2222, sizeof(address2222), nullptr);
	address2222 += ponteiro5;
	DWORD address22222 = 0;
	ReadProcessMemory(hProc, (void*)address2222, &address22222, sizeof(address22222), nullptr);
	address22222 += ponteiro6;
	DWORD address222222 = 0;
	ReadProcessMemory(hProc, (void*)address22222, &address222222, sizeof(address222222), nullptr);
	address222222 += ponteiro7;
	DWORD address2222222 = 0;
	ReadProcessMemory(hProc, (void*)address222222, &address2222222, sizeof(address2222222), nullptr);
	address2222222 += ponteiro8;
	DWORD address22222222 = 0;
	ReadProcessMemory(hProc, (void*)address2222222, &address22222222, sizeof(address22222222), nullptr);
	address22222222 += ponteiro9;
	DWORD address222222222 = 0;
	ReadProcessMemory(hProc, (void*)address22222222, &address222222222, sizeof(address222222222), nullptr);
	address222222222 += ponteiro10;
	return address222222222;
}

/// <summary>
/// Funcao usada para sobrescrever endereços de memoria, a partir de um offset 
/// </summary>
/// <param name="Offset"></param>
/// <param name="valor"></param>
/// <returns></returns>
bool SobrescreverMemoria(DWORD Offset, int valor)
{
	DWORD pId;
	//HWND hWnd = FindWindow(0, TEXT("Minecraft 1.8.9"));
	HWND hWnd = FindWindow(0, Jogo);
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	return WriteProcessMemory(hProc, (void*)Offset, &valor, sizeof(valor), nullptr); //write
}
#pragma endregion




/// <summary>
/// Void do menu principal, contendo as opcoes do principal
/// </summary>
void MenuPrincipal()
{
	DefinirMenuAnterior(Fechado);
	AddBreak();
	AddTitle("BresoDEV GUI Menu", "Menu Principal", 6);
	AddBreak();
	AddOption("Max Lifes", 1);
	AddBreak("Exemplos:", 0);
	AddInt("Int ", intss, 2);
	AddFloat("Float", flouut, 3);
	AddBool("Bool", Booul, 4);
	AddArray("Array", ArrayIndex, Arrays, 5);
	AddBreak();
	AddOption("Desativar Menu", 6);
	AddBreak("---------", 5);
	AddCredits("Created by BresoDEV"); 
}

/// <summary>
/// Menu de cores. Aconselho deixar esse menu sempre, para o usuario poder personalizar o menu do jeito que quiser
/// </summary>
void MenuDeCores()
{
	DefinirMenuAnterior(Principal);
	AddBreak();
	AddTitle("BresoDEV GUI Menu", "Cores e Posicoes", 8);
	AddBreak();
	AddInt("Cor do Topo", corBanner, 1);
	AddInt("Cor do Scrool", corScroller, 2);
	AddInt("Cor do Scrool 2", corScroller2, 3);
	AddInt("Transparencia", transparencia, 4);
	AddInt("PosX", posX, 5);
	AddInt("PosY", posY, 6);
	AddInt("Width", width, 7);
	AddInt("Height", height, 8);
	AddBreak();
	AddBreak("-----------------");
	AddCredits("Created by BresoDEV");
}

/// <summary>
/// Funcao que le o ID do menu atual e chama a void correspondente ao menu
/// </summary>
/// <param name="ENUM ou ID do menu"></param>
void Menus(int enume)
{
	switch (enume)
	{
	case Principal:		MenuPrincipal();			break;
	case Cores:			MenuDeCores();				break;
	}
}


/// <summary>
/// Funcao que executa ai clicar na opcao, fique atento aos exemplos de como construir seu mod corretamente
/// </summary>
/// <param name="menu"></param>
/// <param name="opcao"></param>
void AplicarOpcao(int menu, int opcao)
{
	HWND hWnd = FindWindow(0, Jogo);
	DWORD pId;
	GetWindowThreadProcessId(hWnd, &pId);
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	switch (menuAtual)
	{
	case Principal:
	{
		switch (opcaoAtual)
		{
		case 1:
			SobrescreverMemoria(0x72C5AC, 99);
			break;
		case 2://int option
			if (intss == 100)
				intss = 0;
			else
				intss++;
			break;
		case 3://float option
			if (flouut == 10.0)
				flouut = 1.0;
			else
				flouut += 1.0;
			break;
		case 4: //bool option
			Booul = !Booul;
			break;
		case 5: //array option
			if (ArrayIndex == 10)
				ArrayIndex = 0;
			else
				ArrayIndex++;
			break;
		case 6: 
			detachMenu();
			break;
		}
	}
	break;
	case Cores:
	{
		switch (opcaoAtual)
		{
		case 1:		if (corBanner <= 100) corBanner++; else corBanner = 0;					break;
		case 2:		if (corScroller <= 100) corScroller++; else corScroller = 0;			break;
		case 3:		if (corScroller2 <= 100) corScroller2++; else corScroller2 = 0;			break;
		case 4:		if (transparencia <= 255) transparencia++; else transparencia = 100; 	break;
		case 5:		if (posX <= 1000) posX++; else posX = 100;								break;
		case 6:		if (posY <= 1000) posY++; else posY = 100;								break;
		case 7:		if (width <= 1000) width++; else width = 100;							break;
		case 8:		if (height <= 1000) height++; else height = 100;							break;
		}
	}
	break;
	}
	UpdateMenuLayout();
	CloseHandle(hProc);
	system("cls");
	Menus(menuAtual);
	Sleep(velocidade);
}


#pragma region OUTRAS FUNCOES

/// <summary>
/// Cria um quadrado na tela. Pode ser usado para exibir fora do layout do menu
/// </summary>
/// <param name="posx"></param>
/// <param name="posy"></param>
/// <param name="tamx"></param>
/// <param name="tamy"></param>
/// <param name="r"></param>
/// <param name="g"></param>
/// <param name="b"></param>
void DRAW_RECT(int posx, int posy, int tamx, int tamy, int r, int g, int b)//LOOP
{
	//ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);
	HDC hDC_Desktop = GetDC(0);
	RECT rect = { posx, posy, tamx, tamy };
	HBRUSH blueBrush = CreateSolidBrush(RGB(r, g, b));
	FillRect(hDC_Desktop, &rect, blueBrush);
	Sleep(1);
}

/// <summary>
/// Exibe um texto na tela. Pode ser usado para exibir fora do layout do menu
/// </summary>
/// <param name="posx"></param>
/// <param name="posy"></param>
/// <param name="textor"></param>
/// <param name="textog"></param>
/// <param name="textob"></param>
void DRAW_TEXT(int posx, int posy, int textor, int textog, int textob)
{
	HDC hdc = GetDC(0);
	RECT rect = { posx, posy, 1800, 1600 };
	SetTextColor(hdc, RGB(textor, textog, textob));
	SetBkMode(hdc, TRANSPARENT);
	SetBkColor(hdc, RGB(0, 0, 0));
	DrawText(hdc, L"My text", -1, &rect, DT_LEFT);
}

/// <summary>
/// Checka se o menu esta aberto. TRUE para aberto e FALSE para fechado
/// </summary>
/// <returns></returns>
bool MenuAberto()
{
	if (showhide == true && menuAtual != 0)
		return true;
	else
		return false;
}
#pragma endregion



/// <summary>
/// Void usada para funcoes que precisam ser executadas continuamente. Note que tem 3 variavoes
/// </summary>
/// <param name="Constante: Executa sempre, independente do menu estar aberto ou nao"></param>
/// <param name="Menu aberto: So executa em loop caso o menu esteja aberto."></param>
/// <param name="Menu fechado: So executa caso o menu esteja fechado"></param>
void Loop()
{
	if (MenuAberto())
	{
		//So executa em loop caso o menu esteja aberto	 
	}
	else
	{
		//So executa caso o menu esteja fechado
	}
	//Executa sempre, independente do menu estar aberto ou nao
}

int main()
{
	if (!Detach)
	{
		UpdateMenuLayout();
		tamanhoFonte(15);
		Menus(1);
		while (!Detach)
		{
			Loop();
			Controles();
			MenuShowHide();
		}
	}
}
