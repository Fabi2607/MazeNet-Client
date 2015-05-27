/**
* @file LogManager.cpp
* @author Fabian Kantereit
* @date 10.11.2014 10:04
*
* contains the CfgManager class implementation
*/
#include <Constants.hpp>
#include "CfgManager.hpp"

namespace mazenet {
namespace util {
namespace cfg {

/****************************************************************/

CfgManager::CfgManager() : mutex_(), cmdOpts_(), overrides_(), configuration_() {
  try {
    configuration_.load(cCfgFile);
  } catch (...) {
    std::cout << "critical initialization error, config invalid please create "
                 "a default one, or check the existing configuration for errors"
              << std::endl;
    throw mazenet::Exception();
  }
}

/****************************************************************/

CfgManager& CfgManager::instance() {
  static CfgManager instance_;
  return instance_;
}

/****************************************************************/

CfgManager::~CfgManager() {
}

/****************************************************************/

ExecutionMode CfgManager::parseCmdLineOptions(int argc, char* argv[]) {
  using namespace boost;
  lock_guard<recursive_mutex> lock(mutex_);
  cmdOpts_.init_options(argc, argv);
  ExecutionMode mode = cmdOpts_.execute();
  translateCmdOpts();
  getExecutionMode(mode);
  return mode;
}

/****************************************************************/

void CfgManager::translateCmdOpts() {
  // translation of commandline options into overrides_

  // Order like in config.json
  if (cmdOpts_.vm_.count("host")) {
    overrides_.set("server.host", cmdOpts_.vm_["host"].as<std::string>());
  }

  if (cmdOpts_.vm_.count("port")) {
    overrides_.set("server.port", cmdOpts_.vm_["port"].as<std::string>());
  }

  if (cmdOpts_.vm_.count("workflows")) {
    overrides_.set_collection<std::vector<std::string>>("simulation.workflows", cmdOpts_.vm_["workflows"].as<std::vector<std::string>>() );
  }

  if (cmdOpts_.vm_.count("interactive")) {
    overrides_.set("simulation.mode", "interactive");
  }

  if (cmdOpts_.vm_.count("uuid")) {
    overrides_.set("simulation.uuid", cmdOpts_.vm_["uuid"].as<std::string>());
  }

  // not available in config.json
  if (cmdOpts_.vm_.count("child")) {
    overrides_.set("simulation.child", cmdOpts_.vm_["child"].as<unsigned>());
  }

  if (cmdOpts_.vm_.count("logdir")) {
    overrides_.set("log.directory", cmdOpts_.vm_["logdir"].as<std::string>());
  }

  if (cmdOpts_.vm_.count("verbose")) {
    overrides_.set("log.verbose", true);
  }

  if (cmdOpts_.vm_.count("loglevel")) {
    overrides_.set("log.level", cmdOpts_.vm_["loglevel"].as<unsigned>());
  }
  // End of config.json overrides

  if (cmdOpts_.vm_.count("default-settings")) {
    createDefault();
  }

  if (cmdOpts_.vm_.count("dump-overrides")) {
    dumpOverrides(cCfgOverrideFile);
  }
}

/****************************************************************/

void CfgManager::getExecutionMode(ExecutionMode& mode) {
  if (mode != ExecutionMode::EXIT) {
    std::string sim_mode = get<std::string>("simulation.mode", "");
    if (sim_mode == "interactive") {
      mode = ExecutionMode::INTERACTIVE;
    } else if (sim_mode == "sequential") {
      mode = ExecutionMode::SEQUENTIAL;
    } else if (sim_mode == "parallel") {
      mode = ExecutionMode::PARALLEL_MASTER;
    }

    // this child might have been spawned in interactive parallel mode
    if (get<unsigned>("simulation.child", 0)){
      mode = ExecutionMode::PARALLEL_CHILD;
    }
  }
}

/****************************************************************/

void CfgManager::createDefault() {
  using namespace boost;
  lock_guard<recursive_mutex> lock(mutex_);

  // server category
  configuration_.set<std::string>("server.host"   , "127.0.0.1");
  configuration_.set<std::string>("server.port"   ,     "30400");
  configuration_.set<int>        ("server.timeout",          60);
  configuration_.set<unsigned>   ("server.retry"  ,           5);

  // simulation category
  configuration_.set_collection<std::vector<std::string>>("simulation.workflows", std::vector<std::string>{"TestCase"});

  configuration_.set<unsigned>   ("simulation.runtime_min",            1);
  configuration_.set<unsigned>   ("simulation.delay_ms"   ,         1000);
  configuration_.set<std::string>("simulation.mode"       , "sequential");
  configuration_.set<unsigned>   ("simulation.runner"     ,            1);

  // log category
  configuration_.set<bool>("log.main"            ,  true);
  configuration_.set<bool>("log.network"         , false);
  configuration_.set<bool>("log.python"          , false);
  configuration_.set<bool>("log.simulation"      ,  true);
  configuration_.set<bool>("log.command_profiles",  true);
  configuration_.set<bool>("log.command_traces"  ,  true);
  configuration_.set<bool>("log.verbose"         , false);
  configuration_.set<int> ("log.level"           ,     0);

  save();
}

/****************************************************************/

void CfgManager::dumpOverrides(std::string const& filename) const {
  using namespace boost;
  lock_guard<recursive_mutex> lock(mutex_);
  overrides_.store(filename);
}

/****************************************************************/

void CfgManager::save() const {
  using namespace boost;
  lock_guard<recursive_mutex> lock(mutex_);
  configuration_.store(cCfgFile);
}

/****************************************************************/

}
}
}
