#ifndef EXCEPTIONS_DOM
#define EXCEPTIONS_DOM

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

class InvalidCharacterError : public exception {
    private:
        string message;
    public:
        InvalidCharacterError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};

class NotSupportedError : public exception {
    private:
        string message;
    public:
        NotSupportedError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};

class HeirarchyRequestError : public exception {
    private:
        string message;
    public:
        HeirarchyRequestError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};

class NotFoundError : public exception {
    private:
        string message;
    public:
        NotFoundError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};


class NamespaceError : public exception {
    private:
        string message;
    public:
        NamespaceError(const char* msg): message(msg){};

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


class InUseAttributeError: public exception {
    private:
        string message;
    public:
        InUseAttributeError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};

class SyntaxError: public exception {
    private:
        string message;
    public:
        SyntaxError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};

class IndexSizeError: public exception {
    private:
        string message;
    public:
        IndexSizeError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};

class InvalidNodeTypeError: public exception {
    private:
        string message;
    public:
        InvalidNodeTypeError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};


class WrongDocumentError: public exception {
    private:
        string message;
    public:
        WrongDocumentError(const char* msg): message(msg){};

        const char* what() const noexcept {
            return message.c_str();
        }
};

int main(){}

#endif