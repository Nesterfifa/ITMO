import org.jetbrains.annotations.NotNull;

import java.util.*;
import java.util.stream.Collectors;

public class ConsistentHashImpl<K> implements ConsistentHash<K> {
    static class HashAndShard {
        final int hash;
        final Shard shard;

        HashAndShard(final int hash, final Shard shard) {
            this.shard = shard;
            this.hash = hash;
        }
    }

    private List<HashAndShard> shardHashes = new ArrayList<>();

    @NotNull
    @Override
    public Shard getShardByKey(K key) {
        int l = -1;
        int r = shardHashes.size();
        int hash = key.hashCode();
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (shardHashes.get(m).hash < hash) {
                l = m;
            } else {
                r = m;
            }
        }

        return r < shardHashes.size() ? shardHashes.get(r).shard : shardHashes.get(0).shard;
    }

    @NotNull
    @Override
    public Map<Shard, Set<HashRange>> addShard(@NotNull Shard newShard, @NotNull Set<Integer> vnodeHashes) {
        Map<Shard, Set<HashRange>> diff = new HashMap<>();
        List<Integer> vnodeHashesSorted = vnodeHashes.stream().sorted().collect(Collectors.toList());
        if (vnodeHashesSorted.isEmpty()) {
            return diff;
        }
        if (shardHashes.isEmpty()) {
            shardHashes = vnodeHashesSorted
                    .stream()
                    .map(hash -> new HashAndShard(hash, newShard))
                    .collect(Collectors.toList());
            return diff;
        }

        int itShardHashes = 0;
        int itNewHashes = 0;
        List<HashAndShard> newShardHashes = new ArrayList<>();
        for (int i = 0; i < vnodeHashes.size() + shardHashes.size(); i++) {
            if (itShardHashes == shardHashes.size()
                    || itNewHashes < vnodeHashesSorted.size()
                    && shardHashes.get(itShardHashes).hash > vnodeHashesSorted.get(itNewHashes)) {
                newShardHashes.add(new HashAndShard(vnodeHashesSorted.get(itNewHashes++), newShard));
            } else {
                newShardHashes.add(shardHashes.get(itShardHashes++));
            }
        }
        shardHashes = newShardHashes;

        int leftBorderIdx = shardHashes.size() - 1;
        while (vnodeHashes.contains(shardHashes.get(leftBorderIdx).hash)) {
            leftBorderIdx--;
        }
        int leftBorder = shardHashes.get(leftBorderIdx).hash + 1;

        for (int i = 0; i < shardHashes.size(); i++) {
            int prev = storageIdx(i - 1);
            int next = storageIdx(i + 1);
            if (!vnodeHashes.contains(shardHashes.get(prev).hash) && vnodeHashes.contains(shardHashes.get(i).hash)) {
                leftBorder = shardHashes.get(prev).hash + 1;
            }
            if (!vnodeHashes.contains(shardHashes.get(next).hash) && vnodeHashes.contains(shardHashes.get(i).hash)) {
                diff.putIfAbsent(shardHashes.get(next).shard, new HashSet<>());
                diff.get(shardHashes.get(next).shard).add(new HashRange(leftBorder, shardHashes.get(i).hash));
            }
        }

        return diff;
    }

    @NotNull
    @Override
    public Map<Shard, Set<HashRange>> removeShard(@NotNull Shard shard) {
        Map<Shard, Set<HashRange>> diff = new HashMap<>();
        List<HashAndShard> newShardHashes = new ArrayList<>();

        int leftBorderIdx = shardHashes.size() - 1;
        while (shardHashes.get(leftBorderIdx).shard.equals(shard)) {
            leftBorderIdx--;
        }
        int leftBorder = shardHashes.get(leftBorderIdx).hash + 1;
        for (int i = 0; i < shardHashes.size(); i++) {
            HashAndShard cur = shardHashes.get(i);
            if (!cur.shard.equals(shard)) {
                newShardHashes.add(cur);
            } else {
                int prev = storageIdx(i - 1);
                int next = storageIdx(i + 1);
                if (!shardHashes.get(prev).shard.equals(shard) && cur.shard.equals(shard)) {
                    leftBorder = shardHashes.get(prev).hash + 1;
                }
                if (!shardHashes.get(next).shard.equals(shard) && cur.shard.equals(shard)) {
                    diff.putIfAbsent(shardHashes.get(next).shard, new HashSet<>());
                    diff.get(shardHashes.get(next).shard).add(new HashRange(leftBorder, cur.hash));
                }
            }
        }

        shardHashes = newShardHashes;
        return diff;
    }

    private int storageIdx(int i) {
        return (i + shardHashes.size()) % shardHashes.size();
    }
}
