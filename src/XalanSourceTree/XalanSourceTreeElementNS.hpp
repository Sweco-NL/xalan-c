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
#if !defined(XALANSOURCETREEELEMENTNS_HEADER_GUARD_1357924680)
#define XALANSOURCETREEELEMENTNS_HEADER_GUARD_1357924680



#include <XalanSourceTree/XalanSourceTreeDefinitions.hpp>



#include <XalanSourceTree/XalanSourceTreeElement.hpp>



class XALAN_XALANSOURCETREE_EXPORT XalanSourceTreeElementNS : public XalanSourceTreeElement
{
public:

	/**
	 * Constructor.
	 *
	 * @param theTagName The tag name of the element
	 * @param theLocalName The local name of the attribute
	 * @param theNamespaceURI The namespace URI of the attribute
	 * @param thePrefix The namespace prefix of the attribute
	 * @param theOwnerDocument The document that owns the instance
	 * @param theAttributes An array of pointers to the attribute instances for the element
	 * @param theAttributeCount The number of attributes.
	 * @param theParentElement The parent element, if any.
	 * @param thePreviousSibling The previous sibling, if any.
	 * @param theNextSibling The next sibling, if any.
	 * @param theIndex The document-order index of the node.
	 */
	XalanSourceTreeElementNS(
			const XalanDOMString&		theTagName,
			const XalanDOMString&		theLocalName,
			const XalanDOMString&		theNamespaceURI,
			const XalanDOMString&		thePrefix,
			XalanSourceTreeDocument*	theOwnerDocument,
			XalanSourceTreeAttr**		theAttributes,
			AttributesCountType			theAttributeCount,
			XalanSourceTreeElement*		theParentElement = 0,
			XalanNode*					thePreviousSibling = 0,
			XalanNode*					theNextSibling = 0,
			unsigned int				theIndex = 0);

	virtual
	~XalanSourceTreeElementNS();


#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
	virtual XalanNode*
#else
	virtual XalanSourceTreeElementNS*
#endif
	cloneNode(bool deep) const;

	virtual const XalanDOMString&
	getNamespaceURI() const;

	virtual const XalanDOMString&
	getPrefix() const;

	virtual const XalanDOMString&
	getLocalName() const;

protected:

	XalanSourceTreeElementNS(
			const XalanSourceTreeElementNS&		theSource,
			bool								deep);

	XalanSourceTreeElementNS(
			const XalanSourceTreeElement&	theSource,
			bool							deep);
private:

	// Not implemented...
	XalanSourceTreeElementNS&
	operator=(const XalanSourceTreeElementNS&	theSource);

	bool
	operator==(const XalanSourceTreeElementNS&	theRHS) const;


	// Data members...
	const XalanDOMString&	m_localName;

	const XalanDOMString&	m_prefix;

	const XalanDOMString&	m_namespaceURI;
};



#endif	// !defined(XALANSOURCETREEELEMENTNS_HEADER_GUARD_1357924680)