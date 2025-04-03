#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <windows.h>
#include <winsock2.h>
#include "lib/httplib.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>

namespace fs = std::filesystem;


void AdjustVolume(float percentage) {
    CoInitialize(nullptr);
    IMMDeviceEnumerator* pEnumerator = nullptr;
    IMMDevice* pDevice = nullptr;
    IAudioEndpointVolume* pVolume = nullptr;

    if (FAILED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator))) {
        std::cerr << "Error IMMDeviceEnumerator" << std::endl;
        return;
    }

    if (FAILED(pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice))) {
        std::cerr << "Error getting audiodevice" << std::endl;
        pEnumerator->Release();
        return;
    }

    if (FAILED(pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (void**)&pVolume))) {
        std::cerr << "error IAudioEndpointVolume" << std::endl;
        pDevice->Release();
        pEnumerator->Release();
        return;
    }

    float currentVolume = 0.0f;
    pVolume->GetMasterVolumeLevelScalar(&currentVolume);

    float newVolume = std::min(std::max(currentVolume + percentage, 0.0f), 1.0f);
    pVolume->SetMasterVolumeLevelScalar(newVolume, nullptr);

    std::cout << "New Volume: " << newVolume * 100 << "%" << std::endl;

    pVolume->Release();
    pDevice->Release();
    pEnumerator->Release();
    CoUninitialize();
}

void openFile(const std::string& filePath) {
    ShellExecute(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void setcolor(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}
//FUNCTIONS

std::string shutdwn() {
    system("shutdown /s /t 1");
    return 0;
}

std::string restart() {
    system("shutdown /r /t 1");
    return 0;
}

std::string logout() {
    system("shutdown /l");
    return 0;
}

std::string discord() {
    system("C:/Users/bohmo/AppData/Local/Discord/app-1.0.9187/Discord.exe");
    return 0;
}

std::string telega() {
    std::string tgpath = "C:/Users/bohmo/AppData/Roaming/Telegram Desktop/Telegram.exe"; //ЕБАННЫЙ В РОТ     
    openFile(tgpath);
    return 0;

}

std::string ff() {
    std::string ffpath = "C:/Program Files/Mozilla Firefox/firefox.exe";
    openFile(ffpath);
    return 0;
}

std::string expl() {
    system("explorer.exe");
    return 0;
}

std::string steam() {
    std::string steampath = "C:/Program Files (x86)/Steam/steam.exe";
    openFile(steampath);
    return 0;
}

std::string vsc(){
    std::string vscpath = "D:/Microsoft VS Code/Code.exe";
    openFile(vscpath);
    return 0;
}

std::string tskmgr() {
    system("taskmgr.exe");
    return 0;
}

std::string volup() {
    AdjustVolume(0.1f);
    return 0;
}

std::string voldn() {
    AdjustVolume(-0.1f);
    return 0;
}

std::string terminate() {
    MessageBox(NULL, "PCCT WILL BE TERMINATED IN 1S", "WARNING", MB_OK | MB_ICONWARNING); 
    Sleep(1);
    system("taskkill /f /im build.exe");
    return 0;
}

//FS


std::string load_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file) {
        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }
    return "";
}

std::string get_mime_type(const std::string& filename) {
    if (filename.ends_with(".png")) return "image/png";
    if (filename.ends_with(".ttf")) return "font/ttf";
    if (filename.ends_with(".jpg") || filename.ends_with(".jpeg")) return "image/jpeg";
    return "application/octet-stream";
}

