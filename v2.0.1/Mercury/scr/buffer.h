#ifndef MERCURY_BUFFER_HEADER_FILE
#define MERCURY_BUFFER_HEADER_FILE
#include <string>
using namespace std;

char* MerBuffer_read_file_source(string file_name, string &source);
char* MerBuffer_read_file(string file_name);

#endif // MERCURY_BUFFER_HEADER_FILE