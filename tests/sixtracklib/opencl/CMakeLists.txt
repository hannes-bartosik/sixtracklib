# tests/sixtracklib/opencl/CMakeLists.txt

if( GTEST_FOUND )

    set(   C99_UNIT_TEST_TARGETS )
    set(   CXX_UNIT_TEST_TARGETS )

    set(   SIXTRACKL_TEST_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES}
         ${SIXTRACKL_GTEST_LIBRARIES} sixtrack_test sixtrack m dl )

    # ==========================================================================
    # test_context_setup_cxx:

    add_executable( test_context_setup_opencl_c99 test_context_setup_c99.cpp )
    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS}
         test_context_setup_opencl_c99 )
    add_test( C99_OpenCL_ContextSetupTests test_context_setup_opencl_c99 )

    # --------------------------------------------------------------------------
    # test_context_setup_cxx:

    add_executable( test_context_setup_opencl_cxx test_context_setup_cxx.cpp )
    set( CXX_UNIT_TEST_TARGETS ${CXX_UNIT_TEST_TARGETS}
         test_context_setup_opencl_cxx )
    add_test( CXX_OpenCL_ContextSetupTests test_context_setup_opencl_cxx )

    # ==========================================================================
    # test_context_opencl_c99:

    add_executable( test_context_opencl_c99 test_context_opencl_c99.cpp )
    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS} test_context_opencl_c99 )
    add_test( C99_OpenCL_ContextTests test_context_opencl_c99 )

    # --------------------------------------------------------------------------
    # test_context_opencl_cxx:

    add_executable( test_context_opencl_cxx test_context_opencl_cxx.cpp )
    set( CXX_UNIT_TEST_TARGETS ${CXX_UNIT_TEST_TARGETS} test_context_opencl_cxx )
    add_test( CXX_OpenCL_ContextTests test_context_opencl_cxx )

    # ==========================================================================
    # test_argument_update_region_opencl_c99:

    add_executable( test_argument_update_region_opencl_c99
                    test_argument_update_region_c99.cpp )

    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS}
         test_argument_update_region_opencl_c99 )

    add_test( C99_OpenCL_ClArgumentUpdateRegionTest
              test_argument_update_region_opencl_c99 )

    # --------------------------------------------------------------------------
    # test_argument_update_region_opencl_cxx:

    add_executable( test_argument_update_region_opencl_cxx
                    test_argument_update_region_cxx.cpp )

    set( CXX_UNIT_TEST_TARGETS ${CXX_UNIT_TEST_TARGETS}
         test_argument_update_region_opencl_cxx )

    add_test( CXX_OpenCL_ClArgumentUpdateRegionTest
              test_argument_update_region_opencl_cxx )

    # ==========================================================================
    # test_buffer_opencl_c99:

    add_executable( test_buffer_opencl_c99 test_buffer_opencl_c99.cpp )
    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS} test_buffer_opencl_c99 )
    add_test( C99_OpenCL_BufferTests test_buffer_opencl_c99 )

    # ==========================================================================
    # test_particles_opencl_c99:

    add_executable( test_particles_opencl_c99 test_particles_opencl_c99.cpp )
    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS} test_particles_opencl_c99 )
    add_test( C99_OpenCL_ParticleBufferTests test_particles_opencl_c99 )

    # ==========================================================================
    # test_be_drift_opencl_c99:

    add_executable( test_be_drift_opencl_c99 test_be_drift_opencl_c99.cpp )
    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS} test_be_drift_opencl_c99 )
    add_test( C99_OpenCL_BeamElementsDriftTests test_be_drift_opencl_c99 )

    # ==========================================================================
    # test_track_elem_by_elem_opencl_c99:

    add_executable( test_track_elem_by_elem_opencl_c99
                    test_track_elem_by_elem_opencl_c99.cpp )

    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS}
         test_track_elem_by_elem_opencl_c99 )

    add_test( C99_OpenCL_TrackElemByElemTests
              test_track_elem_by_elem_opencl_c99 )

    # ==========================================================================
    # test_be_monitor_opencl_c99:

    add_executable( test_be_monitor_opencl_c99 test_be_monitor_opencl_c99.cpp )
    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS} test_be_monitor_opencl_c99 )
    add_test( C99_OpenCL_BeamElementsMonitorTests test_be_monitor_opencl_c99 )

    # ==========================================================================
    # test_track_opencl_c99:

    add_executable( test_track_opencl_c99 test_track_opencl_c99.cpp )
    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS} test_track_opencl_c99 )
    add_test( C99_OpenCL_TrackParticlesTests test_track_opencl_c99 )

    # ==========================================================================
    # test_track_job_opencl_c99:

    add_executable( test_track_job_cl_opencl_c99
                    test_track_job_cl_opencl_c99.cpp )

    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS}
         test_track_job_cl_opencl_c99 )
    add_test( C99_OpenCL_TrackJobClTests test_track_job_cl_opencl_c99 )

    # --------------------------------------------------------------------------
    # test_track_job_opencl_cxx:

    add_executable( test_track_job_cl_opencl_cxx
                    test_track_job_cl_opencl_cxx.cpp )

    set( CXX_UNIT_TEST_TARGETS ${CXX_UNIT_TEST_TARGETS}
         test_track_job_cl_opencl_cxx )
    add_test( CXX_OpenCL_TrackJobClTests test_track_job_cl_opencl_cxx )

    # ==========================================================================
    # test_track_job_cl_collect_push_opencl_c99:

    add_executable( test_track_job_cl_collect_push_opencl_c99
                    test_track_job_cl_collect_push_c99.cpp )

    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS}
         test_track_job_cl_collect_push_opencl_c99 )

    add_test( C99_TrackJobClCollectPushTests
              test_track_job_cl_collect_push_opencl_c99 )

    set_property( TEST C99_TrackJobClCollectPushTests APPEND PROPERTY
        DEPENDS C99_OpenCL_TrackJobClTests )

    # --------------------------------------------------------------------------
    # test_track_job_cl_collect_push_opencl_cxx:

    add_executable( test_track_job_cl_collect_push_opencl_cxx
                    test_track_job_cl_collect_push_cxx.cpp )

    set( CXX_UNIT_TEST_TARGETS ${CXX_UNIT_TEST_TARGETS}
         test_track_job_cl_collect_push_opencl_cxx )

    add_test( CXX_TrackJobClCollectPushTests
              test_track_job_cl_collect_push_opencl_cxx )

    set_property( TEST CXX_TrackJobClCollectPushTests APPEND PROPERTY
        DEPENDS CXX_OpenCL_TrackJobClTests )

    # ==========================================================================
    # test_track_job_update_region_opencl_c99:

    add_executable( test_track_job_update_region_opencl_c99
                    test_track_job_update_region_c99.cpp )

    set( C99_UNIT_TEST_TARGETS ${C99_UNIT_TEST_TARGETS}
         test_track_job_update_region_opencl_c99 )

    add_test( C99_OpenCL_ClTrackJobUpdateBeamElementsRegionTest
              test_track_job_update_region_opencl_c99 )

    # --------------------------------------------------------------------------
    # test_track_job_update_region_opencl_cxx:

    add_executable( test_track_job_update_region_opencl_cxx
                    test_track_job_update_region_cxx.cpp )

    set( CXX_UNIT_TEST_TARGETS ${CXX_UNIT_TEST_TARGETS}
         test_track_job_update_region_opencl_cxx )

    add_test( CXX_OpenCL_ClTrackJobUpdateBeamElementsRegionTest
              test_track_job_update_region_opencl_cxx )

    # *************************************************************************
    # Set all properties:

    if( C99_UNIT_TEST_TARGETS )

        set_property( TARGET ${C99_UNIT_TEST_TARGETS}
                      PROPERTY LINK_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES} )

        set_property(
            TARGET ${C99_UNIT_TEST_TARGETS}
            APPEND PROPERTY INCLUDE_DIRECTORIES
            "${CMAKE_SOURCE_DIR}"
            "${CMAKE_SOURCE_DIR}/tests"
            $<BUILD_INTERFACE:${SIXTRACKL_GTEST_INCLUDE_DIRS}>
        )

        set_property( TARGET ${C99_UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD 11 )
        set_property( TARGET ${C99_UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD_REQUIRED ON )
        set_property( TARGET ${C99_UNIT_TEST_TARGETS} PROPERTY COMPILE_OPTIONS
                      ${SIXTRACKLIB_CPU_FLAGS} -Wall -Werror -pedantic )
    endif()

    if( CXX_UNIT_TEST_TARGETS )

        set_property( TARGET ${CXX_UNIT_TEST_TARGETS}
                      PROPERTY LINK_LIBRARIES ${SIXTRACKL_TEST_LIBRARIES} )

        set_property(
            TARGET ${CXX_UNIT_TEST_TARGETS}
            APPEND PROPERTY INCLUDE_DIRECTORIES
            "${CMAKE_SOURCE_DIR}"
            "${CMAKE_SOURCE_DIR}/tests"
            $<BUILD_INTERFACE:${SIXTRACKL_GTEST_INCLUDE_DIRS}>
        )

        set_property( TARGET ${CXX_UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD 11 )
        set_property( TARGET ${CXX_UNIT_TEST_TARGETS} PROPERTY CXX_STANDARD_REQUIRED ON )
        set_property( TARGET ${CXX_UNIT_TEST_TARGETS} PROPERTY COMPILE_OPTIONS
                      ${SIXTRACKLIB_CPU_FLAGS} -Wall -Werror -pedantic )
    endif()

endif()
