# -- Add target to global list --
list(APPEND MOD_FEM_EXEC_LIST "CREATE_MOD_FEM_FORMING_PRISM_STD")
list(APPEND MOD_FEM_EXEC_LIST "CREATE_MOD_FEM_FORMING_HYBRID_STD")
list(APPEND MOD_FEM_EXEC_LIST "CREATE_MOD_FEM_FORMING_REMESH_STD") 
list(APPEND MOD_FEM_EXEC_LIST "CREATE_MOD_FEM_FORMING_PRISM2D_STD")
list(APPEND MOD_FEM_EXEC_LIST "CREATE_MOD_FEM_FORMING_PRISM_STD_QUAD")
list(APPEND MOD_FEM_EXEC_LIST "CREATE_MOD_FEM_FORMING_HYBRID_STD_QUAD")
list(APPEND MOD_FEM_EXEC_LIST "CREATE_MOD_FEM_FORMING_REMESH_STD_QUAD") 
list(APPEND MOD_FEM_EXEC_LIST "CREATE_MOD_FEM_FORMING_PRISM2D_STD_QUAD")


set(MOD_FEM_EXEC_LIST "${MOD_FEM_EXEC_LIST}" PARENT_SCOPE)

# -- Exec files --
set(pdd_forming_srcdir "${CMAKE_SOURCE_DIR}/pdd_forming")
set(PDD_FORMING_PRISM_STD_EXE "MOD_FEM_forming_prism_std")
set(PDD_FORMING_HYBRID_STD_EXE "MOD_FEM_forming_hybrid_std")
set(PDD_FORMING_PRISM2D_STD_EXE "MOD_FEM_forming_prism2d_std")
set(PDD_FORMING_REMESH_STD_EXE "MOD_FEM_forming_remesh_std")
set(PDD_FORMING_PRISM_STD_QUAD_EXE "MOD_FEM_forming_prism_std_quad")
set(PDD_FORMING_HYBRID_STD_QUAD_EXE "MOD_FEM_forming_hybrid_std_quad")
set(PDD_FORMING_PRISM2D_STD_QUAD_EXE "MOD_FEM_forming_prism2d_std_quad")
set(PDD_FORMING_REMESH_STD_QUAD_EXE "MOD_FEM_forming_remesh_std_quad")

# -- Include directories --
list(APPEND PDD_FORMING_INCLUDE_DIRS
  ${pdd_forming_srcdir}/adaptation
  ${pdd_forming_srcdir}/input_output
  ${pdd_forming_srcdir}/materials
  ${pdd_forming_srcdir}/linear_solver_interface
  ${pdd_forming_srcdir}/main
  ${pdd_forming_srcdir}/include
  ${pdd_forming_srcdir}/time_integration
  ${pdd_forming_srcdir}/weak_formulation
  ${pdd_forming_srcdir}
)
if(PDD_FORMING_INCLUDE_DIRS)
  set(PDD_FORMING_INCLUDE_DIRS ${PDD_FORMING_INCLUDE_DIRS} PARENT_SCOPE)
endif()
# -- Source files list --
collect_src_from_include_dirs(PDD_FORMING_INCLUDE_DIRS)

# -- Target --
include_directories(${PDD_FORMING_INCLUDE_DIRS} ${PDD_FORMING_EXTERNAL_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

if(CREATE_MOD_FEM_FORMING_PRISM_STD)
  if(NOT ${MODFEM_ACCEL} STREQUAL "opencl")
    add_executable(${PDD_FORMING_PRISM_STD_EXE} ${SOURCE_FILES})
    #target_link_libraries(${PDD_FORMING_PRISM_STD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_prism apl_std_lin utl_system utl_util tml_omp ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD})
    target_link_libraries(${PDD_FORMING_PRISM_STD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_prism apl_std_lin utl_system utl_util ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD})
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM_STD_EXE} PROPERTIES COMPILE_DEFINITIONS ${MODFEM_MPI_CODE_DEFINE} RELEASE_POSTFIX "${RELEASE_POSTFIX}" DEBUG_POSTFIX "${DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM_STD_EXE} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM_STD_EXE} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")
  else()
    message(WARNING "OpenCL for PDD_FORMING_PRISM_STD not implemented yet!!!")
  endif()
endif()

