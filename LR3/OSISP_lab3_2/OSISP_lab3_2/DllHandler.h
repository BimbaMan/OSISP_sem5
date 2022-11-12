#ifndef DLLHANDLER_H
#define DLLHANDLER_H

#include <wtypes.h>
#include <vector>

namespace lab
{
    typedef void (*drawProc)(HDC hdc, int x, int y, int radius); 

    class DllHandler
    {
        public:
        DllHandler();
        ~DllHandler();

        const void draw(HDC hdc, int x, int y, int radius);
        void changeDll();

        private:
        const LPCSTR procName = "draw";

        std::vector<LPCWSTR>* dllNames;
        drawProc loadedProc;
        HMODULE loadedDll;
        int loadedDllIndex;
    };
}

#endif
