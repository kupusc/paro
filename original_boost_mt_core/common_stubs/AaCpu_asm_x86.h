/**
********************************************************************************
* @file                  $HeadURL$
* @version               $LastChangedRevision$
* @date                  $LastChangedDate$
* @author                $Author$
*
* @brief                 AaCpu service x86 architecture related asm macros
* @module                AaCpu 
* @owner                 Vladimir Cundekovic
*
* Copyright 2011 Nokia Siemens Networks. All rights reserved.
*******************************************************************************/

#ifndef _AACPU_ASM_X86_H
#define _AACPU_ASM_X86_H

/*----------------------- DOXYGEN GROUPS --------------------------------------*/

/*----------------------- INCLUDED FILES --------------------------------------*/

#include <IfAaCpu.h>
#include <IfAaCpuOptimization.h>

/* For aligment check */
#ifdef AACPU_ALIGMENT_CHECK_ENABLED
# include <inttypes.h>
# include <assert.h>
# ifndef AACPU_ADDRESS_ALIGMENT
#  define AACPU_ADDRESS_ALIGMENT 0x3
# endif
# ifndef AACPU_ASSERT
#  define AACPU_ASSERT assert
# endif
# define AACPU_DO_PTR_ALIGMENT_CHECK(__ptr) AACPU_ASSERT((((uintptr_t)(__ptr)) & AACPU_ADDRESS_ALIGMENT) == 0) 
#else
# define AACPU_DO_PTR_ALIGMENT_CHECK(__ptr)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------- PUBLIC DECLARATIONS --------------------------------*/

/* 
* In this file we provide optimized versions for following operations. 
* These defines ensures that unoptimized versions are not taken into use.
* If all necessary defines are not set for every implemented optimization,
* duplicated symbols would occur during linking.
*/
#define AACPU_ATOMIC_CMP_SWAP_32_OPTIMIZED /* AaCpuAtomicCmpSwap32 */
#define AACPU_SPINLOCK_TRY_LOCK_OPTIMIZED /* AaCpuSpinLockTryLock */
#define AACPU_SPINLOCK_UNLOCK_OPTIMIZED /* AaCpuSpinLockUnlock */
#define AACPU_ATOMIC_ADD_32_OPTIMIZED /* AaCpuAtomicAdd32 */
#define AACPU_ATOMIC_SWAP_32_OPTIMIZED /* AaCpuAtomicSwap32 */
#define AACPU_ATOMIC_CMP_SWAP_32_OPTIMIZED /* AaCpuAtomicCmpSwap32 */
#define AACPU_TIMEBASE_READ_OPTIMIZED /* AaCpuTimeBaseGet */
#define AACPU_BIT_SWAP_BYTE_ORDER_32_OPTIMIZED /* AaCpuBitSwapByteOrder32 */


#define i386_V 1

/* Select optimized implementation for specific CPU type */
#if AACPU_CPU_TYPE_VP==i386_V

/*-----------------------------------------------------------------------------
 * Description: tries to lock a spinlock
 *---------------------------------------------------------------------------*/
#ifdef __GNUC__
int AaCpuSpinLockTryLock(TAaCpuSpinLock* lock)
{
    volatile int oldValue = AACPU_SPINLOCK_LOCKED; /* We try to acquire the lock */

    AACPU_DO_PTR_ALIGMENT_CHECK(lock);

    __asm__ __volatile__(
        "xchg %0,%1" /* Use i386 Exchange data instruction to swap lock's value to oldValue atomically */
        : "=r" (oldValue), "+m" (lock->value) /* Use register for oldValue and direct memory address for lock->value output */
        : "r" (oldValue) /* Input is oldValue */ 
        : "memory"); /* Some updates to memory done by xchg so inform asm about it */

    /* If lock acquiring succeeded, old value should be unlocked (i.e. 1), otherwice
       someone is already owning the lock */
    return oldValue;

} /* AaCpuSpinLockTryLock */
#endif


/*-----------------------------------------------------------------------------
 * Description: releases spinlock
 *---------------------------------------------------------------------------*/
