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

#include "XalanSourceTreeHelper.hpp"



#include <cassert>



#include <XalanDOM/XalanDOMException.hpp>



#include "XalanSourceTreeComment.hpp"
#include "XalanSourceTreeDocument.hpp"
#include "XalanSourceTreeElement.hpp"
#include "XalanSourceTreeProcessingInstruction.hpp"
#include "XalanSourceTreeText.hpp"



inline XalanSourceTreeComment*
castToComment(XalanNode*	theNode)
{
#if defined(XALAN_OLD_STYLE_CASTS)
	return (XalanSourceTreeComment*)theNode;
#else
	return static_cast<XalanSourceTreeComment*>(theNode);
#endif
}



inline XalanSourceTreeElement*
castToElement(XalanNode*	theNode)
{
#if defined(XALAN_OLD_STYLE_CASTS)
	return (XalanSourceTreeElement*)theNode;
#else
	return static_cast<XalanSourceTreeElement*>(theNode);
#endif
}



inline XalanSourceTreeProcessingInstruction*
castToProcessingInstruction(XalanNode*	theNode)
{
#if defined(XALAN_OLD_STYLE_CASTS)
	return (XalanSourceTreeProcessingInstruction*)theNode;
#else
	return static_cast<XalanSourceTreeProcessingInstruction*>(theNode);
#endif
}



inline XalanSourceTreeText*
castToText(XalanNode*	theNode)
{
#if defined(XALAN_OLD_STYLE_CASTS)
	return (XalanSourceTreeText*)theNode;
#else
	return static_cast<XalanSourceTreeText*>(theNode);
#endif
}



template<class NodeType>
inline void
doAppendSibling(
			XalanNode*	theSibling,
			NodeType*	theNewSibling)
{
	assert(theSibling != 0);
	assert(theNewSibling != 0);

	XalanNode* const	theLastSibling = XalanSourceTreeHelper::getLastSibling(theSibling);

	switch(theLastSibling->getNodeType())
	{
	case XalanNode::COMMENT_NODE:
		castToComment(theLastSibling)->appendSiblingNode(theNewSibling);
		break;

	case XalanNode::ELEMENT_NODE:
		castToElement(theLastSibling)->appendSiblingNode(theNewSibling);
		break;

	case XalanNode::PROCESSING_INSTRUCTION_NODE:
		castToProcessingInstruction(theLastSibling)->appendSiblingNode(theNewSibling);
		break;

	case XalanNode::TEXT_NODE:
		castToText(theLastSibling)->appendSiblingNode(theNewSibling);
		break;

	default:
		throw XalanDOMException(XalanDOMException::HIERARCHY_REQUEST_ERR);
		break;
	}
}



template<class NodeType>
inline void
doAppendToLastSibling(
			XalanNode*	theLastSibling,
			NodeType*	theNewSibling)
{
	assert(theLastSibling != 0);
	assert(theNewSibling != 0);
	assert(theLastSibling->getNextSibling() == 0);

	switch(theLastSibling->getNodeType())
	{
	case XalanNode::COMMENT_NODE:
		castToComment(theLastSibling)->appendSiblingNode(theNewSibling);
		break;

	case XalanNode::ELEMENT_NODE:
		castToElement(theLastSibling)->appendSiblingNode(theNewSibling);
		break;

	case XalanNode::PROCESSING_INSTRUCTION_NODE:
		castToProcessingInstruction(theLastSibling)->appendSiblingNode(theNewSibling);
		break;

	case XalanNode::TEXT_NODE:
		castToText(theLastSibling)->appendSiblingNode(theNewSibling);
		break;

	default:
		throw XalanDOMException(XalanDOMException::HIERARCHY_REQUEST_ERR);
		break;
	}
}



template <class NodeType1, class NodeType2>
inline void
append(
			NodeType1*		thePreviousSibling,
			XalanNode*&		theNextSiblingSlot,
			NodeType2*		theNewSibling)
{
	if (theNextSiblingSlot == 0)
	{
		theNextSiblingSlot = theNewSibling;

		if (thePreviousSibling != 0)
		{
			theNewSibling->setPreviousSibling(thePreviousSibling);
		}
	}
	else
	{
		doAppendSibling(theNextSiblingSlot, theNewSibling);
	}
}



template <class NodeType>
inline void
append(
			XalanNode*&		theNextSiblingSlot,
			NodeType*		theNewSibling)
{
	if (theNextSiblingSlot == 0)
	{
		theNextSiblingSlot = theNewSibling;
	}
	else
	{
		doAppendSibling(theNextSiblingSlot, theNewSibling);
	}
}



template <class NodeType>
inline void
doAppendSibling(
			NodeType*		thePreviousSibling,
			XalanNode*&		theNextSiblingSlot,
			XalanNode*		theNewSibling)
{
	assert(theNewSibling != 0);
	assert(theNextSiblingSlot == 0 || theNextSiblingSlot->getParentNode() == theNewSibling->getParentNode());

	switch(theNewSibling->getNodeType())
	{
	case XalanNode::COMMENT_NODE:
		append(thePreviousSibling, theNextSiblingSlot, castToComment(theNewSibling));
		break;

	case XalanNode::ELEMENT_NODE:
		append(thePreviousSibling, theNextSiblingSlot, castToElement(theNewSibling));
		break;

	case XalanNode::PROCESSING_INSTRUCTION_NODE:
		append(thePreviousSibling, theNextSiblingSlot, castToProcessingInstruction(theNewSibling));
		break;

	case XalanNode::TEXT_NODE:
		append(thePreviousSibling, theNextSiblingSlot, castToText(theNewSibling));
		break;

	default:
		throw XalanDOMException(XalanDOMException::HIERARCHY_REQUEST_ERR);
		break;
	}
}



