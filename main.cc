#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
class Contents {
public:
  Contents(int id, std::string chr,std::vector<std::string> in_strv)
    :id(id),chr(chr), m_strv(in_strv){
     m_strv.push_back("aaaa");
     m_strv.push_back("ffffaaaa");
   }
    std::vector<std::string> m_strv;
    int id;
    std::string chr;
};

std::ostream& operator<<(std::ostream &out, const Contents &me){
    for (int i = 0;i<me.m_strv.size(); ++i)
    out << "Id: " << me.id << " Chr: " << me.chr <<me.m_strv.back();
    return out;
}

std::vector<std::string> tmpv;
//tmpv.push_back("vector 1");
//tmpv.push_back("vector 201");

const Contents defaultBad (-1, "my local string", tmpv);
const size_t Container_Vector_Size = 4;

struct Container{
    std::vector<Contents> data;

    Container():data(Container_Vector_Size, defaultBad){}

    void serialize( std::ostream &stream ) const {
        for( size_t i = 0; i < Container_Vector_Size; ++i){
            stream.write( reinterpret_cast <const char*> ( &data[i] ), sizeof( Contents ) ); 
        }
    }
    void deserialize( std::istream &stream ) {
        data.clear();
        std::vector<char> buffer(sizeof(Contents));
        for( size_t i = 0; i < Container_Vector_Size; ++i){
            stream.read(&buffer[0], sizeof(Contents));
            data.push_back(*reinterpret_cast<Contents*>(&buffer[0]));
        }
    }
};

std::stringbuf& operator<<(std::stringbuf &stream, Container &me) {
    std::istream ibuffer(&stream);
    me.deserialize(ibuffer);
    return stream;
}

std::stringbuf& operator>>(std::stringbuf &stream, const Container &me) {
    std::ostream obuffer(&stream);
    me.serialize(obuffer);
    return stream;
}

std::ostream& operator<<(std::ostream &stream, const Container &me) {
    stream << "Container {" << std::endl;
    for( size_t i = 0; i < Container_Vector_Size; ++i){
        stream << i << ": " << me.data[i] << std::endl;
    }
    stream << "}" << std::endl << std::endl;
    return stream;
}

int main(){
    Container start;
    start.data[0].id = 1;
    start.data[0].chr = "first test";

    start.data[1].id = 2;
    start.data[1].chr = "second test";

    start.data[2].id = 3;
    start.data[2].chr = "third test";

    start.data[3].id = 4;
    start.data[3].chr = "fourth test";

    Container reached;
    std::stringbuf buffer;
    buffer >> start;
    buffer << reached;


    std::cout << start;
    std::cout << reached;
}