int main() {
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window, 0);
    httplib::Server svr;

    //sending html/css/js

    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        std::ifstream file("../src/index.html");
        if(file) {
            res.set_content(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()), "text/html");
        }
        else {
            res.set_content("HTML Loading Error", "text/plain");
        }
    });

    svr.Get("/script.js", [](const httplib::Request&, httplib::Response& res) {
        std::ifstream file("../src/js/script.js");
        if(file) {
            res.set_content(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()), "application/javascript");
        } 
        else {
            res.set_content("JavaScript Loading Error", "text/plain");
        }
    });

    svr.Get("/style.css", [](const httplib::Request&, httplib::Response& res) {
        std::ifstream file("../src/css/style.css");
        if(file) {
            res.set_content(std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()), "text/css");
        } 
        else {
            res.set_content("CSS Loading Error", "text/plain");
        }
    });

    svr.Get(R"(/assets/(.+))", [](const httplib::Request& req, httplib::Response& res) {
        std::string filename = "../assets/" + req.matches[1].str();

        if (fs::exists(filename) && (filename.ends_with(".jpg") || filename.ends_with(".png") || filename.ends_with(".ttf"))) {
            std::string content = load_file(filename);
            res.set_content(content, get_mime_type(filename));
        } else {
            res.status = 404;
        }
    });

    //functions handlers

    svr.Get("/shtdwn", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling Function.." << std:: endl;
        std::string shtdownr = shutdwn();
        res.set_content(shtdownr, "text/plain");
    });

    svr.Get("/rstrt", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling Restart.." << std::endl;
        std::string restartr = restart();
        res.set_content(restartr, "text/plain");
    });

    svr.Get("/logout", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling Log Out.." << std::endl;
        std::string logoutr = logout();
        res.set_content(logoutr, "text/plain");
    });

    //apps

    svr.Get("/discord", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling Discord.." << std::endl;
        std::string dsr = discord();
        res.set_content(dsr, "text/plain");
    });

    svr.Get("/telega", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling Telegram.." << std::endl;
        std::string tgr = telega();
        res.set_content(tgr, "text/plain");
    });

    svr.Get("/firefox", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling FireFox.." << std::endl;
        std::string ffr = ff();
        res.set_content(ffr, "text/plain");
    });


    svr.Get("/explorer", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling Explorer.." << std::endl;
        std::string explr = expl();
        res.set_content(explr, "text/plain");
    });

    svr.Get("/steam", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling Steam.." << std::endl;
        std::string steamr = steam();
        res.set_content(steamr, "text/plain");
    });

    svr.Get("/vsc", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling VSC.." << std::endl;
        std::string vscr = vsc();
        res.set_content(vscr, "text/plain");
    });

    svr.Get("/tskmgr", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling TASKMGR.." << std::endl;
        std::string tskmgrr = tskmgr();
        res.set_content(tskmgrr, "text/plain");
    });

    //control

    svr.Get("/volup", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling volup.." << std::endl;
        std::string volupr = volup();
        res.set_content(volupr, "text/plain");
    });

    svr.Get("/voldn", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling voldn.." << std::endl;
        std::string voldnr = voldn();
        res.set_content(voldnr, "text/plain");
    });



    svr.Get("/terminate", [](const httplib::Request&, httplib::Response& res) {
        std::cout << "Calling terminate.." << std::endl;
        std::string tern = terminate();
        res.set_content(tern, "text/plain");
    });


    setcolor(4);
    std::cout << R"( (                     )      )         (        )   (                 )      )   (                                   
 )\ )   (       (   ( /(   ( /(   *   ) )\ )  ( /(   )\ )    *   )  ( /(   ( /(   )\ )      )      (                  
(()/(   )\      )\  )\())  )\())` )  /((()/(  )\()) (()/(  ` )  /(  )\())  )\()) (()/(   ( /(      )\                 
 /(_))(((_)   (((_)((_)\  ((_)\  ( )(_))/(_))((_)\   /(_))  ( )(_))((_)\  ((_)\   /(_))  )(_)) __(((_)    _      _    
(_))  )\___   )\___  ((_)  _((_)(_(_())(_))    ((_) (_))   (_(_())   ((_)   ((_) (_))   ((_)  / /)\___  _| |_  _| |_  
| _ \((/ __| ((/ __|/ _ \ | \| ||_   _|| _ \  / _ \ | |    |_   _|  / _ \  / _ \ | |    |_  )/ /((/ __||_   _||_   _| 
|  _/ | (__   | (__| (_) || .` |  | |  |   / | (_) || |__    | |   | (_) || (_) || |__   / //_/  | (__   |_|    |_|   
|_|    \___|   \___|\___/ |_|\_|  |_|  |_|_\  \___/ |____|   |_|    \___/  \___/ |____| /___|     \___|               
)" << std::endl;
    setcolor(2);
    std::cout << "Server has started on http://192.168.0.107:5000\n";
    svr.listen("192.168.0.107", 5000);
}
