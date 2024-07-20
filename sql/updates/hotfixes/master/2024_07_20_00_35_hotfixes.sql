--
-- Table structure for table `chr_customization_geoset`
--
DROP TABLE IF EXISTS `chr_customization_geoset`;
CREATE TABLE `chr_customization_geoset` (
  `ID` int unsigned NOT NULL DEFAULT '0',
  `GeosetType` int NOT NULL DEFAULT '0',
  `GeosetID` int NOT NULL DEFAULT '0',
  `Modifier` int NOT NULL DEFAULT '0',
  `VerifiedBuild` int NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`,`VerifiedBuild`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;