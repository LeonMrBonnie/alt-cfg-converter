#pragma once
#include "alt-config/alt-config.h"
#include "nlohmann/json.h"

namespace Converter
{
    std::string    CfgToJson(std::string& input);
    nlohmann::json ConvertCfgValueToJsonValue(alt::config::Node& value);

    std::string       JsonToCfg(std::string& input);
    alt::config::Node ConvertJsonValueToCfgValue(nlohmann::json& value);
}  // namespace Converter
