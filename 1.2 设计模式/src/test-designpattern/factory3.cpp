#include <string>
// 实现导出数据的接口, 导出数据的格式包含 xml，json，文本格式txt 后面可能扩展excel格式csv
class IExport {
public:
    virtual bool Export(const std::string &data) = 0;
    virtual ~IExport(){}
};

class ExportXml : public IExport {
public:
    virtual bool Export(const std::string &data) {
        return true;
    }
};

class ExportJson : public IExport {
public:
    virtual bool Export(const std::string &data) {
        return true;
    }
};

class ExportTxt : public IExport {
public:
    virtual bool Export(const std::string &data) {
        return true;
    }
};

class ExportCSV : public IExport {
public:
    virtual bool Export(const std::string &data) {
        return true;
    }
};

class IExportFactory {
public:
    IExportFactory() {
        _export = nullptr;
    }
    virtual ~IExportFactory() {
        if (_export) {
            delete _export;
            _export = nullptr;
        }
    }
    bool Export(const std::string &data) {
        if (_export == nullptr) {
            _export = NewExport();
        }
        return _export->Export(data);
    }
protected:
    virtual IExport * NewExport(/* ... */) = 0;
private:
    IExport* _export;
};

class ExportXmlFactory : public IExportFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportXml();
        // 可能之后有什么操作
        return temp;
    }
};
class ExportJsonFactory : public IExportFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportJson;
        // 可能之后有什么操作
        return temp;
    }
};
class ExportTxtFactory : public IExportFactory {
protected:
    IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportTxt;
        // 可能之后有什么操作
        return temp;
    }
};

class ExportCSVFactory : public IExportFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportCSV;
        // 可能之后有什么操作
        return temp;
    }
};

int main () {
    IExportFactory *factory = new ExportTxtFactory();
    factory->Export("hello world");
    return 0;
}