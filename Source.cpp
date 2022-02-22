
#include <iostream>
#include <windows.h>
#include <iostream>
#include <vector>
#include <conio.h> 
#include <TlHelp32.h>
#include <stdio.h> 
#include <tchar.h>  
#include "enums.h"

using namespace std;

void Menus(int enume);
void AplicarOpcao(int menu, int opcao);

#pragma region GAME CONFIG
LPCWSTR Jogo = TEXT("Minecraft 1.8.9");
LPCWSTR Jogo_exe = TEXT("javaw.exe");
#pragma endregion

#pragma region LAYOUT
int x = 50;
int y = 50;
int transparencia = 230;
bool showhide = true;
int posX = 70;
int posY = 100;
int width = 300;
int height = 450;
int velocidade = 150;
int menuAtual = 1;
int menuAnterior = 1;
int opcaoAtual = 1;
int ponteiroOpcao;
int maxOpcoes = 10;
int corBanner = 30;
int corScroller = 30;
int corScroller2 = CinzaEscuro;
std::string espacamentoMenu = "   ";

#pragma endregion

#pragma region CONSOLE DESIGN
void SetMenuColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}
void SetTopMost(HWND hWnd)
{
	RECT rect;

	GetWindowRect(hWnd, &rect);



	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, posX, posY, width, height, SWP_SHOWWINDOW);
}
void SetBOTTOM(HWND hWnd)
{
	RECT rect;

	GetWindowRect(hWnd, &rect);



	SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, posX, posY, width, height, SWP_HIDEWINDOW);
}
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
void MenuLoadSetWindow()
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
	Menus(1);
}
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
void AddOption(std::string Texto, int opcao = 10000)
{  
	if (opcao == opcaoAtual)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller);
		std::cout << espacamentoMenu << Texto <<std::endl;
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller2);
		std::cout << espacamentoMenu << Texto << std::endl;
	}
}

void AddTitle(std::string Texto, int maxOpcoesMenuAtual)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, corBanner);
	std::cout << espacamentoMenu << Texto << "   " << opcaoAtual << "/" << maxOpcoes << std::endl;
	maxOpcoes = maxOpcoesMenuAtual;
}


void AddBool(std::string Texto, bool boleta, int opcao)
{
	if (opcao == opcaoAtual)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller);
		if (boleta)
			std::cout << espacamentoMenu  << Texto << ": Ativado" << std::endl;
		else
			std::cout << espacamentoMenu  << Texto << ": Desativado" << std::endl;
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



void AddInt(std::string Texto, int inteiro, int opcao)
{
	if (opcao == opcaoAtual)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller);
		std::cout << espacamentoMenu  << Texto << " < " << inteiro << " >" << std::endl;
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller2);
		std::cout << espacamentoMenu << Texto << " < " << inteiro << " >" << std::endl;
	}

}





void AddFloat(std::string Texto, float flutuante, int opcao)
{
	if (opcao == opcaoAtual)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller);
		std::cout << espacamentoMenu  << Texto << " < " << flutuante << " >" << std::endl;
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, corScroller2);
		std::cout << espacamentoMenu << Texto << " < " << flutuante << " >" << std::endl;
	}
}


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


void AddBreak(std::string Texto = "")
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, corScroller2);
	std::cout << espacamentoMenu << Texto << std::endl;
}

void DefinirMenuAnterior(int menu)
{
	menuAnterior = menu;
}

void ProxMenu(int menu)
{
	menuAtual = menu;
	opcaoAtual = 1;
}

void MenuAnterior()
{
	menuAtual = menuAnterior;
}

#pragma endregion

#pragma region CONTROLES
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
		if (GetAsyncKeyState(VK_RIGHT))
		{
			AplicarOpcao(menuAtual, opcaoAtual);
			system("cls");
			Menus(menuAtual);
			Sleep(velocidade);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			AplicarOpcao(menuAtual, opcaoAtual);
			system("cls");
			Menus(menuAtual);
			Sleep(velocidade);
		}
	}

}
#pragma endregion

