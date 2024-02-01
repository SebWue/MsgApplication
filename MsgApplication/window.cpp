#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include <vector>
#include <Windows.h>
#include <WindowsX.h> // mouse tracker

using namespace std;
#include "calcW.h"
#include "window.h"
#include "endecryp.h"
#include "generateKey.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int whatWindow = 0;
wchar_t CLASS_NAME[] = L"mainWND";
HWND hwnd;
string inputTxt;
bool writing = false;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);
    hwnd;
    // Create the window.
        hwnd = CreateWindowEx(
            0,                              // Optional window styles.
            CLASS_NAME,                     // Window class
            L"Learn to Program Windows",    // Window text
            WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,            // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, 1200, 700,

            NULL,       // Parent window    
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
        );
    if (hwnd == NULL)
    {
        cout << "Error at setting up window";
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop. Like an event handler
    CreateFont(15, NULL, NULL, NULL, FW_DONTCARE, 0, 0, 0,0,0,0,0,0,0);
    MSG msg = {  };

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

bool CALLBACK SetFont(HWND child, LPARAM font) {
    SendMessage(child, WM_SETFONT, font, true);
    return true;
}

int mode = 0;
int encryNumDis = 250;
#define HELP 0
#define RSA_MODE 1
#define SYMM_ENCRY_MODE 2
vector<TCHAR> in;
vector<UINT> ownencry;
vector<TCHAR> ownencryChar;
vector<TCHAR> decry;
vector<TCHAR> keysout;
BOOL overflow = false;
UINT priva, publ, modu;

vector<TCHAR> returnOutputEncry(int fillIn, vector<TCHAR> fillTo, int key) {

    fillTo.push_back(L' '); 
    switch (key) {
    case 1:
        fillTo.push_back(L'P');
        fillTo.push_back(L'r');
        fillTo.push_back(L'i');
        fillTo.push_back(L'v');
        fillTo.push_back(L'a');
        fillTo.push_back(L't');
        fillTo.push_back(L'e');
        fillTo.push_back(L':');
        fillTo.push_back(L' ');
        break;
    case 2:
        fillTo.push_back(L'P');
        fillTo.push_back(L'u');
        fillTo.push_back(L'b');
        fillTo.push_back(L'l');
        fillTo.push_back(L'i');
        fillTo.push_back(L'c');
        fillTo.push_back(L': ');
        fillTo.push_back(L' ');
        break;
    case 3:
        fillTo.push_back(L'M');
        fillTo.push_back(L'o');
        fillTo.push_back(L'd');
        fillTo.push_back(L'u');
        fillTo.push_back(L'l');
        fillTo.push_back(L'o');
        fillTo.push_back(L':');
        fillTo.push_back(L' ');
        break;

    default:
        break;
    }
    TCHAR c;
    int temp1 = fillIn, len = 0;
    int filler;

    //get the lenght of the number
    while (temp1 != 0) {
        temp1 /= 10;
        len++;
    }
    int temp2 = len;
    temp1 = fillIn;

    for (int i = 0; i < len; i++) {
        filler = (int)(temp1 / pow(10, temp2 - 1)) % 10;
        temp2--;
        //making shure to not have a overfol of of the side of the rand

        int nCharWidth = 0;
        //placing the numbers into the vector
        switch (filler) {
            //one = (TCHAR)49, two = (TCHAR)50, three = 51, four = (TCHAR)52; five = (TCHAR)53, six = (TCHAR)54, seven = (TCHAR)55, eight = (TCHAR)56, nine = (TCHAR)57
        case 0:
            fillTo.push_back((TCHAR)48);
            break;
        case 1:
            fillTo.push_back((TCHAR)49);
            break;
        case 2:
            fillTo.push_back((TCHAR)50);
            break;
        case 3:
            fillTo.push_back((TCHAR)51);
            break;
        case 4:
            fillTo.push_back((TCHAR)52);
            break;
        case 5:
            fillTo.push_back((TCHAR)53);
            break;
        case 6:
            fillTo.push_back((TCHAR)54);
            break;
        case 7:
            fillTo.push_back((TCHAR)55);
            break;
        case 8:
            fillTo.push_back((TCHAR)56);
            break;
        case 9:
            fillTo.push_back((TCHAR)57);
            break;
        }
        //if the limit gets exeeded while in progess of writing a number into the vector
        if (key == NULL) {

            HDC hdc = GetDC(hwnd);
            GetCharWidth32(hdc, (UINT)fillTo[fillTo.size() - 1], (UINT)fillTo[fillTo.size() - 1], &nCharWidth);
            encryNumDis += nCharWidth;
            vector<TCHAR> temp;             //the characters that get replaced get put here
            if (encryNumDis > 1000) {
                for (int j = 0; j <= i; j++) {
                    temp.push_back(fillTo[fillTo.size() - 1 - i + j]);
                }

                fillTo[fillTo.size() - 1 - i] = 0x0D;

                for (int j = 0; j < i; j++) {
                    if (j == fillTo.size()) {
                        fillTo.push_back(temp[temp.size() - 1]);
                    }
                    else {
                        fillTo[fillTo.size() - i + j] = temp[j];
                    }
                }
                encryNumDis = 230;
            }
        }
    }
    // dont work yet...
    //--------------------------------------
    return fillTo;
}
int keys = 0;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HFONT hFont1;
    hFont1 = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Impact"));
    int xPos;
    int yPos;
    generateKey getKeys;
    endecryp rsa;
    calcW wmath;
    HDC hdc;                   // handle to device context 
    TEXTMETRIC tm;             // structure for text metrics 
    static DWORD dwCharX;      // average width of characters 
    static DWORD dwCharY;      // height of characters 
    static DWORD dwClientX;    // width of client area 
    static DWORD dwClientY;    // height of client area 
    static DWORD dwLineLen;    // line length 
    static DWORD dwLines;      // text lines in client area 
    static int nCaretPosX = 200; // horizontal position of caret 
    static int nCaretPosY = 600; // vertical position of caret 
    static int CaretTxtPos = 0; // position of the Caret in the Text
    static int nCharWidth = 0; // width of a character 
    static int cch = 0;        // characters in buffer 
    static int nCurChar = 0;   // index of current character 
    static PTCHAR pchInputBuf;   // input buffer
    int cCR = 0;               // count of carriage returns 
    int nCRIndex = 0;          // index of last carriage return 
    int nVirtKey;              // virtual-key code 
    TCHAR szBuf[128];          // temporary buffer 
    TCHAR ch;                  // current character 
    PAINTSTRUCT ps;            // required by BeginPaint 
    RECT rc;                   // output rectangle for DrawText 
    SIZE sz;                   // string dimensions 
    COLORREF crPrevText;       // previous text color 
    COLORREF crPrevBk;         // previous background color
    size_t* pcch;
    HRESULT hResult;

    switch (uMsg)
    {
    case WM_CREATE:
        wcout << L"WM_CREATE\n";
        // Get the metrics of the current font. 

        hdc = GetDC(hwnd);
        GetTextMetrics(hdc, &tm);

        // Save the average character width and height. 

        dwCharX = tm.tmAveCharWidth;
        dwCharY = tm.tmHeight;
        mode = HELP;
        EnumChildWindows(hwnd, (WNDENUMPROC)SetFont, (LPARAM)GetStockObject(DEFAULT_GUI_FONT));
        rsa.getKeys(priva, publ, modu);
        keysout = returnOutputEncry(priva, keysout, 1);
        keysout = returnOutputEncry(publ, keysout, 2);
        keysout = returnOutputEncry(modu, keysout, 3);
        return 0;

    case WM_SIZE:

        // Save the new width and height of the client area. 

        dwClientX = LOWORD(lParam);
        dwClientY = HIWORD(lParam);
        // Calculate the maximum width of a line and the 
        // maximum number of lines in the client area. 

        dwLineLen = dwClientX - dwCharX;
        dwLines = dwClientY / dwCharY;
        if (mode == HELP) {
            SetRect(&rc, 0, 0, 1200, 700);
            InvalidateRect(hwnd, &rc, TRUE);
            mode = RSA_MODE;
        }
        break;

    case WM_SETFOCUS:
        wcout <<L"WM_SETFOCUS\n";
        break;

    case WM_KILLFOCUS:
        HideCaret(hwnd);
        DestroyCaret();
        break;

    case WM_DESTROY:
        PostQuitMessage(0);

        GlobalFree((HGLOBAL)pchInputBuf);
        UnregisterHotKey(hwnd, 0xAAAA);
        return 0;
    case WM_LBUTTONDOWN:

        xPos = GET_X_LPARAM(lParam);
        yPos = GET_Y_LPARAM(lParam);
        if (xPos > 0 && xPos < 200 && yPos > 50 && yPos < 100) {
            getKeys.newThreadToCheck();
            rsa.getKeys(priva, publ, modu);
            keysout.clear();
            keysout = returnOutputEncry(priva, keysout, 1);
            keysout = returnOutputEncry(publ, keysout, 2);
            keysout = returnOutputEncry(modu, keysout, 3);
            SetRect(&rc, 0, 0, 1200, 700);
            InvalidateRect(hwnd, &rc, TRUE);
            cout << "HIT";
        }
        break;
    case WM_CHAR:
        
        switch (wParam)
        {
        case 0x08:  //backspace 

            if (in.size() >= 1) {
                hdc = GetDC(hwnd);
                GetCharWidth32(hdc, (UINT)in[in.size() - 1], (UINT)in[in.size() - 1], &nCharWidth);
                nCaretPosX -= nCharWidth;
                if (in[in.size() - 1] == 0x0D) {
                    nCaretPosY -= 17;
                    nCaretPosX = 1175;
                }
                in.erase(in.begin() + in.size() - 1);
                if (overflow) {
                    overflow = !overflow;
                }
                SetRect(&rc, 0, 0, 1200, 700);
                InvalidateRect(hwnd, &rc, TRUE);
            }
            break;
        case 0x0A:  //linefeed
        case 0x1B:  //escape

            MessageBeep((UINT)-1);
            return 0;

        case 0x09:  //tab

            // Convert tabs to four consecutive spaces.
            for (int i = 0; i < 4; i++)
                SendMessage(hwnd, WM_CHAR, 0x20, 0);    //0x20 = space
            return 0;

        case 0x0D:  //carrige return

            if (mode == RSA_MODE) {
                ownencry.clear();
                ownencryChar.clear();
                decry.clear();
                //if carrige return is pressed, encrypt the typed stuff
                TCHAR c;
                UINT f;
                UINT temp;
                for (int n = 0; n < in.size(); n++) {
                    c = in[n];
                    f = rsa.encrypt(c);
                    ownencry.push_back(f);

                    UINT tempf = f;
                    int len = 0;
                    //writing the result in a vector to output the encrypted characters
                    ownencryChar = returnOutputEncry(f, ownencryChar, NULL);
                    cout << ownencry[n] << " ";
                }
                encryNumDis = 0;
                UINT cint;
                for (int n = 0; n < ownencry.size(); n++) {
                    cint = ownencry[n];
                    decry.push_back(rsa.decrypt(cint));
                }
                for (int pos = 0; pos < decry.size(); pos++) {
                    wcout << decry[pos];
                }
                cout << endl;
                SetRect(&rc, 0, 0, 1200, 700);
                InvalidateRect(hwnd, &rc, TRUE);
            }

            else {
                mode = RSA_MODE;
                SetRect(&rc, 0, 0, 1200, 700);
                InvalidateRect(hwnd, &rc, TRUE);
            }

            break;

        default:    //recived input is displayable

            if (!overflow) {
                if (mode == RSA_MODE || mode == SYMM_ENCRY_MODE) {
                    ch = (TCHAR)wParam;
                    wcout << ch;
                    //Retrive the character's width and output the character

                    hdc = GetDC(hwnd);
                    GetCharWidth32(hdc, (UINT)wParam, (UINT)wParam, &nCharWidth);
                    TextOut(hdc, nCaretPosX, nCaretPosY * dwCharY, &ch, 1);
                    ReleaseDC(hwnd, hdc);

                    //Calculate the new horizontal position of the caret. If the position exceeds the maximum, insert a carrige return and move the caret to the beginning of next line

                    nCaretPosX += nCharWidth;
                    if ((DWORD)nCaretPosX > dwLineLen) {
                        nCaretPosX = 200 + nCharWidth;
                        in.push_back(0x0D);
                        nCaretPosY += 17;
                    }
                    in.push_back(ch);

                    nCurChar = cch;
                    SetRect(&rc, 190, 600, 1200, 700);
                    InvalidateRect(hwnd, &rc, TRUE);
                }
                break;
            }
            else {
                MessageBeep(2);
                break;
            }
            //-----------------
            //wParam switch over
        }
        break;

    case WM_KEYDOWN:
        switch (wParam) {
        case VK_LEFT:   //LEFT ARROW
            
            break;
        case VK_RIGHT:
            // Caret moves to the right or, when a carriage 
            // return is encountered, to the beginning of 
            // the next line. 
        case VK_UP:
        case VK_DOWN:
            MessageBeep((UINT)-1);
            return 0;
        case VK_HOME:
        case VK_END:
            break;
        }
        return 0;

    case WM_PAINT:
        
        HDC hdc = BeginPaint(hwnd, &ps);


        //Background Color
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        SetRect(&rc, 5, 0, 190, 50);
        DrawTextW(hdc, L"Modes", -1, &rc, DT_LEFT);
        SetRect(&rc, 0, 0, 190, 700);
        HBRUSH rectcolor;
        rectcolor = CreateSolidBrush(RGB(0, 0, 0));
        FrameRect(hdc, &rc, rectcolor);

        SetRect(&rc, 0, 50, 190, 100);
        FrameRect(hdc, &rc, rectcolor);
        SetRect(&rc, 27, 67, 190, 100);
        DrawTextW(hdc, L"Generate Keys", -1, &rc, DT_LEFT);

        HideCaret(hwnd);

        SetRect(&rc, 200, 10, 300, 100);
        DrawTextW(hdc, L"Keys: ", -1, &rc, DT_LEFT);

        SetRect(&rc, 200, 30, 500, 100);
        keysout.push_back('\0');
        DrawTextW(hdc, keysout.data(), -1, &rc, DT_LEFT);
        keysout.pop_back();

            if (620 + (nCaretPosY - 600) < 660) {
                //Messagebox
                RoundRect(hdc, 190, 595, dwLineLen + 5, 620 + (nCaretPosY - 600), 30, 30);

                SetRect(&rc, 200, 600, dwLineLen, dwClientY);
                //DrawTextW takes only NULL terminated Strings. So to not get unexpectet results, we need to nullterminate the vector with saved shit
                if (in.size() == 0) {
                    DrawTextW(hdc, L"Message", -1, &rc, DT_LEFT);
                }
                in.push_back(L'\0');
                DrawTextW(hdc, in.data(), -1, &rc, DT_LEFT);
                //Delete the NULL so it isnt terminated anymore
                in.pop_back();

                SetRect(&rc, 190, 595, dwLineLen + 5, 620 + (nCaretPosY - 600));
                //FrameRect(hdc, &rc, rectcolor);
            }
            // if the Message box is too full, display an error Window
            else {
                MessageBox(hwnd, L"OVERFLOW, TOO MANY CHARACTERS", L"WARNING: OVERFLOW", NULL);
                overflow = true;
                break; 
            } 
            if (decry.size() != NULL) {
                SetRect(&rc, 205, 180, dwLineLen, dwClientY);
                DrawTextW(hdc, L"Enrypted Text: ", -1, &rc, DT_LEFT);
                SetRect(&rc, 250, 200, dwLineLen, dwClientY);
                ownencryChar.push_back(L'\0');
                DrawTextW(hdc, ownencryChar.data(), -1, &rc, DT_LEFT);
                ownencryChar.pop_back();
                SetRect(&rc, 200, 300, dwLineLen, dwClientY);
                decry.push_back(L'\0');
                DrawTextW(hdc, decry.data(), -1, &rc, DT_LEFT);
                //Delete the NULL so it isnt terminated anymore
                decry.pop_back();
            }
            CreateCaret(hwnd, NULL, 0, dwCharY);
            SetCaretBlinkTime(600);
            SetCaretPos(nCaretPosX, nCaretPosY);
            ReleaseDC(hwnd, hdc);
            ShowCaret(hwnd);
        
        EndPaint(hwnd, &ps);
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void window::create()
{
    wWinMain(0, 0, 0, 1);
}
