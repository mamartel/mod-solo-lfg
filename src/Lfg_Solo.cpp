/*
** Made by Traesh https://github.com/Traesh
** AzerothCore 2019 http://www.azerothcore.org/
** Conan513 https://github.com/conan513
** Made into a module by Micrah https://github.com/milestorme/
*/

#include "ScriptMgr.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "World.h"
#include "LFGMgr.h"
#include "Chat.h"
#include "Opcodes.h"

class lfg_solo : public PlayerScript
{
public:
    lfg_solo() : PlayerScript("lfg_solo") { }

    void OnLogin(Player* /*player*/)
    {
        if (sConfigMgr->GetIntDefault("LFG.SoloMode", true))
        {
            if (!sLFGMgr->IsSoloLFG())
            {
                sLFGMgr->ToggleSoloLFG();
            }
        }
    }
};

class lfg_solo_config : public WorldScript
{
public:
    lfg_solo_config() : WorldScript("lfg_solo_config") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload) {
            std::string conf_path = _CONF_DIR;
            std::string cfg_file = conf_path + "/SoloLfg.conf";

            std::string cfg_def_file = cfg_file + ".dist";
            sConfigMgr->LoadMore(cfg_def_file.c_str());
            sConfigMgr->LoadMore(cfg_file.c_str());
        }
    }
};

void AddLfgSoloScripts()
{
    new lfg_solo();
    new lfg_solo_config();
}
