#include <boost/algorithm/string.hpp>
#include "Analysis/BackgroundModel/interface/Tools.h"


namespace analysis {
  namespace backgroundmodel {

    std::vector<ParamModifier> parseModifiers(const std::vector<std::string>& input) {
      std::vector<ParamModifier> output;
      for (const auto& i : input) {
	std::vector<std::string> nameAndModifiers;
	boost::split(nameAndModifiers, i, boost::is_any_of(":"));
	const std::string name(nameAndModifiers.at(0));
	ParamModifier paramModifier(name);
	std::vector<std::string> modifiers;
	boost::split(modifiers, nameAndModifiers.at(1), boost::is_any_of(","));
	for (const auto& m : modifiers) {
	  if (m.find("start") != std::string::npos)
	    paramModifier.start(StrToNum<float>(m.substr(m.find("=") + 1)));
	  if (m.find("min") != std::string::npos)
	    paramModifier.min(StrToNum<float>(m.substr(m.find("=") + 1)));
	  if (m.find("max") != std::string::npos)
	    paramModifier.max(StrToNum<float>(m.substr(m.find("=") + 1)));
	  if (m.find("constant") != std::string::npos) paramModifier.constant();
	  if (m.find("floating") != std::string::npos) paramModifier.floating();
	}
	output.push_back(paramModifier);
      }
      return output;
    }

  }
}
