# 🌊 Flood Evacuation Planning System 🚨  
**SDG Goal 11: Make cities and human settlements inclusive, safe, resilient, and sustainable**

---

## 📘 Project Description
The **Flood Evacuation Planning System** is a C++ console application that helps communities prepare for and respond to floods. It provides a simple, menu-driven interface that allows users to mark flooded areas, view flood statuses, receive evacuation recommendations, manage emergency alerts, and reset data for repeated use.  

This project integrates **Data Structures and Algorithms (DSA)** to ensure efficiency, reliability, and scalability:
- **Vectors**: Store barangay names, flood status, and evacuation center details.  
- **Unordered Map (Hash Map)**: Fast lookup of barangay names to node indices.  
- **Graph (Adjacency List)**: Represent road networks between barangays.  
- **Priority Queue + Dijkstra’s Algorithm**: Compute shortest and safest evacuation routes.  
- **Sorting**: Rank evacuation centers by distance and capacity.  
- **Queue (FIFO)**: Manage emergency alerts in real-time.  

By combining these DSA concepts, the system demonstrates how academic knowledge can be applied to build practical, socially relevant disaster management tools that directly support **SDG 11: Sustainable Cities and Communities**.

---

## 📌 Overview
The system provides seven core functions:
1. Mark flooded areas  
2. View flood status  
3. Evacuation recommendation (shortest path + ranking)  
4. View emergency alerts  
5. Clear alerts  
6. Reset flood status  
7. Exit  

---

## 🎯 Problem Statement
Floods often cause:
- Unclear evacuation routes  
- Poor tracking of affected barangays  
- Inefficient alert management  

This system addresses these issues by:
- Tracking flood status using **vectors**  
- Finding safe routes using **Dijkstra’s shortest path algorithm**  
- Managing alerts with **queues**  
- Resetting data for repeated use  

---

## ⚙️ Features
- **Flood Tracking**: Mark barangays as flooded and view their status.  
- **Evacuation Recommendation**: Suggest nearest evacuation center using shortest path + capacity check.  
- **Emergency Alerts**: Queue-based alert system for real-time flood warnings.  
- **Data Reset**: Clear flood status and alerts for reuse.  

---

## 🧩 Data Structures & Algorithms
| **Concept**              | **Usage in System** |
|---------------------------|----------------------|
| `vector`                 | Store barangay names, flood status, evacuation centers |
| `unordered_map`          | Map barangay names to node indices |
| `vector<vector<pair<int,int>>>` | Graph adjacency list for roads |
| `priority_queue` + Dijkstra | Shortest path for evacuation |
| `sort()`                 | Rank evacuation centers |
| `queue`                  | Manage emergency alerts |

---

## ⚙️ Installation / Setup
Clone the repository:
```bash
git clone https://github.com/your-username/flood-evacuation-system.git
