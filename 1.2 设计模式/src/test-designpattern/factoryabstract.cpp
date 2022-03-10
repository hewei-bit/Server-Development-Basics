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

class IImport {
public:
    virtual bool Import(const std::string &data) = 0;
    virtual ~IImport(){}
};

class ImportXml : public IImport {
public:
    virtual bool Import(const std::string &data) {
        return true;
    }
};

class ImportJson : public IImport {
public:
    virtual bool Import(const std::string &data) {
        return true;
    }
};

class ImportTxt : public IImport {
public:
    virtual bool Import(const std::string &data) {
        return true;
    }
};

// 对于初学者： 知道扩展代码
// 5年
class ImportCSV : public IImport {
public:
    virtual bool Import(const std::string &data) {
        // ....
        return true;
    }
};

class IDataApiFactory {
public:
    IDataApiFactory() {
        _export = nullptr;
        _import = nullptr;
    }
    virtual ~IDataApiFactory() {
        if (_export) {
            delete _export;
            _export = nullptr;
        }
        if (_import) {
            delete _import;
            _import = nullptr;
        }
    }
    bool Export(const std::string &data) {
        if (_export == nullptr) {
            _export = NewExport();
        }
        return _export->Export(data);
    }
    bool Import(const std::string &data) {
        if (_import == nullptr) {
            _import = NewImport();
        }
        return _import->Import(data);
    }
protected:
    virtual IExport * NewExport(/* ... */) = 0;
    virtual IImport * NewImport(/* ... */) = 0;
private:
    IExport *_export;
    IImport *_import;
};

class XmlApiFactory : public IDataApiFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportXml;
        // 可能之后有什么操作
        return temp;
    }
    virtual IImport * NewImport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IImport * temp = new ImportXml;
        // 可能之后有什么操作
        return temp;
    }
};

class JsonApiFactory : public IDataApiFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportJson;
        // 可能之后有什么操作
        return temp;
    }
    virtual IImport * NewImport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IImport * temp = new ImportJson;
        // 可能之后有什么操作
        return temp;
    }
};
class TxtApiFactory : public IDataApiFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportTxt;
        // 可能之后有什么操作
        return temp;
    }
    virtual IImport * NewImport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IImport * temp = new ImportTxt;
        // 可能之后有什么操作
        return temp;
    }
};

class CSVApiFactory : public IDataApiFactory {
protected:
    virtual IExport * NewExport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IExport * temp = new ExportCSV;
        // 可能之后有什么操作
        return temp;
    }
    virtual IImport * NewImport(/* ... */) {
        // 可能有其它操作，或者许多参数
        IImport * temp = new ImportCSV;
        // 可能之后有什么操作
        return temp;
    }
};

// 相关性  依赖性    工作当中
int main () {
    IDataApiFactory *factory = new CSVApiFactory();
    factory->Import("hello world");
    factory->Export("hello world");
    return 0;
}