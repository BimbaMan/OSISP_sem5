#include "DllHandler.h"

namespace lab
{
    DllHandler::DllHandler() //мен€е длльки   класс хранит пути к длл       длл нэйм - массив строк
    {
        this->dllNames = new std::vector<LPCWSTR>();
        this->dllNames->push_back(L"..\\plugins\\drawingdll.dll");
        this->dllNames->push_back(L"..\\plugins\\anotherdrawingdll.dll");

        this->loadedDll = LoadLibrary(this->dllNames->at(0));   //хэндлер дл€ загруженной в данный момент длл

        if (loadedDll == NULL) //если после попытки грузануть длл - ничего не найдено
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

    DllHandler::~DllHandler() //деструктор освобождает ресурсы
    {
        FreeLibrary(this->loadedDll);
        delete(this->dllNames);
    }

    const void DllHandler::draw(HDC hdc, int x, int y, int radius) //метод дл€ рисовани€
    {
        this->loadedProc(hdc, x, y, radius); //вызывает процедуру
    }

    void DllHandler::changeDll()    //мен€ет загруженную длльку
    {   //индекс акт эл-та
        if (this->loadedDllIndex == this->dllNames->size() - 1) //если последн€€ в списке - берем 0, иначе - берем следующую
            this->loadedDllIndex = 0;
        else
            ++this->loadedDllIndex;

        FreeLibrary(this->loadedDll); //выгружает загруженную длл из пам€ти 
        this->loadedDll = LoadLibrary(this->dllNames->at(this->loadedDllIndex)); //грузим следующую 
        this->loadedProc = (drawProc)GetProcAddress(this->loadedDll, this->procName); //рисуем
    }
}
