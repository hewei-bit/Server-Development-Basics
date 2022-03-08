class Context {

};

class ProStategy {
public:
    virtual double CalcPro(const Context &ctx) = 0;
    virtual ~ProStategy(); 
};
// cpp
class VAC_Spring : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};
// cpp
class VAC_QiXi : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};
class VAC_QiXi1  : public VAC_QiXi {
public:
    virtual double CalcPro(const Context &ctx){}
};
// cpp
class VAC_Wuyi : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};
// cpp
class VAC_GuoQing : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};

class VAC_Shengdan : public ProStategy {
public:
    virtual double CalcPro(const Context &ctx){}
};

class Promotion {
public:
    Promotion(ProStategy *sss) : s(sss){}
    ~Promotion(){}
    double CalcPromotion(const Context &ctx){
        return s->CalcPro(ctx);
    }
private:
    ProStategy *s;
};

int main () {
    Context ctx;
    ProStategy *s = new VAC_QiXi1();
    Promotion *p = new Promotion(s);
    p->CalcPromotion(ctx);
    return 0;
}