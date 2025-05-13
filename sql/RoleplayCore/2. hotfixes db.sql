-- ----------------------------
-- Table structure for chr_customization_material
-- ----------------------------
DROP TABLE IF EXISTS `chr_customization_material`;
CREATE TABLE `chr_customization_material`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `ChrModelTextureTargetID` int NOT NULL DEFAULT 0,
  `MaterialResourcesID` int NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for creature_display_info_option
-- ----------------------------
DROP TABLE IF EXISTS `creature_display_info_option`;
CREATE TABLE `creature_display_info_option`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `ChrCustomizationOptionID` int NOT NULL DEFAULT 0,
  `ChrCustomizationChoiceID` int NOT NULL DEFAULT 0,
  `CreatureDisplayInfoExtraID` int NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for game_tips
-- ----------------------------
DROP TABLE IF EXISTS `game_tips`;
CREATE TABLE `game_tips`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `Text` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `SortIndex` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `MinLevel` int NOT NULL DEFAULT 0,
  `MaxLevel` int NOT NULL DEFAULT 0,
  `ContentTuningID` int NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for game_tips_locale
-- ----------------------------
DROP TABLE IF EXISTS `game_tips_locale`;
CREATE TABLE `game_tips_locale`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `locale` varchar(4) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `Text_lang` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `locale`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for light_params
-- ----------------------------
DROP TABLE IF EXISTS `light_params`;
CREATE TABLE `light_params`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `OverrideCelestialSphere1` float NOT NULL DEFAULT 0,
  `OverrideCelestialSphere2` float NOT NULL DEFAULT 0,
  `OverrideCelestialSphere3` float NOT NULL DEFAULT 0,
  `Field_11_0_0_54210_0011` float NOT NULL DEFAULT 0,
  `Field_11_0_0_54210_0012` float NOT NULL DEFAULT 0,
  `Field_11_0_0_54210_0013` float NOT NULL DEFAULT 0,
  `HighlightSky` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `LightSkyboxID` smallint UNSIGNED NOT NULL DEFAULT 0,
  `CloudTypeID` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `Glow` float NOT NULL DEFAULT 0,
  `WaterShallowAlpha` float NOT NULL DEFAULT 0,
  `WaterDeepAlpha` float NOT NULL DEFAULT 0,
  `OceanShallowAlpha` float NOT NULL DEFAULT 0,
  `OceanDeepAlpha` float NOT NULL DEFAULT 0,
  `Flags` int NOT NULL DEFAULT 0,
  `SsaoSettingsID` int NOT NULL DEFAULT 0,
  `Field_11_0_0_54210_012` float NOT NULL DEFAULT 0,
  `Field_11_0_0_54210_013` float NOT NULL DEFAULT 0,
  `Field_11_0_0_54210_014` float NOT NULL DEFAULT 0,
  `Field_11_0_0_54210_015` float NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for light_skybox
