#include "sixtracklib/testlib/common/patricles/particles_addr.hpp"
#include "sixtracklib/testlib/common/patricles/particles_addr.h"

#include <cstddef>
#include <cstdlib>
#include <random>

#include "sixtracklib/testlib/common/generic_obj.h"

#include "sixtracklib/common/definitions.h"
#include "sixtracklib/common/control/definitions.h"
#include "sixtracklib/common/buffer.h"
#include "sixtracklib/common/buffer.hpp"
#include "sixtracklib/common/particles.h"
#include "sixtracklib/common/particles/particles_addr.h"

#include "sixtracklib/common/control/controller_base.hpp"
#include "sixtracklib/common/control/controller_base.h"
#include "sixtracklib/common/control/argument_base.hpp"
#include "sixtracklib/common/control/argument_base.h"

namespace st = SIXTRL_CXX_NAMESPACE;

namespace SIXTRL_CXX_NAMESPACE
{
    namespace tests
    {
        /* ----------------------------------------------------------------- */

        st::arch_status_t TestParticlesAddr_prepare_buffers(
            st::Buffer& SIXTRL_RESTRICT_REF paddr_buffer,
            st::Buffer& SIXTRL_RESTRICT_REF particles_buffer,
            st::buffer_size_t const num_elements,
            st::buffer_size_t const min_num_particles,
            st::buffer_size_t const max_num_particles,
            double const probablity_for_non_particles,
            st::buffer_size_t const initial_seed_value =
                st::buffer_size_t{ 20190517u } )
        {
            return st::tests::TestParticlesAddr_prepare_buffers(
                paddr_buffer.getCApiPtr(), particles_buffer.getCApiPtr(),
                    num_elements, min_num_particles, max_num_particles,
                        probablity_for_non_particles, initial_seed_value );
        }

        st::arch_status_t TestParticlesAddr_verify_structure(
            st::Buffer const& SIXTRL_RESTRICT_REF paddr_buffer,
            st::Buffer const& SIXTRL_RESTRICT_REF particles_buffer )
        {
            return st::tests::TestParticlesAddr_verify_structure(
                paddr_buffer.getCApiPtr(), particles_buffer.getCApiPtr() );
        }

        st::arch_status_t TestParticlesAddr_verify_addresses(
            st::Buffer const& SIXTRL_RESTRICT_REF paddr_buffer,
            st::Buffer const& SIXTRL_RESTRICT_REF particles_buffer )
        {
            return st::tests::TestParticlesAddr_verify_addresses(
                paddr_buffer.getCApiPtr(), particles_buffer.getCApiPtr() );
        }

        /* ----------------------------------------------------------------- */

        bool TestParticlesAddr_prepare_ctrl_args_test(
            st::ControllerBase* SIXTRL_RESTRICT ctrl,
            st::ArgumentBase* SIXTRL_RESTRICT paddr_arg,
            st::Buffer& SIXTRL_RESTRICT_REF paddr_buffer,
            st::ArgumentBase* SIXTRL_RESTRICT particles_arg,
            st::Buffer& SIXTRL_RESTRICT_REF particles_buffer,
            st::ArgumentBase* SIXTRL_RESTRICT result_arg )
        {
            return ::NS(TestParticlesAddr_prepare_ctrl_args_test)(
                ctrl, paddr_arg, paddr_buffer.getCApiPtr(), particles_arg,
                    particles_buffer.getCApiPtr(), result_arg );
        }
        
        bool TestParticlesAddr_evaluate_ctrl_args_test(
            st::ControllerBase* SIXTRL_RESTRICT ctrl,
            st::ArgumentBase* SIXTRL_RESTRICT paddr_arg,
            st::Buffer& SIXTRL_RESTRICT_REF paddr_buffer,
            st::ArgumentBase* SIXTRL_RESTRICT particles_arg,
            st::Buffer& SIXTRL_RESTRICT_REF particles_buffer,
            st::ArgumentBase* SIXTRL_RESTRICT result_arg )
        {
            return ::NS(TestParticlesAddr_evaluate_ctrl_args_test)(
                ctrl, paddr_arg, paddr_buffer.getCApiPtr(), particles_arg,
                    particles_buffer.getCApiPtr(), result_arg );
        }
    }
}

