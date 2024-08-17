DELIMITER //
DROP PROCEDURE IF EXISTS AddEmptyItem;
CREATE DEFINER = CURRENT_USER PROCEDURE AddEmptyItem(IN SIndex int, IN SName text, IN SDescription text, IN SIcon int, IN SSlot int)
BEGIN
DELETE FROM `item` WHERE `ID` = SIndex;
DELETE FROM `item_sparse` WHERE `ID` = SIndex;
DELETE FROM `item_sparse_locale` WHERE `ID` = SIndex;
DELETE FROM `hotfix_data`  WHERE `TableHash` = 1344507586 AND `ID` = SIndex;
DELETE FROM `hotfix_data`  WHERE `TableHash` = 1786539638 AND `ID` = SIndex;

INSERT INTO `item` (`ID`, `ClassID`, `SubclassID`, `Material`, `InventoryType`, `SheatheType`, `SoundOverrideSubclassID`, `IconFileDataID`, `ItemGroupSoundsID`, `VerifiedBuild`) VALUES (SIndex, 15, 14, 0, SSlot, 0, 0, SIcon, 0, -44232);
INSERT INTO `item_sparse` (`ID`, `AllowableRace`, `Description`, `Display`, `ExpansionID`, `QualityModifier`, `Flags1`,`Stackable`, `ItemLevel`, `AllowableClass`, `Material`, `Bonding`, `RequiredLevel`, `InventoryType`, `OverallQualityID`, `VerifiedBuild`) VALUES (SIndex, -1, SDescription, sName, 0, 0, 0, 1, 1, -1, 0, 1, 1, SSlot, 8, -44232);
INSERT INTO `item_sparse_locale` (`ID`, `locale`, `Description_lang`, `Display_lang`,`VerifiedBuild`) VALUES (SIndex, "ruRU", SDescription, SName, -44232);
INSERT INTO `hotfix_data` (`ID`,`TableHash`,`RecordId`,`Status`,`VerifiedBuild`) VALUES (SIndex, 1344507586, SIndex, 1, -44232); /* ITEM */
INSERT INTO `hotfix_data` (`ID`,`TableHash`,`RecordId`,`Status`,`VerifiedBuild`) VALUES (SIndex, 1786539638, SIndex, 1, -44232); /* ITEM SPARSEE */
END
//

/* ============================================ */
CALL AddEmptyItem(1000001, "Шлем", "Данный предмет может принимать облик любого другого предмета.", 457903, 1);
CALL AddEmptyItem(1000002, "Наплечники", "Данный предмет может принимать облик любого другого предмета.", 457981, 3);
CALL AddEmptyItem(1000003, "Рубашка", "Данный предмет может принимать облик любого другого предмета.", 4279079, 4);
CALL AddEmptyItem(1000004, "Нагрудник", "Данный предмет может принимать облик любого другого предмета.", 457828, 5);
CALL AddEmptyItem(1000005, "Пояс", "Данный предмет может принимать облик любого другого предмета.", 457708, 6);
CALL AddEmptyItem(1000006, "Поножи", "Данный предмет может принимать облик любого другого предмета.", 457945, 7);
CALL AddEmptyItem(1000007, "Ботинки", "Данный предмет может принимать облик любого другого предмета.", 457750, 8);
CALL AddEmptyItem(1000008, "Наручи", "Данный предмет может принимать облик любого другого предмета.", 457786, 9);
CALL AddEmptyItem(1000009, "Перчатки", "Данный предмет может принимать облик любого другого предмета.", 457861, 10);
CALL AddEmptyItem(1000010, "Правая рука", "Данный предмет может принимать облик любого другого предмета.", 1714096, 21);
CALL AddEmptyItem(1000011, "Левая рука", "Данный предмет может принимать облик любого другого предмета.", 1044536, 14);
CALL AddEmptyItem(1000012, "Плащ", "Данный предмет может принимать облик любого другого предмета.", 4907432, 16);
CALL AddEmptyItem(1000013, "Накидка", "Данный предмет может принимать облик любого другого предмета.", 514261, 19);
/* ============================================ */

DROP PROCEDURE AddEmptyItem;