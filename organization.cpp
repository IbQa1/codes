#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <windows.h>
using namespace std;
namespace fs = filesystem;
void display(string x)
{
    for (int i = 0; i < x.size(); i++)
    {

        Sleep(1);
        cout << x[i];
    }
}
int getSize(string path)
{
    ifstream file(path, ios::binary | ios::ate);
    int size = file.tellg();
    return size / 1024;
}

void reorder_type(string path1, string path2, int x)
{
    for (auto &t : fs::directory_iterator(path1))
    {
        if (fs::is_directory(t.path()))
        {
            reorder_type(t.path().string(), path2, x);

            continue;
        }
        string p = t.path().filename().string();
        bool b = false;
        string name;
        for (int i = 0; i < p.size(); i++)
        {
            switch (x)
            {
            case 2:
            {
                if (p[i] == '.' && p[i + 1] == 't' && p[i + 2] == 'x' && p[i + 3] == 't')
                {
                    name = "TXT_Folder";
                    b = true;
                }
                break;
            }
            case 3:
            {
                if (p[i] == '.' && p[i + 1] == 'd' && p[i + 2] == 'o' && p[i + 3] == 'c' && p[i + 4] == 'x')
                {
                    name = "DOCX_Folder";
                    b = true;
                }
                break;
            }
            case 4:
            {
                if (p[i] == '.' && p[i + 1] == 'p' && p[i + 2] == 'd' && p[i + 3] == 'f')
                {
                    name = "PDF_Folder";
                    b = true;
                }
                break;
            }
            case 5:
            {
                if (p[i] == '.' && p[i + 1] == 'p' && p[i + 2] == 'p' && p[i + 3] == 't' && p[i + 4] == 'x')
                {
                    name = "PPTX_Folder";
                    b = true;
                }
                break;
            }
            case 6:
            {
                if (p[i] == '.' && p[i + 1] == 'm' && p[i + 2] == 'p' && p[i + 3] == '3')
                {
                    name = "MP3_Folder";
                    b = true;
                }
                break;
            }
            case 7:
            {
                if (p[i] == '.' && p[i + 1] == 'm' && p[i + 2] == 'p' && p[i + 3] == '4')
                {
                    name = "MP4_Folder";
                    b = true;
                }
                break;
            }
            case 8:
            {
                if (p[i] == '.' && p[i + 1] == 'c' && p[i + 2] == 's' && p[i + 3] == 'v')
                {
                    name = "CSV_Folder";
                    b = true;
                }
                break;
            }
            case 9:
            {
                if (p[i] == '.' && p[i + 1] == 'r' && p[i + 2] == 'a' && p[i + 3] == 'r')
                {
                    name = "RAR_Folder";
                    b = true;
                }
                break;
            }
            case 10:
            {
                if (p[i] == '.' && p[i + 1] == 'p' && p[i + 2] == 'n' && p[i + 3] == 'g')
                {
                    name = "PNG_Folder";
                    b = true;
                }
                break;
            }
            case 11:
            {
                if (p[i] == '.' && p[i + 1] == 'j' && p[i + 2] == 'p' && p[i + 3] == 'g')
                {
                    name = "JPG_Folder";
                    b = true;
                }
                break;
            }
            case 12:
            {
                if (p[i] == '.' && p[i + 1] == 'c' && p[i + 2] == 'p' && p[i + 3] == 'p')
                {
                    name = "CPP_Folder";
                    b = true;
                }
                break;
            }
            case 13:
            {
                if (p[i] == '.' && p[i + 1] == 'h' && p[i + 2] == 't' && p[i + 3] == 'm' && p[i + 4] == 'l')
                {
                    name = "HTML_Folder";
                    b = true;
                }
                break;
            }
            }
        }
        if (b)
        {
            fs::create_directory(path2 + "\\" + name);
            fs::rename(path1 + "\\" + p, path2 + "\\" + name + "\\" + p);
        }
    }
}
void reorder_size(string path1, string path2)
{
    for (auto &t : fs::directory_iterator(path1))
    {
        string p = t.path().filename().string();
        if (fs::is_directory(t.path()) && t.path().filename().string() != "Less Than 1 MB" &&
            t.path().filename().string() != "1 - 10 MB" && t.path().filename().string() != "11 - 50 MB" && t.path().filename().string() != "51 - 100 MB" && t.path().filename().string() != "More than 100 MB")
        {
            reorder_size(t.path().string(), path2);
            fs::remove(t.path());
            continue;
        }

        if (!(fs::is_directory(t.path())) && getSize(t.path().string()) < 1024)
        {
            if (!(fs::exists(path2 + "\\" + "Less Than 1 MB")))
                fs::create_directory(path2 + "\\" + "Less Than 1 MB");
            fs::rename(path1 + "\\" + p, path2 + "\\" + "Less Than 1 MB" + "\\" + p);
        }
        else if (!(fs::is_directory(t.path())) && getSize(t.path().string()) <= 1024 * 10)
        {
            if (!(fs::exists(path2 + "\\" + "1 - 10 MB")))
                fs::create_directory(path2 + "\\" + "1 - 10 MB");
            fs::rename(path1 + "\\" + p, path2 + "\\" + "1 - 10 MB" + "\\" + p);
        }
        else if (!(fs::is_directory(t.path())) && getSize(t.path().string()) <= 1024 * 50)
        {
            if (!(fs::exists(path2 + "\\" + "11 - 50 MB")))
                fs::create_directory(path2 + "\\" + "11 - 50 MB");
            fs::rename(path1 + "\\" + p, path2 + "\\" + "11 - 50 MB" + "\\" + p);
        }
        else if (!(fs::is_directory(t.path())) && getSize(t.path().string()) <= 1024 * 100)
        {
            if (!(fs::exists(path2 + "\\" + "51 - 100 MB")))
                fs::create_directory(path2 + "\\" + "51 - 100 MB");
            fs::rename(path1 + "\\" + p, path2 + "\\" + "51 - 100 MB" + "\\" + p);
        }
        else if (!(fs::is_directory(t.path())) && getSize(t.path().string()) > 1024 * 100)
        {
            if (!(fs::exists(path2 + "\\" + "More than 100 MB")))
                fs::create_directory(path2 + "\\" + "More than 100 MB");
            fs::rename(path1 + "\\" + p, path2 + "\\" + "More than 100 MB" + "\\" + p);
        }
    }
}

