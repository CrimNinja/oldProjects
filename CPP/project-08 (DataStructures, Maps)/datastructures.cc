// Datastructures.cc

#include "datastructures.hh"

#include <cmath>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <vector>
#include <random>

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

}

Datastructures::~Datastructures()
{

}

unsigned int Datastructures::size()
{
    return townlist.size();
}

void Datastructures::clear()
{
    townlist.clear();
    townmap.clear();
    alphamap.clear();
    distmap.clear();
    alphalistUpdated = false;
    distlistUpdated = false;
}

std::string Datastructures::get_name(TownID id)
{
    if (townlist.size() == 0) {
        return NO_NAME;
    }
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        return mapIter->second.name;
    }
    return NO_NAME;
}

std::pair<int, int> Datastructures::get_coordinates(TownID id)
{
    if (townlist.size() == 0) {
        return {NO_VALUE, NO_VALUE};
    }
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        return std::pair<int, int> (mapIter->second.x, mapIter->second.y);
    }
    return {NO_VALUE, NO_VALUE};
}

int Datastructures::get_tax(TownID id)
{
    if (townlist.size() == 0) {
        return NO_VALUE;
    }
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        return mapIter->second.tax;
    }
    return NO_VALUE;
}

std::vector<TownID> Datastructures::get_vassals(TownID id)
{
    if (townlist.size() == 0) {
        return {NO_ID};
    }
    tlist.clear();
    mapIter = townmap.find(id);
    if (mapIter != townmap.end()) {
        tlist = mapIter->second.vassal;
        return tlist;
    }
    return {NO_ID};
}

std::vector<TownID> Datastructures::all_towns()
{
    return townlist;
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

    townlist.push_back(id);
    return true;
}

bool Datastructures::change_town_name(TownID id, const std::string& newname)
{
    if (townlist.size() == 0) {
        return false;
    }
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
    tlist.clear();
    if (townlist.size() == 0) {
        return false;
    }
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
//                    if (tlist.size() > 10) {
                        townmap.at(tempID).vassal.push_back(tID);
//                    } else {
//                        townmap.at(tempID).vassal.insert(std::upper_bound(
//                                                             townmap.at(tempID).vassal.begin(),
//                                                             townmap.at(tempID).vassal.end(),
//                                                             tID), tID);
//                    }
                }
//                if (tlist.size() > 10) {
                    std::sort(townmap.at(tempID).vassal.begin(), townmap.at(tempID).vassal.end());
//                }
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
        for (unsigned int i = 0; i < townlist.size(); ++i) {
            if (townlist[i] == id) {
                townlist.erase(townlist.begin() + i);
            }
//            if (alphalistUpdated) {
//                if (alphalist[i] == id) {
//                    alphalist.erase(townlist.begin() + i);
//                }
//            }
//            if (distlistUpdated) {
//                if (distlist[i] == id) {
//                    distlist.erase(townlist.begin() + i);
//                }
//            }
        }
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
    if (townlist.size() == 0) {
        return {};
    }
    if (alphalistUpdated) {
        return alphalist;
    }

    alphalist.clear();
    alphalist.reserve(townlist.size());

    for (auto town : alphamap) {
        alphalist.push_back(town.second);
    }
    alphalistUpdated = true;
    return alphalist;
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    if (townlist.size() == 0) {
        return {};
    }
    if (distlistUpdated) {
        return distlist;
    }

    distlist.clear();
    distlist.reserve(townlist.size());

    for (auto town : distmap) {
        distlist.push_back(town.second);
    }
    distlistUpdated = true;
    return distlist;
}

std::vector<TownID> Datastructures::find_towns(std::string const& name)
{
    if (townlist.size() == 0) {
        return {};
    }
    tlist.clear();

    auto ren = alphamap.equal_range(name);
    for (auto it = ren.first; it != ren.second; ++it) {
        tlist.push_back(it->second);
    }

    std::sort(tlist.begin(), tlist.end());
    return tlist;
}

TownID Datastructures::min_distance()
{
    if (townlist.size() == 0)
        return NO_ID;

    if (distlistUpdated) {
        return distlist[0];
    }

    distlist.clear();
    distlist.reserve(townlist.size());

    for (auto town : distmap) {
        distlist.push_back(town.second);
    }
    distlistUpdated = true;
    return distlist[0];
}

TownID Datastructures::max_distance()
{
    if (townlist.size() == 0)
        return NO_ID;

    if (distlistUpdated) {
        return distlist[townlist.size() - 1];
    }

    distlist.clear();
    distlist.reserve(townlist.size());

    for (auto town : distmap) {
        distlist.push_back(town.second);
    }
    distlistUpdated = true;
    return distlist[townlist.size() - 1];
}

TownID Datastructures::nth_distance(unsigned int n)
{
    if (townlist.size() == 0 || n == 0 || n > townlist.size())
        return NO_ID;

    if (distlistUpdated) {
        return distlist[n - 1];
    }

    distlist.clear();
    distlist.reserve(townlist.size());

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

    tlist.clear();
    tlist.reserve(townlist.size());
    distmapxy.clear();

    for (auto town : townmap) {
        tempn = abs(town.second.x - x) + abs(town.second.y - y);
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
    tlist.clear();
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

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    idception.clear();
    tlist.clear();
    vlist.clear();
    tempn = 0;
    if (townlist.size() == 0) {
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
    tempn = NO_VALUE;
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

void Datastructures::add_vassal_vectors(const TownID &id) {
    vlist.push_back(id);
    if(townmap.at(id).vassal.size() != 0) {
        for (auto vassal : townmap.at(id).vassal) {
            add_vassal_vectors(vassal);
            idception.push_back(vlist);
            vlist.clear();
        }
    }
}

int Datastructures::vassal_taxes(const TownID &id) {
    if (townmap.at(id).vassal.size() != 0) {
        int vassal_tax = 0;
        for (auto vassal : townmap.at(id).vassal) {
            vassal_tax += vassal_taxes(vassal);
        }
        return (int) (0.1 * (townmap.at(id).tax + vassal_tax));
    } else {
        return (int) (0.1 * townmap.at(id).tax);
    }
}

