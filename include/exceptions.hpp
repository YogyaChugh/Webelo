#pragma once

#include <string>

using namespace std;

class InvalidStateError : public exception {
    private:
        string message;
    public:
        InvalidStateError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};

class AbortError: public exception {
    private:
        string message;
    public:
        AbortError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};