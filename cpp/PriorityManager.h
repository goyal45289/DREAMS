#ifndef PRIORITY_MANAGER_H
#define PRIORITY_MANAGER_H
#include <queue>
#include <vector>
#include "Disaster.h"
struct DisasterOrder{bool operator()(const Disaster&a,const Disaster&b)const{return a.priority()==b.priority()?a.id>b.id:a.priority()<b.priority();}};
class PriorityManager{std::priority_queue<Disaster,std::vector<Disaster>,DisasterOrder> q;public:void push(const Disaster&d){q.push(d);}bool empty()const{return q.empty();}Disaster pop(){Disaster d=q.top();q.pop();return d;}};
#endif
