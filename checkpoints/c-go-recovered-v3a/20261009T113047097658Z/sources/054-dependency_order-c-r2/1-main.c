#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // Adjacency list using linked lists for edges
    // We need to handle duplicate edges - they don't affect correctness but we should avoid processing them multiple times
    // For topological sort with duplicates, we can just ignore them since they represent the same constraint
    
    int *head = malloc(N * sizeof(int));
    int *next = NULL;
    int *to = NULL;
    int edge_count = 0;
    
    if (N > 0) {
        head = calloc(N, sizeof(int));
    }
    
    // We'll use a simple approach: for each node, store edges in a linked list
    // To handle duplicates efficiently during processing, we can mark visited edges
    
    int *in_degree = calloc(N, sizeof(int));
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Add edge u -> v
        if (head[u] == -1) {
            head[u] = edge_count;
        } else {
            // Check if edge already exists to avoid duplicates
            int temp = head[u];
            while (temp != -1 && to[temp] != v) {
                temp = next[temp];
            }
            if (temp == -1 || to[temp] != v) {
                // Edge doesn't exist, add it
                int new_edge = edge_count++;
                head[u] = new_edge;
                to[new_edge] = v;
                next[new_edge] = -1;
            }
        }
        
        in_degree[v]++;
    }
    
    // Reset head for proper initialization (already done above)
    // But we need to ensure head is properly set up
    
    // Re-initialize head array with -1
    if (N > 0) {
        memset(head, -1, N * sizeof(int));
    }
    
    // Now re-read edges and build the graph properly
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Add edge u -> v if not duplicate
        int temp = head[u];
        while (temp != -1 && to[temp] != v) {
            temp = next[temp];
        }
        if (temp == -1 || to[temp] != v) {
            int new_edge = edge_count++;
            head[u] = new_edge; // Add to front of list
            to[new_edge] = v;
            next[new_edge] = -1;
            
            // Update head pointer since we added at front
            if (head[u] == -1) {
                head[u] = new_edge;
            } else {
                // Need to find the end of the list and add there? 
                // Actually, let's use a simpler approach: just append to list
                // But we need to maintain order for lexicographic smallest
                
                // Let's change approach: use arrays for adjacency with proper management
            }
        }
    }
    
    // Actually, let's restart with a cleaner implementation
    
    free(head);
    free(in_degree);
    
    head = calloc(N, sizeof(int));
    in_degree = calloc(N, sizeof(int));
    to = malloc(100 * sizeof(int));
    next = malloc(100 * sizeof(int));
    edge_count = 0;
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Add edge u -> v
        int new_edge = edge_count++;
        to[new_edge] = v;
        next[new_edge] = head[u];
        head[u] = new_edge;
        in_degree[v]++;
    }
    
    // For lexicographically smallest topological sort, we need to process nodes with minimum in-degree
    // But when there are multiple choices, we pick the smallest node index
    
    // Use a min-heap or simply iterate 0..N-1 each time (N is small, <= 20)
    
    int result[20];
    int result_count = 0;
    int remaining = N;
    
    while (remaining > 0) {
        int min_node = -1;
        int min_in_degree = N + 1;
        
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0 && head[i] != -1) { // Check if node has any outgoing edges? No, check if it's in the graph
                // Actually, we need to track which nodes are still in the graph
                // But since we're using a simple approach, let's track processed nodes
                
                // Better: use a separate array to mark processed nodes
            }
        }
        
        // Let's restructure: maintain a set of available nodes (in_degree == 0)
        // Each iteration, pick the smallest available node
        
        int best_node = -1;
        for (int i = 0; i < N; i++) {
            if (in_degree[i] == 0 && head[i] != -1 || (N > 0 && in_degree[i] == 0)) {
                // Check if node is still active (has outgoing edges or we haven't processed it)
                // Actually, a node with no outgoing edges can still be processed
                // We need to track which nodes have been added to result
                
                // Let's use a simpler approach: just check in_degree and see if node hasn't been output yet
            }
        }
        
        // We need to track which nodes have been output
        int *output = calloc(N, sizeof(int));
        
        while (remaining > 0) {
            best_node = -1;
            for (int i = 0; i < N; i++) {
                if (!output[i] && in_degree[i] == 0) {
                    if (best_node == -1 || i < best_node) {
                        best_node = i;
                    }
                }
            }
            
            if (best_node == -1) {
                // Cycle detected
                printf("ERROR\n");
                return 0;
            }
            
            result[result_count++] = best_node;
            output[best_node] = 1;
            remaining--;
            
            // Decrease in_degree of neighbors
            int temp = head[best_node];
            while (temp != -1) {
                int v = to[temp];
                in_degree[v]--;
                temp = next[temp];
            }
        }
        
        free(output);
    }
    
    // Output result
    for (int i = 0; i < N; i++) {
        printf("%d%c", result[i], i == N - 1 ? '\n' : ' ');
    }
    
    return 0;
}