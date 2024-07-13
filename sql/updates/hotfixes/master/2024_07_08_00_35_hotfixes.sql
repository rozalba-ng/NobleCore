--
-- Table structure for table `item_display_info_model_mat_res`
--
DROP TABLE IF EXISTS `item_display_info_model_mat_res`;
CREATE TABLE `item_display_info_model_mat_res` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `MaterialResourcesID` int NOT NULL DEFAULT '0',
  `TextureType` int NOT NULL DEFAULT '0',
  `ModelIndex` int NOT NULL DEFAULT '0',
  `ItemDisplayInfoID` int NOT NULL DEFAULT '0',
  `VerifiedBuild` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;