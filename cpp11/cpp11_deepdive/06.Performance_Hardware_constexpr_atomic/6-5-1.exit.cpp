        #include <cstdlib>
        #include <iostream>
        using namespace std;
        void openDevice() { cout << "device is opened." << endl; }
        void resetDeviceStat() { cout << "device stat is reset." << endl; }
        void closeDevice() { cout << "device is closed." << endl; }
        int main() {
            atexit(closeDevice);
            atexit(resetDeviceStat);
            openDevice();
            exit(0);
        }
        //编译选项: g++ 6-5-1.cpp
