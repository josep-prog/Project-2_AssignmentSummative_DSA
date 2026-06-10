### **Question 1: Job Scheduling Using Max-Heap**

For this task, I implemented an array-based Max-Heap to simulate a cloud scheduler that always processes the highest-priority job first. Each job was assigned a unique ID (A–K) and a priority value. I first built a binary tree from the given array and converted it into a Max-Heap using the heapify-down process. When the urgent job with priority 100 arrived, it was inserted at the end of the heap and moved upward until it became the root. Later, when the urgent job was removed, the last node replaced the root and heapify-down was applied to restore the Max-Heap property.

The main challenge was maintaining the heap structure after insertion and deletion. To solve this, I implemented separate heapify-up and heapify-down functions that automatically reposition nodes whenever the heap property is violated. This ensured that the highest-priority job always remained at the root while keeping insertion and deletion operations efficient.

### **Question 2: Airport Security Priority Queue**

In this task, I used a Max-Heap to manage passengers based on their risk scores. Each heap node stored both the passenger's name and risk score, allowing the passenger with the highest risk to always remain at the root. After building the heap, I extracted passengers to generate the screening order from highest to lowest risk. I also demonstrated insertion when a passenger with a risk score of 98 arrived and deletion when that passenger was later cleared.

A challenge was ensuring that passenger names remained correctly associated with their risk scores during heap operations. To address this, I stored both pieces of information in a single structure and swapped the entire structure whenever nodes were rearranged. This preserved data consistency while maintaining the Max-Heap property throughout all operations.

### **Question 3: Fiber-Optic Network Using Kruskal's Algorithm**

For this problem, I represented the smart city network as an adjacency matrix and applied Kruskal's Algorithm to find the Minimum Spanning Tree (MST). The algorithm sorted all fiber-optic links by cost and selected the cheapest connections that did not create cycles. This process continued until all hubs were connected, resulting in a network with the minimum possible installation cost.

The main challenge was avoiding cycles while still choosing the lowest-cost connections. I solved this by using the Union-Find technique, which checks whether two hubs are already connected before adding a new link. This allowed me to construct an efficient and reliable network while minimizing the overall installation cost.

### **Question 4: Cyber Incident Investigation Using BFS**

In this task, I modeled the enterprise communication system as a graph and used Breadth-First Search (BFS) to investigate a suspected compromised workstation. Starting from the user-selected node, BFS explored all directly connected workstations and identified its immediate neighbors. The algorithm then examined the data transfer times associated with those connections.

The challenge was determining which neighboring workstation posed the greatest risk of exposure. To solve this, I compared the transfer times of all directly connected workstations during the traversal and identified the connection with the highest value. This provided a simple way to highlight the workstation most likely to have been affected by the breach.

### **Question 5: Banking Risk Analysis Using Bellman-Ford**

For this problem, I modeled the banking transaction network as a weighted graph and implemented the Bellman-Ford algorithm to calculate the minimum cumulative transaction cost from Branch A to every other branch. The algorithm repeatedly relaxed all edges until the shortest paths were determined, allowing efficient analysis of risk propagation throughout the network.

A key challenge was detecting negative-weight cycles, which could indicate unstable or potentially exploitable transaction routes. To address this, I performed an additional relaxation pass after computing the shortest paths. If any distance could still be reduced, the program reported the existence of a negative cycle; otherwise, it displayed the shortest paths and minimum costs from Branch A to all other branches.

