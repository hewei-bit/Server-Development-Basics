#include <vector>

//
class IDisplay {
public:
    virtual void Show(float temperature) = 0;
    virtual ~IDisplay() {}
};

class DisplayA : public IDisplay {
public:
    virtual void Show(float temperature);
private:
    void jianyi();
};

class DisplayB : public IDisplay{
public:
    virtual void Show(float temperature);
};

class DisplayC : public IDisplay{
public:
    virtual void Show(float temperature);
};

class WeatherData {
};

class DataCenter {
public:
    void Attach(IDisplay * ob);
    void Detach(IDisplay * ob);
    void Notify() {
        float temper = CalcTemperature();
        for (auto iter = obs.begin(); iter != obs.end(); iter++) {
            (*iter)->Show(temper);
        }
    }

// 接口隔离
private:
    virtual WeatherData * GetWeatherData();

    virtual float CalcTemperature() {
        WeatherData * data = GetWeatherData();
        // ...
        float temper/* = */;
        return temper;
    }
    std::vector<IDisplay*> obs;
};

int main() {
    DataCenter *center = new DataCenter;
    IDisplay *da = new DisplayA();
    IDisplay *db = new DisplayB();
    IDisplay *dc = new DisplayC();
    center->Attach(da);
    center->Attach(db);
    center->Attach(dc);


    
    center->Notify();
    
    //-----
    center->Detach(db);
    center->Notify();
    return 0;
}