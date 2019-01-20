// Datastructures.cc

#include "datastructures.hh"

#include <iostream>
#include <random>
#include <climits>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
#include <list>
#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}


Datastructures::Datastructures()
{
    // Replace with actual implementation
}

Datastructures::~Datastructures()
{
    // Replace with actual implementation
}

unsigned int Datastructures::size()
{
    return townmap.size();
}

void Datastructures::clear()
{
    townmap.clear();
    alphamap.clear();
    distmap.clear();
    roadmap.clear();
    alphalistUpdated = false;
    distlistUpdated = false;
}

std::string Datastructures::get_name(TownID id)
{
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        return mapIter->second.name;
    }
    return NO_NAME;
}

Coord Datastructures::get_coordinates(TownID id)
{
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        return std::pair<int, int> (mapIter->second.x, mapIter->second.y);
    }
    return {NO_VALUE, NO_VALUE};
}

int Datastructures::get_tax(TownID id)
{
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        return mapIter->second.tax;
    }
    return NO_VALUE;
}

std::vector<TownID> Datastructures::get_vassals(TownID id)
{
    std::vector<TownID> tlist;
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        tlist = mapIter->second.vassal;
        return tlist;
    }
    return {NO_ID};
}

std::vector<TownID> Datastructures::all_towns()
{
    std::vector<TownID> townList;
    for (auto town : townmap) {
        townList.push_back(town.first);
    }
    return townList;
}

bool Datastructures::add_town(TownID id, const std::string& name, int x, int y, int tax)
{
    if (townmap.find(id) != townmap.end()) {
        return false;
    }

    dist = abs(x) + abs(y);

    townmap.insert(std::pair<TownID, TownData> (id, TownData(id, name, x, y, tax)));
    alphamap.insert(std::pair<std::string, TownID> (name, id));
    distmap.insert(std::pair<int, TownID> (dist, id));

    distlistUpdated = false;
    alphalistUpdated = false;

    return true;
}

bool Datastructures::change_town_name(TownID id, const std::string& newname)
{
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        (*mapIter).second.name = newname;
        alphalistUpdated = false;

        for (auto town : alphamap) {
            if (town.second == id) {
                alphamap.erase(town.first);
                alphamap.insert(std::pair<std::string, TownID> (newname, id));
                break;
            }
        }
        return true;
    }
    return false;
}

bool Datastructures::remove_town(TownID id)
{
    std::vector<TownID> tlist;
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        tempID = mapIter->second.master;
        if (tempID != "") {
            townmap.at(tempID).vassal.erase(std::find(townmap.at(tempID).vassal.begin(),
                                                      townmap.at(tempID).vassal.end(), id));
            tlist = mapIter->second.vassal;
            if (!tlist.empty()) {
                for (auto tID : tlist) {
                    townmap.at(tID).master = tempID;
                    townmap.at(tempID).vassal.push_back(tID);
                }
                std::sort(townmap.at(tempID).vassal.begin(), townmap.at(tempID).vassal.end());
            }
        } else {
            tlist = mapIter->second.vassal;
            if (!tlist.empty()) {
                for (auto tID : tlist) {
                    townmap.at(tID).master = "";
                }
            }
        }
        townmap.erase(mapIter);
        iter = alphamap.begin();
        while (iter != alphamap.end()) {
            if (iter->second == id) {
                alphamap.erase(iter);
                break;
            }
            ++iter;
        }
        iter2 = distmap.begin();
        while (iter2 != distmap.end()) {
            if (iter2->second == id) {
                distmap.erase(iter2);
                break;
            }
            ++iter2;
        }
        alphalistUpdated = false;
        distlistUpdated = false;
        return true;
    }
    return false;
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    if (townmap.size() == 0) {
        return {};
    }
    if (alphalistUpdated) {
        return alphalist;
    }

    alphalist.clear();
    alphalist.reserve(townmap.size());

    for (auto town : alphamap) {
        alphalist.push_back(town.second);
    }
    alphalistUpdated = true;
    return alphalist;
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    if (townmap.size() == 0) {
        return {};
    }
    if (distlistUpdated) {
        return distlist;
    }

    distlist.clear();
    distlist.reserve(townmap.size());

    for (auto town : distmap) {
        distlist.push_back(town.second);
    }
    distlistUpdated = true;
    return distlist;
}