int main()
{
    while (true)
    {
        system("cls");

        string path;
        display("Enter folder path: ");
        cin >> path;
        if (!fs::is_directory(path))
        {
            display("Failed to open directory.\n");
            break;
        }
        int ans;
        display("1. Display Files.\n2. Reorder According to Types.\n3. Reorder According to Size\nEnter Your Choice: ");
        cin >> ans;
        if (ans == 1)
            for (auto &t : fs::directory_iterator(path))
            {
                string path = t.path().string();
                cout << path << " Size: " << getSize(path) << " KB"
                     << " File name: " << t.path().filename().string() << endl;
            }

        else if (ans == 2)
        {
            display("[1] Reorder all files\n[2] Reorder the .txt files.\n[3] Reorder the .docx files.\n[4] Reorder the .pdf files.\n"
                    "[5] Reorder the .pptx files.\n[6] Reorder the .mp3 files.\n[7] Reorder the .mp4 files.\n[8] Reorder the .csv files.\n"
                    "[9] Reorder the .rar files.\n[10] Reorder the .png files.\n[11] Reorder the .jpg files.\n[12] Reorder the .cpp files.\n[13] Reorder the .html files.\n");

            display("Enter your choice: ");
            cin >> ans;
            if (ans == 1)
            {
                for (int i = 2; i <= 13; i++)
                    reorder_type(path, path, i);
            }
            else if (ans > 13)
                display("Out of Range\n");
            else
                reorder_type(path, path, ans);
            system("Color 20");

            display("Order Successful.\n");
        }
        else if (ans == 3)
        {
            reorder_size(path, path);
            system("Color 20");
            display("Order Successful.\n");
        }
         display("\n-- -- -- -- -- -- -- -- -- -- -- -\n1.Reorder Again\n2.Exit\nEnter Your Choice : ");
        cin >>
            ans;
        if (ans != 1)
            break;
    }
}