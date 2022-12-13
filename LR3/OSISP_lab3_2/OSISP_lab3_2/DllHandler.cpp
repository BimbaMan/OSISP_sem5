#include "DllHandler.h"

namespace lab
{
    DllHandler::DllHandler() 
    {
        this->dllNames = new std::vector<LPCWSTR>();
        this->dllNames->push_back(L"..\\plugins\\drawingdll.dll");
        this->dllNames->push_back(L"..\\plugins\\anotherdrawingdll.dll");

        this->loadedDll = LoadLibrary(this->dllNames->at(0));   //������� ��� ����������� � ������ ������ dll

        if (loadedDll == NULL) //������ �������� dll
        {
            delete(this->dllNames);
            throw std::exception();
        }

        this->loadedDllIndex = 0;
        this->loadedProc = (drawProc)GetProcAddress(this->loadedDll, this->procName); // ����� ���������

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

    const void DllHandler::draw(HDC hdc, int x, int y, int radius) //����� ���������
    {
        this->loadedProc(hdc, x, y, radius); //����� ��������� ���������
    }

    void DllHandler::changeDll()    //������ ����������� dll
    {   
        if (this->loadedDllIndex == this->dllNames->size() - 1) //���� ��������� � ������ - ����� 0, ����� - ����� ���������
            this->loadedDllIndex = 0;
        else
            ++this->loadedDllIndex;

        FreeLibrary(this->loadedDll); //��������� ����������� dll �� ������ 
        this->loadedDll = LoadLibrary(this->dllNames->at(this->loadedDllIndex)); //�������� ��������� dll
        this->loadedProc = (drawProc)GetProcAddress(this->loadedDll, this->procName); //���������
    }
}