std::vector<TownID> Datastructures::find_towns(std::string const& name)
{
    if (townmap.size() == 0) {
        return {};
    }
    std::vector<TownID> tlist;

    auto ren = alphamap.equal_range(name);
    for (auto it = ren.first; it != ren.second; ++it) {
        tlist.push_back(it->second);
    }

    std::sort(tlist.begin(), tlist.end());
    return tlist;
}

TownID Datastructures::min_distance()
{
    if (townmap.size() == 0)
        return NO_ID;

    if (distlistUpdated) {
        return distlist[0];
    }

    distlist.clear();
    distlist.reserve(townmap.size());

    for (auto town : distmap) {
        distlist.push_back(town.second);
    }
    distlistUpdated = true;
    return distlist[0];
}

TownID Datastructures::max_distance()
{
    if (townmap.size() == 0)
        return NO_ID;

    if (distlistUpdated) {
        return distlist[townmap.size() - 1];
    }

    distlist.clear();
    distlist.reserve(townmap.size());

    for (auto town : distmap) {
        distlist.push_back(town.second);
    }
    distlistUpdated = true;
    return distlist[townmap.size() - 1];
}

TownID Datastructures::nth_distance(unsigned int n)
{
    if (townmap.size() == 0 || n == 0 || n > townmap.size())
        return NO_ID;

    if (distlistUpdated) {
        return distlist[n - 1];
    }

    distlist.clear();
    distlist.reserve(townmap.size());

    for (auto town : distmap) {
        distlist.push_back(town.second);
    }
    distlistUpdated = true;
    return distlist[n - 1];
}

std::vector<TownID> Datastructures::towns_distance_increasing_from(int x, int y)
{
    if (x == 0 && y == 0 && distlistUpdated) {
        return towns_distance_increasing();
    }

    std::vector<TownID> tlist;
    tlist.reserve(townmap.size());
    std::multimap<int, TownID> distmapxy;

    for (auto town : townmap) {
        auto tempn = abs(town.second.x - x) + abs(town.second.y - y);
        distmapxy.insert(std::pair<int, TownID> (tempn, town.first));
    }
    for (auto town : distmapxy) {
        tlist.push_back(town.second);
    }
    return tlist;
}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    mapIter = townmap.find(masterid);
    std::unordered_map<TownID, TownData>::iterator mapIter2 = townmap.find(vassalid);
    if (mapIter != townmap.end() && mapIter2 != townmap.end()) {
        if(mapIter2->second.master == "") {
            mapIter->second.vassal.insert(std::upper_bound(mapIter->second.vassal.begin(),
                                                           mapIter->second.vassal.end(),
                                                           vassalid), vassalid);
            mapIter2->second.master = masterid;
            return true;
        }
    }
    return false;
}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    std::vector<TownID> tlist;
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        tlist.push_back(id);
        while (mapIter->second.master != "") {
            tlist.push_back(mapIter->second.master);
            mapIter = townmap.find(mapIter->second.master);
        }
    }
    return tlist;
}

std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    std::vector<std::pair<TownID, TownID>> roads;
    for (auto town1 : roadmap) {
        for (auto town2 : town1.second) {
            roads.push_back(std::pair<TownID, TownID> (town1.first, town2));
        }
    }
    return roads; // Replace with actual implementation
}

std::vector<TownID> Datastructures::get_roads_from(TownID id)
{
    if (townmap.find(id) != townmap.end()) {
        std::vector<TownID> roads;
        for (auto town : townmap.at(id).connections) {
            roads.push_back(town);
        }
        return roads;
    }
    return {NO_ID}; // Replace with actual implementation
}

bool Datastructures::add_road(TownID town1, TownID town2)
{
    if (townmap.find(town1) != townmap.end() &&
            townmap.find(town2) != townmap.end()) {
        if (roadmap[town1].find(town2) == roadmap[town1].end()) {
            if (town1 < town2) {
                roadmap[town1].insert(town2);
            } else {
                roadmap[town2].insert(town1);
            }
            townmap.at(town1).connections.insert(town2);
            townmap.at(town2).connections.insert(town1);
            return true;
        }
    }
    return false; // Replace with actual implementation
}

