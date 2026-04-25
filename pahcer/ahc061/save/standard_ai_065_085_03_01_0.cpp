#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

// AIパラメータ（仮の値）
const double WA = 0.65;  // 誰の領土でもないマスの重み
const double WB = 0.85;  // 自分の領土（レベル未満）の重み
const double WC = 0.3;  // 他のプレイヤーの領土（レベル1）の重み
const double WD = 0.1;  // 他のプレイヤーの領土（レベル2以上）の重み
const double EPSILON = 0;  // ランダム行動の確率

const int N = 10;
const int MAX_TURN = 100;
const int DX[4] = {-1, 1, 0, 0};  // 上下左右
const int DY[4] = {0, 0, -1, 1};

struct State {
    int owner[10][10];      // 各マスの所有者 (-1: 無所属, 0-M-1: プレイヤーID)
    int level[10][10];      // 各マスのレベル
    vector<pair<int, int>> player_pos;  // プレイヤーの現在位置 {row, col}
    vector<vector<int>> V;  // 各マスの価値
    int M;  // プレイヤー数
    int U;  // レベル上限
    mt19937 rng;  // 乱数生成器

    State() : rng(0) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                owner[i][j] = -1;
                level[i][j] = 0;
            }
        }
    }

    // 到達可能領土をBFSで計算
    vector<pair<int, int>> get_reachable_territory(int player_id) {
        vector<vector<bool>> visited(10, vector<bool>(10, false));
        vector<pair<int, int>> reachable;
        queue<pair<int, int>> que;

        // プレイヤーの現在位置から開始
        int start_r = player_pos[player_id].first;
        int start_c = player_pos[player_id].second;
        que.push({start_r, start_c});
        visited[start_r][start_c] = true;

        while (!que.empty()) {
            auto [r, c] = que.front(); que.pop();
            
            // 自領土なら拡張可能
            if (owner[r][c] == player_id) {
                for (int d = 0; d < 4; d++) {
                    int nr = r + DX[d];
                    int nc = c + DY[d];
                    if (nr >= 0 && nr < 10 && nc >= 0 && nc < 10 && !visited[nr][nc] && owner[nr][nc] == player_id) {
                        visited[nr][nc] = true;
                        que.push({nr, nc});
                    }
                }
            }
            
            // 到達可能領土に追加
            reachable.push_back({r, c});
        }

        return reachable;
    }

    // 移動可能なマスを取得（到達可能領土 + 隣接マス、かつ他の駒がない場所）
    vector<pair<int, int>> get_valid_moves(int player_id) {
        auto reachable = get_reachable_territory(player_id);
        vector<pair<int, int>> moves;
        vector<vector<bool>> added(10, vector<bool>(10, false));

        // 到達可能領土のマスを追加
        for (auto [r, c] : reachable) {
            if (!added[r][c]) {
                bool occupied = false;
                for (auto [pr, pc] : player_pos) {
                    if (pr == r && pc == c) {
                        occupied = true;
                        break;
                    }
                }
                if (!occupied) {
                    moves.push_back({r, c});
                    added[r][c] = true;
                }
            }
        }

        // 隣接マスを追加
        for (auto [r, c] : reachable) {
            for (int d = 0; d < 4; d++) {
                int nr = r + DX[d];
                int nc = c + DY[d];
                if (nr >= 0 && nr < 10 && nc >= 0 && nc < 10 && !added[nr][nc]) {
                    bool occupied = false;
                    for (auto [pr, pc] : player_pos) {
                        if (pr == nr && pc == nc) {
                            occupied = true;
                            break;
                        }
                    }
                    if (!occupied) {
                        moves.push_back({nr, nc});
                        added[nr][nc] = true;
                    }
                }
            }
        }

        return moves;
    }

    // プレイヤーpのマス(i,j)に対する評価値を計算
    double evaluate_cell(int player_id, int r, int c) {
        if (owner[r][c] == -1) {
            return V[r][c] * WA;
        } else if (owner[r][c] == player_id) {
            if (level[r][c] < U) {
                return V[r][c] * WB;
            } else {
                return 0.0;  // レベル上限に達している
            }
        } else {
            if (level[r][c] == 1) {
                return V[r][c] * WC;
            } else {
                return V[r][c] * WD;
            }
        }
    }

    // AI風の行動（貪欲 or ランダム）
    pair<int, int> decide_move_ai(int player_id) {
        auto moves = get_valid_moves(player_id);
        if (moves.empty()) {
            return player_pos[player_id];  // 動けなければその場にとどまる
        }

        // 確率εでランダム行動
        uniform_real_distribution<double> dist(0.0, 1.0);
        if (dist(rng) < EPSILON) {
            uniform_int_distribution<int> move_dist(0, moves.size() - 1);
            return moves[move_dist(rng)];
        }

        // 貪欲行動：評価値が最大のマスを選択
        double max_score = -1;
        vector<pair<int, int>> best_moves;
        
        for (auto [r, c] : moves) {
            double score = evaluate_cell(player_id, r, c);
            if (score > max_score) {
                max_score = score;
                best_moves.clear();
                best_moves.push_back({r, c});
            } else if (abs(score - max_score) < 1e-9) {
                best_moves.push_back({r, c});
            }
        }

        // 同点の場合はランダムに選ぶ
        uniform_int_distribution<int> best_dist(0, best_moves.size() - 1);
        return best_moves[best_dist(rng)];
    }

    // 自プレイヤー（プレイヤー0）の行動を決定（とりあえずAIと同じロジック）
    pair<int, int> decide_move_player0() {
        return decide_move_ai(0);
    }

    // ゲームの1ターンを完全にシミュレート
    void simulate_turn(const vector<pair<int, int>>& destinations) {
        // 1. 移動先の決定（すでにdestinationsとして渡されている）

        // 2. 競合解決
        vector<vector<vector<int>>> pos_to_players(10, vector<vector<int>>(10));  // 各マスにいるプレイヤーIDのリスト
        vector<bool> repelled(M, false);  // 各プレイヤーが跳ね返されたかどうか
        
        for (int p = 0; p < M; p++) {
            int r = destinations[p].first;
            int c = destinations[p].second;
            pos_to_players[r][c].push_back(p);
        }

        // 各マスについて、複数の駒が存在する場合の処理
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (pos_to_players[i][j].size() > 1) {
                    // そのマスの所有者の駒が含まれるかチェック
                    bool owner_found = false;
                    int owner_id = owner[i][j];
                    
                    for (int p : pos_to_players[i][j]) {
                        if (p == owner_id) {
                            owner_found = true;
                            break;
                        }
                    }
                    
                    if (owner_found) {
                        // 所有者の駒のみを盤面に残し、他の駒を回収
                        for (int p : pos_to_players[i][j]) {
                            if (p != owner_id) {
                                repelled[p] = true;
                            }
                        }
                    } else {
                        // 所有者の駒が含まれない場合は、すべての駒を回収
                        for (int p : pos_to_players[i][j]) {
                            repelled[p] = true;
                        }
                    }
                }
            }
        }

        // 3. 領土の更新
        for (int p = 0; p < M; p++) {
            if (repelled[p]) continue;  // 回収された駒は処理しない
            
            int r = destinations[p].first;
            int c = destinations[p].second;
            
            if (owner[r][c] == -1) {
                // 占領：誰の領土でもないマス → 自分の領土、レベル1
                owner[r][c] = p;
                level[r][c] = 1;
            } else if (owner[r][c] == p) {
                // 強化：自分の領土 → レベルを1増加（上限U）
                if (level[r][c] < U) {
                    level[r][c]++;
                }
            } else {
                // 攻撃：他のプレイヤーの領土 → レベルを1減少
                level[r][c]--;
                
                if (level[r][c] == 0) {
                    // レベルが0になった → 自分の領土、レベル1
                    owner[r][c] = p;
                    level[r][c] = 1;
                } else {
                    // レベルが0でない → 攻撃したプレイヤーの駒を回収
                    repelled[p] = true;
                }
            }
        }

        // 4. 駒の復帰：回収された駒は元の位置に戻す
        for (int p = 0; p < M; p++) {
            if (repelled[p]) {
                // 元の位置に戻す
                player_pos[p] = destinations[p];
            } else {
                // 回収されなかった駒は新しい位置に移動
                player_pos[p] = destinations[p];
            }
        }
    }

    // スコアを計算
    long long calculate_score(int player_id) {
        long long score = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (owner[i][j] == player_id) {
                    score += (long long)V[i][j] * level[i][j];
                }
            }
        }
        return score;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    State state;

    // 初期入力を読み込む
    int dummy_n, T;
    cin >> dummy_n >> state.M >> T >> state.U;
    
    state.V.assign(10, vector<int>(10));
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> state.V[i][j];
        }
    }

    state.player_pos.resize(state.M);
    for (int p = 0; p < state.M; p++) {
        cin >> state.player_pos[p].first >> state.player_pos[p].second;
        int r = state.player_pos[p].first;
        int c = state.player_pos[p].second;
        state.owner[r][c] = p;
        state.level[r][c] = 1;
    }

    // ゲームループ
    for (int turn = 0; turn < MAX_TURN; turn++) {
        // 各プレイヤーの移動先を決定
        vector<pair<int, int>> destinations(state.M);
        
        // プレイヤー0（自分）の移動先を決定
        destinations[0] = state.decide_move_player0();
        
        // AIプレイヤーの移動先を決定
        for (int p = 1; p < state.M; p++) {
            destinations[p] = state.decide_move_ai(p);
        }

        // 決定した移動先を出力
        cout << destinations[0].first << " " << destinations[0].second << endl;
        cout.flush();

        // ターン結果を読み込む
        for (int p = 0; p < state.M; p++) {
            int tx, ty;
            cin >> tx >> ty;
        }
        for (int p = 0; p < state.M; p++) {
            int ex, ey;
            cin >> ex >> ey;
            state.player_pos[p] = {ex, ey};
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cin >> state.owner[i][j];
            }
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cin >> state.level[i][j];
            }
        }
    }

    return 0;
}