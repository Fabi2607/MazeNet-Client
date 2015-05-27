/**
* @file ProgramOptions.cpp
* @author Fabian Kantereit
* @date 10.11.2014 10:04
*
* contains the ProgramOptions class which manages commandline parameters
*/
#include "ProgramOptions.hpp"

namespace mazenet {
namespace util {
namespace cfg {

ProgramOptions::ProgramOptions() : cmdline_options_(), vm_() {

}

void ProgramOptions::init_options(int argc, char* argv[]) {
  /** description of general category */
  po::options_description general("General");
  general.add_options()
             ("host,h", po::value<std::string>(), "specify hostname")
             ("port,p", po::value<std::string>(), "specify port")
             ("timeout,t", po::value<int>(), "server timeout in seconds")
             ("version,v", "display program version")
             ("help", "display help message");

  /** description of debug category */
  po::options_description debug("Debug");
  debug.add_options()
           ("verbose", "display verbose console output")
           ("loglevel", po::value<unsigned>(), "minimum level required for log triggering \n 0[info] - 5[critical]")
           ("default-settings", "restore default configuration")
           ("dump-overrides", "dumps all overrides")
           ("interactive,i", "activates the interactive mode");

  po::options_description internal("Internal");
  internal.add_options()
              ("child", po::value<unsigned>(), "execute as child process with id")
              ("workflows", po::value<std::vector<std::string>>()->multitoken(), "workflow assigned to this process")
              ("logdir", po::value<std::string>(), "base directory for logging")
              ("uuid", po::value<std::string>(), "UUID if this context");

  cmdline_options_.add(general).add(debug).add(internal);

  try {
    po::store(po::command_line_parser(argc, argv).options(cmdline_options_).run(), vm_);
    po::notify(vm_);
  } catch (...) {

  }
}

ExecutionMode ProgramOptions::execute() {
  if (vm_.count("help")) {
    print_help();
    return ExecutionMode::EXIT;
  }
  if (vm_.count("version")) {
    print_version();
    return ExecutionMode::EXIT;
  }

  return ExecutionMode::NONE;
}

}
}
}