if(CREATE_MOD_FEM_FORMING_PRISM_STD_QUAD)
  if(NOT ${MODFEM_ACCEL} STREQUAL "opencl")
    add_executable(${PDD_FORMING_PRISM_STD_QUAD_EXE} ${SOURCE_FILES})
    #target_link_libraries(${PDD_FORMING_PRISM_STD_QUAD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_prism apl_std_lin utl_system utl_util tml_omp ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD})
    target_link_libraries(${PDD_FORMING_PRISM_STD_QUAD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_prism apl_std_quad utl_system utl_util ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD})
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM_STD_QUAD_EXE} PROPERTIES COMPILE_DEFINITIONS ${MODFEM_MPI_CODE_DEFINE} RELEASE_POSTFIX "${RELEASE_POSTFIX}" DEBUG_POSTFIX "${DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM_STD_QUAD_EXE} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM_STD_QUAD_EXE} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")
  else()
    message(WARNING "OpenCL for PDD_FORMING_PRISM_STD_QUAD not implemented yet!!!")
  endif()
endif()

if(CREATE_MOD_FEM_FORMING_HYBRID_STD)
  if(NOT ${MODFEM_ACCEL} STREQUAL "opencl")
    add_executable(${PDD_FORMING_HYBRID_STD_EXE} ${SOURCE_FILES})
    target_link_libraries(${PDD_FORMING_HYBRID_STD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_t4_prism apl_std_lin utl_system utl_util ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD} )
    target_link_libraries(${PDD_FORMING_HYBRID_STD_EXE} ${MODFEM_USER_LIBS})
    target_link_libraries(${PDD_FORMING_HYBRID_STD_EXE} ${MODFEM_USER_LIBS})
    SET_TARGET_PROPERTIES(${PDD_FORMING_HYBRID_STD_EXE} PROPERTIES COMPILE_DEFINITIONS ${MODFEM_MPI_CODE_DEFINE} RELEASE_POSTFIX "${RELEASE_POSTFIX}" DEBUG_POSTFIX "${DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_HYBRID_STD_EXE} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")  
    SET_TARGET_PROPERTIES(${PDD_FORMING_HYBRID_STD_EXE} PROPERTIES LINK_FLAGS "${LINK_FLAGS}" )
    #message("${PDD_FORMING_HYBRID_STD_EXE} LINK_FLAGS ARE: ${LINK_FLAGS}")
    #message("${PDD_FORMING_HYBRID_STD_EXE} COMPILE_DEFINITIONS ARE: ${MODFEM_MPI_CODE_DEFINE}")
    #message("${PDD_FORMING_HYBRID_STD_EXE} COMPILE_FLAGS ARE: ${COMPILE_FLAGS}")
  else()
    message(WARNING "OpenCL for PDD_FORMING_HYBRID_STD not implemented yet!!!")
  endif()
endif()

if(CREATE_MOD_FEM_FORMING_HYBRID_STD_QUAD)
  if(NOT ${MODFEM_ACCEL} STREQUAL "opencl")
    add_executable(${PDD_FORMING_HYBRID_STD_QUAD_EXE} ${SOURCE_FILES})
    target_link_libraries(${PDD_FORMING_HYBRID_STD_QUAD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_t4_prism apl_std_quad utl_system utl_util ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD} )
    target_link_libraries(${PDD_FORMING_HYBRID_STD_QUAD_EXE} ${MODFEM_USER_LIBS})
    target_link_libraries(${PDD_FORMING_HYBRID_STD_QUAD_EXE} ${MODFEM_USER_LIBS})
    SET_TARGET_PROPERTIES(${PDD_FORMING_HYBRID_STD_QUAD_EXE} PROPERTIES COMPILE_DEFINITIONS ${MODFEM_MPI_CODE_DEFINE} RELEASE_POSTFIX "${RELEASE_POSTFIX}" DEBUG_POSTFIX "${DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_HYBRID_STD_QUAD_EXE} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")  
    SET_TARGET_PROPERTIES(${PDD_FORMING_HYBRID_STD_QUAD_EXE} PROPERTIES LINK_FLAGS "${LINK_FLAGS}" )
    #message("${PDD_FORMING_HYBRID_STD_QUAD_EXE} LINK_FLAGS ARE: ${LINK_FLAGS}")
    #message("${PDD_FORMING_HYBRID_STD_QUAD_EXE} COMPILE_DEFINITIONS ARE: ${MODFEM_MPI_CODE_DEFINE}")
    #message("${PDD_FORMING_HYBRID_STD_QUAD_EXE} COMPILE_FLAGS ARE: ${COMPILE_FLAGS}")
  else()
    message(WARNING "OpenCL for PDD_FORMING_HYBRID_STD_QUAD not implemented yet!!!")
  endif()
endif()

