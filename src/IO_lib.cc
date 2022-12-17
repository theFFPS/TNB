#include <IO.hh>
#include <fstream>
namespace TNB {
    string ReadFile(string fileName) {
        string out;
        string line;
        ifstream f (fileName);
        if (! f.good()) exit(-1);
        while (getline(f, line)) out += line;
        f.close();
        return FromBytes(out);
    }
    string FromBytes(string data) {
        string out;
        for (int i = 0; i < (int)data.size(); i++) out += data[i] + 100; 
        return out;
    }
    string ToBytes(string data) {
        string out;
        for (int i = 0; i < (int)data.size(); i++) out += data[i] - 100; 
        return out;
    }
    string IntAsString(unsigned long long intt) {
        stringstream ss;
        ss << intt;
        return ss.str();
    }
    void WriteToFile(string fileName, string serializedData) {
        string toWrite = "100a\\" + IntAsString(serializedData.size()) + "\\" + serializedData;
        ofstream f (fileName);
        f << ToBytes(toWrite);
        f.close();
    }
}