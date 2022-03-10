#include <iostream>
using namespace std;

#if 0
class ZooShow {
public:
    void Show0() {
        cout << "show0" << endl;
    }
    void Show2() {
        cout << "show2" << endl;
    }
};

class ZooShowEx {
public:
    void Show1() {
        cout << "show1" << endl;
    }
    void Show3() {
        cout << "show3" << endl;
    }
};

// 不满足单一职责 ， 开 扩展 修改闭原则
// 动物园固定流程，迭代创新
// 稳定和变化   一定的方向上变化
#else if 2
class ZooShow {
public:
    ZooShow(int type = 1) : _type(type) {}

public:
    void Show() {
        if (Show0())
            PlayGame(); // 里氏替换
        Show1();
        Show2();
        Show3();
    }

// 接口隔离 不要让用户去选择它们不需要的接口
private:
    void PlayGame() {
        cout << "after Show0, then play game" << endl;
    }

private:
    bool Show0() {
        cout << _type << " show0" << endl;
        return true;
    }

    void Show1() {
        if (_type == 1) {
            cout << _type << " Show1" << endl;
        } else if (_type == 2) {
            cout << _type << " Show1" << endl;
        } else if (_type == 3) {

        }
    }

    void Show2() {
        if (_type == 20) {
            
        }
        cout << "base Show2" << endl;
    }

    void Show3() {
        if (_type == 1) {
            cout << _type << " Show1" << endl;
        } else if (_type == 2) {
            cout << _type << " Show1" << endl;
        }
    }
private:
    int _type;
};

#endif

int main () {
#if 0
    ZooShow *zs = new ZooShow;
    ZooShowEx *zs1 = new ZooShowEx;
    zs->Show0();
    zs1->Show1();
    zs->Show2();
    zs1->Show3();
#else if 2
    ZooShow *zs = new ZooShow(1);
    zs->Show();
#endif
    return 0;
}