if(CREATE_MOD_FEM_FORMING_REMESH_STD)
  if(NOT ${MODFEM_ACCEL} STREQUAL "opencl")
    add_executable(${PDD_FORMING_REMESH_STD_EXE} ${SOURCE_FILES})
    target_link_libraries(${PDD_FORMING_REMESH_STD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_remesh apl_std_lin utl_system utl_util ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD})
    SET_TARGET_PROPERTIES(${PDD_FORMING_REMESH_STD_EXE} PROPERTIES COMPILE_DEFINITIONS ${MODFEM_MPI_CODE_DEFINE} RELEASE_POSTFIX "${RELEASE_POSTFIX}" DEBUG_POSTFIX "${DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_REMESH_STD_EXE} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_REMESH_STD_EXE} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")
  else()
    message(WARNING "OpenCL for PDD_FORMING_REMESH_STD not implemented yet!!!")
  endif()
endif()

if(CREATE_MOD_FEM_FORMING_REMESH_STD_QUAD)
  if(NOT ${MODFEM_ACCEL} STREQUAL "opencl")
    add_executable(${PDD_FORMING_REMESH_STD_QUAD_EXE} ${SOURCE_FILES})
    target_link_libraries(${PDD_FORMING_REMESH_STD_QUAD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_remesh apl_std_quad utl_system utl_util ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD})
    SET_TARGET_PROPERTIES(${PDD_FORMING_REMESH_STD_QUAD_EXE} PROPERTIES COMPILE_DEFINITIONS ${MODFEM_MPI_CODE_DEFINE} RELEASE_POSTFIX "${RELEASE_POSTFIX}" DEBUG_POSTFIX "${DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_REMESH_STD_QUAD_EXE} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_REMESH_STD_QUAD_EXE} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")
  else()
    message(WARNING "OpenCL for PDD_FORMING_REMESH_STD_QUAD not implemented yet!!!")
  endif()
endif()


if(CREATE_MOD_FEM_FORMING_PRISM2D_STD)
  if(NOT ${MODFEM_ACCEL} STREQUAL "opencl")
    add_executable(${PDD_FORMING_PRISM2D_STD_EXE} ${SOURCE_FILES})
    target_link_libraries(${PDD_FORMING_PRISM2D_STD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_prism_2D apl_std_lin utl_system utl_util ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD})
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM2D_STD_EXE} PROPERTIES COMPILE_DEFINITIONS ${MODFEM_MPI_CODE_DEFINE} RELEASE_POSTFIX "${RELEASE_POSTFIX}" DEBUG_POSTFIX "${DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM2D_STD_EXE} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM2D_STD_EXE} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")
  else()
    message(WARNING "OpenCL for PDD_FORMING_PRISM2D_STD not implemented yet!!!")
  endif()
endif()

if(CREATE_MOD_FEM_FORMING_PRISM2D_STD_QUAD)
  if(NOT ${MODFEM_ACCEL} STREQUAL "opencl")
    add_executable(${PDD_FORMING_PRISM2D_STD_QUAD_EXE} ${SOURCE_FILES})
    target_link_libraries(${PDD_FORMING_PRISM2D_STD_QUAD_EXE} ${PDD_FORMING_EXTERNAL_LIBRARIES} mml_prism_2D apl_std_quad utl_system utl_util ${MODFEM_DIRECT_SOLVER_MODULE} ${MODFEM_ITER_SOLVER_MODULE} ${MODFEM_MPI_LIBS_STD})
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM2D_STD_QUAD_EXE} PROPERTIES COMPILE_DEFINITIONS ${MODFEM_MPI_CODE_DEFINE} RELEASE_POSTFIX "${RELEASE_POSTFIX}" DEBUG_POSTFIX "${DEBUG_POSTFIX}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM2D_STD_QUAD_EXE} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
    SET_TARGET_PROPERTIES(${PDD_FORMING_PRISM2D_STD_QUAD_EXE} PROPERTIES LINK_FLAGS "${LINK_FLAGS}")
  else()
    message(WARNING "OpenCL for PDD_FORMING_PRISM2D_STD_QUAD not implemented yet!!!")
  endif()
endif()


##############################################################################################################
enable_testing ()

foreach(folder ${MKL_INCLUDE_DIRS})
    set(KKK "${KKK}${folder}:")
endforeach()

foreach(folder ${MKL_LIBRARY_DIRS})
    set(KKK "${KKK}${folder}:")
endforeach()

set(KKK "${KKK}.")



set(CTEST_BUILD_DIR $ENV{PWD})
set(CTEST_DIR ${CMAKE_SOURCE_DIR}/../ctest)


add_test (forming_Make ${CTEST_DIR}/build.sh ${CTEST_BUILD_DIR}/pdd_forming/ ${ENV_PLATFORM} ${KKK})

set (passRegex "^Test passed")
set (failRegex "Fail")


