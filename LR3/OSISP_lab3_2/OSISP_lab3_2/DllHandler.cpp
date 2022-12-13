#include "DllHandler.h"

namespace lab
{
    DllHandler::DllHandler() 
    {
        this->dllNames = new std::vector<LPCWSTR>();
        this->dllNames->push_back(L"..\\plugins\\drawingdll.dll");
        this->dllNames->push_back(L"..\\plugins\\anotherdrawingdll.dll");

        this->loadedDll = LoadLibrary(this->dllNames->at(0));   //хэндлер дл€ загруженной в данный момент dll

        if (loadedDll == NULL) //ошибка загрузки dll
        {
            delete(this->dllNames);
            throw std::exception();
        }

        this->loadedDllIndex = 0;
        this->loadedProc = (drawProc)GetProcAddress(this->loadedDll, this->procName); // адрес процедуры

        if (loadedProc == NULL)
        {
            delete(this->dllNames);
            FreeLibrary(this->loadedDll);
            throw std::exception();
        }
    }

    DllHandler::~DllHandler()
    {
        FreeLibrary(this->loadedDll);
        delete(this->dllNames);
    }

    const void DllHandler::draw(HDC hdc, int x, int y, int radius) //метод рисовани€
    {
        this->loadedProc(hdc, x, y, radius); //вызов процедуры рисовани€
    }

    void DllHandler::changeDll()    //мен€ет загруженную dll
    {   
        if (this->loadedDllIndex == this->dllNames->size() - 1) //если последн€€ в списке - берем 0, иначе - берем следующую
            this->loadedDllIndex = 0;
        else
            ++this->loadedDllIndex;

        FreeLibrary(this->loadedDll); //выгружает загруженную dll из пам€ти 
        this->loadedDll = LoadLibrary(this->dllNames->at(this->loadedDllIndex)); //загрузка слудующей dll
        this->loadedProc = (drawProc)GetProcAddress(this->loadedDll, this->procName); //рисование
    }
}
