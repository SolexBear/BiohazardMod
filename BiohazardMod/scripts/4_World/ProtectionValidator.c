//ProtectionValidator.c
class ProtectionValidator {
    static int GetProtectionPoints(PlayerBase player, map<string, ref array<int>> suitData) {
        int total = 0;

        foreach (string itemName, ref array<int> values : suitData) {
            ItemBase item = FindItemOnPlayer(player, itemName);
            if (item) {
                total += values[0]; // punkty ochrony
                if (values.Count() > 1 && values[1] == 1 && !HasFilter(item)) {
                    total -= values[0]; // brak filtra = brak ochrony
                }
            }
        }

        return total;
    }

    static bool IsProtected(PlayerBase player, map<string, ref array<int>> suitData, int requiredPoints = 100) {
        return GetProtectionPoints(player, suitData) >= requiredPoints;
    }

    static ItemBase FindItemOnPlayer(PlayerBase player, string itemName) {
        array<ItemBase> items;
        player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);
        foreach (ItemBase item : items) {
            if (item && item.GetType() == itemName) return item;
        }
        return null;
    }

    static bool HasFilter(ItemBase mask) {
        return mask.FindAttachmentBySlotName("GasMaskFilter") != null;
    }
}
