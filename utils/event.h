#ifndef _EVENT
#define _EVENT

#include <string>
#include <vector>
#include <algorithm>

struct event_type{
    double timestamp;
    std::string type;
};

class event_list{
    public:
        event_list();
        ~event_list();
        // overloading 
        void set(const event_type x);
        // get 
        int get(event_type& x);
        // size
        int size();
        // record
        void record(const event_type x);
        // Global
        std::vector<event_type> rec;
    private:
        std::vector<event_type> list;
};

#endif