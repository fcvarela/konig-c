# Konig todo list

## Graphics

 - Node weight/mass to visual size
 - Node and edge labels
 - Node weight decay to original weight based on time
 - Click to show more info (tweakbar)
 - Stop using fixed-function pipeline and move to GL4.1
 - Remove all interdepencencies (graph has no solver, renderer has no ui)

## General

 - ProtoRPC interface to graph/visual api
 - Aggregate state management for VBOs (optimization)
 - Move all update, realloc remap logic to insert/remove functions
 
## Algo/Physical simulation

 - Octree partitioning for fast n-body simulation (currently _very_ slow)
 - Reallocation of vbos only when vectors grow -> same as above
 - Actual graph representation for Dijskstra, A* searches
 - Topological sorting on acyclic graphs

## UI
 - Enable click on edge to highlight route to root node (check for loops)

