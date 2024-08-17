SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

DROP TABLE IF EXISTS `spell_visual_kit_effect`;
CREATE TABLE `spell_visual_kit_effect`  (
  `ID` int UNSIGNED NOT NULL,
  `EffectType` int NULL DEFAULT NULL,
  `Effect` int NULL DEFAULT NULL,
  `ParentSpellVisualKitID` int NULL DEFAULT NULL,
  `VerifiedBuild` int NULL DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
