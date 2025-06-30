#include "events.hpp"
#include <vector>

class AbortController{
    private:
        AbortSignal signal;
    public:
    AbortController();

    AbortSignal getsignal();

    template <typename T>
    void abort(T reason);
}

template <typename T>
class AbortSignal: public EventTarget{
    private:
        bool aborted;
        T reason;
    public:
        const AbortSignal abort(T reason);
        //TODO: Expose to only Window and Worker
        //TODO: EnforceRange
        const AbortSignal timeout(unsigned long long milliseconds);
        const AbortSignal _any(std::vector<AbortSignal> signals);
        void throwIfAborted();
        EventHandler onabort;
        bool dependent;
        std::vector<AbortSignal> source_signals = {};
        std::vector<AbortSignal> dependent_signals = {};


        bool getaborted(){
            return aborted;
        }
        T getreason(){
            return reason;
        }
}