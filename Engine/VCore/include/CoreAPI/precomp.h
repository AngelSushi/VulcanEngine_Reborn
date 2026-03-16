#pragma once

#include <string>
#include <vector>
#include <any>
#include <set>
#include <unordered_map>
#include <variant>
#include <typeindex>
#include <memory>
#include <functional>
#include <filesystem>
#include <fstream>

#include <fmt/core.h>
#include <gsl/assert>

#include <nlohmann/json.hpp>
#include <clay/clay.h>
#include <CoreAPI/Types.h>

#include <Reflection/ReflectionBase.h>
#include <Reflection/Property/VProperty.h>
#include <Reflection/Function/FunctionUtils.h>
#include <Reflection/Function/VFunction.h>
#include <Reflection/Function/VStaticFunction.h>
#include <Reflection/VClass.h>
#include <Reflection/VStruct.h>

#include <TVector.h>