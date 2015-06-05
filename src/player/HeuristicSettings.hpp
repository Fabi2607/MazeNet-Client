#ifndef MAZENET_CLIENT_HEURISTICSETTINGS_HPP
#define MAZENET_CLIENT_HEURISTICSETTINGS_HPP

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
    transitionMoveValue = cfgMan.get<int>("heuristic.position.transitionMoveValue");
    distanceBaseValue = cfgMan.get<int>("heuristic.position.distanceBaseValue");
    distanceFactor = cfgMan.get<int>("heuristic.position.distanceFactor");
    moveOutOfMapPenalty = cfgMan.get<int>("heuristic.position.moveOutOfMapPenalty");
  }

  int reachableFieldValue;
  int reachableTreasureValue;
  int reachableHomeValue;
  int reachableHomeCutoff;

  int onTreasureScore;
  int transitionMoveValue;
  int distanceBaseValue;
  int distanceFactor;
  int moveOutOfMapPenalty;
};


#endif //MAZENET_CLIENT_HEURISTICSETTINGS_HPP