bool Datastructures::remove_road(TownID town1, TownID town2)
{
    if (town1 > town2) {
        tempID = town1;
        town1 = town2;
        town2 = tempID;
    }

    auto pos = roadmap.find(town1);
    if (pos != roadmap.end()) {
        auto road = roadmap.at(town1).find(town2);
        if (road != roadmap.at(town1).end()) {
            roadmap.at(town1).erase(road);
            townmap.at(town1).connections.erase(town2);
            townmap.at(town2).connections.erase(town1);
            return true;
        }
    }
    return false; // Replace with actual implementation
}

void Datastructures::clear_roads()
{
    roadmap.clear();
    for (auto town : townmap) {
        town.second.connections.clear();
    }
    // Replace with actual implementation
}

std::vector<TownID> Datastructures::any_route(TownID fromid, TownID toid)
{
    if (townmap.find(fromid) != townmap.end() &&
            townmap.find(toid) != townmap.end()) {
        std::vector<TownID> route;
        if (fromid == toid) {
            route.push_back(fromid);
            return route;
        }

        std::map<TownID, bool> visited;
        std::map<TownID, TownID> parent;

        for (auto town : townmap) {
            visited[town.first] = false;
            parent[town.first] = NO_ID;
        }

        std::list<TownID> queue;
        visited.at(fromid) = true;
        queue.push_back(fromid);

        TownID fid;

        while (!queue.empty()) {
            fid = queue.front();
            queue.pop_front();

            for (auto town : townmap.at(fid).connections) {
                if (!visited.at(town)) {
                    visited.at(town) = true;
                    queue.push_back(town);
                    parent.at(town) = fid;
                    if (town == toid) {
                        TownID curr = town;
                        route.push_back(town);
                        while (curr != fromid) {
                            route.insert(route.begin(), parent.at(curr));
                            curr = parent.at(curr);
                        }
                        return route;
                    }
                }
            }
        }
        return {};
    }
    return {NO_ID}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    idception.clear();
    std::vector<TownID> tlist;
    vlist.clear();
    unsigned int tempn = 0;
    if (townmap.size() == 0) {
        return {};
    }

    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        if (mapIter->second.vassal.size() == 0) {
            tlist.push_back(id);
            return tlist;
        }
        add_vassal_vectors(id);
    }

    for (auto list : idception) {
        if (list.size() > tempn) {
            tempn = list.size();
            tlist = list;
        }
    }
    return tlist;
}

int Datastructures::total_net_tax(TownID id)
{
    unsigned int tempn = NO_VALUE;
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        tempn = mapIter->second.tax;
        for (auto vid : townmap.at(id).vassal) {
            tempn += vassal_taxes(vid);
        }
        if (mapIter->second.master != "") {
            tempn -= (int) (0.1 * tempn);
        }
    }
    return tempn;
}

std::vector<TownID> Datastructures::least_towns_route(TownID fromid, TownID toid)
{
    return any_route(fromid, toid);
    /*if (townmap.find(fromid) != townmap.end() &&
            townmap.find(toid) != townmap.end()) {
        std::list<TownID> queue;
        std::map<TownID, bool> visited;
        std::map<TownID, TownID> parent;

        std::vector<TownID> route;

        for (auto town : townmap) {
            visited[town.first] = false;
            parent[town.first] = NO_ID;
        }

        visited.at(fromid) = true;
        queue.push_back(fromid);

        TownID fid;

        while (!queue.empty()) {
            fid = queue.front();
            queue.pop_front();

            for (auto town : townmap.at(fid).connections) {
                if (!visited.at(town)) {
                    visited.at(town) = true;
                    parent.at(town) = fid;
                    queue.push_back(town);

                    if (town == toid) {
                        TownID curr = town;
                        route.push_back(curr);
                        while (curr != fromid) {
                            route.insert(route.begin(), parent.at(curr));
                            curr = parent.at(curr);
                        }
                        return route;
                    }
                }
            }
        }
        return {};
    }
    return {NO_ID}; // Replace with actual implementation*/
}