void
XalanSourceTreeHelper::appendSibling(
			XalanSourceTreeDocument*	theDocument,
			XalanNode*&					theNextSiblingSlot,
			XalanNode*					theNewSibling)
{
	if (theNewSibling->getOwnerDocument() != theDocument)
	{
		throw XalanDOMException(XalanDOMException::WRONG_DOCUMENT_ERR);
	}
	else
	{
		switch(theNewSibling->getNodeType())
		{
		case XalanNode::COMMENT_NODE:
			append(theNextSiblingSlot, castToComment(theNewSibling));
			break;

		case XalanNode::ELEMENT_NODE:
			append(theNextSiblingSlot, castToElement(theNewSibling));
			break;

		case XalanNode::PROCESSING_INSTRUCTION_NODE:
			append(theNextSiblingSlot, castToProcessingInstruction(theNewSibling));
			break;

		default:
			throw XalanDOMException(XalanDOMException::HIERARCHY_REQUEST_ERR);
			break;
		}
	}
}



void
XalanSourceTreeHelper::appendSibling(
			XalanSourceTreeComment*		theNode,
			XalanNode*&					theNextSiblingSlot,
			XalanNode*					theNewSibling)
{
	doAppendSibling(theNode, theNextSiblingSlot, theNewSibling);
}



void
XalanSourceTreeHelper::appendSibling(
			XalanSourceTreeElement*		theNode,
			XalanNode*&					theNextSiblingSlot,
			XalanNode*					theNewSibling)
{
	doAppendSibling(theNode, theNextSiblingSlot, theNewSibling);
}



void
XalanSourceTreeHelper::appendSibling(
			XalanSourceTreeProcessingInstruction*	theNode,
			XalanNode*&								theNextSiblingSlot,
			XalanNode*								theNewSibling)
{
	doAppendSibling(theNode, theNextSiblingSlot, theNewSibling);
}



void
XalanSourceTreeHelper::appendSibling(
			XalanSourceTreeText*	theNode,
			XalanNode*&				theNextSiblingSlot,
			XalanNode*				theNewSibling)
{
	doAppendSibling(theNode, theNextSiblingSlot, theNewSibling);
}



void
XalanSourceTreeHelper::appendSibling(
			XalanNode*					theLastSibling,
			XalanSourceTreeComment*		theNewLastSibling)
{
	doAppendToLastSibling(theLastSibling, theNewLastSibling);
}



void
XalanSourceTreeHelper::appendSibling(
			XalanNode*					theLastSibling,
			XalanSourceTreeElement*		theNewLastSibling)
{
	doAppendToLastSibling(theLastSibling, theNewLastSibling);
}



void
XalanSourceTreeHelper::appendSibling(
			XalanNode*								theLastSibling,
			XalanSourceTreeProcessingInstruction*	theNewLastSibling)
{
	doAppendToLastSibling(theLastSibling, theNewLastSibling);
}



void
XalanSourceTreeHelper::appendSibling(
			XalanNode*				theLastSibling,
			XalanSourceTreeText*	theNewLastSibling)
{
	doAppendToLastSibling(theLastSibling, theNewLastSibling);
}



XalanNode*
doGetLastSibling(XalanNode*		theNode)
{
	if (theNode == 0)
	{
		return 0;
	}
	else
	{
		XalanNode*	theNextSibling = theNode->getNextSibling();

		while(theNextSibling != 0)
		{
			theNode = theNextSibling;

			theNextSibling = theNode->getNextSibling();
		}

		return theNode;
	}
}



template <class NodeType>
void
doAppendSiblingToChild(
			XalanSourceTreeElement*		theOwnerElement,
			XalanNode*&					theFirstChildSlot,
			NodeType*					theNewSibling)
{
	assert(theOwnerElement != 0);
	assert(theNewSibling != 0);

	if (theNewSibling->getParentElement() != theOwnerElement)
	{
		theNewSibling->setParentElement(theOwnerElement);
	}

	if (theFirstChildSlot == 0)
	{
		append(theFirstChildSlot, theNewSibling);
	}
	else
	{
		XalanNode* const	theLastSibling = doGetLastSibling(theFirstChildSlot);

		doAppendSibling(theLastSibling, theNewSibling);	
	}
}



void
XalanSourceTreeHelper::appendSiblingToChild(
			XalanSourceTreeElement*		theOwnerElement,
			XalanNode*&					theFirstChildSlot,
			XalanSourceTreeComment*		theNewSibling)
{
	doAppendSiblingToChild(theOwnerElement, theFirstChildSlot, theNewSibling);
}



void
XalanSourceTreeHelper::appendSiblingToChild(
			XalanSourceTreeElement*		theOwnerElement,
			XalanNode*&					theFirstChildSlot,
			XalanSourceTreeElement*		theNewSibling)
{
	doAppendSiblingToChild(theOwnerElement, theFirstChildSlot, theNewSibling);
}



void
XalanSourceTreeHelper::appendSiblingToChild(
			XalanSourceTreeElement*					theOwnerElement,
			XalanNode*&								theFirstChildSlot,
			XalanSourceTreeProcessingInstruction*	theNewSibling)
{
	doAppendSiblingToChild(theOwnerElement, theFirstChildSlot, theNewSibling);
}



void
XalanSourceTreeHelper::appendSiblingToChild(
			XalanSourceTreeElement*		theOwnerElement,
			XalanNode*&					theFirstChildSlot,
			XalanSourceTreeText*		theNewSibling)
{
	doAppendSiblingToChild(theOwnerElement, theFirstChildSlot, theNewSibling);
}




XalanNode*
XalanSourceTreeHelper::getLastSibling(XalanNode*	theNode)
{
	return doGetLastSibling(theNode);
}