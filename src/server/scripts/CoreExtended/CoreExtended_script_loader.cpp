/*
* Copyright 2025 RoleplayCore and etc OS core
*/
 
// Info: Call Repack scripts here

void AddSC_zone_elwyn_forest();
void AddSC_zone_gilneas_city1();
void AddSC_duskwood_custom();

// #################################################### //
// Add in AddCoreExtendedScripts(){ .. } without void. //
// #################################################### //

void AddCoreExtendedScripts()
{
    AddSC_zone_elwyn_forest();

    AddSC_zone_gilneas_city1();
    AddSC_duskwood_custom();
}

