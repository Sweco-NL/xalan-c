/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999-2000 The Apache Software Foundation.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:  
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xalan" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */
#if !defined(XALANSOURCEATTRIBUTESVECTOR_HEADER_GUARD_1357924680)
#define XALANSOURCEATTRIBUTESVECTOR_HEADER_GUARD_1357924680



#include <XalanSourceTree/XalanSourceTreeDefinitions.hpp>



#include <list>
#include <utility>
#include <vector>



class XalanSourceTreeAttr;



class XALAN_XALANSOURCETREE_EXPORT XalanSourceTreeAttributesVector
{
public:

#if defined(XALAN_NO_NAMESPACES)
	typedef vector<XalanSourceTreeAttr*>	VectorType;
	typedef VectorType::size_type			size_type;
	typedef pair<size_type, VectorType>		ListEntryType;
	typedef list<ListEntryType>				ListType;
#else
	typedef std::vector<XalanSourceTreeAttr*>	VectorType;
	typedef VectorType::size_type				size_type;
	typedef std::pair<size_type, VectorType>	ListEntryType;
	typedef std::list<ListEntryType>			ListType;
#endif

    // Default size for vector allocation.
	enum { eDefaultBlockSize = 500 };

	/**
	 * Constructor.
	 *
	 * @param theBlockSize The block size when allocating.
	 */
	XalanSourceTreeAttributesVector(size_type	theBlockSize = eDefaultBlockSize);

	~XalanSourceTreeAttributesVector();


	/**
	 * Allocate slots for the given number of pointers to XalanSourceTreeAttr
	 * instance and return the address of the slots.
	 *
	 * @param theCount The number of slots to allocate
	 */
	XalanSourceTreeAttr**
	allocate(size_type	theCount);

private:

	// Utility functions...
	XalanSourceTreeAttr**
	createEntry(
			size_type	theBlockSize,
			size_type	theCount);

	ListEntryType*
	findEntry(size_type		theCount);

	// Not implemented...
	XalanSourceTreeAttributesVector(const XalanSourceTreeAttributesVector&	theSource);

	XalanSourceTreeAttributesVector&
	operator=(const XalanSourceTreeAttributesVector&	theSource);

	bool
	operator==(const XalanSourceTreeAttributesVector&	theRHS) const;


	// Data members...
	ListType			m_list;

	const size_type		m_blockSize;

	ListEntryType*		m_lastEntryFound;
};



#endif	// !defined(XALANSOURCEATTRIBUTESVECTOR_HEADER_GUARD_1357924680)