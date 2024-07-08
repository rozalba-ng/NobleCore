--
-- Table structure for table `item_display_info`
--
DROP TABLE IF EXISTS `item_display_info`;
CREATE TABLE `item_display_info` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `GeosetGroupOverride` int NOT NULL DEFAULT '0',
  `ItemVisual` int NOT NULL DEFAULT '0',
  `ParticleColorID` int NOT NULL DEFAULT '0',
  `ItemRangedDisplayInfoID` int NOT NULL DEFAULT '0',
  `OverrideSwooshSoundKitID` int NOT NULL DEFAULT '0',
  `SheatheTransformMatrixID` int NOT NULL DEFAULT '0',
  `StateSpellVisualKitID` int NOT NULL DEFAULT '0',
  `SheathedSpellVisualKitID` int NOT NULL DEFAULT '0',
  `UnsheathedSpellVisualKitID` int NOT NULL DEFAULT '0',
  `Flags` int NOT NULL DEFAULT '0',
  `ModelResourcesID1` int NOT NULL DEFAULT '0',
  `ModelResourcesID2` int NOT NULL DEFAULT '0',
  `ModelMaterialResourcesID1` int NOT NULL DEFAULT '0',
  `ModelMaterialResourcesID2` int NOT NULL DEFAULT '0',
  `ModelType1` int NOT NULL DEFAULT '0',
  `ModelType2` int NOT NULL DEFAULT '0',
  `GeosetGroup1` int NOT NULL DEFAULT '0',
  `GeosetGroup2` int NOT NULL DEFAULT '0',
  `GeosetGroup3` int NOT NULL DEFAULT '0',
  `GeosetGroup4` int NOT NULL DEFAULT '0',
  `GeosetGroup5` int NOT NULL DEFAULT '0',
  `GeosetGroup6` int NOT NULL DEFAULT '0',
  `AttachmentGeosetGroup1` int NOT NULL DEFAULT '0',
  `AttachmentGeosetGroup2` int NOT NULL DEFAULT '0',
  `AttachmentGeosetGroup3` int NOT NULL DEFAULT '0',
  `AttachmentGeosetGroup4` int NOT NULL DEFAULT '0',
  `AttachmentGeosetGroup5` int NOT NULL DEFAULT '0',
  `AttachmentGeosetGroup6` int NOT NULL DEFAULT '0',
  `HelmetGeosetVis1` int NOT NULL DEFAULT '0',
  `HelmetGeosetVis2` int NOT NULL DEFAULT '0',
  `VerifiedBuild` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Table structure for table `item_display_info_material_res`
--
DROP TABLE IF EXISTS `item_display_info_material_res`;
CREATE TABLE `item_display_info_material_res` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `ComponentSection` tinyint unsigned NOT NULL DEFAULT '0',
  `MaterialResourcesID` int NOT NULL DEFAULT '0',
  `ItemDisplayInfoID` int NOT NULL DEFAULT '0',
  `VerifiedBuild` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;