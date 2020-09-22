      #include <iostream>
        using namespace std;
        template<typename ... T> void DummyWrapper(T... t) {}
        template <typename T> T pr(T t) {
            cout << t;
            return t;
        }
        template<typename... A>
        void VTPrint(A... a) {
            DummyWrapper(pr(a)...); // 包扩展解包为pr(1), pr(", ")..., pr(", abc\n")
        };
        int main() {
            VTPrint(1, ", ", 1.2, ", abc\n");
        }
        // 编译选项：xlC -+ -qlanglvl=variadictemplates 6-2-5.cpp
