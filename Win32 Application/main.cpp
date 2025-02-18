#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

// Windows sürüm tanımları
#define WINVER 0x0500
#define _WIN32_WINNT 0x0500
#define _WIN32_IE 0x0500  

#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdarg.h>

#pragma comment(lib, "comctl32.lib")

//-----------------------------------------------------------------
// Grup Kutusu Kontrol ID’leri
#define IDC_GROUP1        201
#define IDC_GROUP2        202
#define IDC_GROUP3        203

// Hotkey Set 1 Kontrol ID’leri
#define IDC_STATIC_METIN1     101
#define IDC_EDIT_METIN1       102
#define IDC_STATIC_HOTKEY1    103
#define IDC_EDIT_HOTKEY1      104
#define IDC_CHECK_ALT1        105
#define IDC_CHECK_CTRL1       106
#define IDC_CHECK_SHIFT1      107
#define IDC_BUTTON_REG1       108
#define IDC_STATIC_KAYIT1     109
#define IDC_BUTTON_RESET1     110

// Hotkey Set 2 Kontrol ID’leri
#define IDC_STATIC_METIN2     111
#define IDC_EDIT_METIN2       112
#define IDC_STATIC_HOTKEY2    113
#define IDC_EDIT_HOTKEY2      114
#define IDC_CHECK_ALT2        115
#define IDC_CHECK_CTRL2       116
#define IDC_CHECK_SHIFT2      117
#define IDC_BUTTON_REG2       118
#define IDC_STATIC_KAYIT2     119
#define IDC_BUTTON_RESET2     120

// Hotkey Set 3 Kontrol ID’leri
#define IDC_STATIC_METIN3     121
#define IDC_EDIT_METIN3       122
#define IDC_STATIC_HOTKEY3    123
#define IDC_EDIT_HOTKEY3      124
#define IDC_CHECK_ALT3        125
#define IDC_CHECK_CTRL3       126
#define IDC_CHECK_SHIFT3      127
#define IDC_BUTTON_REG3       128
#define IDC_STATIC_KAYIT3     129
#define IDC_BUTTON_RESET3     130

// Global metinler (varsayılan değerler)
static TCHAR g_metin1[256] = _T("ESMERAY");
static TCHAR g_metin2[256] = _T("EMPİRE");
static TCHAR g_metin3[256] = _T("COMPANY");

// Hotkey ID’leri (RegisterHotKey için benzersiz ID’ler)
static const int g_hotkeyID1 = 1;
static const int g_hotkeyID2 = 2;
static const int g_hotkeyID3 = 3;

// Sistem tepsisi için global NOTIFYICONDATA yapısı
static NOTIFYICONDATA g_nid = {0};
static const UINT WM_TRAYICON = WM_USER + 1; // Tray icon mesajı

// Global font (kontrollerde kullanılacak)
static HFONT g_hFont = NULL;

