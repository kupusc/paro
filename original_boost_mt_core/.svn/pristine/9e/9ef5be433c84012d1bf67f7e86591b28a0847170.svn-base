#ifndef _WORKAROUND_NON_LEAKING_OXF_ALLOCATOR_123B2625_F204_45D8_A846_59BB72B084C4_
#define _WORKAROUND_NON_LEAKING_OXF_ALLOCATOR_123B2625_F204_45D8_A846_59BB72B084C4_

#include <boost/thread.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <deque>

template<typename OMClass>
class WorkaroundNonLeakingOXFAllocator
{
public:
    static OMClass* allocate(int numOfInstances)
    {
        boost::interprocess::scoped_lock<boost::mutex> guard(instance.mAllocatedLock);

        instance.mAllocated.push_back(new char[sizeof(OMClass) * numOfInstances]);
        return reinterpret_cast<OMClass*>(instance.mAllocated.back());
    }

protected:
    ~WorkaroundNonLeakingOXFAllocator()
    {
        for(Allocated::const_iterator i = mAllocated.begin(); mAllocated.end() != i; ++i)
        {
            delete[] *i;
        }
    }

    typedef std::deque<char*> Allocated;
    Allocated mAllocated;
    boost::mutex mAllocatedLock;

    static WorkaroundNonLeakingOXFAllocator instance;

};

template<typename OMClass>
WorkaroundNonLeakingOXFAllocator<OMClass> WorkaroundNonLeakingOXFAllocator<OMClass>::instance;

#endif //_WORKAROUND_NON_LEAKING_OXF_ALLOCATOR_123B2625_F204_45D8_A846_59BB72B084C4_
