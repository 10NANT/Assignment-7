#include <vector>
#include <unordered_map>
#include <queue>

class Solution {
public:
    int networkDelayTime(std::vector<std::vector<int>>& times, int n, int k) {
        std::unordered_map<int, std::vector<std::pair<int, int>>> graph;

        for (int i = 0; i < times.size(); i++) {
            int from = times[i][0];
            int to = times[i][1];
            int weight = times[i][2];
            graph[from].push_back({to, weight});
        }
      
        std::vector<int> dist(n + 1, -1);
        dist[k] = 0;

        std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            std::greater<std::pair<int, int>>
        > pq;

        pq.push({0, k});

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (currentDist > dist[node]) {
                continue;
            }

            for (auto edge : graph[node]) {
                int nextNode = edge.first;
                int weight = edge.second;
                int newDist = currentDist + weight;

                if (dist[nextNode] == -1 || newDist < dist[nextNode]) {
                    dist[nextNode] = newDist;
                    pq.push({newDist, nextNode});
                }
            }
        }

        int answer = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == -1) {
                return -1;
            }
            answer = std::max(answer, dist[i]);
        }

        return answer;
    }
};
