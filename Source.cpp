 
#include <iostream>
#include <windows.h>
#include <iostream>
#include <vector>
#include <conio.h> 
#include <TlHelp32.h>
#include <stdio.h> 
#include <tchar.h> 

 
int x = 50;
int y = 50;
int transparencia = 230;
bool showhide = true;
int posX = 70;
int posY = 100;
int width = 200;
int height = 450;
int velocidade = 250;
int menuAtual = 1;
int opcaoAtual = 1;
int ponteiroOpcao;
int maxOpcoes = 10;
std::string espacamentoMenu = "   ";
LPCWSTR Jogo = TEXT("Minecraft 1.8.9");
LPCWSTR Jogo_exe = TEXT("javaw.exe");



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
		HWND hWnd = FindWindow(0, TEXT("Minecraft 1.8.9"));
		GetWindowThreadProcessId(hWnd, &pId);
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
		return WriteProcessMemory(hProc, (void*)Offset, &valor, sizeof(valor), nullptr); //write
	}






void Menus(int enume);

void AddOption(std::string Texto, int opcao = 10000)
{
	if (opcao == opcaoAtual)
		std::cout << espacamentoMenu << "-> " << Texto << std::endl;
	else
		std::cout << espacamentoMenu << Texto << std::endl;
}



void AddTitle(std::string Texto, int maxOpcoesMenuAtual)
{
	std::cout << espacamentoMenu << Texto << "   " << opcaoAtual << "/" << maxOpcoes << std::endl;
	maxOpcoes = maxOpcoesMenuAtual;
}


void AddBool(std::string Texto, bool boleta, int opcao)
{
	if (opcao == opcaoAtual)
	{
		if (boleta)
			std::cout << espacamentoMenu << "-> " << Texto << ": Ativado" << std::endl;
		else
			std::cout << espacamentoMenu << "-> " << Texto << ": Desativado" << std::endl;
	}
	else
	{
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
		std::cout << "-> " << Texto << " < " << inteiro << " >" << std::endl;
	}
	else
	{
		std::cout << espacamentoMenu << Texto << " < " << inteiro << " >" << std::endl;
	}

}


void AddFloat(std::string Texto, float flutuante, int opcao)
{
	if (opcao == opcaoAtual)
	{
		std::cout << espacamentoMenu << "-> " << Texto << " < " << flutuante << " >" << std::endl;
	}
	else
	{
		std::cout << espacamentoMenu << Texto << " < " << flutuante << " >" << std::endl;
	}
}


void AddArray(std::string Texto, int ponteiro, std::string arrays[], int opcao)
{
	if (opcao == opcaoAtual)
	{
		std::cout << espacamentoMenu << "-> " << Texto << " < " << arrays[ponteiro] << " >" << std::endl;
	}
	else
	{
		std::cout << espacamentoMenu << Texto << " < " << arrays[ponteiro] << " >" << std::endl;
	}

}


void AddBreak(std::string Texto = "")
{
	std::cout << espacamentoMenu << Texto << std::endl;
}




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




void Menus(int enume)
{
	switch (enume)
	{
	case 1:
		AddBreak();
		AddTitle("171 Mod Menu", 3);
		AddBreak();
		AddOption("Max Dinheiro", 1);
		AddOption("Vazio", 2);
		AddOption("Vazio", 3);
		AddBreak();
		AddBreak("-----------------");
		AddOption("Created by BresoDEV");
		break;
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
	case 1:
		switch (opcaoAtual)
		{

		case 1:if (SobrescreverMemoria(0x14FE3F38, 200) > 0) { MessageBox(NULL, _T("Open the message box "), _T("message"), MB_OK | MB_SYSTEMMODAL); } break;
		case 2:if (SobrescreverMemoria(0x140FFEE8, 99999) > 0) {} break;
		case 3:if (SobrescreverMemoria(0x20B3B420, 99999) > 0) {} break;
		}
		break;
	}

	CloseHandle(hProc);
	

	system("cls");
	Menus(menuAtual);
	Sleep(velocidade);
}



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
			if (menuAtual == 1)
			{
				AplicarOpcao(menuAtual, opcaoAtual);
				system("cls");
				Menus(menuAtual);
				Sleep(velocidade);
			}
		}
	}
	
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
