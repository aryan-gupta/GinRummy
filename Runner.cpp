#include <windows.h> 

// http://faq.cprogramming.com/cgi-bin/smartfaq.cgi?answer=1044654269&id=1043284392

int main(void) {
	char szPath[] = ".\\bin\\final.exe";
	PROCESS_INFORMATION pif;  //Gives info on the thread and process for the new process
	STARTUPINFO si;          //Defines how to start the program

	ZeroMemory(&si,sizeof(si)); //Zero the STARTUPINFO struct
	si.cb = sizeof(si);         //Must set size of structure

	BOOL bRet = CreateProcess(
		szPath, //Path to executable file
		NULL,   //Command string - not needed here
		NULL,   //Process handle not inherited
		NULL,   //Thread handle not inherited
		FALSE,  //No inheritance of handles
		0,      //No special flags
		NULL,   //Same environment block as this prog
		"bin",   //Current directory - no separate path
		&si,    //Pointer to STARTUPINFO
		&pif
	);   //Pointer to PROCESS_INFORMATION

	if(bRet == FALSE) {
		MessageBox(HWND_DESKTOP,"Unable to start program","",MB_OK);
		return 1;
	}

	CloseHandle(pif.hProcess);   //Close handle to process
	CloseHandle(pif.hThread);    //Close handle to thread

	return 0;
}