#include "Item.h"
#include "ScriptMgr.h"

namespace Noblegarden
{
    class CustomPlayerHandler : PlayerScript
    {
    // Init
    public:
        CustomPlayerHandler() : PlayerScript("custom_player_handler")
        {

        }

    // API
    public:
        void OnCreate(Player* player) override;
        void OnLogin(Player* player, bool firstLogin) override;

    private:
        void SetInitialItems(Player* player);

    // Datatables
    private:
        std::map<EquipmentSlots, int> m_default_Set = {
            { EquipmentSlots::EQUIPMENT_SLOT_HEAD,      1000001 },
            { EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS, 1000002 },
            { EquipmentSlots::EQUIPMENT_SLOT_BODY,      1000003 },
            { EquipmentSlots::EQUIPMENT_SLOT_CHEST,     1000004 },
            { EquipmentSlots::EQUIPMENT_SLOT_WAIST,     1000005 },
            { EquipmentSlots::EQUIPMENT_SLOT_LEGS,      1000006 },
            { EquipmentSlots::EQUIPMENT_SLOT_FEET,      1000007 },
            { EquipmentSlots::EQUIPMENT_SLOT_WRISTS,    1000008 },
            { EquipmentSlots::EQUIPMENT_SLOT_HANDS,     1000009 },
            { EquipmentSlots::EQUIPMENT_SLOT_MAINHAND,  1000010 },
            { EquipmentSlots::EQUIPMENT_SLOT_OFFHAND,   1000011 },
            { EquipmentSlots::EQUIPMENT_SLOT_BACK,      1000012 },
            { EquipmentSlots::EQUIPMENT_SLOT_TABARD,    1000013 },
        };
    };
};
