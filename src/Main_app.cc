#include <Data.hh>
using namespace TNB;
int main(int argc, char **argv) { 
    if (argc < 2) return 1;
    string arg = argv[1];
    if (arg == "test") {
        if (argc < 3) return 1;
        string test = argv[2];
        if (test == "writer") {
            TNBWriter writer;
            cout << "Data to write:" << endl;
            cout << "TAG   TYPE   VALUE" << endl;
            cout << "t      NUM   9" << endl;
            cout << "s      STR   Hi!" << endl;
            cout << "d      ARR   1, 2" << endl;
            cout << "b     BOOL   true" << endl;
            cout << "c     CONT   { s1: 1 }" << endl;
            writer.Push("t", (float)9);
            writer.Push("s", (string)"Hi!");
            Array arr;
            Container cont;
            cont.Push("s1", (float)1);
            arr.Push(ArrayElement((float)1, -1));
            arr.Push(ArrayElement((float)2, -1));
            writer.Push("d", arr);
            writer.Push("b", true);
            writer.Push("c", cont);
            cout << "Serialized as string: " << writer.AsString() << endl;
            writer.Write("test.tnb");
        } else if (test == "reader") {
            TNBParser parser = TNBParser("test.tnb");
            cout << "Version of TNB: " << parser.GetVersion() << endl;
            cout << "Data size: " << parser.GetSize() << endl;
            cout << parser.Get("t").AsString() << endl;
            cout << parser.Get("s").AsString() << endl;
            cout << parser.Get("b").AsString() << endl;
            cout << parser.Get("d").AsString() << endl;
            cout << parser.Get("c").AsString() << endl;
        }
    } else if (arg == "read") {
        if (argc < 3) return 1;
        string file = argv[2];
        TNBParser parser = TNBParser(file);
        list<string> tags = parser.GetTags();
        for (string tag : tags) {
            Element element = parser.Get(tag);
            if (element.GetType() == 3) {
                cout << element.GetTag() << ": ";
                
            }
        }
    }
    return 0;
}
