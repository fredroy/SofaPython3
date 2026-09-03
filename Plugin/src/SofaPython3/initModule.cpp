/******************************************************************************
*                              SofaPython3 plugin                             *
*                  (c) 2021 CNRS, University of Lille, INRIA                  *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/

#include <SofaPython3/config.h>

#include "PythonEnvironment.h"
using sofapython3::PythonEnvironment;

#include <SofaPython3/initModule.h>

#include <sofa/core/init.h>
#include <sofa/defaulttype/init.h>
#include <sofa/simulation/init.h>
#include <sofa/helper/init.h>
#include <sofa/simulation/graph/init.h>


std::optional<std::string> get_env_var(const std::string& name) 
{
#ifdef _WIN32
    // Convert UTF-8 name to UTF-16 for the wide Win32 API.
    int wname_len = MultiByteToWideChar(
        CP_UTF8, 0, name.c_str(), -1, nullptr, 0);
    if (wname_len <= 0) 
    {
        return std::nullopt;
    }
    std::wstring wname(static_cast<size_t>(wname_len) - 1, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, name.c_str(), -1, wname.data(), wname_len);

    // First call: find required buffer size.
    DWORD size = GetEnvironmentVariableW(wname.c_str(), nullptr, 0);
    if (size == 0) 
    {
        // Not set. (Call GetLastError() if you need to distinguish
        // "unset" from "set to empty string" — ERROR_ENVVAR_NOT_FOUND.)
        return std::nullopt;
    }

    std::wstring wvalue(size, L'\0');
    DWORD written = GetEnvironmentVariableW(wname.c_str(), wvalue.data(), size);
    if (written == 0 || written >= size) 
    {
        return std::nullopt;
    }
    wvalue.resize(written); // drop the trailing null counted in `size`

    // Convert back to UTF-8 for a stable, platform-independent return type.
    int utf8_len = WideCharToMultiByte(
        CP_UTF8, 0, wvalue.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8_len <= 0) 
    {
        return std::nullopt;
    }
    std::string result(static_cast<size_t>(utf8_len) - 1, '\0');
    WideCharToMultiByte(
        CP_UTF8, 0, wvalue.c_str(), -1, result.data(), utf8_len, nullptr, nullptr);

    return result;

#else
    // Linux / macOS: environ-backed getenv() is consistent with setenv(),
    // so no cache-sync issue exists here.
    const char* value = std::getenv(name.c_str());
    if (value == nullptr) 
    {
        return std::nullopt;
    }
    return std::string(value);
#endif
}

extern "C" {

SOFAPYTHON3_API void initExternalModule();
SOFAPYTHON3_API const char* getModuleName();
SOFAPYTHON3_API const char* getModuleVersion();
SOFAPYTHON3_API const char* getModuleLicense();
SOFAPYTHON3_API const char* getModuleDescription();
SOFAPYTHON3_API const char* getModuleComponentList();
SOFAPYTHON3_API bool moduleIsInitialized();

void initExternalModule()
{
    static bool first = true;

    if (first)
    {
        sofa::helper::init();
        sofa::defaulttype::init();
        sofa::core::init();
        sofa::simulation::core::init();
        sofa::simulation::graph::init();

        std::string pythonenv{};
        auto env_var = get_env_var("OVERRIDE_PYTHON_ENV");
        if (env_var.has_value())
        {
            pythonenv = env_var.value();
            msg_warning("SofaPython3") << "Using override Python environment: " << pythonenv;
        }
        else
        {
            msg_warning("SofaPython3") << "OVERRIDE_PYTHON_ENV is empty.";
        }

        PythonEnvironment::Init(pythonenv);
        first = false;
    }
    PythonEnvironment::addPluginManagerCallback();
}

const char* getModuleName()
{
    return "SofaPython3";
}

const char* getModuleVersion()
{
    return "1.0";
}

const char* getModuleLicense()
{
    return "LGPL";
}

const char* getModuleDescription()
{
    return "This plugin contains the interpreter for python3.";
}

const char* getModuleComponentList()
{
    return "";
}

bool moduleIsInitialized()
{
    return PythonEnvironment::isInitialized();
}

}

namespace sofapython3
{
    void init()
    {
        initExternalModule();
    }
}