-- ----------------------------
DROP TABLE IF EXISTS `light_skybox`;
CREATE TABLE `light_skybox`  (
  `Id` int UNSIGNED NOT NULL DEFAULT 0,
  `Name` mediumtext CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `Flags` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `SkyboxFileDataID` int NOT NULL DEFAULT 0,
  `CelestialSkyboxFileDataID` int NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`Id`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for model_file_data
-- ----------------------------
DROP TABLE IF EXISTS `model_file_data`;
CREATE TABLE `model_file_data`  (
  `Geobox1` float NOT NULL DEFAULT 0,
  `Geobox2` float NOT NULL DEFAULT 0,
  `Geobox3` float NOT NULL DEFAULT 0,
  `Geobox4` float NOT NULL DEFAULT 0,
  `Geobox5` float NOT NULL DEFAULT 0,
  `Geobox6` float NOT NULL DEFAULT 0,
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `Flags` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `LogCount` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `ModelID` int UNSIGNED NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  `ModelResourcesID` int NOT NULL,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for npc_model_item_slot_display_info
-- ----------------------------
DROP TABLE IF EXISTS `npc_model_item_slot_display_info`;
CREATE TABLE `npc_model_item_slot_display_info`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `DisplayID` int UNSIGNED NOT NULL DEFAULT 0,
  `Slot` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `ExtendedDisplayID` int UNSIGNED NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for screen_effect
-- ----------------------------
DROP TABLE IF EXISTS `screen_effect`;
CREATE TABLE `screen_effect`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `DisplayName` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `Param1` int NOT NULL DEFAULT 0,
  `Param2` int NOT NULL DEFAULT 0,
  `Param3` int NOT NULL DEFAULT 0,
  `Param4` int NOT NULL DEFAULT 0,
  `Effect` tinyint NOT NULL DEFAULT 0,
  `FullScreenEffectID` int UNSIGNED NOT NULL DEFAULT 0,
  `LightParamsID` smallint UNSIGNED NOT NULL DEFAULT 0,
  `LightParamsFadeIn` smallint UNSIGNED NOT NULL DEFAULT 0,
  `LightParamsFadeOut` smallint UNSIGNED NOT NULL DEFAULT 0,
  `SoundAmbienceID` int UNSIGNED NOT NULL DEFAULT 0,
  `ZoneMusicID` int UNSIGNED NOT NULL DEFAULT 0,
  `TimeOfDayOverride` smallint NOT NULL DEFAULT 0,
  `EffectMask` tinyint NOT NULL DEFAULT 0,
  `LightFlags` int UNSIGNED NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for sound_kit_advanced
-- ----------------------------
DROP TABLE IF EXISTS `sound_kit_advanced`;
CREATE TABLE `sound_kit_advanced`  (
  `ID` int NOT NULL DEFAULT 0,
  `SoundKitID` int UNSIGNED NOT NULL DEFAULT 0,
  `InnerRadius2D` float NOT NULL DEFAULT 0,
  `OuterRadius2D` float NOT NULL DEFAULT 0,
  `TimeA` int UNSIGNED NOT NULL DEFAULT 0,
  `TimeB` int UNSIGNED NOT NULL DEFAULT 0,
  `TimeC` int UNSIGNED NOT NULL DEFAULT 0,
  `TimeD` int UNSIGNED NOT NULL DEFAULT 0,
  `RandomOffsetRange` int NOT NULL DEFAULT 0,
  `Usage` tinyint NOT NULL DEFAULT 0,
  `TimeIntervalMin` int UNSIGNED NOT NULL DEFAULT 0,
  `TimeIntervalMax` int UNSIGNED NOT NULL DEFAULT 0,
  `DelayMin` int UNSIGNED NOT NULL DEFAULT 0,
  `DelayMax` int UNSIGNED NOT NULL DEFAULT 0,
  `VolumeSliderCategory` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `DuckToSFX` float NOT NULL DEFAULT 0,
  `DuckToMusic` float NOT NULL DEFAULT 0,
  `DuckToAmbience` float NOT NULL DEFAULT 0,
  `DuckToDialog` float NOT NULL DEFAULT 0,
  `DuckToSuppressors` float NOT NULL DEFAULT 0,
  `DuckToCinematicSFX` float NOT NULL DEFAULT 0,
  `DuckToCinematicMusic` float NOT NULL DEFAULT 0,
  `InnerRadiusOfInfluence` float NOT NULL DEFAULT 0,
  `OuterRadiusOfInfluence` float NOT NULL DEFAULT 0,
  `TimeToDuck` int UNSIGNED NOT NULL DEFAULT 0,
  `TimeToUnduck` int UNSIGNED NOT NULL DEFAULT 0,
  `InsideAngle` float NOT NULL DEFAULT 0,
  `OutsideAngle` float NOT NULL DEFAULT 0,
  `OutsideVolume` float NOT NULL DEFAULT 0,
  `MinRandomPosOffset` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `MaxRandomPosOffset` smallint UNSIGNED NOT NULL DEFAULT 0,
  `MsOffset` int NOT NULL DEFAULT 0,
  `TimeCooldownMin` int UNSIGNED NOT NULL DEFAULT 0,
  `TimeCooldownMax` int UNSIGNED NOT NULL DEFAULT 0,
  `MaxInstancesBehavior` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `VolumeControlType` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `VolumeFadeInTimeMin` int NOT NULL DEFAULT 0,
  `VolumeFadeInTimeMax` int NOT NULL DEFAULT 0,
  `VolumeFadeInCurveID` int UNSIGNED NOT NULL DEFAULT 0,
  `VolumeFadeOutTimeMin` int NOT NULL DEFAULT 0,
  `VolumeFadeOutTimeMax` int NOT NULL DEFAULT 0,
  `VolumeFadeOutCurveID` int UNSIGNED NOT NULL DEFAULT 0,
  `ChanceToPlay` float NOT NULL DEFAULT 0,
  `RolloffType` int NOT NULL DEFAULT 0,
  `RolloffParam0` float NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_045` float NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_046` float NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_047` int NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_048` int NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_049` float NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_050` float NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_051` float NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_052` float NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_053` float NOT NULL DEFAULT 0,
  `Field_8_2_0_30080_054` float NOT NULL DEFAULT 0,
  `Field_9_1_0_38312_055` float NOT NULL DEFAULT 0,
  `Field_9_1_0_38312_056` float NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for sound_kit_entry
-- ----------------------------
DROP TABLE IF EXISTS `sound_kit_entry`;
CREATE TABLE `sound_kit_entry`  (
  `ID` int NOT NULL DEFAULT 0,
  `SoundKitID` int UNSIGNED NOT NULL DEFAULT 0,
  `FileDataID` int NOT NULL DEFAULT 0,
  `Frequency` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `Volume` float NOT NULL DEFAULT 0,
  `PlayerConditionID` int UNSIGNED NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for specialization_spells_display
-- ----------------------------
DROP TABLE IF EXISTS `specialization_spells_display`;
CREATE TABLE `specialization_spells_display`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `SpecializationID` smallint UNSIGNED NOT NULL DEFAULT 0,
  `SpecllID1` int UNSIGNED NOT NULL DEFAULT 0,
  `SpecllID2` int UNSIGNED NOT NULL DEFAULT 0,
  `SpecllID3` int UNSIGNED NOT NULL DEFAULT 0,
  `SpecllID4` int UNSIGNED NOT NULL DEFAULT 0,
  `SpecllID5` int UNSIGNED NOT NULL DEFAULT 0,
  `SpecllID6` int UNSIGNED NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for spell
-- ----------------------------
DROP TABLE IF EXISTS `spell`;
CREATE TABLE `spell`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `NameSubtext` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `Description` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `AuraDescription` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for spell_locale
-- ----------------------------
DROP TABLE IF EXISTS `spell_locale`;
CREATE TABLE `spell_locale`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `locale` varchar(4) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `NameSubtext_lang` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `Description_lang` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `AuraDescription_lang` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `locale`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for texture_file_data
-- ----------------------------
DROP TABLE IF EXISTS `texture_file_data`;
CREATE TABLE `texture_file_data`  (
  `ID` int UNSIGNED NOT NULL,
  `UsageType` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `TextureID` int NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for vehicle_poi_type
-- ----------------------------
DROP TABLE IF EXISTS `vehicle_poi_type`;
CREATE TABLE `vehicle_poi_type`  (
  `ID` int NOT NULL DEFAULT 0,
  `Flags` int NOT NULL DEFAULT 0,
  `TextureWidth` int NOT NULL DEFAULT 0,
  `TextureHeight` int NOT NULL DEFAULT 0,
  `OccupiedTexture` int NOT NULL DEFAULT 0,
  `UnoccupiedTexture` int NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for sound_ambience
-- ----------------------------
CREATE TABLE `sound_ambience`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `Flags` int NOT NULL DEFAULT 0,
  `FlavorSoundFilterID` int UNSIGNED NOT NULL DEFAULT 0,
  `AmbienceID1` int UNSIGNED NOT NULL DEFAULT 0,
  `AmbienceID2` int UNSIGNED NOT NULL DEFAULT 0,
  `AmbienceStartID1` int UNSIGNED NOT NULL DEFAULT 0,
  `AmbienceStartID2` int UNSIGNED NOT NULL DEFAULT 0,
  `AmbienceStopID1` int UNSIGNED NOT NULL DEFAULT 0,
  `AmbienceStopID2` int UNSIGNED NOT NULL DEFAULT 0,
  `SoundKitID1` int UNSIGNED NOT NULL DEFAULT 0,
  `SoundKitID2` int UNSIGNED NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for zone_music
-- ----------------------------
CREATE TABLE `zone_music`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `SetName` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `SilenceIntervalMin1` int UNSIGNED NOT NULL DEFAULT 0,
  `SilenceIntervalMin2` int UNSIGNED NOT NULL DEFAULT 0,
  `SilenceIntervalMax1` int UNSIGNED NOT NULL DEFAULT 0,
  `SilenceIntervalMax2` int UNSIGNED NOT NULL DEFAULT 0,
  `Sounds1` int UNSIGNED NOT NULL DEFAULT 0,
  `Sounds2` int UNSIGNED NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for zone_music_locale
-- ----------------------------
CREATE TABLE `zone_music_locale`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `locale` varchar(4) CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NOT NULL,
  `SetName_lang` text CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci NULL,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `locale`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic PARTITION BY LIST COLUMNS (`locale`)
PARTITIONS 10
(PARTITION `deDE` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 ,
PARTITION `esES` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 ,
PARTITION `esMX` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 ,
PARTITION `frFR` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 ,
PARTITION `itIT` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 ,
PARTITION `koKR` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 ,
PARTITION `ptBR` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 ,
PARTITION `ruRU` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 ,
PARTITION `zhCN` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 ,
PARTITION `zhTW` ENGINE = InnoDB MAX_ROWS = 0 MIN_ROWS = 0 );

-- ----------------------------
-- Table structure for npc_sounds
-- ----------------------------
CREATE TABLE `npc_sounds` (
	`ID` INT(10) UNSIGNED NOT NULL,
	`hello` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`goodbye` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`pissed` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`ack` INT(10) UNSIGNED NOT NULL DEFAULT '0',
	`VerifiedBuild` INT(11) NOT NULL DEFAULT '0',
	PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE=InnoDB CHARACTER SET = utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `research_branch`;
CREATE TABLE IF NOT EXISTS `research_branch` (
  `Id` int unsigned NOT NULL DEFAULT '0',
  `Name` text,
  `ResearchFieldId` tinyint unsigned NOT NULL DEFAULT '0',
  `CurrencyId` smallint unsigned NOT NULL DEFAULT '0',
  `TextureFileId` int NOT NULL DEFAULT '0',
  `BigTextureFileId` int NOT NULL DEFAULT '0',
  `ItemId` int NOT NULL DEFAULT '0',
  `VerifiedBuild` smallint NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB CHARACTER SET = utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `research_branch_locale`;
CREATE TABLE IF NOT EXISTS `research_branch_locale` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `Name_lang` text,
  `VerifiedBuild` smallint NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`locale`)
) ENGINE=InnoDB CHARACTER SET = utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `research_project`;
CREATE TABLE IF NOT EXISTS `research_project` (
  `Name` text,
  `Description` text,
  `Id` int unsigned NOT NULL DEFAULT '0',
  `Rarity` tinyint unsigned NOT NULL DEFAULT '0',
  `SpellId` int NOT NULL DEFAULT '0',
  `ResearchBranchId` smallint unsigned NOT NULL DEFAULT '0',
  `NumSockets` tinyint unsigned NOT NULL DEFAULT '0',
  `TextureFileId` int NOT NULL DEFAULT '0',
  `RequiredWeight` int unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` smallint NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB CHARACTER SET = utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `research_project_locale`;
CREATE TABLE IF NOT EXISTS `research_project_locale` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `Name_lang` text,
  `Description_lang` text,
  `VerifiedBuild` smallint NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`locale`)
) ENGINE=InnoDB CHARACTER SET = utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `research_site`;
CREATE TABLE IF NOT EXISTS `research_site` (
  `Id` int unsigned NOT NULL DEFAULT '0',
  `Name` text,
  `MapId` smallint NOT NULL DEFAULT '0',
  `QuestPoiBlobId` int NOT NULL DEFAULT '0',
  `AreaPOIIconEnum` int unsigned NOT NULL DEFAULT '0',
  `VerifiedBuild` smallint NOT NULL DEFAULT '0',
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB CHARACTER SET = utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `research_site_locale`;
CREATE TABLE IF NOT EXISTS `research_site_locale` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `locale` varchar(4) NOT NULL,
  `Name_lang` text,
  `VerifiedBuild` smallint NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`locale`)
) ENGINE=InnoDB CHARACTER SET = utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `quest_p_o_i_point`;
CREATE TABLE IF NOT EXISTS `quest_p_o_i_point` (
  `ID` int NOT NULL DEFAULT '0',
  `X` smallint NOT NULL DEFAULT '0',
  `Y` smallint NOT NULL DEFAULT '0',
  `Z` smallint NOT NULL DEFAULT '0',
  `QuestPOIBlobID` int NOT NULL DEFAULT '0',
  `VerifiedBuild` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB CHARACTER SET = utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `pvp_bracket_types`;
CREATE TABLE `pvp_bracket_types` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `BracketID` tinyint NOT NULL DEFAULT '0',
  `WeeklyQuestID_0` int NOT NULL DEFAULT '0',
  `WeeklyQuestID_1` int NOT NULL DEFAULT '0',
  `WeeklyQuestID_2` int NOT NULL DEFAULT '0',
  `WeeklyQuestID_3` int NOT NULL DEFAULT '0',
  `VerifiedBuild` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`, `VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
