/*  SPMod - SourcePawn Scripting Engine for Half-Life
 *  Copyright (C) 2018  SPMod Development Team
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include "spmod.hpp"

class PluginMngr;
class ForwardMngr;

class SPGlobal : public ISPGlobal
{
public:
    SPGlobal() = delete;
    SPGlobal(const fs::path &dllDir) : m_SPModDir(dllDir.parent_path().parent_path()),
                                        m_pluginManager(nullptr),
                                        m_forwardManager(std::make_unique<ForwardMngr>()),
                                        m_spFactory(nullptr)
                                        { }
    ~SPGlobal()
    {
        #ifdef SP_POSIX
            dlclose(m_SPLibraryHandle);
        #else
            // TODO: windows
        #endif
    }

    // ISPGlobal
    const char *getHome() const override
    {
        return m_SPModDir.c_str();
    }
    const char *getModName() const override
    {
        return m_modName.c_str();
    }
    IPluginMngr *getPluginManager() const override
    {
        return reinterpret_cast<IPluginMngr *>(m_pluginManager.get());
    }
    IForwardMngr *getForwardManager() const override
    {
        return reinterpret_cast<IForwardMngr *>(m_forwardManager.get());
    }
    SourcePawn::ISourcePawnEnvironment *getSPEnvironment() const override
    {
        return m_spFactory->CurrentEnvironment();
    }

    bool addModule(sp_nativeinfo_t *natives, const char *name, sp_api_t api) override;

    // SPGlobal
    PluginMngr *getPluginManagerCore() const
    {
        return m_pluginManager.get();
    }
    ForwardMngr *getForwardManagerCore() const
    {
        return m_forwardManager.get();
    }
    void initPluginManager();
    void setModName(std::string_view name)
    {
        m_modName = name;
    }
    void setScriptsDir(std::string_view folder);
    const auto &getModulesList() const
    {
        return m_modulesNames;
    }

    #ifdef SP_POSIX
    void setSPFactory(void *library,
                        SourcePawn::ISourcePawnFactory *factory);
    #else
    //void setSPFactory(void *library, SourcePawn::ISourcePawnFactory *factory);
    #endif

    void initDefaultsForwards();

private:

    struct NativeDef
    {
        sp_nativeinfo_t *natives;
        size_t num;
    };

    fs::path m_SPModScriptsDir;
    fs::path m_SPModDir;
    std::unique_ptr<PluginMngr> m_pluginManager;
    std::unique_ptr<ForwardMngr> m_forwardManager;
    std::string m_modName;
    std::unordered_map<std::string, NativeDef> m_modulesNames;
    SourcePawn::ISourcePawnFactory *m_spFactory;

    // SourcePawn library handle
    #ifdef SP_POSIX
    void *m_SPLibraryHandle;
    #else
    // TODO: windows
    #endif
};

extern std::unique_ptr<SPGlobal> gSPGlobal;
