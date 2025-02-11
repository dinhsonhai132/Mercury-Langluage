#include <exception>
#include <string>
using namespace std;

class Mer_RuntimeError {
private:
    string fullMsg;
public:
    Mer_RuntimeError(const string& msg) : fullMsg("Runtime Error: " + msg) {}
    const char* what() const throw();
};

class Mer_Error {
private:
    string fullMsg;
public:
    Mer_Error(const string& msg) : fullMsg("Error: " + msg) {}
    const char* what() const throw();
};