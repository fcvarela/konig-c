# Konig Features

## Graphics

 - Node weight/mass to visual size
 - Node and edge labels
 - Node weight decay to original weight based on time
 - Click to show more info
 - Draw to offscreen FBO
 - Stop using fixed-function pipeline and move to GL4.1
 
## Settings
 - Customise appearance (graph colours, background colours)
 - Particle glow

## General

 - ProtoRPC interface to graph/visual api
 - Aggregate state management for VBOs (optimization)
 
## Algo/Physical simulation

 - Octree partitioning for fast n-body simulation (currently _very_ slow
 - Reallocation of vbos only when vectors grow
 - Actual graph representation for Dijskstra, A* searches
 - Topological sorting on acyclic graphs
 