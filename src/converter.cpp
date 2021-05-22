#include "converter.h"

namespace Converter
{
    std::string CfgToJson(std::string& input)
    {
        alt::config::Parser parser(input.c_str(), input.size());
        nlohmann::json      output;
        try
        {
            // Parse the cfg file and convert to JSON
            auto cfg = parser.Parse();
            output   = ConvertCfgValueToJsonValue(cfg);
            // Return the JSON string
            return output.dump(4);
        }
        catch(...)
        {
            return std::string();
        }
    }

    nlohmann::json ConvertCfgValueToJsonValue(alt::config::Node& value)
    {
        nlohmann::json jsonValue;
        // This check can be left out, but it's left in for clarity
        if(value.IsNone())
        {
            jsonValue = nullptr;
        }
        else if(value.IsScalar())
        {
            // This is ugly, but (probably) the best way to do this
            try
            {
                jsonValue = value.ToBool();
            }
            catch(...)
            {
                // Not a bool, so next check if its a number
                try
                {
                    jsonValue = value.ToNumber();
                }
                catch(...)
                {
                    // Not a bool and not a number, so it has to be a normal string
                    jsonValue = value.ToString();
                }
            }
        }
        else if(value.IsDict())
        {
            auto                                  dict = value.ToDict();
            std::map<std::string, nlohmann::json> jsonDict;
            for(auto& kv : dict)
            {
                jsonDict[kv.first] = ConvertCfgValueToJsonValue(kv.second);
            }
            jsonValue = jsonDict;
        }
        else if(value.IsList())
        {
            auto                        list = value.ToList();
            std::vector<nlohmann::json> jsonList;
            for(auto& node : list)
            {
                jsonList.push_back(ConvertCfgValueToJsonValue(node));
            }
            jsonValue = jsonList;
        }

        return jsonValue;
    }

    std::string JsonToCfg(std::string& input)
    {
        nlohmann::json    json;
        alt::config::Node output;
        try
        {
            // Parse the JSON file and convert to cfg
            json   = nlohmann::json::parse(input);
            output = ConvertJsonValueToCfgValue(json);

            // Return the cfg string
            std::stringstream stream;
            alt::config::Emitter().Emit(output, stream);
            return stream.str();
        }
        catch(std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return std::string();
        }
    }
    alt::config::Node ConvertJsonValueToCfgValue(nlohmann::json& value)
    {
        alt::config::Node cfgValue;

        using nlohmann::detail::value_t;
        switch(value.type())
        {
            case value_t::null:
            {
                cfgValue = alt::config::Node();
                break;
            }
            case value_t::object:
            {
                cfgValue = alt::config::Node::Dict();
                for(nlohmann::json::iterator it = value.begin(); it != value.end(); ++it)
                {
                    cfgValue[it.key()] = ConvertJsonValueToCfgValue(it.value());
                }
                break;
            }
            case value_t::array:
            {
                cfgValue = alt::config::Node::List(value.size());
                for(int i = 0; i < value.size(); i++)
                {
                    cfgValue[i] = ConvertJsonValueToCfgValue(value[i]);
                }
                break;
            }
            case value_t::string:
            {
                cfgValue = value.get<std::string>();
                break;
            }
            case value_t::boolean:
            {
                cfgValue = value.get<bool>();
                break;
            }
            case value_t::number_integer:
            {
                cfgValue = value.get<int64_t>();
                break;
            }
            case value_t::number_unsigned:
            {
                cfgValue = value.get<uint64_t>();
                break;
            }
            case value_t::number_float:
            {
                cfgValue = value.get<float>();
                break;
            }
        }

        return cfgValue;
    }
}  // namespace Converter
