#include "custom_player_handler.h"

namespace Noblegarden
{
    void CustomPlayerHandler::OnCreate(Player* player)
    {
       
    }

    void CustomPlayerHandler::OnLogin(Player* player, bool firstLogin)
    {
        if (firstLogin)
        {
            SetInitialItems(player);
        }
    }

    void CustomPlayerHandler::SetInitialItems(Player* player)
    {
        for (uint8 i = EquipmentSlots::EQUIPMENT_SLOT_START; i < EquipmentSlots::EQUIPMENT_SLOT_END; i++)
        {
            if (Item* pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            {
                player->RemoveItem(INVENTORY_SLOT_BAG_0, i, true);
            }

            auto slot = (EquipmentSlots)i;
            auto dest = ((INVENTORY_SLOT_BAG_0 << 8) | i);

            if (m_default_Set.contains(slot))
            {
                player->EquipNewItem(dest, m_default_Set.at(slot), ItemContext::NONE, true);
            }
        }
    }
};

void AddSC_CystomPlayerHandler()
{
    new Noblegarden::CustomPlayerHandler();
}
