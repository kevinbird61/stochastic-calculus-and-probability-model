#include "event.h"

event_list::event_list(){}

event_list::~event_list(){}

// let the smallest be last
bool comp(const event_type &a,const event_type &b){return a.timestamp > b.timestamp;}

void event_list::set(const event_type x){
    // push the x into list ,and sort it
    list.push_back(x);
    // sort it
    std::sort(list.begin(),list.end(),comp);
}

void event_list::set(const double ts, const std::string type){
    // create 
    event_type x;
    x.timestamp=ts;
    x.type=type;
    // push the x into list ,and sort it
    list.push_back(x);
    // sort it
    std::sort(list.begin(),list.end(),comp);
}

int event_list::get(event_type& x){
    if(list.size()>0){
        x = list.back();
        list.pop_back();
        return 1;
    }
    else{
        fprintf(stderr,"Nothing left in event list!\n");
        return 0;
    }
}

int event_list::size(){
    return list.size();
}

void event_list::record(event_type x){
    if(rec.size()==0)
        rec.push_back(x);
    else{
        // update time
        x.timestamp += rec.back().timestamp;
        // push back into record
        rec.push_back(x);
    }
}