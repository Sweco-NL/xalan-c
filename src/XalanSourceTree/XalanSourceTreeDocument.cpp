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
 *	  notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *	  notice, this list of conditions and the following disclaimer in
 *	  the documentation and/or other materials provided with the
 *	  distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *	  if any, must include the following acknowledgment:  
 *		 "This product includes software developed by the
 *		  Apache Software Foundation (http://www.apache.org/)."
 *	  Alternately, this acknowledgment may appear in the software itself,
 *	  if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xalan" and "Apache Software Foundation" must
 *	  not be used to endorse or promote products derived from this
 *	  software without prior written permission. For written 
 *	  permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *	  nor may "Apache" appear in their name, without prior written
 *	  permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.	IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
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
#include "XalanSourceTreeDocument.hpp"



#include <sax/AttributeList.hpp>
#include <sax2/Attributes.hpp>



#include <XalanDOM/XalanDOMException.hpp>



#include <PlatformSupport/PrefixResolver.hpp>
#include <PlatformSupport/XalanUnicode.hpp>



#include "XalanSourceTreeHelper.hpp"



static const XalanDOMString		s_emptyString;



XalanSourceTreeDocument::XalanSourceTreeDocument(
			unsigned long	theNumber,
			bool			fPoolAllText,
			unsigned int	theNamesStringPoolBlockSize,
			unsigned int	theNamesStringPoolBucketCount,
			unsigned int	theNamesStringPoolBucketSize,
			unsigned int	theValuesStringPoolBlockSize,
			unsigned int	theValuesStringPoolBucketCount,
			unsigned int	theValuesStringPoolBucketSize) :
	XalanDocument(),
	m_number(theNumber),
	m_firstChild(0),
	m_documentElement(0),
	m_attributeAllocator(200),
	m_attributeNSAllocator(50),
	m_commentAllocator(20),
	m_elementAllocator(200),
	m_elementNSAllocator(200),
	m_piAllocator(25),
	m_textAllocator(200),
	m_textIWSAllocator(400),
	m_namesStringPool(theNamesStringPoolBlockSize, theNamesStringPoolBucketCount, theNamesStringPoolBucketSize),
	m_valuesStringPool(theValuesStringPoolBlockSize, theValuesStringPoolBucketCount, theValuesStringPoolBucketSize),
	m_attributesVector(),
	m_nextIndexValue(2),
	m_poolAllText(fPoolAllText),
	m_elementsByID(),
	m_unparsedEntityURIs(),
	m_nonPooledStrings(),
	m_stringBuffer()
{
}



XalanSourceTreeDocument::~XalanSourceTreeDocument()
{
}



const XalanDOMString&
XalanSourceTreeDocument::getNodeName() const
{
	return s_nameString;
}



const XalanDOMString&
XalanSourceTreeDocument::getNodeValue() const
{
	return s_emptyString;
}



XalanSourceTreeDocument::NodeType
XalanSourceTreeDocument::getNodeType() const
{
	return DOCUMENT_NODE;
}



XalanNode*
XalanSourceTreeDocument::getParentNode() const
{
	return 0;
}



const XalanNodeList*
XalanSourceTreeDocument::getChildNodes() const
{
	throw XalanDOMException(XalanDOMException::NOT_SUPPORTED_ERR);

	// Dummy return value...
	return 0;
}



XalanNode*
XalanSourceTreeDocument::getFirstChild() const
{
	return m_firstChild;
}



XalanNode*
XalanSourceTreeDocument::getLastChild() const
{
	return m_documentElement;
}



XalanNode*
XalanSourceTreeDocument::getPreviousSibling() const
{
	return 0;
}



XalanNode*
XalanSourceTreeDocument::getNextSibling() const
{
	return 0;
}



const XalanNamedNodeMap*
XalanSourceTreeDocument::getAttributes() const
{
	return 0;
}



XalanDocument*
XalanSourceTreeDocument::getOwnerDocument() const
{
	return 0;
}



#if defined(XALAN_NO_COVARIANT_RETURN_TYPE)
XalanNode*
#else
XalanSourceTreeDocument*
#endif
XalanSourceTreeDocument::cloneNode(bool		/* deep */) const
{
	return 0;
}



XalanNode*
XalanSourceTreeDocument::insertBefore(
			XalanNode*	/* newChild */,
			XalanNode*	/* refChild */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanNode*
XalanSourceTreeDocument::replaceChild(
			XalanNode*	/* newChild */,
			XalanNode*	/* oldChild */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanNode*
XalanSourceTreeDocument::removeChild(XalanNode*	 /* oldChild */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanNode*
XalanSourceTreeDocument::appendChild(XalanNode*		/* newChild */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



bool
XalanSourceTreeDocument::hasChildNodes() const
{
	return m_documentElement != 0 ? true : false;
}



void
XalanSourceTreeDocument::setNodeValue(const XalanDOMString&		/* nodeValue */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);
}



void
XalanSourceTreeDocument::normalize()
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);
}


bool
XalanSourceTreeDocument::supports(
			const XalanDOMString&	/* feature */,
			const XalanDOMString&	/* version */) const
{
	return false;
}



const XalanDOMString&
XalanSourceTreeDocument::getNamespaceURI() const
{
	return s_emptyString;
}



const XalanDOMString&
XalanSourceTreeDocument::getPrefix() const
{
	return s_emptyString;
}



const XalanDOMString&
XalanSourceTreeDocument::getLocalName() const
{
	return s_nameString;
}



void
XalanSourceTreeDocument::setPrefix(const XalanDOMString&	/* prefix */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);
}



bool
XalanSourceTreeDocument::isIndexed() const
{
	return true;
}



unsigned long
XalanSourceTreeDocument::getIndex() const
{
	return 1;
}



XalanElement*
XalanSourceTreeDocument::createElement(const XalanDOMString&	/* tagName */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanDocumentFragment*
XalanSourceTreeDocument::createDocumentFragment()
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanText*
XalanSourceTreeDocument::createTextNode(const XalanDOMString&	/* data */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanComment*
XalanSourceTreeDocument::createComment(const XalanDOMString&	/* data */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanCDATASection*
XalanSourceTreeDocument::createCDATASection(const XalanDOMString&	/* data */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanProcessingInstruction*
XalanSourceTreeDocument::createProcessingInstruction(
			const XalanDOMString&	/* target */,
			const XalanDOMString&	/* data */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanAttr*
XalanSourceTreeDocument::createAttribute(const XalanDOMString&	/* name */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanEntityReference*
XalanSourceTreeDocument::createEntityReference(const XalanDOMString&	/* name */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	// Dummy return value...
	return 0;
}



XalanDocumentType*
XalanSourceTreeDocument::getDoctype() const
{
	return 0;
}




XalanDOMImplementation*
XalanSourceTreeDocument::getImplementation() const
{
	return 0;
}



XalanElement*
XalanSourceTreeDocument::getDocumentElement() const
{
	return m_documentElement;
}



XalanNodeList*
XalanSourceTreeDocument::getElementsByTagName(const XalanDOMString&	/* tagname */) const
{
	// Not supported...
	return 0;
}



XalanNode*
XalanSourceTreeDocument::importNode(
			XalanNode*	/* importedNode */,
			bool		/* deep */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	return 0;
}



XalanElement*
XalanSourceTreeDocument::createElementNS(
			const XalanDOMString&	/* namespaceURI */,
			const XalanDOMString&	/* qualifiedName */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	return 0;
}



XalanAttr*
XalanSourceTreeDocument::createAttributeNS(
			const XalanDOMString&	/* namespaceURI */,
			const XalanDOMString&	/* qualifiedName */)
{
	throw XalanDOMException(XalanDOMException::NO_MODIFICATION_ALLOWED_ERR);

	return 0;
}



XalanNodeList*
XalanSourceTreeDocument::getElementsByTagNameNS(
			const XalanDOMString&	/* namespaceURI */,
			const XalanDOMString&	/* localName */) const
{
	// Not supported
	return 0;
}



XalanElement*
XalanSourceTreeDocument::getElementById(const XalanDOMString&	elementId) const
{
	const ElementByIDMapType::const_iterator	i =
		m_elementsByID.find(c_wstr(elementId));

	if (i == m_elementsByID.end())
	{
		return 0;
	}
	else
	{
		return (*i).second;
	}
}



unsigned long
XalanSourceTreeDocument::getNumber() const
{
	return m_number;
}



XalanSourceTreeElement*
XalanSourceTreeDocument::createElementNode(
			const XalanDOMChar*			name,
			const AttributeList&		attrs,
			XalanSourceTreeElement*		theParentElement,
			XalanNode*					thePreviousSibling,
			XalanNode*					theNextSibling)
{
	// We might have typedef'ed this to something smaller than unsigned int.
	const AttributesCountType	theAttributeCount = AttributesCountType(attrs.getLength());

	// assert that we didn't lose anything...
	assert(theAttributeCount == attrs.getLength());

	XalanSourceTreeAttr** const		theAttributeVector =
		theAttributeCount == 0 ? 0 : m_attributesVector.allocate(theAttributeCount);

	XalanSourceTreeElement* const	theNewElement =
			m_elementAllocator.create(
				m_namesStringPool.get(name),
				this,
				theAttributeVector,
				theAttributeCount,
				theParentElement,
				thePreviousSibling,
				theNextSibling,
				m_nextIndexValue++);

	// Now, create the attributes...
	for(AttributesCountType i = 0; i < theAttributeCount; ++i)
	{
		const XalanDOMChar* const	theName =
			attrs.getName(i);
		assert(theName != 0);

		const XalanDOMChar* const	theValue =
			attrs.getValue(i);
		assert(theValue != 0);

		theAttributeVector[i] =
			m_attributeAllocator.create(
				m_namesStringPool.get(theName),
				m_valuesStringPool.get(theValue),
				theNewElement,
				m_nextIndexValue++);
	}

	return theNewElement;
}



XalanSourceTreeElement*
XalanSourceTreeDocument::createElementNode(
			const XalanDOMChar*			tagName,
			const AttributeList&		attrs,
			const PrefixResolver&		thePrefixResolver,
			XalanSourceTreeElement*		theParentElement,
			XalanNode*					thePreviousSibling,
			XalanNode*					theNextSibling)
{
	// We might have typedef'ed this to something smaller than unsigned int.
	const AttributesCountType	theAttributeCount = AttributesCountType(attrs.getLength());

	// assert that we didn't lose anything...
	assert(theAttributeCount == attrs.getLength());

	XalanSourceTreeAttr** const		theAttributeVector =
		theAttributeCount == 0 ? 0 : m_attributesVector.allocate(theAttributeCount);

	XalanSourceTreeElement* const	theNewElement =
		createElement(
			tagName,
			theAttributeVector,
			theAttributeCount,
			theParentElement,
			thePreviousSibling,
			theNextSibling,
			thePrefixResolver);
	assert(theNewElement != 0);

	// Now, create the attributes...
	for(AttributesCountType i = 0; i < theAttributeCount; ++i)
	{
		const XalanDOMChar* const	theName =
			attrs.getName(i);
		assert(theName != 0);

		const XalanDOMChar* const	theValue =
			attrs.getValue(i);
		assert(theValue != 0);

		theAttributeVector[i] =
			createAttribute(
				theName,
				theValue,
				theNewElement,
				thePrefixResolver);

		assert(theAttributeVector[i] != 0);
	}

	return theNewElement;
}



inline const XalanDOMString&
getElementNodePrefix(
			const XalanDOMChar*		qname,
			XalanDOMStringPool*		theStringPool,
			unsigned int			theLength,			
			unsigned int			theColonIndex)
{
	if(theColonIndex == theLength)
	{
		return  theStringPool->get(XalanDOMString()); 
	}
	else
	{
		return  theStringPool->get(qname, theColonIndex);
	}
	

}



XalanSourceTreeElement*
XalanSourceTreeDocument::createElementNode(
			const XalanDOMChar*			uri,
			const XalanDOMChar*			localname,
			const XalanDOMChar*			qname,
			const Attributes&			attrs,
			XalanSourceTreeElement*		theParentElement,
			XalanNode*					thePreviousSibling,
			XalanNode*					theNextSibling)
{

	// We might have typedef'ed this to something smaller than unsigned int.
	const AttributesCountType	theAttributeCount = AttributesCountType(attrs.getLength());

	// assert that we didn't lose anything...
	assert(theAttributeCount == attrs.getLength());

	XalanSourceTreeAttr** const		theAttributeVector =
		theAttributeCount == 0 ? 0 : m_attributesVector.allocate(theAttributeCount);

	const unsigned int	theColonIndex = indexOf(qname, XalanUnicode::charColon);
	const unsigned int	theLength = length(qname);

	XalanSourceTreeElement* const	theNewElement =
		m_elementNSAllocator.create(
				m_namesStringPool.get(qname),
				m_namesStringPool.get(localname),
				m_namesStringPool.get(uri),
				// This is the prefix...
				getElementNodePrefix(qname, &m_namesStringPool, theLength, theColonIndex),
				this,
				theAttributeVector,
				theAttributeCount,
				theParentElement,
				thePreviousSibling,
				theNextSibling,
				m_nextIndexValue++);

	if (theAttributeCount != 0)
	{
		createAttributes(attrs, theAttributeVector, theAttributeCount, theNewElement);
	}

	return theNewElement;
}



XalanSourceTreeElement*
XalanSourceTreeDocument::createElementNode(
			const XalanDOMChar*			name,
			const Attributes&			attrs,
			XalanSourceTreeElement*		theParentElement,
			XalanNode*					thePreviousSibling,
			XalanNode*					theNextSibling)
{
	// We might have typedef'ed this to something smaller than unsigned int.
	const AttributesCountType	theAttributeCount = AttributesCountType(attrs.getLength());

	// assert that we didn't lose anything...
	assert(theAttributeCount == attrs.getLength());

	XalanSourceTreeAttr** const		theAttributeVector =
		theAttributeCount == 0 ? 0 : m_attributesVector.allocate(theAttributeCount);

	assert(indexOf(name, XalanUnicode::charColon) == length(name));

	XalanSourceTreeElement* const	theNewElement =
		m_elementAllocator.create(
				m_namesStringPool.get(name),
				this,
				theAttributeVector,
				theAttributeCount,
				theParentElement,
				thePreviousSibling,
				theNextSibling,
				m_nextIndexValue++);

	if (theAttributeCount != 0)
	{
		createAttributes(attrs, theAttributeVector, theAttributeCount, theNewElement);
	}

	return theNewElement;
}



XalanSourceTreeComment*
XalanSourceTreeDocument::createCommentNode(
			const XalanDOMChar*			data,
			unsigned int				length,
			XalanSourceTreeElement*		theParentElement,
			XalanNode*					thePreviousSibling,
			XalanNode*					theNextSibling)
{
	return m_commentAllocator.create(
				m_valuesStringPool.get(data, length),
				this,
				theParentElement,
				thePreviousSibling,
				theNextSibling,
				m_nextIndexValue++);
}



XalanSourceTreeProcessingInstruction*
XalanSourceTreeDocument::createProcessingInstructionNode(
			const XalanDOMChar*			target,
			const XalanDOMChar*			data,
			XalanSourceTreeElement*		theParentElement,
			XalanNode*					thePreviousSibling,
			XalanNode*					theNextSibling)
{
	assert(target != 0);
	assert(data != 0);

	return m_piAllocator.create(
				m_namesStringPool.get(target),
				m_valuesStringPool.get(data),
				this,
				theParentElement,
				thePreviousSibling,
				theNextSibling,
				m_nextIndexValue++);
}



inline const XalanDOMString&
XalanSourceTreeDocument::getTextNodeString(
			const XalanDOMChar*		chars,
			unsigned int			length)
{
	if (m_poolAllText == true)
	{
		return m_valuesStringPool.get(chars, length);
	}
	else
	{
		const StringCollectionType::iterator	theIterator =
				m_nonPooledStrings.insert(m_nonPooledStrings.end(), XalanDOMString());

		XalanDOMString&		theString = *theIterator;

		assign(theString, chars, length);

		assert(length == ::length(theString));

		return theString;
	}
}



const XalanDOMString*
XalanSourceTreeDocument::getNamespaceForPrefix(
			const XalanDOMChar*		theName,
			const PrefixResolver&	thePrefixResolver,
			XalanDOMString&			thePrefix,
			bool					fUseDefault)
{
	const unsigned int	theLength = length(theName);
	const unsigned int	theColonIndex = indexOf(theName, XalanUnicode::charColon);

	if (theColonIndex != theLength)
	{
		// Get the prefix from theName...
		assign(thePrefix, theName, theColonIndex);
		assert(length(thePrefix) != 0);

		return thePrefixResolver.getNamespaceForPrefix(thePrefix);
	}
	else
	{
		clear(thePrefix);

		if (fUseDefault == false)
		{
			return 0;
		}
		else
		{
			return thePrefixResolver.getNamespaceForPrefix(s_emptyString);
		}
	}
}



XalanSourceTreeText*
XalanSourceTreeDocument::createTextNode(
			const XalanDOMChar*			chars,
			unsigned int				length,
			XalanSourceTreeElement*		theParentElement,
			XalanNode*					thePreviousSibling,
			XalanNode*					theNextSibling)
{
	assert(chars != 0);

	if (isXMLWhitespace(chars, 0, length) == true)
	{
		const XalanDOMString&	theString = m_valuesStringPool.get(chars, length);

		return m_textIWSAllocator.create(
				theString,
				theParentElement,
				thePreviousSibling,
				theNextSibling,
				m_nextIndexValue++);
	}
	else
	{
		return m_textAllocator.create(
				getTextNodeString(chars, length),
				theParentElement,
				thePreviousSibling,
				theNextSibling,
				m_nextIndexValue++);
	}
}



XalanSourceTreeText*
XalanSourceTreeDocument::createTextIWSNode(
			const XalanDOMChar*			chars,
			unsigned int				length,
			XalanSourceTreeElement*		theParentElement,
			XalanNode*					thePreviousSibling,
			XalanNode*					theNextSibling)
{
	assert(chars != 0);

	return m_textIWSAllocator.create(
			m_valuesStringPool.get(chars, length),
			theParentElement,
			thePreviousSibling,
			theNextSibling,
			m_nextIndexValue++);
}



void
XalanSourceTreeDocument::unparsedEntityDeclaration(
			const XalanDOMChar*		name,
			const XalanDOMChar*		publicId,
			const XalanDOMChar*		systemId,
			const XalanDOMChar*		notationName)
{
	m_unparsedEntityURIs[XalanDOMString(name)] = XalanDOMString(systemId);
}



const XalanDOMString&
XalanSourceTreeDocument::getUnparsedEntityURI(const XalanDOMString&		theName) const
{
	const UnparsedEntityURIMapType::const_iterator	i =
		m_unparsedEntityURIs.find(theName);

	if (i != m_unparsedEntityURIs.end())
	{
		return (*i).second;
	}
	else
	{
		return s_emptyString;
	}
}



XalanSourceTreeAttr*
XalanSourceTreeDocument::createAttribute(
			const XalanDOMChar*			theName,
			const XalanDOMChar*			theValue,
			XalanSourceTreeElement*		theOwnerElement,
			const PrefixResolver&		thePrefixResolver)
{
	// Get the namespace for the theName.  Since attributes do not use
	// the default namespace, make sure we don't get it...
	const XalanDOMString* const		theNamespace =
		getNamespaceForPrefix(
				theName,
				thePrefixResolver,
				m_stringBuffer,
				false);

	assert(theNamespace == 0 && length(m_stringBuffer) == 0 ||
		   theNamespace != 0 && length(m_stringBuffer) != 0);

	if (theNamespace == 0 || length(*theNamespace) == 0)
	{
		return m_attributeAllocator.create(
				m_namesStringPool.get(theName),
				m_valuesStringPool.get(theValue),
				theOwnerElement,
				m_nextIndexValue++);
	}
	else
	{
		// There must be a prefix, so we don't have to check to see if
		// we got one...

		// The constructor parameters for AttrNS are:
		//
		// name
		// local name
		// namespace URI
		// prefix
		// value
		// owner element
		// index
		//
		return m_attributeNSAllocator.create(
				m_namesStringPool.get(theName),
				m_namesStringPool.get(theName + length(m_stringBuffer) + 1),
				m_namesStringPool.get(*theNamespace),
				// This is the prefix...
				m_namesStringPool.get(m_stringBuffer),
				m_valuesStringPool.get(theValue),
				theOwnerElement,
				m_nextIndexValue++);
	}
}



XalanSourceTreeElement*
XalanSourceTreeDocument::createElement(
			const XalanDOMChar*			theTagName,
			XalanSourceTreeAttr**		theAttributeVector,
			AttributesCountType			theAttributeCount,
			XalanSourceTreeElement*		theParentElement,
			XalanNode*					thePreviousSibling,
			XalanNode*					theNextSibling,
			const PrefixResolver&		thePrefixResolver)
{
	const XalanDOMString* const		theNamespace =
		getNamespaceForPrefix(
				theTagName,
				thePrefixResolver,
				m_stringBuffer,
				true);

	if (theNamespace == 0 || length(*theNamespace) == 0)
	{
		// the prefix was returned by getNamespaceForPrefix()...
		assert(length(m_stringBuffer) == 0);

		return m_elementAllocator.create(
				m_namesStringPool.get(theTagName),
				this,
				theAttributeVector,
				theAttributeCount,
				theParentElement,
				thePreviousSibling,
				theNextSibling,
				m_nextIndexValue++);
	}
	else
	{
		// We need figure out if there's a prefix on theTagName.  If not,
		// the local name is the same as the tag name.  Otherwise, we need
		// to remove the prefix and the ':' that separates them.  If
		// m_stringBuffer is of length 0, there's no prefix.
		const unsigned int			thePrefixLength = length(m_stringBuffer);

		const XalanDOMChar* const	theLocalName =
			thePrefixLength == 0 ? theTagName : theTagName + thePrefixLength + 1;

		// The constructor parameters for ElementNS are:
		//
		// tag name
		// local name
		// namespace URI
		// prefix
		// owner document
		// attributes
		// attribute count
		// parent element
		// previous sibling
		// next sibling
		// index
		//
		return m_elementNSAllocator.create(
				m_namesStringPool.get(theTagName),
				m_namesStringPool.get(theLocalName),
				m_namesStringPool.get(*theNamespace),
				m_namesStringPool.get(m_stringBuffer),
				this,
				theAttributeVector,
				theAttributeCount,
				theParentElement,
				thePreviousSibling,
				theNextSibling,
				m_nextIndexValue++);
	}
}



void
XalanSourceTreeDocument::createAttributes(
			const Attributes&			theAttributes,
			XalanSourceTreeAttr**		theAttributeVector,
			AttributesCountType			theAttributeCount,
			XalanSourceTreeElement*		theOwnerElement)
{
	// Now, create the attributes...
	for(AttributesCountType i = 0; i < theAttributeCount; ++i)
	{
		const XalanDOMChar* const	theQName =
			theAttributes.getQName(i);
		assert(theQName != 0);

		const XalanDOMChar* const	theValue =
			theAttributes.getValue(i);
		assert(theValue != 0);

		const XalanDOMChar* const	theURI =
			theAttributes.getURI(i);

		if (length(theURI) == 0)
		{
			theAttributeVector[i] =
				m_attributeAllocator.create(
					m_namesStringPool.get(theQName),
					m_valuesStringPool.get(theValue),
					theOwnerElement,
					m_nextIndexValue++);
		}
		else
		{
			const XalanDOMChar* const	theLocalName =
				theAttributes.getLocalName(i);
			assert(theLocalName != 0);

			const unsigned int	theColonIndex = indexOf(theQName, XalanUnicode::charColon);
			assert(theColonIndex != length(theQName));

			// The constructor parameters for AttrNS are:
			//
			// name
			// local name
			// namespace URI
			// prefix
			// value
			// owner element
			// index
			//
			theAttributeVector[i] =
				m_attributeNSAllocator.create(
						m_namesStringPool.get(theQName),
						m_namesStringPool.get(theLocalName),
						m_namesStringPool.get(theURI),
						// This is the prefix...
						m_namesStringPool.get(theQName, theColonIndex),
						m_valuesStringPool.get(theValue),
						theOwnerElement,
						m_nextIndexValue++);
		}

		// OK, now let's see if we have an ID attribute...
		const XalanDOMChar*		theType =
			theAttributes.getType(i);

		// Look for an attribute that was declared as type ID in the DTD.
		// Note that we can just save a pointer to the attribute's XalanDOMString
		// data, since the attribute is guaranteed to exist for as long as the
		// document does.
		if (*theType == XalanUnicode::charLetter_I &&
			*++theType == XalanUnicode::charLetter_D &&
			*++theType == 0)
		{
			// The XPath says that if there are duplicate IDs, the first node is
			// always returned, so use insert(), rather than []
			m_elementsByID.insert(
				ElementByIDMapType::value_type(
					c_wstr(theAttributeVector[i]->getValue()),
					theOwnerElement));
		}
	}
}



void
XalanSourceTreeDocument::appendChildNode(XalanSourceTreeComment*	theChild)
{
	XalanSourceTreeHelper::appendSibling(this, m_firstChild, theChild);
}



void
XalanSourceTreeDocument::appendChildNode(XalanSourceTreeElement*	theChild)
{
	if (m_documentElement != 0)
	{
		throw XalanDOMException(XalanDOMException::HIERARCHY_REQUEST_ERR);
	}
	else
	{
		m_documentElement = theChild;

		XalanSourceTreeHelper::appendSibling(this, m_firstChild, theChild);
	}
}



void
XalanSourceTreeDocument::appendChildNode(XalanSourceTreeProcessingInstruction*	theChild)
{
	XalanSourceTreeHelper::appendSibling(this, m_firstChild, theChild);
}



static XalanDOMString	s_nameString;



const XalanDOMString&	XalanSourceTreeDocument::s_nameString = ::s_nameString;



void
XalanSourceTreeDocument::initialize()
{
	::s_nameString = XALAN_STATIC_UCODE_STRING("#document");
}



void
XalanSourceTreeDocument::terminate()
{
	releaseMemory(::s_nameString);
}