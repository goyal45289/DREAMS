#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <algorithm>
class CityGraph{std::map<std::string,std::vector<std::pair<std::string,int>>> g;public:CityGraph(){road("Zone A","Zone B",5);road("Zone A","Zone C",10);road("Zone B","Zone C",3);road("Zone B","Zone D",7);road("Zone C","Zone D",2);}void road(std::string a,std::string b,int w){g[a].push_back({b,w});g[b].push_back({a,w});}bool route(std::string s,std::string t,std::vector<std::string>&p,int&cost) const{using N=std::pair<int,std::string>;std::priority_queue<N,std::vector<N>,std::greater<N>>q;std::map<std::string,int>d;std::map<std::string,std::string>prev;for(auto&x:g)d[x.first]=std::numeric_limits<int>::max();if(!d.count(s)||!d.count(t))return false;d[s]=0;q.push({0,s});while(!q.empty()){auto x=q.top();q.pop();if(x.first!=d[x.second])continue;for(auto&e:g.find(x.second)->second)if(d[x.second]+e.second<d[e.first]){d[e.first]=d[x.second]+e.second;prev[e.first]=x.second;q.push({d[e.first],e.first});}}if(d[t]==std::numeric_limits<int>::max())return false;cost=d[t];for(std::string u=t;;u=prev[u]){p.push_back(u);if(u==s)break;}std::reverse(p.begin(),p.end());return true;}};
#endif
