/************************************************************************
File mmph_prism.h - internal information for parallel overlap for 
                   mesh manipulation module for prismatic elements       

Contains:
  - constants
  - data types 
  - global variables (for the whole module)
  - function headers                     

------------------------------  			
History:        
        08.2011 - Krzysztof Banas, initial version
*************************************************************************/

#ifndef _mmph_prism_
#define _mmph_prism_

#include "mmh_intf.h"

#include "mmph_intf.h"


/*** CONSTANTS ***/

#define MMC_MAX_NUM_MESH   10   /* maximal number of meshes */

/*** DATA TYPES ***/

/* type IPID - InterProcessorID - main type for parallel modules */
typedef struct {
  int owner;        /* owner ID (from 1 to nrproc) */
  int id_at_owner;
} mmpt_ipid;

/* node structure */
typedef struct {
  int owner;        /* owner ID (from 1 to nrproc) */
  int id_at_owner;
} mmpt_nodes;

/* edge structure */
typedef struct {
  int owner;        /* owner ID (from 1 to nrproc) */
  int id_at_owner;
} mmpt_edges;

/* face structure */
typedef struct {
  int owner;        /* owner ID (from 1 to nrproc) */
  int id_at_owner;
} mmpt_faces;

/* element structure */
typedef struct {
  int owner;        /* owner ID (from 1 to nrproc) */
  int id_at_owner;
} mmpt_elems;

/* info about refinements - data exchanged between subdoamins */
typedef struct{
  /* for each refined element (prism or hexahedron):
     element_ID, element_type, new_node_ID (if any), 
     new_edges_IDs, new_faces_IDs (horizontal+vertical), new_elems_IDs (sons)
     1 + 1 + [1] + 3..6 + 10..12 + 8 = 23..29
  */
  int* elem;
  /* for each refined face:
     face_ID, face_type,  
     new_node_ID (if any), new_edges_IDs, new_faces_IDs (sons) 
     1 + 1 + [1] + 3..4 + 4 = 9..11
  */
  int* face;
  /* for each refined edge:
     edge_ID, new_node_ID, new_edges_IDs (sons) 
     1 + 1 + 2 = 4
  */
  int* edge;
} mmpt_ref_info;

typedef struct{
  int* face; /* list of deleted owned faces */
  int* edge; /* list of deleted owned edges */
} mmpt_del_info;

/* 
 * data structure to handle parallel adaptivity 
 */

/* structure with arrays of overlap entities' local and alien IDs */
/* (alien ID is an ID on another processor) */
/* for each processor, sharing entities with the given one, there is */
/* a separate set of lists (to speed up searching of lists, they should be */
/* stored in increasing order of local IDs !!!!!*/
typedef struct{
  int nr_elem_alien[MMPC_MAX_NUM_SUB];
  int nr_face_alien[MMPC_MAX_NUM_SUB];
  int nr_edge_alien[MMPC_MAX_NUM_SUB];
  int nr_vert_alien[MMPC_MAX_NUM_SUB];
  int nr_elem_ovl[MMPC_MAX_NUM_SUB];
  int* l_elem_ovl_loc[MMPC_MAX_NUM_SUB];
  int* l_elem_ovl_ali[MMPC_MAX_NUM_SUB];
  int nr_face_ovl[MMPC_MAX_NUM_SUB];
  int* l_face_ovl_loc[MMPC_MAX_NUM_SUB];
  int* l_face_ovl_ali[MMPC_MAX_NUM_SUB];
  int nr_edge_ovl[MMPC_MAX_NUM_SUB];
  int* l_edge_ovl_loc[MMPC_MAX_NUM_SUB];
  int* l_edge_ovl_ali[MMPC_MAX_NUM_SUB];
  int nr_vert_ovl[MMPC_MAX_NUM_SUB];
  int* l_vert_ovl_loc[MMPC_MAX_NUM_SUB];
  int* l_vert_ovl_ali[MMPC_MAX_NUM_SUB];
} mmpt_mesh_ovl;

/* structure with mesh data */
typedef struct {
  mmpt_nodes   *node;        /* pointer to array of nodes */
  mmpt_edges   *edge;        /* pointer to array of edges */
  mmpt_faces   *face;        /* pointer to array of faces */
  mmpt_elems   *elem;        /* pointer to array of elements */
  mmpt_ref_info *ref_loc;
  mmpt_ref_info *ref_ali;
  mmpt_del_info *del_loc;
  mmpt_mesh_ovl *mesh_ovls;
} mmpt_mesh;

/*** GLOBAL VARIABLES for the whole module ***/

extern int       mmpv_nr_meshes;   /* the number of meshes in the problem */
extern int       mmpv_cur_mesh_id;              /* ID of the current mesh */
extern mmpt_mesh  mmpv_meshes[MMC_MAX_NUM_MESH];        /* array of meshes */

extern int mmpv_nr_sub;
extern int mmpv_my_proc_id;

/*** LOCAL PROCEDURES  ***/

/**--------------------------------------------------------
  mmpr_select_mesh - to select the proper mesh   
---------------------------------------------------------*/
mmpt_mesh* mmpr_select_mesh( /* returns pointer to the chosen mesh */
			   /* to avoid errors if input is not valid */
			   /* it returns the pointer to the current mesh */
  int Mesh_id    /* in: mesh ID or 0 (MMC_CUR_MESH_ID) for the current mesh */
  );

#endif