// Yardımcı: Debug mesajı gönderme
void DebugMsg(const TCHAR* format, ...)
{
    TCHAR buffer[512];
    va_list args;
    va_start(args, format);
    _vstprintf_s(buffer, _countof(buffer), format, args);
    va_end(args);
    OutputDebugString(buffer);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // Hotkey Set 1 kontrolleri
    static HWND hGroup1, hStaticMetin1, hEditMetin1, hStaticHotkey1, hEditHotkey1;
    static HWND hCheckAlt1, hCheckCtrl1, hCheckShift1, hButtonReg1, hButtonReset1, hStaticKayit1;
    // Hotkey Set 2 kontrolleri
    static HWND hGroup2, hStaticMetin2, hEditMetin2, hStaticHotkey2, hEditHotkey2;
    static HWND hCheckAlt2, hCheckCtrl2, hCheckShift2, hButtonReg2, hButtonReset2, hStaticKayit2;
    // Hotkey Set 3 kontrolleri
    static HWND hGroup3, hStaticMetin3, hEditMetin3, hStaticHotkey3, hEditHotkey3;
    static HWND hCheckAlt3, hCheckCtrl3, hCheckShift3, hButtonReg3, hButtonReset3, hStaticKayit3;

    switch(msg)
    {
    case WM_CREATE:
        {
            HINSTANCE hInst = ((LPCREATESTRUCT)lParam)->hInstance;

            // --- Font Oluşturma (Segoe UI, 24 punto) ---
            g_hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
                                  DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                  DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Segoe UI"));

            // ----- Group Box ve Hotkey Set 1 -----
            hGroup1 = CreateWindowEx(0, _T("BUTTON"), _T("Hotkey Set 1"),
                WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                20, 20, 760, 140, hwnd, (HMENU)IDC_GROUP1, hInst, NULL);
            SendMessage(hGroup1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hStaticMetin1 = CreateWindowEx(0, _T("STATIC"), _T("Metin:"),
                WS_CHILD | WS_VISIBLE,
                30, 50, 90, 30, hwnd, (HMENU)IDC_STATIC_METIN1, hInst, NULL);
            SendMessage(hStaticMetin1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hEditMetin1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), g_metin1,
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                130, 50, 220, 35, hwnd, (HMENU)IDC_EDIT_METIN1, hInst, NULL);
            SendMessage(hEditMetin1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hStaticHotkey1 = CreateWindowEx(0, _T("STATIC"), _T("Hotkey:"),
                WS_CHILD | WS_VISIBLE,
                370, 50, 110, 30, hwnd, (HMENU)IDC_STATIC_HOTKEY1, hInst, NULL);
            SendMessage(hStaticHotkey1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hEditHotkey1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                490, 50, 60, 35, hwnd, (HMENU)IDC_EDIT_HOTKEY1, hInst, NULL);
            SendMessage(hEditHotkey1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hCheckAlt1 = CreateWindowEx(0, _T("BUTTON"), _T("ALT"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                30, 95, 90, 30, hwnd, (HMENU)IDC_CHECK_ALT1, hInst, NULL);
            SendMessage(hCheckAlt1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hCheckCtrl1 = CreateWindowEx(0, _T("BUTTON"), _T("CTRL"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                130, 95, 90, 30, hwnd, (HMENU)IDC_CHECK_CTRL1, hInst, NULL);
            SendMessage(hCheckCtrl1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hCheckShift1 = CreateWindowEx(0, _T("BUTTON"), _T("SHIFT"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                230, 95, 100, 30, hwnd, (HMENU)IDC_CHECK_SHIFT1, hInst, NULL);
            SendMessage(hCheckShift1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hButtonReg1 = CreateWindowEx(0, _T("BUTTON"), _T("Kaydet"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                350, 95, 100, 35, hwnd, (HMENU)IDC_BUTTON_REG1, hInst, NULL);
            SendMessage(hButtonReg1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hButtonReset1 = CreateWindowEx(0, _T("BUTTON"), _T("Reset"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                460, 95, 80, 35, hwnd, (HMENU)IDC_BUTTON_RESET1, hInst, NULL);
            SendMessage(hButtonReset1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hStaticKayit1 = CreateWindowEx(0, _T("STATIC"), _T("Kayıtlı Hotkey: Yok"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
                550, 95, 220, 35, hwnd, (HMENU)IDC_STATIC_KAYIT1, hInst, NULL);
            SendMessage(hStaticKayit1, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            // ----- Group Box ve Hotkey Set 2 -----
            hGroup2 = CreateWindowEx(0, _T("BUTTON"), _T("Hotkey Set 2"),
                WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                20, 180, 760, 140, hwnd, (HMENU)IDC_GROUP2, hInst, NULL);
            SendMessage(hGroup2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hStaticMetin2 = CreateWindowEx(0, _T("STATIC"), _T("Metin:"),
                WS_CHILD | WS_VISIBLE,
                30, 210, 90, 30, hwnd, (HMENU)IDC_STATIC_METIN2, hInst, NULL);
            SendMessage(hStaticMetin2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hEditMetin2 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), g_metin2,
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                130, 210, 220, 35, hwnd, (HMENU)IDC_EDIT_METIN2, hInst, NULL);
            SendMessage(hEditMetin2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hStaticHotkey2 = CreateWindowEx(0, _T("STATIC"), _T("Hotkey:"),
                WS_CHILD | WS_VISIBLE,
                370, 210, 110, 30, hwnd, (HMENU)IDC_STATIC_HOTKEY2, hInst, NULL);
            SendMessage(hStaticHotkey2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hEditHotkey2 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                490, 210, 60, 35, hwnd, (HMENU)IDC_EDIT_HOTKEY2, hInst, NULL);
            SendMessage(hEditHotkey2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hCheckAlt2 = CreateWindowEx(0, _T("BUTTON"), _T("ALT"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                30, 255, 90, 30, hwnd, (HMENU)IDC_CHECK_ALT2, hInst, NULL);
            SendMessage(hCheckAlt2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hCheckCtrl2 = CreateWindowEx(0, _T("BUTTON"), _T("CTRL"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                130, 255, 90, 30, hwnd, (HMENU)IDC_CHECK_CTRL2, hInst, NULL);
            SendMessage(hCheckCtrl2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hCheckShift2 = CreateWindowEx(0, _T("BUTTON"), _T("SHIFT"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                230, 255, 100, 30, hwnd, (HMENU)IDC_CHECK_SHIFT2, hInst, NULL);
            SendMessage(hCheckShift2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hButtonReg2 = CreateWindowEx(0, _T("BUTTON"), _T("Kaydet"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                350, 255, 100, 35, hwnd, (HMENU)IDC_BUTTON_REG2, hInst, NULL);
            SendMessage(hButtonReg2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hButtonReset2 = CreateWindowEx(0, _T("BUTTON"), _T("Reset"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                460, 255, 80, 35, hwnd, (HMENU)IDC_BUTTON_RESET2, hInst, NULL);
            SendMessage(hButtonReset2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hStaticKayit2 = CreateWindowEx(0, _T("STATIC"), _T("Kayıtlı Hotkey: Yok"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
                550, 255, 220, 35, hwnd, (HMENU)IDC_STATIC_KAYIT2, hInst, NULL);
            SendMessage(hStaticKayit2, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            // ----- Group Box ve Hotkey Set 3 -----
            hGroup3 = CreateWindowEx(0, _T("BUTTON"), _T("Hotkey Set 3"),
                WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                20, 340, 760, 140, hwnd, (HMENU)IDC_GROUP3, hInst, NULL);
            SendMessage(hGroup3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hStaticMetin3 = CreateWindowEx(0, _T("STATIC"), _T("Metin:"),
                WS_CHILD | WS_VISIBLE,
                30, 370, 90, 30, hwnd, (HMENU)IDC_STATIC_METIN3, hInst, NULL);
            SendMessage(hStaticMetin3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hEditMetin3 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), g_metin3,
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                130, 370, 220, 35, hwnd, (HMENU)IDC_EDIT_METIN3, hInst, NULL);
            SendMessage(hEditMetin3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hStaticHotkey3 = CreateWindowEx(0, _T("STATIC"), _T("Hotkey:"),
                WS_CHILD | WS_VISIBLE,
                370, 370, 110, 30, hwnd, (HMENU)IDC_STATIC_HOTKEY3, hInst, NULL);
            SendMessage(hStaticHotkey3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hEditHotkey3 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("EDIT"), _T(""),
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
                490, 370, 60, 35, hwnd, (HMENU)IDC_EDIT_HOTKEY3, hInst, NULL);
            SendMessage(hEditHotkey3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hCheckAlt3 = CreateWindowEx(0, _T("BUTTON"), _T("ALT"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                30, 415, 90, 30, hwnd, (HMENU)IDC_CHECK_ALT3, hInst, NULL);
            SendMessage(hCheckAlt3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hCheckCtrl3 = CreateWindowEx(0, _T("BUTTON"), _T("CTRL"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                130, 415, 90, 30, hwnd, (HMENU)IDC_CHECK_CTRL3, hInst, NULL);
            SendMessage(hCheckCtrl3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hCheckShift3 = CreateWindowEx(0, _T("BUTTON"), _T("SHIFT"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                230, 415, 100, 30, hwnd, (HMENU)IDC_CHECK_SHIFT3, hInst, NULL);
            SendMessage(hCheckShift3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hButtonReg3 = CreateWindowEx(0, _T("BUTTON"), _T("Kaydet"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                350, 415, 100, 35, hwnd, (HMENU)IDC_BUTTON_REG3, hInst, NULL);
            SendMessage(hButtonReg3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hButtonReset3 = CreateWindowEx(0, _T("BUTTON"), _T("Reset"),
                WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                460, 415, 80, 35, hwnd, (HMENU)IDC_BUTTON_RESET3, hInst, NULL);
            SendMessage(hButtonReset3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            hStaticKayit3 = CreateWindowEx(0, _T("STATIC"), _T("Kayıtlı Hotkey: Yok"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE,
                550, 415, 220, 35, hwnd, (HMENU)IDC_STATIC_KAYIT3, hInst, NULL);
            SendMessage(hStaticKayit3, WM_SETFONT, (WPARAM)g_hFont, TRUE);

            // ----- Sistem Tepsisi (Tray Icon) -----
            g_nid.cbSize = sizeof(NOTIFYICONDATA);
            g_nid.hWnd = hwnd;
            g_nid.uID = 1001;
            g_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
            g_nid.uCallbackMessage = WM_TRAYICON;
            g_nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            _tcscpy_s(g_nid.szTip, _T("Modern Multi Hotkey Uygulaması"));
            if(!Shell_NotifyIcon(NIM_ADD, &g_nid))
            {
                DebugMsg(_T("Tray icon eklenemedi.\n"));
            }
            else
            {
                DebugMsg(_T("Tray icon eklendi.\n"));
            }
        }
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // --- Hotkey Set 1 Kaydet Butonu ---
            if(wmId == IDC_BUTTON_REG1)
            {
                TCHAR keyBuffer[32] = {0};
                GetWindowText(hEditHotkey1, keyBuffer, _countof(keyBuffer));
                int key;
                if(_tcslen(keyBuffer) > 0)
                {
                    key = (int)_totupper(keyBuffer[0]);
                }
                else if(SendMessage(hCheckAlt1, BM_GETCHECK, 0, 0) == BST_CHECKED)
                {
                    key = VK_MENU;
                }
                else if(SendMessage(hCheckCtrl1, BM_GETCHECK, 0, 0) == BST_CHECKED)
                {
                    key = VK_CONTROL;
                }
                else if(SendMessage(hCheckShift1, BM_GETCHECK, 0, 0) == BST_CHECKED)
                {
                    key = VK_SHIFT;
                }
                else
                {
                    MessageBox(hwnd, _T("Hotkey tuşu belirtilmedi! Lütfen bir tuş girin ya da ALT, CTRL veya SHIFT seçili olsun."), _T("Hata"), MB_OK | MB_ICONERROR);
                    break;
                }
                GetWindowText(hEditMetin1, g_metin1, _countof(g_metin1));
                int modifiers = 0;
                if(SendMessage(hCheckAlt1, BM_GETCHECK, 0, 0) == BST_CHECKED)
                    modifiers |= MOD_ALT;
                if(SendMessage(hCheckCtrl1, BM_GETCHECK, 0, 0) == BST_CHECKED)
                    modifiers |= MOD_CONTROL;
                if(SendMessage(hCheckShift1, BM_GETCHECK, 0, 0) == BST_CHECKED)
                    modifiers |= MOD_SHIFT;

                UnregisterHotKey(hwnd, g_hotkeyID1);
                if(RegisterHotKey(hwnd, g_hotkeyID1, modifiers, key))
                {
                    TCHAR modStr[32] = _T("");
                    if(modifiers & MOD_ALT)
                        _tcscat_s(modStr, _countof(modStr), _T("ALT+"));
                    if(modifiers & MOD_CONTROL)
                        _tcscat_s(modStr, _countof(modStr), _T("CTRL+"));
                    if(modifiers & MOD_SHIFT)
                        _tcscat_s(modStr, _countof(modStr), _T("SHIFT+"));
                    TCHAR keyChar[2] = { (TCHAR)key, 0 };
                    TCHAR displayHK[128];
                    _stprintf_s(displayHK, _countof(displayHK), _T("Kayıtlı Hotkey: %s%s"), modStr, keyChar);
                    SetWindowText(hStaticKayit1, displayHK);
                    DebugMsg(_T("Hotkey 1 kaydedildi: mod=%s, key=%c\n"), modStr, key);
                    MessageBox(hwnd, _T("Hotkey 1 başarıyla kaydedildi!"), _T("Başarılı"), MB_OK);
                }
                else
                {
                    DWORD err = GetLastError();
                    TCHAR errMsg[256];
                    _stprintf_s(errMsg, _countof(errMsg), _T("Hotkey 1 kaydı başarısız! Hata: %d"), err);
                    DebugMsg(_T("%s\n"), errMsg);
                    MessageBox(hwnd, errMsg, _T("Hata"), MB_OK | MB_ICONERROR);
                    SetWindowText(hStaticKayit1, _T("Kayıtlı Hotkey: Yok"));
                }
            }
                else if(wmId == IDC_BUTTON_RESET1)
                {
                    // Hotkey'i sistemden kaldır
                    UnregisterHotKey(hwnd, g_hotkeyID1);
                    // Hotkey alanını temizle
                    SetWindowText(hEditHotkey1, _T(""));
                    // Modifier check box'larını sıfırla
                    SendMessage(hCheckAlt1, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(hCheckCtrl1, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(hCheckShift1, BM_SETCHECK, BST_UNCHECKED, 0);
                    // Kayıtlı hotkey gösterimini sıfırla
                    SetWindowText(hStaticKayit1, _T("Kayıtlı Hotkey: Yok"));
                }

            // --- Hotkey Set 2 Kaydet Butonu ---
            else if(wmId == IDC_BUTTON_REG2)
            {
                TCHAR keyBuffer[32] = {0};
                GetWindowText(hEditHotkey2, keyBuffer, _countof(keyBuffer));
                int key;
                if(_tcslen(keyBuffer) > 0)
                {
                    key = (int)_totupper(keyBuffer[0]);
                }
                else if(SendMessage(hCheckAlt2, BM_GETCHECK, 0, 0) == BST_CHECKED)
                {
                    key = VK_MENU;
                }
                else if(SendMessage(hCheckCtrl2, BM_GETCHECK, 0, 0) == BST_CHECKED)
                {
                    key = VK_CONTROL;
                }
                else if(SendMessage(hCheckShift2, BM_GETCHECK, 0, 0) == BST_CHECKED)
                {
                    key = VK_SHIFT;
                }
                else
                {
                    MessageBox(hwnd, _T("Hotkey tuşu belirtilmedi! Lütfen bir tuş girin ya da ALT, CTRL veya SHIFT seçili olsun."), _T("Hata"), MB_OK | MB_ICONERROR);
                    break;
                }
                GetWindowText(hEditMetin2, g_metin2, _countof(g_metin2));
                int modifiers = 0;
                if(SendMessage(hCheckAlt2, BM_GETCHECK, 0, 0) == BST_CHECKED)
                    modifiers |= MOD_ALT;
                if(SendMessage(hCheckCtrl2, BM_GETCHECK, 0, 0) == BST_CHECKED)
                    modifiers |= MOD_CONTROL;
                if(SendMessage(hCheckShift2, BM_GETCHECK, 0, 0) == BST_CHECKED)
                    modifiers |= MOD_SHIFT;

                UnregisterHotKey(hwnd, g_hotkeyID2);
                if(RegisterHotKey(hwnd, g_hotkeyID2, modifiers, key))
                {
                    TCHAR modStr[32] = _T("");
                    if(modifiers & MOD_ALT)
                        _tcscat_s(modStr, _countof(modStr), _T("ALT+"));
                    if(modifiers & MOD_CONTROL)
                        _tcscat_s(modStr, _countof(modStr), _T("CTRL+"));
                    if(modifiers & MOD_SHIFT)
                        _tcscat_s(modStr, _countof(modStr), _T("SHIFT+"));
                    TCHAR keyChar[2] = { (TCHAR)key, 0 };
                    TCHAR displayHK[128];
                    _stprintf_s(displayHK, _countof(displayHK), _T("Kayıtlı Hotkey: %s%s"), modStr, keyChar);
                    SetWindowText(hStaticKayit2, displayHK);
                    DebugMsg(_T("Hotkey 2 kaydedildi: mod=%s, key=%c\n"), modStr, key);
                    MessageBox(hwnd, _T("Hotkey 2 başarıyla kaydedildi!"), _T("Başarılı"), MB_OK);
                }
                else
                {
                    DWORD err = GetLastError();
                    TCHAR errMsg[256];
                    _stprintf_s(errMsg, _countof(errMsg), _T("Hotkey 2 kaydı başarısız! Hata: %d"), err);
                    DebugMsg(_T("%s\n"), errMsg);
                    MessageBox(hwnd, errMsg, _T("Hata"), MB_OK | MB_ICONERROR);
                }
            }
            // --- Hotkey Set 2 Reset Butonu ---
            else if(wmId == IDC_BUTTON_RESET2)
            {
                UnregisterHotKey(hwnd, g_hotkeyID2);
                SetWindowText(hEditHotkey2, _T(""));
                SendMessage(hCheckAlt2, BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(hCheckCtrl2, BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(hCheckShift2, BM_SETCHECK, BST_UNCHECKED, 0);
                SetWindowText(hStaticKayit2, _T("Kayıtlı Hotkey: Yok"));
            }


            // --- Hotkey Set 3 Kaydet Butonu ---
            else if(wmId == IDC_BUTTON_REG3)
            {
                TCHAR keyBuffer[32] = {0};
                GetWindowText(hEditHotkey3, keyBuffer, _countof(keyBuffer));
                int key;
                if(_tcslen(keyBuffer) > 0)
                {
                    key = (int)_totupper(keyBuffer[0]);
                }
                else if(SendMessage(hCheckAlt3, BM_GETCHECK, 0, 0) == BST_CHECKED)
                {
                    key = VK_MENU;
                }
                else if(SendMessage(hCheckCtrl3, BM_GETCHECK, 0, 0) == BST_CHECKED)
                {
                    key = VK_CONTROL;
                }
                else if(SendMessage(hCheckShift3, BM_GETCHECK, 0, 0) == BST_CHECKED)
                {
                    key = VK_SHIFT;
                }
                else
                {
                    MessageBox(hwnd, _T("Hotkey tuşu belirtilmedi! Lütfen bir tuş girin ya da ALT, CTRL veya SHIFT seçili olsun."), _T("Hata"), MB_OK | MB_ICONERROR);
                    break;
                }
                GetWindowText(hEditMetin3, g_metin3, _countof(g_metin3));
                int modifiers = 0;
                if(SendMessage(hCheckAlt3, BM_GETCHECK, 0, 0) == BST_CHECKED)
                    modifiers |= MOD_ALT;
                if(SendMessage(hCheckCtrl3, BM_GETCHECK, 0, 0) == BST_CHECKED)
                    modifiers |= MOD_CONTROL;
                if(SendMessage(hCheckShift3, BM_GETCHECK, 0, 0) == BST_CHECKED)
                    modifiers |= MOD_SHIFT;

                UnregisterHotKey(hwnd, g_hotkeyID3);
                if(RegisterHotKey(hwnd, g_hotkeyID3, modifiers, key))
                {
                    TCHAR modStr[32] = _T("");
                    if(modifiers & MOD_ALT)
                        _tcscat_s(modStr, _countof(modStr), _T("ALT+"));
                    if(modifiers & MOD_CONTROL)
                        _tcscat_s(modStr, _countof(modStr), _T("CTRL+"));
                    if(modifiers & MOD_SHIFT)
                        _tcscat_s(modStr, _countof(modStr), _T("SHIFT+"));
                    TCHAR keyChar[2] = { (TCHAR)key, 0 };
                    TCHAR displayHK[128];
                    _stprintf_s(displayHK, _countof(displayHK), _T("Kayıtlı Hotkey: %s%s"), modStr, keyChar);
                    SetWindowText(hStaticKayit3, displayHK);
                    DebugMsg(_T("Hotkey 3 kaydedildi: mod=%s, key=%c\n"), modStr, key);
                    MessageBox(hwnd, _T("Hotkey 3 başarıyla kaydedildi!"), _T("Başarılı"), MB_OK);
                }
                else
                {
                    DWORD err = GetLastError();
                    TCHAR errMsg[256];
                    _stprintf_s(errMsg, _countof(errMsg), _T("Hotkey 3 kaydı başarısız! Hata: %d"), err);
                    DebugMsg(_T("%s\n"), errMsg);
                    MessageBox(hwnd, errMsg, _T("Hata"), MB_OK | MB_ICONERROR);
                }
            }
            // --- Hotkey Set 3 Reset Butonu ---
            else if(wmId == IDC_BUTTON_RESET3)
            {
                UnregisterHotKey(hwnd, g_hotkeyID3);
                SetWindowText(hEditHotkey3, _T(""));
                SendMessage(hCheckAlt3, BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(hCheckCtrl3, BM_SETCHECK, BST_UNCHECKED, 0);
                SendMessage(hCheckShift3, BM_SETCHECK, BST_UNCHECKED, 0);
                SetWindowText(hStaticKayit3, _T("Kayıtlı Hotkey: Yok"));
            }

        }
        break;

    case WM_HOTKEY:
        {
            if((int)wParam == g_hotkeyID1)
            {
                DebugMsg(_T("Hotkey 1 tetiklendi.\n"));
                int len = lstrlen(g_metin1);
                if(len > 0)
                {
                    INPUT* inputs = new INPUT[len * 2];
                    ZeroMemory(inputs, sizeof(INPUT) * len * 2);
                    for(int i = 0; i < len; i++)
                    {
                        inputs[i * 2].type = INPUT_KEYBOARD;
                        inputs[i * 2].ki.wScan = g_metin1[i];
                        inputs[i * 2].ki.dwFlags = KEYEVENTF_UNICODE;
                        inputs[i * 2 + 1].type = INPUT_KEYBOARD;
                        inputs[i * 2 + 1].ki.wScan = g_metin1[i];
                        inputs[i * 2 + 1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
                    }
                    UINT sent = SendInput(len * 2, inputs, sizeof(INPUT));
                    if(sent != (UINT)(len * 2))
                    {
                        DWORD err = GetLastError();
                        DebugMsg(_T("Hotkey 1: SendInput başarısız! Gönderilen: %u, Beklenen: %d, Hata: %d\n"), sent, len * 2, err);
                        MessageBox(hwnd, _T("Hotkey 1: SendInput başarısız!"), _T("Hata"), MB_OK | MB_ICONERROR);
                    }
                    delete[] inputs;
                }
            }
            else if((int)wParam == g_hotkeyID2)
            {
                DebugMsg(_T("Hotkey 2 tetiklendi.\n"));
                int len = lstrlen(g_metin2);
                if(len > 0)
                {
                    INPUT* inputs = new INPUT[len * 2];
                    ZeroMemory(inputs, sizeof(INPUT) * len * 2);
                    for(int i = 0; i < len; i++)
                    {
                        inputs[i * 2].type = INPUT_KEYBOARD;
                        inputs[i * 2].ki.wScan = g_metin2[i];
                        inputs[i * 2].ki.dwFlags = KEYEVENTF_UNICODE;
                        inputs[i * 2 + 1].type = INPUT_KEYBOARD;
                        inputs[i * 2 + 1].ki.wScan = g_metin2[i];
                        inputs[i * 2 + 1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
                    }
                    UINT sent = SendInput(len * 2, inputs, sizeof(INPUT));
                    if(sent != (UINT)(len * 2))
                    {
                        DebugMsg(_T("Hotkey 2: SendInput başarısız! Gönderilen: %u, Beklenen: %d\n"), sent, len * 2);
                        MessageBox(hwnd, _T("Hotkey 2: SendInput başarısız!"), _T("Hata"), MB_OK | MB_ICONERROR);
                    }
                    delete[] inputs;
                }
            }
            else if((int)wParam == g_hotkeyID3)
            {
                DebugMsg(_T("Hotkey 3 tetiklendi.\n"));
                int len = lstrlen(g_metin3);
                if(len > 0)
                {
                    INPUT* inputs = new INPUT[len * 2];
                    ZeroMemory(inputs, sizeof(INPUT) * len * 2);
                    for(int i = 0; i < len; i++)
                    {
                        inputs[i * 2].type = INPUT_KEYBOARD;
                        inputs[i * 2].ki.wScan = g_metin3[i];
                        inputs[i * 2].ki.dwFlags = KEYEVENTF_UNICODE;
                        inputs[i * 2 + 1].type = INPUT_KEYBOARD;
                        inputs[i * 2 + 1].ki.wScan = g_metin3[i];
                        inputs[i * 2 + 1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
                    }
                    UINT sent = SendInput(len * 2, inputs, sizeof(INPUT));
                    if(sent != (UINT)(len * 2))
                    {
                        DebugMsg(_T("Hotkey 3: SendInput başarısız! Gönderilen: %u, Beklenen: %d\n"), sent, len * 2);
                        MessageBox(hwnd, _T("Hotkey 3: SendInput başarısız!"), _T("Hata"), MB_OK | MB_ICONERROR);
                    }
                    delete[] inputs;
                }
            }
        }
        break;

    case WM_TRAYICON:
        {
            if(lParam == WM_LBUTTONDBLCLK)
            {
                ShowWindow(hwnd, SW_RESTORE);
                SetForegroundWindow(hwnd);
            }
        }
        break;

    case WM_DESTROY:
        Shell_NotifyIcon(NIM_DELETE, &g_nid);
        DebugMsg(_T("Tray icon kaldırıldı.\n"));
        UnregisterHotKey(hwnd, g_hotkeyID1);
        UnregisterHotKey(hwnd, g_hotkeyID2);
        UnregisterHotKey(hwnd, g_hotkeyID3);
        if(g_hFont)
        {
            DeleteObject(g_hFont);
            g_hFont = NULL;
        }
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES;
    if(!InitCommonControlsEx(&icex))
    {
        MessageBox(NULL, _T("InitCommonControlsEx başarısız oldu!"), _T("Hata"), MB_OK | MB_ICONERROR);
        return 0;
    }

    const TCHAR szClassName[] = _T("MultiHotkeyClass");
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, _T("Pencere sınıfı kayıt edilemedi!"), _T("Hata"), MB_OK | MB_ICONERROR);
        return 0;
    }

    HWND hwnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, _T("Modern Multi Hotkey Uygulaması"),
                               WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 520,
                               NULL, NULL, hInstance, NULL);
    if(!hwnd)
    {
        MessageBox(NULL, _T("Pencere oluşturulamadı!"), _T("Hata"), MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
