#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>

struct Dfile {
    std::string FName;
    std::string FDirectory;
    int Fsize;

    bool FCanOpen;
    bool FCanSee;
    std::string Fextension;
};

void FDirectoryPrint(std::string BD) {
    std::cout << "Базовая директория: " << BD << std::endl;
}

void BootScreen() {
    std::cout << "===========================" << std::endl;
    std::cout << "     ClearCMD v0.1         " << std::endl;
    std::cout << "===========================" << std::endl;
}

void SimpleError() {
    std::cout << "\033[31m";
    std::cout << "ОШИБКА!" << std::endl;
    std::cout << "\033[35m";
    std::cout << "Неизвестная ошибка!" << std::endl;
    std::cout << "\033[0m";
}

void ClearScreen() {
    std::cout << "\033[2J\033[H";
    BootScreen();
}

void AllUser(std::vector<std::string>& Rights) {
    int a = 0;
    for (int i = 0; i < Rights.size(); i++)
    {
        std::cout << a++ << ". " << Rights[i] << std::endl;
    }
}

void Info(int NowMV) {
    std::cout << "ОС: ClearCMD" << std::endl
        << "Макс. ячеек памяти: 10" << std::endl
        << "Версия памяти: " << NowMV << std::endl
        << "Не релиз!" << std::endl
        << "Версия консоли: 1t (тестовая)" << std::endl;
}

void ShowCommand() {
    std::cout << "1. Справка \n2. CD \n3. Дерево \n4. Инфо \n5. Завершение работы\n6. Очистить\n7. Права\n" << std::endl;
}

int Error(std::string Rights, std::string strct) {
    std::cout << "\033[31m";
    std::cout << "ОШИБКА! ПРОГРАММА АВАРИЙНО ЗАВЕРШИЛАСЬ!" << std::endl;
    std::cout << "\033[35m";
    std::cout << "Пожалуйста, перезагрузите систему! " << std::endl;
    std::cout << "\033[0m";

    std::exit(5);
}

int main() {
    setlocale(LC_ALL, "Ru");
    const size_t max_right = 10;
    const int NowMV = 1;
    int NewMV = 0;
    std::string BD = "C:\\\\";

    bool haveRoot = false; // НЕ ТРОГАТЬ И НЕ МЕНЯТЬ!
    bool shutdown = false; // НЕ ТРОГАТЬ!
    std::vector<std::string> strct{ "\\Users", "\\Main" };
    std::vector<std::string> Rights{ "@User", "@Root", "@Unknown" };

    int user;
    std::string user_string;

    //Анти изменения:
    if (haveRoot)
    {
        std::cout << "\033[31m";
        std::cout << "Ошибка! Защита от изменений!" << std::endl;
        std::cout << "\033[0m";

        std::exit(1);
    }

    if (NowMV != 1 || NewMV != 0)
    {
        std::cout << "\033[31m";
        std::cout << "Ошибка! Защита от изменений!" << std::endl;
        std::cout << "\033[0m";

        std::exit(2);
    }

    //Главный блок:
    BootScreen();

    while (!shutdown) {
        std::cout << "\n1. справка" << std::endl;
        std::cout << "> ";
        std::cin >> user;
        if (user == 1)
        {
            ShowCommand();
        }
        else if (user == 5)
        {
            std::cout << "Завершение работы. Код 0" << std::endl;
            shutdown = true;
        }
        else if (user == 6)
        {
            ClearScreen();
        }
        else if (user == 7)
        {
            std::cout << "1. Добавить права\n2. Изменить права\n3. Все\n4. Назад" << std::endl;
            std::cin >> user;
            if (user == 1)
            {
                if (Rights.size() >= max_right)
                {
                    SimpleError();
                }
                else {
                    std::cout << "Имя: ";
                    //Rights [user_string];
                    std::cin.ignore(10000, '\n');
                    std::getline(std::cin, user_string);
                    Rights.push_back("@" + user_string);
                    std::cout << "Пользователь: @" << user_string << " добавлен." << std::endl;
                }
            }
            else if (user == 2) {
                if (Rights.empty()) {
                    std::cout << "Список прав пуст! Вам нужно добавить пользователя!" << std::endl;
                }
                else {
                    int a = 1;
                    for (size_t i = 0; i < Rights.size(); i++)
                    {
                        std::cout << a++ << ". " << Rights[i] << std::endl;
                    }

                    std::cout << "Выберите пользователя: 1-" << Rights.size() << std::endl;
                    int choice;
                    std::cin >> choice;

                    if (choice < 1 || choice > static_cast<int>(Rights.size()))
                    {
                        std::cout << "Неизвестный пользователь!" << std::endl;
                    }
                    else
                    {
                        std::string userSelect = Rights[choice - 1];
                        std::cout << "Вы выбрали: " << userSelect << std::endl;
                    }
                }
            }
            else if (user == 3)
            {
                AllUser(Rights);
            }
        }
        if (user == 2) {
            FDirectoryPrint(BD);
            std::string PodMenu;

            std::cout << "Вы в меню. Введите 1 для продолжения ИЛИ 2 для возврата в главное меню: " << std::endl;
            std::cin >> PodMenu;
            if (PodMenu == "1")
            {
                while (true)
                {
                    std::cout << "Введите путь: " << std::endl;
                    std::cin.ignore(10000, '\n');
                    std::getline(std::cin, PodMenu);
                }
            }
            if (PodMenu == "2")
            {

            }
            else
            {
                std::cout << "Неизвестная команда" << std::endl;
            }
            //std::cout << "Если вы хотите создать папку, введите 'CD MF {Имя}'" << std::endl;
        }

        else if (user == 4)
        {
            Info(NowMV);
        }
    }

    return 0;
}