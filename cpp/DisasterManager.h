#ifndef DISASTER_MANAGER_H
#define DISASTER_MANAGER_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "Disaster.h"
#include "Resource.h"
#include "PriorityManager.h"
#include "ResourceAllocator.h"
class DisasterManager{std::vector<Disaster>d;std::vector<Resource>r;CityGraph map;ResourceAllocator allocator;int next=1;void dispatch(){PriorityManager q;for(auto&x:d)if(x.status==Disaster::PENDING)q.push(x);while(!q.empty()){Disaster x=q.pop();std::vector<std::string>p;int km=0,k=allocator.choose(x,r,map,p,km);if(k<0)continue;for(auto&v:d)if(v.id==x.id){v.status=Disaster::ASSIGNED;v.resourceId=r[k].id;}std::cout<<"Dispatch incident #"<<x.id<<" via ";for(auto&z:p)std::cout<<z<<" ";std::cout<<"("<<km<<" km)\n";}}public:DisasterManager(){r.emplace_back(101,"Ambulance","Zone A");r.emplace_back(102,"Fire Truck","Zone B");r.emplace_back(103,"Rescue Team","Zone C");}void report(std::string t,int a,int i,int tr,std::string z){d.emplace_back(next++,t,a,i,tr,z);std::cout<<"Reported #"<<next-1<<" severity "<<d.back().severity()<<"\n";dispatch();}void complete(int id){for(auto&x:d)if(x.id==id&&x.status==Disaster::ASSIGNED){for(auto&v:r)if(v.id==x.resourceId)v.release(x.zone);x.status=Disaster::COMPLETED;std::cout<<"Completed #"<<id<<"; resource released.\n";dispatch();return;}std::cout<<"No assigned incident with that ID.\n";}void showDisasters(){for(auto&x:d)std::cout<<"#"<<x.id<<" "<<x.type<<" "<<x.zone<<" "<<x.severity()<<" status="<<(x.status==0?"PENDING":x.status==1?"ASSIGNED":"COMPLETED")<<"\n";}void showDisastersSorted(){std::vector<Disaster> sorted=d;std::sort(sorted.begin(),sorted.end(),[](const Disaster&a,const Disaster&b){return a.priority()==b.priority()?a.id<b.id:a.priority()>b.priority();});for(const auto&x:sorted)std::cout<<"#"<<x.id<<" "<<x.type<<" "<<x.zone<<" "<<x.severity()<<" status="<<(x.status==0?"PENDING":x.status==1?"ASSIGNED":"COMPLETED")<<"\n";}void showResources(){for(auto&x:r)std::cout<<"#"<<x.id<<" "<<x.type<<" "<<x.zone<<" "<<(x.available?"AVAILABLE":"DEPLOYED")<<"\n";}};
#endif
