DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_hun_streamline';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(257044, 'spell_hun_streamline');

DELETE FROM `spell_proc` WHERE `SpellId` IN (342076);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(342076,0x00,9,0x00000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x1,0x2,0x0,0x18,0x0,0,0,0,0); -- Streamline
