//---------------------------------------------------------------------------
#ifndef MyApiUnitH
#define MyApiUnitH
//---------------------------------------------------------------------------
void MyDelay(DWORD msec);
BOOL WeAreAlone (LPSTR szName);
bool OsTypeNT();
bool SetCatalog( AnsiString path );
int Char2Hex( char ch );
void TaskManagerOn();
void TaskManagerOff();
AnsiString XOR_Crypt(AnsiString in, AnsiString pass);
#endif
