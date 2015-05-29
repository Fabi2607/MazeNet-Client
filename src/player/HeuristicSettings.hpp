//
// Created by fkantere on 5/29/15.
//

#ifndef MAZENET_CLIENT_HEURISTICSETTINGS_H
#define MAZENET_CLIENT_HEURISTICSETTINGS_H

#include <util/cfg/CfgManager.hpp>

struct HeuristicSettings {
  HeuristicSettings() {
    using namespace mazenet::util::cfg;
    CfgManager& cfgMan = CfgManager::instance();
    reachableFieldValue = cfgMan.get<int>("heuristic.base.reachableFieldValue");
    reachableTreasureValue = cfgMan.get<int>("heuristic.base.reachableTreasureValue");
    reachableHomeValue = cfgMan.get<int>("heuristic.base.reachableHomeValue");
    reachableHomeCutoff = cfgMan.get<int>("heuristic.base.reachableHomeCutoff");

    onTreasureScore = cfgMan.get<int>("heuristic.position.onTargetValue");
    transitionFieldValue = cfgMan.get<int>("heuristic.position.transitionFieldValue");
    distanceBaseValue = cfgMan.get<int>("heuristic.position.distanceBaseValue");
    distanceFactor = cfgMan.get<int>("heuristic.position.distanceFactor");
  }

  int reachableFieldValue;
  int reachableTreasureValue;
  int reachableHomeValue;
  int reachableHomeCutoff;

  int onTreasureScore;
  int transitionFieldValue;
  int distanceBaseValue;
  int distanceFactor;
};


#endif //MAZENET_CLIENT_HEURISTICSETTINGS_H
