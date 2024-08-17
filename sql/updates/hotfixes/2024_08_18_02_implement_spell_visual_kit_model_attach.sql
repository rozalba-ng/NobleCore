SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

DROP TABLE IF EXISTS `spell_visual_kit_model_attach`;
CREATE TABLE `spell_visual_kit_model_attach`  (
  `ID` int UNSIGNED NOT NULL DEFAULT 0,
  `Offset1` float NOT NULL DEFAULT 0,
  `Offset2` float NOT NULL DEFAULT 0,
  `Offset3` float NOT NULL DEFAULT 0,
  `OffsetVariation1` float NOT NULL DEFAULT 0,
  `OffsetVariation2` float NOT NULL DEFAULT 0,
  `OffsetVariation3` float NOT NULL DEFAULT 0,
  `SpellVisualEffectNameID` int NOT NULL DEFAULT 0,
  `AttachmentID` int NOT NULL DEFAULT 0,
  `PositionerID` int NOT NULL DEFAULT 0,
  `Yaw` float NOT NULL DEFAULT 0,
  `Pitch` float NOT NULL DEFAULT 0,
  `Roll` float NOT NULL DEFAULT 0,
  `YawVariation` float NOT NULL DEFAULT 0,
  `PitchVariation` float NOT NULL DEFAULT 0,
  `RollVariation` float NOT NULL DEFAULT 0,
  `Scale` float NOT NULL DEFAULT 0,
  `ScaleVariation` float NOT NULL DEFAULT 0,
  `StartAnimID` int NOT NULL DEFAULT 0,
  `AnimID` int NOT NULL DEFAULT 0,
  `EndAnimID` int NOT NULL DEFAULT 0,
  `AnimKitID` int NOT NULL DEFAULT 0,
  `Flags` int NOT NULL DEFAULT 0,
  `LowDefModelAttachID` int NOT NULL DEFAULT 0,
  `StartDelay` float NOT NULL DEFAULT 0,
  `Unknown901` float NOT NULL DEFAULT 0,
  `Unknown1100` int NOT NULL DEFAULT 0,
  `ParentSpellVisualKitID` int NOT NULL DEFAULT 0,
  `VerifiedBuild` int NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`, `VerifiedBuild`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_unicode_ci ROW_FORMAT = Dynamic;


SET FOREIGN_KEY_CHECKS = 1;