#pragma region PONTEIROS DE MEMORIA
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

#pragma region EXEMPLOS
//AddInt
int intss = 1;

//AddFloat
float flouut = 1.0;

//AddBool
bool Booul = false;

//AddArray
int ArrayIndex = 0;
std::string Arrays[11] = { "Paulo", "Ana", "Carlos", "Eduardo", "Pedro", "Maria", "Joao", "Alborguetti", "Pedro de Lara", "Anibal", "Chris"};

#pragma endregion



void MenuPrincipal()
{
	DefinirMenuAnterior(Fechado);
	AddBreak();
	AddTitle("BresoDEV GUI Menu", 9);
	AddBreak();
	AddOption("Max Dinheiro", 1);
	AddOption("Submenu 2", 2);
	AddInt("Int ", intss, 3);
	AddFloat("Float", flouut, 4);
	AddBool("Bool", Booul, 5);
	AddArray("Array", ArrayIndex, Arrays, 6);
	AddBreak();
	AddBreak("-----------------");
	AddInt("Cor do Topo", corBanner, 7);
	AddInt("Cor do Scrool", corScroller, 8);
	AddInt("Cor do Scrool 2", corScroller2, 9);
	AddBreak();
	AddBreak();
	AddOption("Created by BresoDEV");
}

void sub2()
{
	DefinirMenuAnterior(Principal);
	AddBreak();
	AddTitle("Submenu 2", 3);
	AddBreak();
	AddOption("Submenu 3", 1);
	AddOption("Vazio", 2);
	AddOption("Vazio", 3);
	AddBreak();
	AddBreak("-----------------");
	AddOption("Created by BresoDEV");
}

void sub3()
{
	DefinirMenuAnterior(Submenu2);
	AddBreak();
	AddTitle("Sub 3", 3);
	AddBreak();
	AddOption("Vazio", 1);
	AddOption("Vazio", 2);
	AddOption("Vazio", 3);
	AddBreak();
	AddBreak("-----------------");
	AddOption("Created by BresoDEV");
}

void Menus(int enume)
{
	switch (enume)
	{
	case Principal: MenuPrincipal();	break;
	case Submenu2:	sub2();				break;
	case Submenu3:	sub3();				break;
	}

}




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
		case 1:  break;
		case 2: ProxMenu(Submenu2); break;
		case 3://int option
			if (intss == 100)
				intss = 0;
			else
				intss++;
			break;
		case 4://float option
			if (flouut == 10.0)
				flouut = 1.0;
			else
				flouut += 1.0;
			break;
		case 5: //bool option
			Booul = !Booul;
			break;
		case 6: //array option
			if (ArrayIndex == 10)
				ArrayIndex = 0;
			else
				ArrayIndex++;
			break;

		case 7: //array option
			if (corBanner == 1000)
				corBanner = 0;
			else
				corBanner++;
			break;

		case 8: //array option
			if (corScroller == 1000)
				corScroller = 0;
			else
				corScroller++;
			break;

		case 9: //array option
			if (corScroller2 == 10)
				corScroller2 = 0;
			else
				corScroller2++;
			break;
		}
	}
	break;
	case Submenu2:
	{
		switch (opcaoAtual)
		{

		case 1: ProxMenu(Submenu3); break;
		case 2:  break;
		case 3:  break;
		}
	}
	break;
	case Submenu3:
	{
		switch (opcaoAtual)
		{

		case 1:  break;
		case 2:  break;
		case 3:  break;
		}
	}
	break;
	}

	CloseHandle(hProc);
	system("cls");
	Menus(menuAtual);
	Sleep(velocidade);
}



int main()
{
	MenuLoadSetWindow();
	while (true)
	{
		Controles();
		MenuShowHide();
	}

}
