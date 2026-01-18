struct Rooted {
private:
    std::size_t size_;
    std::vector<int> depth_;
    std::vector<long long> dist_;
    std::vector<std::vector<int>> parent_;
    std::vector<std::vector<int>> childs_;
    std::size_t doubling_depth_;
    std::vector<int> subtree_size_;
    std::vector<int> in_, out_, in2x_, out2x_;

    void init_vectors(int root) {
        assert(0 <= root);
        assert(root < size_);
        depth_.assign(size_, 0);
        dist_.assign(size_, 0);
        subtree_size_.assign(size_, 0);
        in_.assign(size_, 0);
        out_.assign(size_, 0);
        in2x_.assign(size_, 0);
        out2x_.assign(size_, 0);
        childs_.assign(size_, {});
        doubling_depth_ = 1;
        while ((1 << doubling_depth_) < size_) doubling_depth_++;
        parent_ = std::vector<std::vector<int>>(doubling_depth_, std::vector<int>(size_, root));
    }
    
    void build_doubling() {
        for (int k = 1; k < doubling_depth_; k++) {
            for (int i = 0; i < size_; i++) {
                parent_[k][i] = parent_[k - 1][parent_[k - 1][i]];
            }
        }
    }

public:
    struct EulerTourRange {
        int l;
        int r;
    };

    // `G`は 0-indexed の木
    explicit Rooted(const std::vector<std::vector<int>>& G, int root)
        : size_(G.size()) {
        init_vectors(root);
        int timer = 0, timer2x = 0;
        function<int(int, int, int, long long)> dfs = [&](int u, int from, int distance, long long w_distance) {
            depth_[u] = distance;
            dist_[u] = w_distance;
            parent_[0][u] = from;
            in_[u] = timer++;
            in2x_[u] = timer2x++;
            int subtree_size = 1;
            for (const auto& v : G[u]) {
                if (v == from) continue;
                subtree_size += dfs(v, u, distance + 1, w_distance + 1);
                childs_[u].push_back(v);
            }
            subtree_size_[u] = subtree_size;
            out_[u] = timer;
            out2x_[u] = timer++;
            return subtree_size;
        };
        dfs(root, root, 0, 0);
        build_doubling();
    }

    // `G`は 0-indexed の重み付き木
    explicit Rooted(const std::vector<std::vector<pair<int, long long>>>& G, int root)
        : size_(G.size()) {
        init_vectors(root);
        int timer = 0, timer2x = 0;
        function<int(int, int, int, long long)> dfs = [&](int u, int from, int distance, long long w_distance) {
            depth_[u] = distance;
            dist_[u] = w_distance;
            parent_[0][u] = from;
            in_[u] = timer++;
            in2x_[u] = timer2x++;
            int subtree_size = 1;
            for (const auto& [v, w] : G[u]) {
                if (v == from) continue;
                subtree_size += dfs(v, u, distance + 1, w_distance + w);
                childs_[u].push_back(v);
            }
            subtree_size_[u] = subtree_size;
            out_[u] = timer;
            out2x_[u] = timer++;
            return subtree_size;
        };
        dfs(root, root, 0, 0);
        build_doubling();
    }

    int forward(int u, long long count) {
        int current = u;
        for (int k = 0; k < doubling_depth_; k++) {
            if (!((count >> k) & 1)) continue;
            current = parent_[k][current];
        }
        return current;
    }

    int lca(int u, int v) {
        if (depth_[u] < depth_[v]) swap(u, v);
        u = forward(u, depth_[u] - depth_[v]);
        if (u == v) return u;

        for (int k = doubling_depth_ - 1; k >= 0; k--) {
            if (parent_[k][u] != parent_[k][v]) {
                u = parent_[k][u];
                v = parent_[k][v];
            }
        }
        return parent_[0][u];
    }

    long long dist(int u, int v) {
        return dist_[u] + dist_[v] - 2 * dist_[lca(u, v)];
    }

    int size(int u) {
        return size_;
    }

    int subtree_size(int u) {
        return subtree_size_[u];
    }

    bool is_on_path(int u, int v, int a) {
        return dist(u, v) == dist(u, a) + dist(a, v);
    }

    bool is_ancestor(int u, int may_ancestor) {
        return in_[may_ancestor] <= in_[u] && out_[u] <= out_[may_ancestor];
    }

    EulerTourRange tour_range(int u) {
        return {in_[u], out_[u]};
    }

    EulerTourRange tour_range2x(int u) {
        return {in2x_[u], out2x_[u]};
    }

    long long count_superpaths(int u, int v) {
        if (u == v) return count_superpaths(u);
        auto lca_uv = lca(u, v);
        if (lca_uv == v) swap(u, v);
        if (lca_uv == u) {
            int diff = depth_[v] - depth_[u];
            int w = forward(v, diff - 1);
            long long p_size = size_ - subtree_size_[w];
            return (long long)p_size * subtree_size_[v];
        }
        else {
            return (long long)subtree_size_[u] * subtree_size_[v];
        }
    }

    // [u,u] を含む
    long long count_superpaths(int u) {
        long long ans = (long long)size_ * (size_ - 1) / 2;
        long long p_size = size_ - subtree_size_[u];
        ans -= p_size * (p_size - 1) / 2;
        for (const auto& v : childs_[u]) {
            long long v_size = subtree_size_[v];
            ans -= v_size * (v_size - 1) / 2;
        }
        return ans + 1;
    }
};