#ifdef __GNUC__
void AaCpuSpinLockUnlock(TAaCpuSpinLock* lock)
{
    volatile int oldValue = AACPU_SPINLOCK_UNLOCKED; /* We shall release the lock */

    AACPU_DO_PTR_ALIGMENT_CHECK(lock);

    __asm__ __volatile__(
        "xchg %0,%1" /* Use i386 Exchange data instruction to swap lock's value to oldValue atomically */
        : "=r" (oldValue), "+m" (lock->value) /* Use register for oldValue and direct memory address for lock->value output */
        : "r" (oldValue) /* Input is oldValue (might work also if =r is changed to +r in output operands and this is removed) */ 
        : "memory"); /* Some updates to memory done by xchg so inform asm about it */
       
} /* AaCpuSpinLockUnlock */
#endif

/*-----------------------------------------------------------------------------
 * Description: adds 32bit data atomically
 *---------------------------------------------------------------------------*/
#ifdef __GNUC__
i32 AaCpuAtomicAdd32(TAaCpuAtomic32* atomic, const i32 value)
{
    i32 i = value;
    
    AACPU_DO_PTR_ALIGMENT_CHECK(atomic);

     __asm__ __volatile__(
        "xaddl %0,%1" /* Use x86 exchange (x..) and add (..add..) to atomically add 32bit (..l) value */
        :"+r" (i), "+m" (atomic->data) /* out (i must be here too); + means R/W */
        : : "memory");                 /* scratch */

     return value + i;
} /* AaCpuAtomicAdd32 */
#endif

/*-----------------------------------------------------------------------------
 * Description: swaps 32bit data atomically
 *---------------------------------------------------------------------------*/
#ifdef __GNUC__
i32 AaCpuAtomicSwap32(TAaCpuAtomic32* atomic, i32 value)
{
    AACPU_DO_PTR_ALIGMENT_CHECK(atomic);

     __asm__ __volatile__(
        "xchgl %0,%1" /* Use x86 exchange word to atomically swap 32bit values */
        :"=r" (value) 
        :"m" (atomic->data), "0" (value) /* "0" means that 'value' stays in the same register (more efficient register usage) */
        :"memory");

     return value;
} /* AaCpuAtomicDec32 */
#endif

/*-----------------------------------------------------------------------------
 * Description: compares 32bit data to value and if equal swap atomically
 *---------------------------------------------------------------------------*/
#ifdef __GNUC__
i32 AaCpuAtomicCmpSwap32(TAaCpuAtomic32* atomic, i32 comp, i32 value)
{
    AACPU_DO_PTR_ALIGMENT_CHECK(atomic);
  
    __asm__ __volatile__(
        "lock cmpxchgl %0,%2" /* Swap value and atomic->data if comp equals to atomic->data */
        : "+r"(value), "+a"(comp) /* According to Intel's manual, comp value must be in EAX register i.e. "a" */
        : "m"(atomic->data)
        : "memory");

    return comp;
} /* AaCpuAtomicCmpSwap32 */
#endif

/*-----------------------------------------------------------------------------
 * Description: return current 64bit timebase
 *---------------------------------------------------------------------------*/
#ifdef __GNUC__
u64 AaCpuTimeBaseGet(void)
{
  unsigned long long ticks;
  unsigned long upper_32;
  unsigned long lower_32;

  __asm__ __volatile__ ("rdtsc" : "=a" (lower_32), "=d" (upper_32));

  ticks = upper_32;
  ticks = ticks << 32;
  ticks += lower_32;

  return ticks;
} /* AaCpuTimeBaseGet */
#endif

/*-----------------------------------------------------------------------------
 * Description: changes 32bit value in given address to reversed byte order
 *---------------------------------------------------------------------------*/
#ifdef __GNUC__
u32 AaCpuBitSwapByteOrder32(u32* valuePtr)
{
    const u32 temp = *valuePtr; /* Shall contain the original value */
    u32 swap = temp;

    AACPU_DO_PTR_ALIGMENT_CHECK(valuePtr);

    __asm__ (
"   bswap %0\n"       /* bswap accepts only register operands... */
"   mov %0, %1\n"     /* ...therefore we need additional move */ 
    : "+r" (swap), "=m" (*valuePtr) /* output */
    : "r" (swap)  /* input */
    );

    return temp;
} /* AaCpuBitSwapByteOrder32 */
#endif

#else /* AACPU_CPU_TYPE_VP == i386_V */
# error CPU type not defined or unsupported
#endif

/* CPU type independent implementations */


#ifdef __cplusplus
}
#endif

#endif /*  _AACPU_ASM_X86_H */


