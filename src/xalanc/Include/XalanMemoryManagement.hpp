/*
 * Copyright 1999-2004 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#if !defined(XALANMEMORYMANAGEMENT_HEADER_GUARD_1357924680)
#define XALANMEMORYMANAGEMENT_HEADER_GUARD_1357924680


// Base include file.  Must be first.
#include <new>


#include <xalanc/Include/PlatformDefinitions.hpp>



#include <xercesc/framework/MemoryManager.hpp>




XALAN_CPP_NAMESPACE_BEGIN

typedef XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager		MemoryManagerType;



class XALAN_PLATFORM_EXPORT XalanMemMgrs
{
public:
	
	static MemoryManagerType&
	getDummyMemMgr();
	
	
	static MemoryManagerType&
	getDefaultXercesMemMgr();
};




#if defined (XALAN_DEVELOPMENT)
#define XALAN_DEFAULT_CONSTRACTOR_MEMORY_MGR
#define XALAN_DEFAULT_MEMMGR = XalanMemMgrs::getDummyMemMgr()
#else
#define XALAN_DEFAULT_CONSTRACTOR_MEMORY_MGR = XalanMemMgrs::getDefaultXercesMemMgr()
#define XALAN_DEFAULT_MEMMGR = XalanMemMgrs::getDefaultXercesMemMgr()
#endif



template <class C>
class ConstructValueWithNoMemoryManager 
{ 
public:
    ConstructValueWithNoMemoryManager(MemoryManagerType& /*mgr*/) 
    {
    }

    C value;

};

template <class C>
struct ConstructValueWithMemoryManager
{   
    ConstructValueWithMemoryManager(MemoryManagerType& mgr) :
        value(mgr)
    {
    }

    C value;
};

template <class C>
struct ConstructWithNoMemoryManager
{
    typedef ConstructValueWithNoMemoryManager<C>   ConstructableType;

    static C* construct(C* address, MemoryManagerType& /* mgr */)
    {
        return (C*) new (address) C;
    }

    static C* construct(C* address, const C& theRhs, MemoryManagerType& /* mgr */)
    {
        return (C*) new (address) C(theRhs);
    }
};

template <class C>
struct ConstructWithMemoryManager
{
    typedef ConstructValueWithMemoryManager<C>    ConstructableType;

    static C* construct(C* address, MemoryManagerType& mgr)
    {
        return (C*) new (address) C(mgr);
    }

    static C* construct(C* address, const C& theRhs, MemoryManagerType& mgr)
    {
        return (C*) new (address) C(theRhs, mgr);
    }
};

template <class C>
struct MemoryManagedConstructionTraits
{
    typedef ConstructWithNoMemoryManager<C> Constructor;

};

#define  XALAN_USES_MEMORY_MANAGER(Type)  \
template<> \
struct MemoryManagedConstructionTraits<Type> \
    { \
        typedef ConstructWithMemoryManager<Type> Constructor; \
    };

template <class C>
struct ConstructWithMemoryManagerTraits 
{
    typedef ConstructWithMemoryManager<C>       Constructor;
};

template <class C>
struct ConstructWithNoMemoryManagerTraits
{
    typedef ConstructWithNoMemoryManager<C> Constructor;
};




XALAN_CPP_NAMESPACE_END



#endif  // XALANMEMORYMANAGEMENT_HEADER_GUARD_1357924680

