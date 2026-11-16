#ifndef RESOURCE_ALLOCATOR_H
#define RESOURCE_ALLOCATOR_H
#include <vector>
#include "Resource.h"
#include "Disaster.h"
#include "CityGraph.h"
class ResourceAllocator{public:int choose(Disaster&d,std::vector<Resource>&rs,const CityGraph&g,std::vector<std::string>&p,int&km){std::string need=d.type=="Fire"?"Fire Truck":d.type=="Medical Emergency"?"Ambulance":"Rescue Team";int best=-1,bestKm=1000000;for(int i=0;i<(int)rs.size();++i)if(rs[i].available&&rs[i].type==need){std::vector<std::string>path;int dist;if(g.route(rs[i].zone,d.zone,path,dist)&&dist<bestKm){best=i;bestKm=dist;p=path;}}if(best>=0){rs[best].assign(d.id);d.resourceId=rs[best].id;km=bestKm;}return best;}};
#endif