::NS(arch_status_t) TestParticlesAddr_prepare_buffers(
    ::NS(Buffer)* SIXTRL_RESTRICT paddr_buffer,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(buffer_size_t) const num_elements,
    ::NS(buffer_size_t) const min_num_particles,
    ::NS(buffer_size_t) const max_num_particles,
    double const probablity_for_non_particles,
    ::NS(buffer_size_t) const initial_seed_value )
{
    using size_t = ::NS(buffer_size_t);
    using rand_t = std::mt19937_64;
    using seed_t = rand_t::result_type;
    using particles_t = ::NS(Particles);
    using type_id_t   = ::NS(object_type_id_t);
    using gen_obj_t   = ::NS(GenericObj);

    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    if( ( particles_buffer != nullptr ) &&
        ( num_elements > size_t{ 0 } ) &&
        ( min_num_particles <= max_num_particles ) &&
        ( max_num_particles > size_t{ 0 } ) &&
        ( probablity_for_non_particles >= double{ 0 } ) &&
        ( probablity_for_non_particles <= double{ 1 } ) )
    {
        ::NS(Buffer_clear)( particles_buffer, false );
        ::NS(Buffer_reset)( particles_buffer );

        /* Provide a seed to get some variation of the results */

        seed_t const init_value =
            static_cast< seed_t >( initial_seed_value );

        std::uniform_int_distribution< size_t >
            num_particles_dist( min_num_particles, max_num_particles );

        std::uniform_real_distribution< double >
            not_a_particles_obj_dist( double{ 0.0 }, double{ 1.0 } );

        rand_t prng( init_value );

        status = st::ARCH_STATUS_SUCCESS;

        type_id_t const generic_obj_type =
            ::NS(OBJECT_TYPE_LAST_AVAILABLE);

        size_t const num_d_values = size_t{ 10 };
        size_t const num_e_values = size_t{ 5 };

        for( size_t ii = size_t{ 0 } ; ii < num_elements ; ++ii )
        {
            double const chance_particles =
                not_a_particles_obj_dist( prng );

            if( chance_particles > probablity_for_non_particles )
            {
                size_t const num_particles = num_particles_dist( prng );
                particles_t* p = ::NS(Particles_new)(
                    particles_buffer, num_particles );

                if( ( p == nullptr ) || ( num_particles == size_t{ 0 } ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
            else
            {
                gen_obj_t* gen_obj = ::NS(GenericObj_new)( particles_buffer,
                    generic_obj_type, num_d_values, num_e_values );

                if( gen_obj == nullptr )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }

        if( ( ::NS(Buffer_get_num_of_objects)( particles_buffer ) ==
              num_elements ) && ( status == st::ARCH_STATUS_SUCCESS ) )
        {
            status = ::NS(ParticlesAddr_prepare_buffer_based_on_particles_buffer)(
                paddr_buffer, particles_buffer );
        }
    }

    return status;
}

::NS(arch_status_t) TestParticlesAddr_verify_structure(
    const ::NS(Buffer) *const SIXTRL_RESTRICT paddr_buffer,
    const ::NS(Buffer) *const SIXTRL_RESTRICT particles_buffer )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    using size_t      = ::NS(buffer_size_t);
    using particles_t = ::NS(Particles);
    using paddr_t     = ::NS(ParticlesAddr);
    using type_id_t   = ::NS(object_type_id_t);
    using gen_obj_t   = ::NS(GenericObj);
    using object_t    = ::NS(Object);

    if( ( particles_buffer != nullptr ) &&
        ( !::NS(Buffer_needs_remapping)( particles_buffer ) ) )
    {
        size_t const num_elements =
            ::NS(Buffer_get_num_of_objects)( particles_buffer );

        if( ( num_elements == size_t{ 0 } ) || ( num_elements !=
            ::NS(Buffer_get_num_of_objects)( paddr_buffer ) ) )
        {
            return status;
        }

        status = st::ARCH_STATUS_SUCCESS;

        for( size_t ii = size_t{ 0 } ; ii < num_elements ; ++ii )
        {
            paddr_t const* paddr =
            ::NS(ParticlesAddr_buffer_get_const_particle_addr)(
                paddr_buffer, ii );

            if( paddr == nullptr )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            particles_t const* p = ::NS(Particles_buffer_get_const_particles)(
                particles_buffer, ii );

            if( p != nullptr )
            {
                if( ::NS(Particles_get_num_of_particles)( p ) !=
                        paddr->num_particles )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

            }
            else
            {
                object_t const* obj =
                    ::NS(Buffer_get_const_object)( particles_buffer, ii );

                if( ( paddr->num_particles != size_t{ 0 } ) ||
                    ( obj == nullptr ) || ( ::NS(Object_get_type_id)( obj ) !=
                      ::NS(OBJECT_TYPE_LAST_AVAILABLE) ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }
    }

    return status;
}

::NS(arch_status_t) NS(TestParticlesAddr_verify_addresses)(
    const ::NS(Buffer) *const SIXTRL_RESTRICT paddr_buffer,
    const ::NS(Buffer) *const SIXTRL_RESTRICT particles_buffer )
{
    ::NS(arch_status_t) status = st::ARCH_STATUS_GENERAL_FAILURE;

    using size_t      = ::NS(buffer_size_t);
    using particles_t = ::NS(Particles);
    using paddr_t     = ::NS(ParticlesAddr);
    using type_id_t   = ::NS(object_type_id_t);
    using gen_obj_t   = ::NS(GenericObj);
    using object_t    = ::NS(Object);

    if( ( particles_buffer != nullptr ) &&
        ( !::NS(Buffer_needs_remapping)( particles_buffer ) ) )
    {
        size_t const num_elements =
            ::NS(Buffer_get_num_of_objects)( particles_buffer );

        if( ( num_elements == size_t{ 0 } ) ||
            ( ::NS(Buffer_get_num_of_objects)( paddr_buffer ) !=
                num_elements ) )
        {
            return status;
        }

        status = st::ARCH_STATUS_SUCCESS;

        for( size_t ii = size_t{ 0 } ; ii < num_elements ; ++ii )
        {
            paddr_t const* paddr =
            ::NS(ParticlesAddr_buffer_get_const_particle_addr)(
                paddr_buffer, ii );

            if( paddr == nullptr )
            {
                status = st::ARCH_STATUS_GENERAL_FAILURE;
                break;
            }

            particles_t const* p = ::NS(Particles_buffer_get_const_particles)(
                particles_buffer, ii );

            if( p != nullptr )
            {
                if( ::NS(Particles_get_num_of_particles)( p ) !=
                    paddr->num_particles )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

                paddr_t cmp_paddr;

                ::NS(ParticlesAddr_preset)( &cmp_paddr );
                ::NS(ParticlesAddr_assign_from_particles)( &cmp_paddr, p );

                if( 0 != ::NS(ParticlesAddr_compare_values)(
                    paddr, &cmp_paddr ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }

            }
            else
            {
                object_t const* obj =
                    ::NS(Buffer_get_const_object)( particles_buffer, ii );

                if( ( paddr->num_particles != size_t{ 0 } ) ||
                    ( obj == nullptr ) ||
                    ( ::NS(Object_get_type_id)( obj ) !=
                      ::NS(OBJECT_TYPE_LAST_AVAILABLE) ) )
                {
                    status = st::ARCH_STATUS_GENERAL_FAILURE;
                    break;
                }
            }
        }
    }

    return status;
}

/* ----------------------------------------------------------------- */

bool NS(TestParticlesAddr_evaluate_ctrl_args_test)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT paddr_arg,
    ::NS(Buffer)* SIXTRL_RESTRICT paddr_buffer,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT particles_arg,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT result_arg )
{
    typedef result_reg_t = ::NS(arch_debugging_t);
    
    bool success = false;
    
    result_reg_t result_register = ::NS(ARCH_DEBUGGING_GENERAL_FAILURE);
    
    ::NS(arch_status_t) status = 
        ::NS(ParticlesAddr_prepare_buffer_based_on_particles_buffer)(
            paddr_buffer, particles_buffer );
        
    if( status != st::ARCH_STATUS_SUCCESS ) return success;
    
    status = ::NS(Argument_send_buffer)( particles_arg, particles_buffer );
    if( status != ::NS(ARCH_STATUS_SUCCESS) ) return success;

    status = ::NS(Argument_send_buffer)( addresses_arg, paddr_buffer );
    if( status != ::NS(ARCH_STATUS_SUCCESS) ) return success;
    
    status = ::NS(Argument_send_raw_argument)( 
        result_arg, &result_register, sizeof( result_register ) );
    
    success = ( status == ::NS(ARCH_STATUS_SUCCESS );
    
    return success;
}


bool NS(TestParticlesAddr_evaluate_ctrl_args_test)(
    ::NS(ControllerBase)* SIXTRL_RESTRICT ctrl,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT paddr_arg,
    ::NS(Buffer)* SIXTRL_RESTRICT paddr_buffer,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT particles_arg,
    ::NS(Buffer)* SIXTRL_RESTRICT particles_buffer,
    ::NS(ArgumentBase)* SIXTRL_RESTRICT result_arg )
{
    typedef buf_size_t   = ::NS(buffer_size_t);
    typedef status_t     = ::NS(arch_status_t);
    typedef result_reg_t = ::NS(arch_debugging_t);
    typedef address_t    = ::NS(buffer_addr_t);
    typedef addr_diff_t  = ::NS(buffer_addr_diff_t);

    bool success = false;

    if( ( ctrl != nullptr ) &&
        ( paddr_arg != nullptr ) && ( paddr_buffer != nullptr ) &&
        ( particles_arg != nullptr ) && ( particles_buffer != nullptr ) &&
        ( result_arg != nullptr ) )
    {
        buf_size_t const res_size = sizeof( result_reg_t );

        buf_size_t const slot_size =
            ::NS(Buffer_get_slot_size)( particles_buffer );

        SIXTRL_ASSERT( ::NS(Buffer_get_slot_size)( paddr_buffer ) ==
            slot_size );

        ::NS(Buffer_clear)( paddr_buffer, true );
        ::NS(Buffer_reset)( paddr_buffer );

        SIXTRL_ASSERT( ::NS(Buffer_get_num_of_objects)( paddr_buffer ) == 0u );

        status_t status = ::NS(Argument_receive_buffer)( paddr_buffer );
        result_reg_t result_register = ::NS(ARCH_DEBUGGING_GENERAL_FAILURE);

        if( ( status != ::NS(ARCH_STATUS_SUCCESS ) ) ||
            ( ::NS(Buffer_needs_remapping)( paddr_buffer ) ) )
        {
            return success;
        }

        status = ::NS(Argument_receive_raw_arg)( &result_register, res_size );

        if( ( status != :NS(ARCH_STATUS_SUCCESS) ) ||
            ( result_register != ::NS(ARCH_DEBUGGING_REGISTER_EMPTY) ) )
        {
            success = false;
        }

        if( ::NS(TestParticlesAddr_verify_structure)( paddr_buffer,
           particles_buffer ) != ::NS(ARCH_STATUS_SUCCESS) );

        status = ::NS(Argument_receive_buffer_without_remap)(
            particles_arg, particles_buffer );

        if( status != st::ARCH_STATUS_SUCCESS ) return success;

        SIXTRL_ASSERT( ::NS(Buffer_needs_remapping)( particles_buffer ) );

        address_t const remote_addr = ::NS(ManagdBuffer_get_stored_begin_addr)(
            ::NS(Buffer_get_data_begin)( particles_buffer ), slot_size );

        address_t const host_addr = ::NS(ManagdBuffer_get_buffer_begin_addr)(
            ::NS(Buffer_get_data_begin)( particles_buffer ), slot_size );

        SIXTRL_ASSERT( ( stored_addr != ( address_t )0u ) &&
                       ( begin_addr  != ( address_t )0u ) &&
                       ( stored_addr != begin_addr ) );

        /* remote_addr + addr_offset = host_addr ->
         * addr_offset = host_addr - remote_addr */

        addr_diff_t const addr_offset = host_addr - remote_addr;

        ::NS(Buffer_remap)( particles_buffer );

        ::NS(ParticlesAddr_buffer_all_remap_adresses)(
            paddr_buffer, addr_offset );

        status = ::NS(TestParticlesAddr_verify_addresses)(
            paddr_buffer, particles_buffer );

        success = ( status == st::ARCH_STATUS_SUCCESS );
    }

    return success;
}

/* end: tests/sixtracklib/testlib/common/particles/particles_addr.cpp */
