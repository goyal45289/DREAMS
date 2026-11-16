#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
struct Resource{int id;std::string type,zone;bool available;int incident;Resource(int n,std::string t,std::string z):id(n),type(t),zone(z),available(true),incident(-1){} void assign(int d){available=false;incident=d;}void release(std::string z){available=true;incident=-1;zone=z;}};
#endif
