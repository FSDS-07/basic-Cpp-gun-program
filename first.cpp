#include <iostream>
#include<termios.h>
#include <unistd.h>

using std::cin;
using std::cout;

class Gun {
    private:
        int avam = 6;

    
    public:
        void reload() {
            if (avam==6){
                cout<<"Loaded Fully\n";
            }
            else{
            avam = 6;
            system("paplay gun-reloading_C_minor.wav &");
            cout << "Reloaded!\n";
            }
        }

        void shoot() {
            if (avam > 0) {
                system("paplay gunshot-punchy.wav &");
                cout << "\aBang!!\n";
                avam--;
            } else {
                system("paplay insert-magazine-in-the-gun-fx.wav &");
                cout << "Out of ammo! Press 'r' to reload.\n";
            }
        }

        void amch() {
            system("paplay gun-cock.wav &");
            cout << "\nAmmo Available: " << avam << "\n";
        }
};

char getKey() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main() {
    Gun M64;
    cout << "Press 's' to shoot, 'r' to reload, 'c' to check ammo, 'q' to quit.\n";
    
    while (true) {
        char key = getKey();
        if (key == 'q' || key == 'Q') {
            break;
        } else if (key == '0' || key == 'S') {
            M64.shoot();
        } else if (key == '.' || key == 'C') {
            M64.amch();
        } else if (key == '\n' || key == 'R') {
            M64.reload();
        } else {
            cout << "Invalid key! Press 's' to shoot, 'r' to reload, 'c' to check ammo, 'q' to quit.\n";
        }
    }
}
