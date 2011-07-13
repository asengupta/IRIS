#ifndef WORDFINDER_H
#define WORDFINDER_H

#include <iostream>
#include <cstring>
#include <cstdlib>

namespace Comrade {
    namespace IrisRuntime {

class WordFinder
{
protected:      char* string_handle;
                int ptr;
                bool is_valid;

public:         bool success;

                WordFinder();
                void reset();
                int return_ptr();
                void set_ptr(int p);
                void assign_string(char* str);
                char find_next_nonspace();
                void find_next_word(char* result);
                void find_next_word(int& num);
                bool verify_if_number(char* c);
                ~WordFinder();
};

}
}

#endif

