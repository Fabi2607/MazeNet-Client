# MazeNet-Client

## Build
Needed Libraries:
- Debian: xsdcxx, Arch: xsd
- Debian: libboost-all-dev, Arch: boost
- Debian: libxerces-c-dev, Arch: xerces-c


either run:
'''
$ export MAZENET=`pwd`
$ scripts/mazenet.all.sh
'''

or:
'''
mkdir Build && cd Build
cmake ..
make
'''

## Heuristic configuration

### base

- reachableFieldValue : Value of a field that is reachable by the player

- reachableTreasureValue : Value of a not-yet-found treasure that is reachable by the player

- reachableHomeValue : Value of a reachable Home , will be divided by the number of remaining treasures to increase value over time.

- reachableHomeCutoff : number of remaining treasures, that trigger home value calculation

### position

- onTargetValue : Value for standing on the current treasure, this should be higher than almost everything else (except for enemy reachable home)

- transitionMoveValue : Value of a possible transition move to target from this position. if two transitions are needed value will be divided by 2.

- transitionPossibleTreasureValue : Value of a potential treasures after a transition move if we already know our treasure.

- distanceBaseValue : Base value for distance to target. will be divided by distance*distanceFactor

- distanceFactor : scaling for distance. The above.

- moveOutOfMapPenalty : obsolete. Just here for security reasons.

### enemy

Counter measures against enemy players.

#### next
These values affect the next player

#### best
These values affect the best player

- reachableTreasureValue : value of a treasure the enemy can reach.

- reachableHomeValue : value of a reachable home. This can be used for aggressive late game behaviour. divided by number of remaining treasures

- reachablehomeCutoff : above value will be used as soon as the remaining treasures are below or equal to the cutoff

- transitionMoveTreasureValue : value of a treasure the enemy can reach with a shift operation. divided by number of remaining treasures to increase late game aggressive behaviour.

