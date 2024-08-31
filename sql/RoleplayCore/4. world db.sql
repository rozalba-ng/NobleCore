-- ----------------------------
-- Table structure for creature_template_outfits
-- ----------------------------
DROP TABLE IF EXISTS `creature_template_outfits`;
CREATE TABLE `creature_template_outfits`  (
  `entry` int UNSIGNED NOT NULL,
  `npcsoundsid` INT(10) UNSIGNED NOT NULL DEFAULT '0' COMMENT 'entry from NPCSounds.dbc/db2',
  `race` tinyint UNSIGNED NOT NULL DEFAULT 1,
  `class` tinyint UNSIGNED NOT NULL DEFAULT 1,
  `gender` tinyint UNSIGNED NOT NULL DEFAULT 0 COMMENT '0 for male, 1 for female',
  `spellvisualkitid` int NOT NULL DEFAULT 0,
  `customizations` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  `head` bigint NOT NULL DEFAULT 0,
  `head_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `shoulders` bigint NOT NULL DEFAULT 0,
  `shoulders_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `body` bigint NOT NULL DEFAULT 0,
  `body_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `chest` bigint NOT NULL DEFAULT 0,
  `chest_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `waist` bigint NOT NULL DEFAULT 0,
  `waist_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `legs` bigint NOT NULL DEFAULT 0,
  `legs_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `feet` bigint NOT NULL DEFAULT 0,
  `feet_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `wrists` bigint NOT NULL DEFAULT 0,
  `wrists_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `hands` bigint NOT NULL DEFAULT 0,
  `hands_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `back` bigint NOT NULL DEFAULT 0,
  `back_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `tabard` bigint NOT NULL DEFAULT 0,
  `tabard_appearance` int UNSIGNED NOT NULL DEFAULT 0,
  `guildid` bigint UNSIGNED NOT NULL DEFAULT 0,
  `description` text CHARACTER SET utf8 COLLATE utf8_general_ci NULL,
  PRIMARY KEY (`entry`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = 'Use positive values for item entries and negative to use item displayid for head, shoulders etc.' ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for creature_template_outfits_customizations
-- ----------------------------
DROP TABLE IF EXISTS `creature_template_outfits_customizations`;
CREATE TABLE `creature_template_outfits_customizations`  (
  `chrCustomizationOptionID` int UNSIGNED NOT NULL,
  `chrCustomizationChoiceID` int UNSIGNED NOT NULL DEFAULT 0,
  `outfitID` bigint NOT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of creature_template_outfits_customizations
-- ----------------------------

-- ----------------------------
-- Table structure for scrapping_loot_template
-- ----------------------------
DROP TABLE IF EXISTS `scrapping_loot_template`;
CREATE TABLE `scrapping_loot_template`  (
  `Entry` mediumint UNSIGNED NOT NULL DEFAULT 0,
  `Item` mediumint NOT NULL DEFAULT 0,
  `Reference` mediumint UNSIGNED NOT NULL DEFAULT 0,
  `Chance` float NOT NULL DEFAULT 100,
  `QuestRequired` tinyint(1) NOT NULL DEFAULT 0,
  `LootMode` smallint UNSIGNED NOT NULL DEFAULT 1,
  `GroupId` tinyint UNSIGNED NOT NULL DEFAULT 0,
  `MinCount` int UNSIGNED NOT NULL DEFAULT 1,
  `MaxCount` int UNSIGNED NOT NULL DEFAULT 1,
  `Comment` varchar(255) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`Entry`, `Item`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 1 CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci COMMENT = 'Loot System' ROW_FORMAT = FIXED;

-- ----------------------------
-- Records of scrapping_loot_template
-- ----------------------------
DELETE FROM `scrapping_loot_template`;
INSERT INTO `scrapping_loot_template` (`Entry`, `Item`, `Reference`, `Chance`, `QuestRequired`, `LootMode`, `GroupId`, `MinCount`, `MaxCount`, `Comment`) VALUES
	(1, 160266, 0, 100, 0, 1, 0, 1, 1, NULL),
	(2, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(2, 154165, 0, 100, 0, 1, 0, 1, 8, NULL),
	(2, 11291, 0, 100, 0, 1, 0, 1, 3, NULL),
	(3, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(3, 154165, 0, 100, 0, 1, 0, 2, 8, NULL),
	(3, 11291, 0, 100, 0, 1, 0, 1, 4, NULL),
	(4, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(4, 154165, 0, 100, 0, 1, 0, 4, 8, NULL),
	(4, 11291, 0, 100, 0, 1, 0, 3, 6, NULL),
	(5, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(5, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(5, 159959, 0, 100, 0, 1, 0, 1, 5, NULL),
	(6, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(6, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(6, 152577, 0, 20, 0, 1, 0, 5, 8, NULL),
	(6, 158378, 0, 5, 0, 1, 0, 2, 6, NULL),
	(6, 159959, 0, 100, 0, 1, 0, 1, 8, NULL),
	(7, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(7, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(7, 152577, 0, 5, 0, 1, 0, 4, 6, NULL),
	(7, 158378, 0, 5, 0, 1, 0, 2, 4, NULL),
	(7, 159959, 0, 100, 0, 1, 0, 1, 8, NULL),
	(8, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(8, 152577, 0, 100, 0, 1, 0, 8, 21, NULL),
	(8, 158378, 0, 100, 0, 1, 0, 3, 8, NULL),
	(8, 159959, 0, 100, 0, 1, 0, 5, 10, NULL),
	(9, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(9, 152577, 0, 100, 0, 1, 0, 4, 10, NULL),
	(9, 158378, 0, 100, 0, 1, 0, 2, 6, NULL),
	(9, 159959, 0, 100, 0, 1, 0, 3, 9, NULL),
	(10, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(11, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(12, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(13, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(13, 152541, 0, 100, 0, 1, 0, 1, 3, NULL),
	(13, 154164, 0, 100, 0, 1, 0, 1, 2, NULL),
	(14, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(14, 152541, 0, 100, 0, 1, 0, 2, 5, NULL),
	(14, 152542, 0, 5, 0, 1, 0, 2, 5, NULL),
	(14, 154164, 0, 100, 0, 1, 0, 1, 3, NULL),
	(14, 154165, 0, 20, 0, 1, 0, 3, 9, NULL),
	(15, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(15, 152541, 0, 100, 0, 1, 0, 2, 5, NULL),
	(15, 152542, 0, 5, 0, 1, 0, 1, 4, NULL),
	(15, 154164, 0, 100, 0, 1, 0, 1, 3, NULL),
	(15, 154165, 0, 5, 0, 1, 0, 2, 7, NULL),
	(16, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(16, 152542, 0, 100, 0, 1, 0, 4, 9, NULL),
	(16, 154165, 0, 100, 0, 1, 0, 7, 12, NULL),
	(16, 154722, 0, 100, 0, 1, 0, 3, 21, NULL),
	(17, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(17, 152542, 0, 100, 0, 1, 0, 1, 4, NULL),
	(17, 154165, 0, 100, 0, 1, 0, 5, 8, NULL),
	(17, 154722, 0, 100, 0, 1, 0, 5, 12, NULL),
	(18, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(19, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(20, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(21, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(21, 153050, 0, 100, 0, 1, 0, 1, 3, NULL),
	(21, 154164, 0, 100, 0, 1, 0, 1, 2, NULL),
	(22, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(22, 153051, 0, 10, 0, 1, 0, 8, 17, NULL),
	(22, 154165, 0, 10, 0, 1, 0, 5, 8, NULL),
	(22, 153050, 0, 100, 0, 1, 0, 2, 5, NULL),
	(22, 154164, 0, 100, 0, 1, 0, 2, 3, NULL),
	(23, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(23, 153051, 0, 10, 0, 1, 0, 4, 9, NULL),
	(23, 154165, 0, 10, 0, 1, 0, 2, 8, NULL),
	(23, 153050, 0, 100, 0, 1, 0, 2, 5, NULL),
	(23, 154164, 0, 100, 0, 1, 0, 2, 3, NULL),
	(24, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(24, 152542, 0, 100, 0, 1, 0, 4, 8, NULL),
	(24, 154165, 0, 100, 0, 1, 0, 6, 16, NULL),
	(24, 153051, 0, 100, 0, 1, 0, 8, 18, NULL),
	(24, 160059, 0, 100, 0, 1, 0, 6, 10, NULL),
	(25, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(25, 152542, 0, 100, 0, 1, 0, 1, 2, NULL),
	(25, 154165, 0, 100, 0, 1, 0, 6, 8, NULL),
	(25, 153051, 0, 100, 0, 1, 0, 10, 14, NULL),
	(25, 160059, 0, 100, 0, 1, 0, 3, 7, NULL),
	(26, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(27, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(28, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(29, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(29, 152512, 0, 100, 0, 1, 0, 1, 2, NULL),
	(29, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(30, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(30, 152513, 0, 10, 0, 1, 0, 2, 7, NULL),
	(30, 152579, 0, 10, 0, 1, 0, 2, 9, NULL),
	(30, 152512, 0, 100, 0, 1, 0, 1, 4, NULL),
	(30, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(31, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(31, 152513, 0, 10, 0, 1, 0, 1, 5, NULL),
	(31, 152579, 0, 10, 0, 1, 0, 2, 5, NULL),
	(31, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(31, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(32, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(32, 152542, 0, 100, 0, 1, 0, 4, 8, NULL),
	(32, 154165, 0, 100, 0, 1, 0, 6, 16, NULL),
	(32, 153051, 0, 100, 0, 1, 0, 8, 18, NULL),
	(32, 160059, 0, 100, 0, 1, 0, 6, 10, NULL),
	(33, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(33, 152542, 0, 100, 0, 1, 0, 1, 2, NULL),
	(33, 154165, 0, 100, 0, 1, 0, 6, 8, NULL),
	(33, 153051, 0, 100, 0, 1, 0, 10, 14, NULL),
	(33, 160059, 0, 100, 0, 1, 0, 3, 7, NULL),
	(34, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(35, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(36, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(37, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(37, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(37, 159959, 0, 100, 0, 1, 0, 1, 5, NULL),
	(38, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(38, 152576, 0, 100, 0, 1, 0, 1, 3, NULL),
	(38, 152577, 0, 5, 0, 1, 0, 4, 6, NULL),
	(38, 158378, 0, 5, 0, 1, 0, 2, 4, NULL),
	(38, 159959, 0, 100, 0, 1, 0, 1, 8, NULL),
	(39, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(39, 152577, 0, 100, 0, 1, 0, 4, 10, NULL),
	(39, 158378, 0, 100, 0, 1, 0, 2, 6, NULL),
	(39, 159959, 0, 100, 0, 1, 0, 3, 9, NULL),
	(40, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(40, 153700, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153701, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153702, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153703, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153704, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 153705, 0, 5, 0, 1, 0, 1, 2, NULL),
	(40, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(41, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(41, 154120, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154121, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154122, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154123, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154124, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 154125, 0, 5, 0, 1, 0, 1, 2, NULL),
	(41, 152579, 0, 100, 0, 1, 0, 1, 5, NULL),
	(42, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(42, 154120, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154121, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154122, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154123, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154124, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 154125, 0, 10, 0, 1, 0, 1, 2, NULL),
	(42, 152513, 0, 100, 0, 1, 0, 1, 5, NULL),
	(43, 162460, 0, 100, 0, 1, 0, 15, 15, NULL),
	(44, 162461, 0, 100, 0, 1, 0, 25, 25, NULL),
	(45, 162461, 0, 100, 0, 1, 0, 250, 250, NULL),
	(46, 152668, 0, 100, 0, 1, 0, 1, 1, NULL),
	(47, 152510, 0, 100, 0, 1, 0, 1, 3, NULL),
	(47, 152507, 0, 100, 0, 1, 0, 1, 12, NULL),
	(47, 152505, 0, 100, 0, 1, 0, 1, 12, NULL),
	(47, 152511, 0, 100, 0, 1, 0, 1, 12, NULL),
	(47, 152509, 0, 100, 0, 1, 0, 1, 8, NULL),
	(47, 152506, 0, 100, 0, 1, 0, 1, 8, NULL),
	(47, 152508, 0, 100, 0, 1, 0, 1, 12, NULL),
	(48, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(48, 158188, 0, 50, 0, 1, 0, 2, 8, NULL),
	(48, 158187, 0, 100, 0, 1, 0, 5, 10, NULL),
	(49, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(49, 158188, 0, 50, 0, 1, 0, 5, 11, NULL),
	(49, 158187, 0, 100, 0, 1, 0, 5, 10, NULL),
	(50, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(50, 158189, 0, 25, 0, 1, 0, 1, 4, NULL),
	(50, 158188, 0, 50, 0, 1, 0, 5, 13, NULL),
	(50, 158187, 0, 100, 0, 1, 0, 5, 10, NULL),
	(51, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(51, 11291, 0, 50, 0, 1, 0, 1, 1, NULL),
	(51, 152875, 0, 100, 0, 1, 0, 1, 3, NULL),
	(52, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(52, 11291, 0, 50, 0, 1, 0, 1, 1, NULL),
	(52, 152875, 0, 100, 0, 1, 0, 1, 3, NULL),
	(53, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(53, 11291, 0, 50, 0, 1, 0, 1, 1, NULL),
	(53, 152876, 0, 100, 0, 1, 0, 1, 1, NULL),
	(54, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(54, 153050, 0, 80, 0, 1, 0, 1, 4, NULL),
	(54, 154164, 0, 80, 0, 1, 0, 1, 2, NULL),
	(54, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(55, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(55, 154165, 0, 80, 0, 1, 0, 5, 10, NULL),
	(55, 153051, 0, 80, 0, 1, 0, 5, 10, NULL),
	(55, 160059, 0, 100, 0, 1, 0, 4, 10, NULL),
	(56, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(56, 154165, 0, 80, 0, 1, 0, 9, 12, NULL),
	(56, 153051, 0, 80, 0, 1, 0, 7, 17, NULL),
	(56, 160059, 0, 100, 0, 1, 0, 4, 15, NULL),
	(57, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(57, 153700, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153701, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153702, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153703, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153704, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 153705, 0, 5, 0, 1, 0, 1, 2, NULL),
	(57, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(58, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(58, 154120, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154121, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154122, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154123, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154124, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 154125, 0, 5, 0, 1, 0, 1, 2, NULL),
	(58, 152579, 0, 100, 0, 1, 0, 1, 5, NULL),
	(59, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(59, 154120, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154121, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154122, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154123, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154124, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 154125, 0, 10, 0, 1, 0, 1, 2, NULL),
	(59, 152579, 0, 100, 0, 1, 0, 1, 5, NULL),
	(60, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(60, 152512, 0, 100, 0, 1, 0, 1, 2, NULL),
	(60, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(61, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(61, 152513, 0, 10, 0, 1, 0, 1, 5, NULL),
	(61, 152579, 0, 10, 0, 1, 0, 2, 5, NULL),
	(61, 152512, 0, 100, 0, 1, 0, 1, 3, NULL),
	(61, 160298, 0, 100, 0, 1, 0, 1, 1, NULL),
	(62, 152668, 0, 16, 0, 1, 0, 1, 1, NULL),
	(62, 152542, 0, 100, 0, 1, 0, 1, 2, NULL),
	(62, 154165, 0, 100, 0, 1, 0, 6, 8, NULL),
	(62, 153051, 0, 100, 0, 1, 0, 10, 14, NULL),
	(62, 160059, 0, 100, 0, 1, 0, 3, 7, NULL),
	(63, 152512, 0, 100, 0, 1, 0, 1, 3, ''),
	(63, 152513, 0, 10, 0, 1, 0, 1, 5, ''),
	(63, 152579, 0, 10, 0, 1, 0, 2, 5, ''),
	(63, 152668, 0, 16, 0, 1, 0, 1, 1, ''),
	(63, 160298, 0, 100, 0, 1, 0, 1, 1, '');

REPLACE INTO `creature_model_info` VALUES (105540, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (105328, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (105213, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (112642, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (113958, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (114211, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (106003, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (107058, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (107056, 0, 0, 0, 0);
REPLACE INTO `creature_model_info` VALUES (105268, 0, 0, 0, 0);

REPLACE INTO `spell_script_names` VALUES (5782, 'spell_warl_fear');
REPLACE INTO `spell_script_names` VALUES (204730, 'spell_warl_fear_buff');
REPLACE INTO `spell_script_names` VALUES (146739, 'spell_warl_corruption_effect');
REPLACE INTO `spell_script_names` VALUES (234153, 'spell_warlock_drain_life');
REPLACE INTO `spell_script_names` VALUES (205179, 'aura_warl_phantomatic_singularity');
REPLACE INTO `spell_script_names` VALUES (48181, 'aura_warl_haunt');
REPLACE INTO `spell_script_names` VALUES (205180, 'spell_warlock_summon_darkglare');
REPLACE INTO `spell_script_names` VALUES (5697, 'spell_warlock_unending_breath');
REPLACE INTO `spell_script_names` VALUES (111771, 'spell_warl_demonic_gateway');
REPLACE INTO `spell_script_names` VALUES (105174, 'spell_warl_hand_of_guldan');
REPLACE INTO `spell_script_names` VALUES (86040, 'spell_warl_hand_of_guldan_damage');
REPLACE INTO `spell_script_names` VALUES (104316, 'spell_warlock_call_dreadstalkers');
REPLACE INTO `spell_script_names` VALUES (205231, 'spell_warl_eye_laser');
REPLACE INTO `spell_script_names` VALUES (264178, 'spell_warlock_demonbolt_new');
REPLACE INTO `spell_script_names` VALUES (205145, 'spell_warl_demonic_calling');
REPLACE INTO `spell_script_names` VALUES (157695, 'spell_warl_demonbolt');
REPLACE INTO `spell_script_names` VALUES (196277, 'spell_warl_implosion');
REPLACE INTO `spell_script_names` VALUES (603, 'spell_warlock_doom');
REPLACE INTO `spell_script_names` VALUES (17962, 'spell_warl_conflagrate');
REPLACE INTO `spell_script_names` VALUES (17962, 'spell_warl_conflagrate_aura');
REPLACE INTO `spell_script_names` VALUES (6353, 'spell_warlock_soul_fire');
REPLACE INTO `spell_script_names` VALUES (196447, 'spell_warl_channel_demonfire');
REPLACE INTO `spell_script_names` VALUES (152108, 'spell_warl_cataclysm');
REPLACE INTO `spell_script_names` VALUES (215941, 'spell_warl_soul_conduit');
REPLACE INTO `spell_script_names` VALUES (232670, 'spell_warr_shadowbolt_affliction');
REPLACE INTO `spell_script_names` VALUES (104318, 'spell_warlock_fel_firebolt_wild_imp');
REPLACE INTO `spell_script_names` VALUES (29722, 'spell_warl_incinerate');
REPLACE INTO `spell_script_names` VALUES (980, 'spell_warlock_agony');
REPLACE INTO `spell_script_names` VALUES (386344, 'spell_warlock_inquisitors_gaze');
REPLACE INTO `spell_script_names` VALUES (23920, 'spell_warr_spell_reflect');
REPLACE INTO `spell_script_names` VALUES (228920, 'spell_warr_ravager');
REPLACE INTO `spell_script_names` VALUES (152277, 'spell_warr_ravager');
REPLACE INTO `spell_script_names` VALUES (156287, 'spell_warr_ravager_damage');
REPLACE INTO `spell_script_names` VALUES (190456, 'spell_warr_ignore_pain');
REPLACE INTO `spell_script_names` VALUES (12975,	'spell_warr_last_stand');
REPLACE INTO `spell_script_names` VALUES (64380, 'spell_warr_shattering_throw');
REPLACE INTO `spell_script_names` VALUES (65941, 'spell_warr_shattering_throw');
REPLACE INTO `spell_script_names` VALUES (469, 'spell_warr_shout');
REPLACE INTO `spell_script_names` VALUES (6673, 'spell_warr_shout');
REPLACE INTO `spell_script_names` VALUES (1680, 'spell_warr_wirlwind_dmg');
REPLACE INTO `spell_script_names` VALUES (385952, 'spell_warr_shiel_charge');
REPLACE INTO `spell_script_names` VALUES (153561, 'spell_mage_meteor');
REPLACE INTO `spell_script_names` VALUES (153564, 'spell_mage_meteor_damage');
REPLACE INTO `spell_script_names` VALUES (205025, 'spell_mage_presence_of_mind');
REPLACE INTO `spell_script_names` VALUES (48792,	'spell_dk_icebound_fortitude');
REPLACE INTO `spell_script_names` VALUES (196782, 'aura_dk_outbreak_periodic');
REPLACE INTO `spell_script_names` VALUES (115994, 'spell_dk_unholy_blight');
REPLACE INTO `spell_script_names` VALUES (55090, 'spell_dk_scourge_strike');
REPLACE INTO `spell_script_names` VALUES (152280, 'aura_dk_defile');
REPLACE INTO `spell_script_names` VALUES (156004, 'spell_dk_defile_aura');
REPLACE INTO `spell_script_names` VALUES (215969, 'spell_dk_epidemic');
REPLACE INTO `spell_script_names` VALUES (215969, 'spell_dk_epidemic_aoe');
REPLACE INTO `spell_script_names` VALUES (357208, 'spell_evo_fire_breath');
REPLACE INTO `spell_script_names` VALUES (357208, 'spell_evo_fire_breath_2');
REPLACE INTO `spell_script_names` VALUES (369536, 'spell_evo_soar');
REPLACE INTO `spell_script_names` VALUES (351239, 'spell_evo_cosmic_visage');
REPLACE INTO `spell_script_names` VALUES (34026, 'spell_hun_kill_command');
REPLACE INTO `spell_script_names` VALUES (259489, 'spell_hun_kill_command');
REPLACE INTO `spell_script_names` VALUES (83381, 'spell_hun_kill_command_proc');
REPLACE INTO `spell_script_names` VALUES (19577, 'spell_hun_intimidation');
REPLACE INTO `spell_script_names` VALUES (375891, 'spell_hun_death_chakram');
REPLACE INTO `spell_script_names` VALUES (19574, 'spell_hun_bestial_wrath');
REPLACE INTO `spell_script_names` VALUES (217200, 'spell_hun_barbed_shot');
REPLACE INTO `spell_script_names` VALUES (120679, 'spell_hun_dire_beast');
REPLACE INTO `spell_script_names` VALUES (102199, 'spell_hun_stampede');
REPLACE INTO `spell_script_names` VALUES (321530, 'spell_hun_bloodshed');
REPLACE INTO `spell_script_names` VALUES (260243, 'spell_hun_volley');
REPLACE INTO `spell_script_names` VALUES (186387, 'spell_bursting_shot');
REPLACE INTO `spell_script_names` VALUES (120361, 'spell_hun_barrage');
REPLACE INTO `spell_script_names` VALUES (269751,'spell_hun_flanking_strike');
REPLACE INTO `spell_script_names` VALUES (360966,'spell_hun_spearhead');
REPLACE INTO `spell_script_names` VALUES (259495,'spell_hun_wildfire_bomb');
REPLACE INTO `spell_script_names` VALUES (115191,'spell_rog_stealth_with_subterfuge');
REPLACE INTO `spell_script_names` VALUES (115191,'spell_rog_stealth');
REPLACE INTO `spell_script_names` VALUES (14062, 'spell_rog_nightstalker');
REPLACE INTO `spell_script_names` VALUES (5171, 'spell_rog_slice_and_dice');
REPLACE INTO `spell_script_names` VALUES (315496, 'spell_rog_slice_and_dice');
REPLACE INTO `spell_script_names` VALUES (385616, 'spell_rog_echoing_reprimand');
REPLACE INTO `spell_script_names` VALUES (2823, 'spell_rog_deadly_poison_instant_damage');
REPLACE INTO `spell_script_names` VALUES (51723, 'spell_rog_fan_of_knives');
REPLACE INTO `spell_script_names` VALUES (121411, 'spell_rog_crimson_tempest');
REPLACE INTO `spell_script_names` VALUES (195457, 'spell_rog_grappling_hook');
REPLACE INTO `spell_script_names` VALUES (271877, 'spell_rog_blade_rush');
REPLACE INTO `spell_script_names` VALUES (197835, 'spell_rog_shuriken_storm');
REPLACE INTO `spell_script_names` VALUES (122773, 'spell_pal_lights_hammer');
REPLACE INTO `spell_script_names` VALUES (122773, 'spell_pal_light_hammer_init_summon');
REPLACE INTO `spell_script_names` VALUES (126892, 'spell_monk_zen_pilgrimage');
REPLACE INTO `spell_script_names` VALUES (126895, 'spell_monk_zen_pilgrimage_return');
REPLACE INTO `spell_script_names` VALUES (293866, 'spell_monk_zen_pilgrimage');
REPLACE INTO `spell_script_names` VALUES (100780, 'spell_monk_tiger_palm');
REPLACE INTO `spell_script_names` VALUES (125883, 'spell_monk_zen_flight_check');
REPLACE INTO `spell_script_names` VALUES (116095, 'spell_monk_disable');
REPLACE INTO `spell_script_names` VALUES (116705, 'spell_monk_spear_hand_strike');
REPLACE INTO `spell_script_names` VALUES (107428, 'spell_monk_rising_sun_kick');
REPLACE INTO `spell_script_names` VALUES (115203, 'spell_monk_fortifying_brew');
REPLACE INTO `spell_script_names` VALUES (119582, 'spell_monk_purifying_brew');
REPLACE INTO `spell_script_names` VALUES (115181, 'spell_monk_breath_of_fire');
REPLACE INTO `spell_script_names` VALUES (122278, 'spell_monk_dampen_harm');
--REPLACE INTO `spell_script_names` VALUES (324312, 'spell_monk_clash');
REPLACE INTO `spell_script_names` VALUES (122280, 'spell_monk_healing_elixirs_aura');
REPLACE INTO `spell_script_names` VALUES (116844, 'spell_monk_ring_of_peace');
REPLACE INTO `spell_script_names` VALUES (140023, 'spell_monk_ring_of_peace_dummy');
REPLACE INTO `spell_script_names` VALUES (115098, 'spell_monk_chi_wave');
REPLACE INTO `spell_script_names` VALUES (132464, 'spell_monk_chi_wave_healing_bolt');
REPLACE INTO `spell_script_names` VALUES (132464, 'spell_monk_chi_wave_heal_missile');
REPLACE INTO `spell_script_names` VALUES (132467, 'spell_monk_chi_wave_damage_missile');
REPLACE INTO `spell_script_names` VALUES (130654, 'spell_monk_chi_burst_heal');
--REPLACE INTO `spell_script_names` VALUES (115399, 'spell_monk_black_ox_brew');
REPLACE INTO `spell_script_names` VALUES (115313, 'spell_monk_jade_serpent_statue');
REPLACE INTO `spell_script_names` VALUES (101643, 'spell_monk_transcendence');
REPLACE INTO `spell_script_names` VALUES (101643, 'aura_monk_transcendence');
REPLACE INTO `spell_script_names` VALUES (119996, 'spell_monk_transcendence_transfer');
REPLACE INTO `spell_script_names` VALUES (116670, 'spell_monk_vivify');
REPLACE INTO `spell_script_names` VALUES (115175, 'spell_monk_soothing_mist');
REPLACE INTO `spell_script_names` VALUES (116680, 'spell_focused_thunder_talent_thunder_focus_tea');
REPLACE INTO `spell_script_names` VALUES (124081, 'spell_monk_zen_pulse');
REPLACE INTO `spell_script_names` VALUES (115151, 'spell_monk_renewing_mist');
REPLACE INTO `spell_script_names` VALUES (115151, 'spell_monk_renewing_mist_hot');
REPLACE INTO `spell_script_names` VALUES (119607, 'spell_monk_renewing_mist_jump');
REPLACE INTO `spell_script_names` VALUES (191837, 'spell_monk_essence_font');
REPLACE INTO `spell_script_names` VALUES (191840, 'spell_monk_essence_font_heal');
--REPLACE INTO `spell_script_names` VALUES (197908, 'spell_monk_mana_tea');
REPLACE INTO `spell_script_names` VALUES (124682, 'spell_monk_enveloping_mist');
--REPLACE INTO `spell_script_names` VALUES (137639, 'spell_monk_storm_earth_and_fire');
REPLACE INTO `spell_script_names` VALUES (122470, 'spell_monk_touch_of_karma');
REPLACE INTO `spell_script_names` VALUES (125174, 'spell_monk_touch_of_karma_buff');
REPLACE INTO `spell_script_names` VALUES (113656, 'spell_monk_fists_of_fury');
REPLACE INTO `spell_script_names` VALUES (117418, 'spell_monk_fists_of_fury_damage');
REPLACE INTO `spell_script_names` VALUES (120086, 'spell_monk_fists_of_fury_stun');
REPLACE INTO `spell_script_names` VALUES (123154, 'spell_monk_fists_of_fury_visual');
REPLACE INTO `spell_script_names` VALUES (117418, 'spell_monk_fists_of_fury_visual_filter');
--REPLACE INTO `spell_script_names` VALUES (152175, 'spell_monk_whirling_dragon_punch');
REPLACE INTO `spell_script_names` VALUES (115057, 'spell_monk_flying_serpent_kick');


REPLACE INTO `creature_template` VALUES (59262, 0, 0, 'Demonic Gateway', '', NULL, '', 'interact', 0, 0, 35, 16777216, 1, 1.14286, 1, 0, 0, 2000, 2000, 1, 1, 1, 512, 67108896, 17825793, 0, 0, 11, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_warl_demonic_gateway', NULL, 53040);
REPLACE INTO `creature_template` VALUES (59271, 0, 0, 'Demonic Gateway', '', NULL, '', 'interact', 0, 0, 35, 16777216, 1, 1.14286, 1, 0, 0, 2000, 2000, 1, 1, 1, 512, 67108896, 17825793, 0, 0, 11, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_warl_demonic_gateway', NULL, 53040);
REPLACE INTO `creature_template` VALUES (103673, 0, 0, 'Darkglare', '', '', NULL, '', 0, 0, 954, 0, 1, 0.857143, 1, 0, 0, 1477, 2000, 1, 1, 8, 32768, 2048, 0, 19, 0, 3, 0, '', 0, 1, 0, 121, 0, 0, 1, 0, 0, 'npc_pet_warlock_darkglare', NULL, 53040);
REPLACE INTO `creature_template` VALUES (99739, 0, 0, 'Wild Imps', '', '', NULL, '', 0, 0, 90, 0, 1, 1.14286, 1, 0, 0, 0, 2000, 1, 1, 4, 0, 0, 0, 0, 0, 3, 0, '', 0, 1, 0, 121, 0, 0, 1, 0, 0, 'npc_pet_warlock_wild_imp', NULL, 53040);
REPLACE INTO `creature_template` VALUES (76168, 0, 0, 'Ravager', '', '', NULL, '', 0, 0, 35, 0, 2, 0.714286, 1, 0, 0, 2000, 2000, 1, 1, 1, 33587200, 67667968, 16809984, 0, 0, 10, 0, '', 0, 1, 0, 94, 0, 0, 1, 0, 0, 'npc_warr_ravager', NULL, 53040);
REPLACE INTO `creature_template` VALUES (82521, 0, 0, 'Defile', '', '', NULL, '', 0, 0, 1, 0, 1, 1, 1, 0, 0, 2000, 2000, 1, 1, 1, 17826816, 16, 0, 0, 0, 10, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_dk_defile', NULL, 53040);
REPLACE INTO `creature_template` VALUES (102199, 0, 0, 'Stampede', '', '', NULL, '',	0, 0, 35, 0, 1, 1.14286, 1, 0, 0, 1028, 2000, 1, 1, 1, 33554944, 0, 16777216, 0, 0, 10, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, '', NULL, 53040);
REPLACE INTO `creature_template` VALUES (98035, 0, 0, 'Dreadstalker', '', '', NULL, '', 0, 0, 90, 0, 1, 1.28571, 1, 6, 0, 1444, 2000, 1, 1, 4, 0, 0, 0, 0, 0, 3, 0, '', 0, 1, 0, 133, 0, 0, 1, 0, 0, 'npc_warlock_dreadstalker', NULL, 53040);
REPLACE INTO `creature_template` VALUES (59738, 0, 0,'Light\'s Hammer', '', '', NULL, '', 0, 0, 35, 0, 1, 1.14286, 1, 0, 0, 2000, 2000, 0, 0, 1, 33554432, 67143680, 16777217, 0, 0, 11, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_pal_lights_hammer', NULL, 53040);
REPLACE INTO `creature_template` VALUES (60849, 0, 0, 'Jade Serpent Statue', '', '', NULL, '', 0, 0, 5, 0, 1, 1.14286, 1, 0, 0, 1798, 2000, 1, 1, 1, 512, 32800, 0, 0, 0, 11, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_monk_jade_serpent_statue', NULL, 53040);
REPLACE INTO `creature_template` VALUES (73967, 0, 0, 'Niuzao', '', '', NULL, '', 0, 0, 35, 0, 1, 0.857143, 1, 0, 0, 1989, 2000, 1, 1, 1, 32768, 2048, 0, 0, 0, 1, 0, '', 0, 1, 0, 121, 0, 0, 1, 0, 0, '', NULL, 53040);
--REPLACE INTO `creature_template` VALUES (69792, 0, 0, 'Earth Spirit', '', '', NULL, '', 0, 0, 35, 0, 1, 1.14286, 1, 0, 0, 1749, 2000, 1, 1, 4, 32768, 2064, 0, 0, 0, 7, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_monk_sef_spirit', NULL, 53040);
--REPLACE INTO `creature_template` VALUES (69791, 0, 0, 'Fire Spirit', '', NULL, NULL, NULL, 0, 0, 35, 0, 1, 1.14286, 1, 0, 0, 1749, 2000, 1, 1, 4, 32768, 2064, 0, 0, 0, 7, 0, '', 0, 1, 0, 0, 0, 0, 1, 0, 0, 'npc_monk_sef_spirit', NULL, 53040);
REPLACE INTO `creature_template` VALUES (63508, 0, 0, 'Xuen', '', NULL, NULL, NULL, 0, 0, 35, 0, 1, 1.54286, 1, 0, 0, 721, 2000, 1, 1, 1, 32784, 2048, 0, 0, 0, 1, 0, '', 0, 1, 0, 121, 0, 0, 1, 0, 0, 'npc_monk_xuen', NULL, 53040);

REPLACE INTO `npc_spellclick_spells` VALUES (59262, 113902, 0, 0);
REPLACE INTO `npc_spellclick_spells` VALUES (59271, 113902, 0, 0);

REPLACE INTO `areatrigger_scripts` VALUES (8089, 'at_mage_meteor_timer');
REPLACE INTO `areatrigger_scripts` VALUES (6211, 'at_mage_meteor_burn');
REPLACE INTO `areatrigger_scripts` VALUES (1612, 'at_mage_arcane_orb');
REPLACE INTO `areatrigger_scripts` VALUES (6212, 'at_dk_defile');
REPLACE INTO `areatrigger_scripts` VALUES (3983, 'at_monk_ring_of_peace');
REPLACE INTO `areatrigger_scripts` VALUES (5484, 'at_monk_song_of_chi_ji');
REPLACE INTO `areatrigger_scripts` VALUES (5300, 'at_monk_chi_burst');

REPLACE INTO `areatrigger_create_properties` VALUES (177345, 1, 8089, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 3000, 4, 8, 8, 4, 4, 0.3, 0.3, 0, 0, 'at_mage_meteor_timer', 27101);
REPLACE INTO `areatrigger_create_properties` VALUES (4424, 0, 9170, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 60000, 4, 3, 3, 4, 4, 1, 1, 0, 0, 'at_hun_freezing_trap', 48999);
REPLACE INTO `areatrigger_create_properties` VALUES (510, 0, 3678, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 20000, 4, 10, 10, 7, 7, 3, 3, 0, 0, 'at_hun_flare', 40120);
REPLACE INTO `areatrigger_create_properties` VALUES (4435, 0, 9181, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 60000, 4, 3, 3, 4, 4, 1, 1, 0, 0, 'at_hun_tar_trap_not_activated', 40120);
REPLACE INTO `areatrigger_create_properties` VALUES (4436, 0, 3841, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 30000, 4, 8, 8, 10, 10, 5, 5, 0, 0, 'at_hun_tar_trap_activated', 40120);
REPLACE INTO `areatrigger_create_properties` VALUES (1524, 0, 5972, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 4, 5, 5, 2, 2, 0.3, 0.3, 0, 0, 'at_hun_binding_shot', 31478);
REPLACE INTO `areatrigger_create_properties` VALUES (2392, 0, 6966, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 60000, 4, 3, 3, 4, 4, 1, 1, 0, 0, 'at_hun_steel_trap', 48999);
REPLACE INTO `areatrigger_create_properties` VALUES (9810, 0, 14725, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 60000, 4, 3, 3, 4, 4, 1, 1, 0, 0, 'at_hun_explosive_trap', 48999);
REPLACE INTO `areatrigger_create_properties` VALUES (5484, 0, 10191, 0, 0, 0, 1656, 0, 0, -1, 0, 0, 0, 5716, 5000, 0, 5, 5, 0, 0, 0, 0, 0, 0, 'at_monk_song_of_chi_ji', 48838);
REPLACE INTO `areatrigger_create_properties` VALUES (1316, 0, 5300, 0, 0, 392, 0, 0, 0, -1, 0, 0, 0, 931, 1000, 0, 5, 5, 0, 0, 0, 0, 0, 0, 'at_monk_chi_burst', 40120);
REPLACE INTO `areatrigger_create_properties` VALUES (718, 0, 3983, 0, 0, 0, 0, 0, 0, -256, 255, 0, 0, 0, 5000, 0, 8, 8, 0, 0, 0, 0, 0, 0, 'at_monk_ring_of_peace', 40120);

ALTER TABLE `scrapping_loot_template` ADD `ItemType` tinyint NOT NULL DEFAULT 0 AFTER `Entry`;

--Aquadeus part 
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_warl_backdraft';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(17962, 'spell_warl_backdraft');

DELETE FROM `spell_proc` WHERE `SpellId` IN (117828);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(117828,0x00,5,0x00000000,0x00002040,0x00000002,0x00000000,0x0,0x0,0x1,0x2,0x0,0x10,0x0,0,0,0,0); -- Backdraft

DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_warl_cataclysm';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(152108, 'spell_warl_cataclysm');

DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_warl_roaring_blaze';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(17962, 'spell_warl_roaring_blaze');

DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_warl_conflagrate';
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_warl_conflagrate_aura';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(17962, 'spell_warl_conflagrate');

SET @ATID := 100000;

-- Serverside Areatrigger
DELETE FROM `areatrigger_create_properties` WHERE `Id`=34472 AND `IsCustom`=0;
INSERT INTO `areatrigger_create_properties` (`Id`, `IsCustom`, `AreaTriggerId`, `IsAreatriggerCustom`, `Flags`, `MoveCurveId`, `ScaleCurveId`, `MorphCurveId`, `FacingCurveId`, `AnimId`, `AnimKitId`, `DecalPropertiesId`, `SpellForVisuals`, `TimeToTarget`, `TimeToTargetScale`, `Shape`, `ShapeData0`, `ShapeData1`, `ShapeData2`, `ShapeData3`, `ShapeData4`, `ShapeData5`, `ShapeData6`, `ShapeData7`, `ScriptName`, `VerifiedBuild`) VALUES
(34472, 0, @ATID, 1, 4, 0, 0, 0, 0, -1, 0, 0, NULL, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 'areatrigger_sha_arctic_snowstorm', 0);

DELETE FROM `areatrigger_template` WHERE `Id`=@ATID AND `IsCustom`=1;
INSERT INTO `areatrigger_template` (`Id`, `IsCustom`, `Flags`, `ActionSetId`, `ActionSetFlags`, `VerifiedBuild`) VALUES
(@ATID, 1, 1, 0, 0, 0);

-- Proc
DELETE FROM `spell_proc` WHERE `SpellId` IN (462764);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(462764,0x10,11,0x80000000,0x00000000,0x00000000,0x00000000,0x0,0x0,0x1,0x2,0x0,0x0,0x0,0,0,0,0); -- Arctic Snowstorm

-- Spells
DELETE FROM `spell_script_names` WHERE `ScriptName` = 'spell_sha_arctic_snowstorm';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(462764, 'spell_sha_arctic_snowstorm');

DELETE FROM `spell_script_names` WHERE `spell_id` IN (324540, 980, 146739, 316099) AND `ScriptName`='spell_warl_deaths_embrace';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(324540, 'spell_warl_deaths_embrace'),
(980, 'spell_warl_deaths_embrace'),
(146739, 'spell_warl_deaths_embrace'),
(316099, 'spell_warl_deaths_embrace');

DELETE FROM `spell_script_names` WHERE `spell_id`=234153 AND `ScriptName`='spell_warlock_drain_life';
DELETE FROM `spell_script_names` WHERE `spell_id`=234153 AND `ScriptName`='spell_warl_drain_life';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(234153, 'spell_warl_drain_life');

DELETE FROM `spell_script_names` WHERE `spell_id`= 195182;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(195182, 'spell_dk_marrowrend');

DELETE FROM `spell_script_names` WHERE `spell_id`=316099 AND `ScriptName`='spell_warl_perpetual_unstability';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(316099, 'spell_warl_perpetual_unstability');

DELETE FROM `spell_script_names` WHERE `spell_id`=980 AND `ScriptName`='spell_warl_volatile_agony';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(980, 'spell_warl_volatile_agony');

DELETE FROM `spell_proc` WHERE `SpellId` IN (452999);
INSERT INTO `spell_proc` (`SpellId`,`SchoolMask`,`SpellFamilyName`,`SpellFamilyMask0`,`SpellFamilyMask1`,`SpellFamilyMask2`,`SpellFamilyMask3`,`ProcFlags`,`ProcFlags2`,`SpellTypeMask`,`SpellPhaseMask`,`HitMask`,`AttributesMask`,`DisableEffectsMask`,`ProcsPerMinute`,`Chance`,`Cooldown`,`Charges`) VALUES
(452999,0x20,5,0x00000002,0x00000000,0x00000000,0x00000000,0x0,0x0,0x1,0x2,0x0,0x0,0x0,0,0,0,0); -- Siphon Life

DELETE FROM `spell_script_names` WHERE `spell_id`=452999;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(452999, 'spell_warl_siphon_life');

DELETE FROM `spell_script_names` WHERE `spell_id`=278350;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(278350, 'spell_warl_vile_taint');

DELETE FROM `spell_script_names` WHERE `spell_id`=146739 AND `ScriptName`='spell_warl_absolute_corruption';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(146739, 'spell_warl_absolute_corruption');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_warl_unstable_affliction';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
(316099, 'spell_warl_unstable_affliction');