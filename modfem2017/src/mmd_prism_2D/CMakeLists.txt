set(mmd_prism_2D_srcdir "${CMAKE_SOURCE_DIR}/mmd_prism_2D")

# -- Include directories --
list(APPEND MMD_PRISM_2D_INCLUDE_DIRS
  ${mmd_prism_2D_srcdir}
)

if(MMD_PRISM_2D_INCLUDE_DIRS)
  set(MMD_PRISM_2D_INCLUDE_DIRS ${MMD_PRISM_2D_INCLUDE_DIRS} PARENT_SCOPE)
endif()

# -- Source files list --
collect_src_from_include_dirs(MMD_PRISM_2D_INCLUDE_DIRS)

# -- Target --
include_directories(${MMD_PRISM_2D_INCLUDE_DIRS} ${MMD_PRISM_2D_EXTERNAL_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

add_library(mml_prism_2D ${SOURCE_FILES})
target_link_libraries(mml_prism_2D ${MMD_PRISM_2D_EXTERNAL_LIBRARIES})
SET_TARGET_PROPERTIES(mml_prism_2D PROPERTIES COMPILE_DEFINITIONS ${MODFEM_MPI_CODE_DEFINE})
SET_TARGET_PROPERTIES(mml_prism_2D PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
SET_TARGET_PROPERTIES(mml_prism_2D PROPERTIES LINK_FLAGS "${LINK_FLAGS}")
