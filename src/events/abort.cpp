#ifndef ABORT_MAIN
#define ABORT_MAIN

#include "../include/nodes/node.hpp"
#include "../exceptions.cpp"

AbortController::AbortController(){
    signal = AbortSignal();
}

template <typename T>
AbortController::abort(T reason){
}

const AbortSignal AbortSignal::abort(T reason){
    AbortSignal signal;
    if (reason){
        signal.reason = reason;
    }
    else{
        signal.reason = new AbortError("Aborting...")
    }
    return signal;
}

const AbortSignal timeout(unsigned long long milliseconds){
    AbortSignal signal;
    //*INCOMPLETE
    return signal;
}

const AbortSignal _any(std::vector<AbortSignal> signals){
    AbortSignal signal;
    //*INCOMPLETE
    return signal;
}

void AbortSignal::throwIfAborted(){
    if (aborted){
        throw reason;
    }
}

int main(){}

#endif