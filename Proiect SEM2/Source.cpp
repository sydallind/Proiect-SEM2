#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>
#include "resource.h"

#pragma comment(linker, \
  "\"/manifestdependency:type='Win32' "\
  "name='Microsoft.Windows.Common-Controls' "\
  "version='6.0.0.0' "\
  "processorArchitecture='*' "\
  "publicKeyToken='6595b64144ccf1df' "\
  "language='*'\"")

#pragma comment(lib, "ComCtl32.lib")

TCHAR text1[1024];

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int m, n;
char rez[1028],rez2[1028],aux1[1028];

void ASCII(char *s, TCHAR v[1024])
{
	int i = 0, nr = 0;
	char c;
	for (i = 0; i < strlen(s); i++)
	{
		c = *(s + i);
		while (c != NULL)
		{
			v[nr++] = c % 2 + 48;
			c /= 2;
		}
		v[nr++] = 48;
	}
	int nr1 = nr;
	nr += 3;
	for (nr1; nr1 < nr; nr1++)
		v[nr1] = 48;
}

char *scadere(char s[1028], char CRCbin[5])
{
	char aux[5], kon = 0;
	strcpy(rez, s);
	int k = 0;
	while (rez[k] > 0)
		k++;
	rez[k] = '\0';
	s[k] = '\0';
	for (int i = 0; i < strlen(rez) - 4; i++)
	{
		kon = 0;
		while (rez[i] != 49 && i < strlen(rez) - 4)
			i++;
		if (strncmp(rez + i, CRCbin, 4) == 0)
		{
			for (int j = i; j <= i + 3; j++)
				rez[j] = 48;
			i += 3;
			kon = 0;
		}
		else for (int j = 0; j < 4; j++)
		{
			if (rez[i + j] == CRCbin[j]) rez[i + j] = 48;
			else rez[i + j] = 49;
		}
	}
	int i = strlen(rez) - 4;
	if (rez[i] == 49)
		for (int j = 0; j < 4; j++)
		{
			if (rez[i + j] == CRCbin[j]) rez[i + j] = 48;
			else rez[i + j] = 49;
		}
	int j = strlen(rez);
	for (i = 0; i < j - 3; i++)
		strcpy(rez, rez + 1);
	return rez;
}

INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			SendMessage(hDlg, WM_CLOSE, 0, 0);
			return TRUE;
		case IDC_BUTTON1:
		{
			TCHAR v2[1028];
			char rez2[1024];
			GetDlgItemText(hDlg, IDC_EDIT5, v2, 1028);
			strcpy(rez2, scadere(v2, "1011"));
			if (strcmp(aux1, rez2) == 0) SetDlgItemText(hDlg, IDC_EDIT6, "Nu exista erori la transmitere");
			else SetDlgItemText(hDlg, IDC_EDIT6, "Exista erori la transmitere");
			break;
		}
		case IDC_BUTTON2:
		{
			TCHAR v1[1028];
			char rez[1024];
			GetDlgItemText(hDlg, IDC_EDIT1, text1, 1024);
			ASCII(text1, v1);
			strcpy(aux1,scadere(v1, "1011"));
			SetDlgItemText(hDlg, IDC_EDIT2, v1);
			SetDlgItemText(hDlg, IDC_EDIT5, v1);
			break;
		}
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hDlg, TEXT("Close the program?"), TEXT("Close"),
			MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			DestroyWindow(hDlg);
		}
		return TRUE;

	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}
	return FALSE;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE h0, LPTSTR lpCmdLine, int nCmdShow)
{
	HWND hDlg;
	MSG msg;
	BOOL ret;

	InitCommonControls();
	hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogProc, 0);
	ShowWindow(hDlg, nCmdShow);

	while ((ret = GetMessage(&msg, 0, 0, 0)) != 0) {
		if (ret == -1)
			return -1;

		if (!IsDialogMessage(hDlg, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
};