std::vector<TownID> Datastructures::shortest_route(TownID fromid, TownID toid)
{
    if (townmap.find(fromid) != townmap.end() &&
            townmap.find(toid) != townmap.end()) {
        std::map<TownID, bool> visited;
        std::map<TownID, TownID> parent;
        std::map<TownID, int> dist;

        if (any_route(fromid, toid).empty()) {
            return {};
        }

        for (auto town : townmap) {
            visited[town.first] = false;
            dist[town.first] = INT_MAX;
            parent[town.first] = NO_ID;
        }

        dist.at(fromid) = 0;
        visited.at(fromid) = true;

        std::priority_queue<TownID, std::vector<TownID>, revPriority> queue;
        queue.push(fromid);

        TownID fid;

        while (!queue.empty()) {
            fid = queue.top();
            queue.pop();

            for (auto town : townmap.at(fid).connections) {
                if (!visited.at(town)) {
                    visited.at(town) = true;
                    queue.push(town);
                }
                int roadWeight = abs(townmap.at(town).x - townmap.at(fid).x) +
                        abs(townmap.at(town).y - townmap.at(fid).y);
                if (dist.at(town) > dist.at(fid) + roadWeight) {
                    dist.at(town) = dist.at(fid) + roadWeight;
                    parent.at(town) = fid;
                }
            }
        }
        std::vector<TownID> route;
        TownID curr = toid;
        route.push_back(curr);
        while (curr != fromid) {
            route.insert(route.begin(), parent.at(curr));
            curr = parent.at(curr);
        }
        return route;
    }
    return {NO_ID}; // Replace with actual implementation
}

std::vector<TownID> Datastructures::road_cycle_route(TownID startid)
{
    if (townmap.find(startid) != townmap.end()) {
        std::map<TownID, bool> visited;
        std::map<TownID, TownID> parents;

        TownID routeUtil[size()];

        std::vector<TownID> route;
        counter = 0;

        for (auto town : townmap) {
            visited[town.first] = false;
            parents[town.first] = NO_ID;
        }

        if (isCyclic(startid, visited, startid, routeUtil)) {
            for (int i = 0; i < counter; ++i) {
                route.push_back(routeUtil[i]);
            }

            // Address the case where the startid is part of the cycle by adding the start node.
            if (route.front() != route.back()) {
                route.push_back(route.front());
            }
            return route;
        }
        return {};
    }
    return {NO_ID}; // Replace with actual implementation
}

Dist Datastructures::trim_road_network()
{
    std::vector<std::pair<TownID, TownID>> roads = all_roads();
    std::vector<std::pair<std::pair<TownID, TownID>, int>> weighted_roads;

    int dist1;
    TownID from, to;
    for (auto road : roads) {
        dist1 = abs(townmap.at(road.first).x - townmap.at(road.second).x) +
                abs(townmap.at(road.first).y - townmap.at(road.second).y);
        weighted_roads.push_back(std::pair<std::pair<TownID, TownID>, int> (road, dist1));
    }
    std::sort(weighted_roads.begin(), weighted_roads.end(), roadSort);

    std::map<TownID, bool> visited;
    dist1 = 0;
    parentT.clear();

    for (auto town : townmap) {
        visited[town.first] = false;
        parentT[town.first] = town.first;
    }

    clear_roads();

    for (auto road : weighted_roads) {
        from = findSet(road.first.first);
        to = findSet(road.first.second);
        if (from != to) {
            dist1 += road.second;
            add_road(road.first.first, road.first.second);
            UnionSet(from, to);
        }
    }

    return dist1; // Replace with actual implementation
}

TownID Datastructures::findSet(const TownID &town) {
    if (town == parentT.at(town)) {
        return town;
    } else {
        return findSet(parentT.at(town));
    }
}

void Datastructures::UnionSet(const TownID &town1, const TownID &town2) {
    parentT.at(town1) = parentT.at(town2);
}

bool Datastructures::isCyclic(TownID id, std::map<TownID, bool> &visited,
                              TownID parent, TownID *routeUtil)
{
    visited.at(id) = true;

    for (auto town : townmap.at(id).connections) {
        if (!visited.at(town)) {
            if (isCyclic(town, visited, id, routeUtil)) {
                routeUtil[++counter] = town;
                return true;
            }
        } else if (town != parent) {
            routeUtil[counter] = town;
            return true;
        }
    }
    return false;
}

void Datastructures::add_vassal_vectors(const TownID &id)
{
    vlist.push_back(id);
    for (auto vassal : townmap.at(id).vassal) {
        add_vassal_vectors(vassal);
        idception.push_back(vlist);
        vlist.clear();
    }

}

int Datastructures::vassal_taxes(const TownID &id)
{
    int vassal_tax = 0;
    for (auto vassal : townmap.at(id).vassal) {
        vassal_tax += vassal_taxes(vassal);
    }
    return (int) (0.1 * (townmap.at(id).tax + vassal_tax));
}
